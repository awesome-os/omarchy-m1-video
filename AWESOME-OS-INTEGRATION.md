# Awesome-OS Integration — `omarchy-m1-video`

This repository is the **Awesome-OS** upstream mirror and integration package of [`chriskearney/omarchy-m1-video`](https://github.com/chriskearney/omarchy-m1-video), providing Apple Silicon (M1 / Asahi Linux) hardware video decoding (H.264, HEVC, and VP9 via Apple AVD) for Omarchy desktops.

All upstream source files, kernel patches, `libva` packaging, tests, and the original **GNU General Public License v2.0** (`LICENSE`) are preserved intact.

## Awesome-OS Ecosystem Links

| Repository | Role |
| :--- | :--- |
| [`awesome-os/t2desktop-omarchy`](https://github.com/awesome-os/t2desktop-omarchy) | Omarchy desktop distribution and hardware enablement layer for Apple hardware in Awesome-OS |
| [`awesome-os/t2linux`](https://github.com/awesome-os/t2linux) | Apple Mac Linux kernel and hardware enablement stack (T2 & Apple Silicon sibling track) |

## B8G ABI v3 Zero-Copy Bridge

- [`include/b8g_m1_video_abi.h`](include/b8g_m1_video_abi.h) provides the C11 `B8G_ABI_MAGIC_V3` (`0x33564742`) and 64-byte aligned `B8G_ARENA_V1` zero-copy H.264/HEVC/VP9 AVD/VA-API frame ring descriptor (`b8g_arena_header_v1_t`, `b8g_m1_video_frame_slot_v1_t`, `b8g_m1_video_ring_v1_t`).

## Integration Notes

- **Target Hardware:** Apple Silicon Macs running `linux-asahi` and Omarchy.
- **License:** GPL-2.0 (see [`LICENSE`](LICENSE)).
- **Upstream Source:** <https://github.com/chriskearney/omarchy-m1-video>
- **CI Validation:** [`.github/workflows/awesome-os-ci.yml`](.github/workflows/awesome-os-ci.yml) compile-checks `include/b8g_m1_video_abi.h` (`gcc -std=c11 -Wall -Wextra -fsyntax-only`) and syntax-checks all `.sh` and `.py` scripts on `ubuntu-latest`.
