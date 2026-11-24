#ifndef B8G_M1_VIDEO_ABI_H
#define B8G_M1_VIDEO_ABI_H

#include <stdalign.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Canonical Awesome-OS B8G ABI v3 magic ("BGV3" in little-endian: 0x33564742).
 */
#define B8G_ABI_MAGIC_V3 UINT32_C(0x33564742)
#define B8G_ARENA_VERSION_V1 UINT32_C(1)
#define B8G_ARENA_ALIGN UINT32_C(64)

/**
 * Hardware codec identifiers for Apple Silicon AVD / VA-API zero-copy decode.
 */
typedef enum b8g_m1_codec_id {
    B8G_M1_CODEC_UNKNOWN = 0,
    B8G_M1_CODEC_H264    = 1,
    B8G_M1_CODEC_HEVC    = 2,
    B8G_M1_CODEC_VP9     = 3
} b8g_m1_codec_id_t;

/**
 * 64-byte aligned B8G_ARENA_V1 header for zero-copy shared-memory arenas.
 */
typedef struct b8g_arena_header_v1 {
    alignas(64) uint32_t magic;/* Must equal B8G_ABI_MAGIC_V3 (0x33564742) */
    uint32_t version;          /* Must equal B8G_ARENA_VERSION_V1 (1)      */
    uint32_t flags;            /* Arena capability flags                   */
    uint32_t reserved0;        /* Zero-initialized padding                 */
    uint64_t arena_bytes;      /* Total mapped arena byte length           */
    uint64_t generation;       /* Monotonic epoch / checkpoint counter     */
    uint64_t write_index;      /* Producer cursor (monotonic frame index)  */
    uint64_t read_index;       /* Consumer cursor (monotonic frame index)  */
    uint64_t ring_offset;      /* Byte offset to first frame slot          */
    uint32_t ring_capacity;    /* Power-of-two number of frame ring slots  */
    uint32_t slot_stride;      /* Byte stride per frame slot (64B aligned) */
} b8g_arena_header_v1_t;

/**
 * 64-byte aligned zero-copy H.264/HEVC/VP9 AVD/VA-API frame ring slot descriptor.
 */
typedef struct b8g_m1_video_frame_slot_v1 {
    alignas(64) uint64_t pts_ns;/* Presentation timestamp in nanoseconds   */
    uint64_t dmabuf_offset;    /* Offset within DMA-BUF or B8G_ARENA_V1    */
    int32_t  dmabuf_fd;        /* Exported PRIME DMA-BUF fd (-1 if inline) */
    uint32_t va_surface_id;    /* Underlying libva VASurfaceID             */
    uint32_t codec_id;         /* b8g_m1_codec_id_t                        */
    uint32_t drm_fourcc;       /* DRM fourcc (e.g. NV12 / P010)            */
    uint32_t width;            /* Decoded frame width in pixels            */
    uint32_t height;           /* Decoded frame height in pixels           */
    uint32_t stride_y;         /* Luma plane byte stride                   */
    uint32_t stride_uv;        /* Chroma plane byte stride                 */
    uint32_t bit_depth;        /* Luma bit depth (8 or 10)                 */
    uint32_t frame_flags;      /* Keyframe / color-range / error bitmask   */
    uint64_t avd_job_seq;      /* Kernel AVD decode job sequence number    */
} b8g_m1_video_frame_slot_v1_t;

/**
 * Combined 64-byte aligned AVD/VA-API zero-copy frame ring descriptor.
 */
typedef struct b8g_m1_video_ring_v1 {
    alignas(64) b8g_arena_header_v1_t header;
    uint32_t active_codec;     /* b8g_m1_codec_id_t                        */
    uint32_t max_width;        /* Configured maximum coded width           */
    uint32_t max_height;       /* Configured maximum coded height          */
    uint32_t avd_device_index; /* /dev/videoN index                        */
    uint64_t dropped_frames;   /* Count of backpressure drops              */
    uint64_t decode_errors;    /* Count of AVD/VA-API decode errors        */
    uint8_t  reserved_pad[32]; /* Pad descriptor to exact 128-byte size    */
} b8g_m1_video_ring_v1_t;

_Static_assert(alignof(b8g_arena_header_v1_t) == 64,
               "b8g_arena_header_v1_t must be 64-byte aligned");
_Static_assert(sizeof(b8g_arena_header_v1_t) == 64,
               "b8g_arena_header_v1_t must be 64 bytes");
_Static_assert(alignof(b8g_m1_video_frame_slot_v1_t) == 64,
               "b8g_m1_video_frame_slot_v1_t must be 64-byte aligned");
_Static_assert(sizeof(b8g_m1_video_frame_slot_v1_t) == 64,
               "b8g_m1_video_frame_slot_v1_t must be 64 bytes");
_Static_assert(alignof(b8g_m1_video_ring_v1_t) == 64,
               "b8g_m1_video_ring_v1_t must be 64-byte aligned");
_Static_assert(sizeof(b8g_m1_video_ring_v1_t) == 128,
               "b8g_m1_video_ring_v1_t must be 128 bytes");

#ifdef __cplusplus
}
#endif

#endif /* B8G_M1_VIDEO_ABI_H */
