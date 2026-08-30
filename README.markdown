# Tasmota Builder

CI pipeline to build custom Tasmota images

# Jobs

- `build-tasmota-builder` builds the image with PlatformIO.
- `build-jo` builds the image used to post release notifications.
- `build-release` builds the ESP8266 `tasmota.bin` and `tasmota-minimal.bin` on new Tasmota releases and publishes them to Backblaze B2 and the GitHub release.
- `build-tasmota32-nousa8t` builds a customized ESP32 firmware for the Nous A8T (`tasmota32-nousa8t.bin`) and publishes it to Backblaze B2.

# Customization (`user_config_override.h`)

The firmware for the Nous A8T is customized with a `user_config_override.h` in the repository root. It is not part of the builder image; the `build-tasmota32-nousa8t` job fetches it from the repository and copies it into the extracted Tasmota source tree right before running the build, so a push to `user_config_override.h` alone triggers a new firmware build. The file lists all features and sensors from the [BUILDS documentation](https://tasmota.github.io/docs/BUILDS) and enables only those that are also enabled by default in the ESP8266 build (the first entry of the `t` column), plus `USE_PROMETHEUS` for metrics. Everything that is enabled by default only in the ESP32 build is disabled, which roughly halves the flash usage of the stock `tasmota32.bin`.

# Uploading

Upload `tasmota32-nousa8t.bin` to the device via **Firmware Upgrade**. Unlike the ESP8266, the ESP32 does not support uploading gzipped images, so only the unpacked `.bin` is published; a `.bin.gz` upload fails with `Upload Failed / Not enough space`.

# Release

```command
$ git tag -a v1.0.0-pre1 -m "Preparing release v1.0.0"
$ git push --follow-tags
```

The pipeline will build a new task image.
