FROM python:3
ARG PLATFORM_IO_VERSION
RUN pip install --upgrade pip
RUN pip install -U PlatformIO==${PLATFORM_IO_VERSION}
# Customization of Tasmota for the Nous A8T (ESP32): lists all features and
# sensors from the BUILDS docs, enabling only the ones also enabled for the
# ESP8266 by default, plus USE_PROMETHEUS. Copied into the extracted Tasmota
# source tree by the build-tasmota32-nousa8t job.
COPY user_config_override.h /user_config_override.h
