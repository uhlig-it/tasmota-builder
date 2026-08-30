# Tasmota Builder

CI pipeline to build custom Tasmota images

# Jobs

- `build-tasmota-builder` builds the image with PlatformIO.
- `build-jo` builds the image used to post release notifications.
- `build-release` builds the ESP8266 `tasmota.bin` and `tasmota-minimal.bin` on new Tasmota releases and publishes them to Backblaze B2 and the GitHub release.
- `build-tasmota32-nousa8t` builds a customized ESP32 firmware for the Nous A8T (`tasmota32-nousa8t.bin.gz`) and publishes it to Backblaze B2.

# Customization (`images/tasmota-builder/user_config_override.h`)

The firmware for the Nous A8T is customized with a `user_config_override.h` that is baked into the builder image and copied into the extracted Tasmota source tree by the `build-tasmota32-nousa8t` job. It lists all features and sensors from the [BUILDS documentation](https://tasmota.github.io/docs/BUILDS) and enables only those that are also enabled by default in the ESP8266 build (the first entry of the `t` column), plus `USE_PROMETHEUS` for metrics. Everything that is enabled by default only in the ESP32 build is disabled, which roughly halves the flash usage of the stock `tasmota32.bin`.

# Release

```command
$ git tag -a v1.0.0-pre1 -m "Preparing release v1.0.0"
$ git push --follow-tags
```

The pipeline will build a new task image.