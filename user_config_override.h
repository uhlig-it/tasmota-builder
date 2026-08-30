/*
  user_config_override.h - Customization of Tasmota for the Nous A8T (ESP32)

  Copied into the Tasmota source tree as "tasmota/user_config_override.h" by the
  build-tasmota32-nousa8t pipeline job before running
  `pio run --environment tasmota32` (USE_CONFIG_OVERRIDE is enabled for all envs).

  Goal: a Tasmota ESP32 build that is as small as possible for a Nous A8T plug
  (relay, button, LED and BL0937 energy monitor) while keeping the same feature
  set as the stock ESP8266 "tasmota" build, plus Prometheus metrics.

  Rule: this file lists ALL features and sensors from the BUILDS documentation
  (https://tasmota.github.io/docs/BUILDS). Of those, only the ones that are ALSO
  enabled by default in the ESP8266 build are kept enabled ("t" column of the
  BUILDS table, first entry). Everything that is only enabled in the ESP32 build
  by default (second entry), or in any other variant, is disabled.

  How: features are enabled with `#ifndef / #define / #endif` (best practice from
  the Compile-your-build docs) and disabled with `#ifdef / #undef / #endif`.
  The rules engine parts USE_EXPRESSION and SUPPORT_IF_STATEMENT no longer exist
  as compile-time options since Tasmota v15 (always enabled with USE_RULES).

  Important include order: this file is included at the end of my_user_config.h.
  The feature set of the stock ESP32 build is applied LATER by
  tasmota_configurations_ESP32.h (included from tasmota_globals.h), guarded by
  FIRMWARE_TASMOTA32. Undefining FIRMWARE_TASMOTA32 below prevents that section
  from re-enabling everything we just stripped; the upstream safeboot build uses
  the same mechanism.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

// force the compiler to show a warning to confirm that this file is included
#warning **** user_config_override.h: Using Settings from this File ****

// Do not apply the stock tasmota32 feature set (KNX, Matter, Ethernet, DALI,
// Shelly Pro, most I2C/CO2/particle sensors, ...) after this file has run.
#ifdef FIRMWARE_TASMOTA32
#undef FIRMWARE_TASMOTA32
#endif

// Build identity shown between brackets in the Information page / INFO MQTT
#undef CODE_IMAGE_STR
#define CODE_IMAGE_STR "nousa8t"

// Do not point the web UI "Upgrade" button at the stock tasmota32 build, it
// would silently replace this custom build. Upload new builds manually or set
// `OtaUrl` at runtime (note: HTTPS OTA requires re-enabling USE_MQTT_TLS).
#undef OTA_URL
#define OTA_URL "http://192.168.10.164:3333/tasmota32-nousa8t.bin"

/*********************************************************************************************\
 * All features and sensors from the BUILDS documentation
 * Legend: [l, t, k, s, i, d] columns, "t" = tasmota (ESP8266 / ESP32)
\*********************************************************************************************/

// -- General features -----------------------------

// MY_LANGUAGE en_GB: leave default (en_GB is enabled by default in every variant)

// USE_IMPROV              [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
//   IMPROV serial protocol as used by esp-web-tools
#ifndef USE_IMPROV
#define USE_IMPROV
#endif

// USE_UFILESYS            [-, - / x, -, -, -, -]  -> would be disabled, but is
//   unconditionally re-enabled for ESP32 by the post-config in
//   tasmota_configurations.h (file system is not available on the 1M ESP8266
//   which the table describes). No way to disable it from this file; deviation.
//   On-device file system (LittleFS) for scripts, fonts and user files
#ifdef USE_UFILESYS
#undef USE_UFILESYS
#endif

// USE_ARDUINO_OTA         [-, - / -, -, -, -, -]  -> disable
//   Arduino OTA with ESP8266
#ifdef USE_ARDUINO_OTA
#undef USE_ARDUINO_OTA
#endif

// USE_DOMOTICZ            [-, x / x, x, x, x, -]  -> keep (ESP8266 default)
//   Integration with the Domoticz home automation system
#ifndef USE_DOMOTICZ
#undef USE_DOMOTICZ
#endif

// USE_HOME_ASSISTANT      [-, - / -, -, -, -, -]  -> disable
//   Home Assistant MQTT discovery
#ifdef USE_HOME_ASSISTANT
#undef USE_HOME_ASSISTANT
#endif

// USE_TASMOTA_DISCOVERY   [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
//   Tasmota Discovery support
#ifndef USE_TASMOTA_DISCOVERY
#define USE_TASMOTA_DISCOVERY
#endif

// USE_MQTT_TLS            [-, - / x, -, -, -, -]  -> disable (for ESP8266 too;
//   the BUILDS footnote "enabled by default in every ESP32 variant" is exactly
//   what this build overrides, saving the mbedTLS code)
//   TLS for MQTT connection
#ifdef USE_MQTT_TLS
#undef USE_MQTT_TLS
#endif

// USE_MQTT_CLIENT_CERT    [-, - / -, -, -, -, -]  -> disable
//   MQTT with custom client certificate - requires a private key
#ifdef USE_MQTT_CLIENT_CERT
#undef USE_MQTT_CLIENT_CERT
#endif

// USE_MQTT_AWS_IOT        [-, - / -, -, -, -, -]  -> disable
//   MQTT to AWS IoT Core (requires client certificate, no user/password)
#ifdef USE_MQTT_AWS_IOT
#undef USE_MQTT_AWS_IOT
#endif

// USE_4K_RSA              [-, - / -, -, -, -, -]  -> disable; only affects TLS
//   certificate size and is passed via platformio build flags. No effect here
//   because TLS is disabled above.
//   TLS support for 4096-bit RSA certificates (instead of 2048-bit)
#ifdef USE_4K_RSA
#undef USE_4K_RSA
#endif

// USE_TELEGRAM            [-, - / -, -, -, -, -]  -> disable
//   Telegram messenger (commands and notifications)
#ifdef USE_TELEGRAM
#undef USE_TELEGRAM
#endif

// USE_KNX                 [-, - / x, x, -, -, -]  -> disable (ESP32 default)
//   KNX IP protocol (building automation bus)
#ifdef USE_KNX
#undef USE_KNX
#endif

// USE_TELNET              [-, - / -, -, -, -, -]  -> disable
//   Telnet console access
#ifdef USE_TELNET
#undef USE_TELNET
#endif

// USE_XYZMODEM            [-, - / -, -, -, -, -]  -> disable
//   XModem over serial and telnet
#ifdef USE_XYZMODEM
#undef USE_XYZMODEM
#endif

// USE_WEBSERVER           [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
//   Web server and Wi-Fi Manager
#ifndef USE_WEBSERVER
#define USE_WEBSERVER
#endif

// USE_WEBSEND_RESPONSE    [-, - / -, -, -, -, -]  -> disable
//   Command WebSend response message
#ifdef USE_WEBSEND_RESPONSE
#undef USE_WEBSEND_RESPONSE
#endif

// USE_EMULATION_HUE       [x, x / x, -, x, -, -]  -> keep (ESP8266 default)
//   Hue Bridge emulation for Alexa
#ifndef USE_EMULATION_HUE
#undef USE_EMULATION_HUE
#endif

// USE_EMULATION_WEMO      [x, x / x, -, x, -, -]  -> keep (ESP8266 default)
//   Belkin WeMo emulation for Alexa
#ifndef USE_EMULATION_WEMO
#undef USE_EMULATION_WEMO
#endif

// USE_DISCOVERY           [-, - / -, -, -, -, -]  -> not enabled by default and
//   derived from emulation/OTA; no action needed
//   mDNS discovery (for the emulation bridges and OTA)

// WEBSERVER_ADVERTISE     [-, x / -, x, -, -, x]  -> keep (ESP8266 default;
//   enables <Hostname>.local in the webserver)
//   Provide access to webserver by name <Hostname>.local/
#ifndef WEBSERVER_ADVERTISE
#define WEBSERVER_ADVERTISE
#endif

// MQTT_HOST_DISCOVERY     [-, - / -, -, -, -, -]  -> disable
//   Automatically find the MQTT broker (overrides MQTT_HOST if found)
#ifdef MQTT_HOST_DISCOVERY
#undef MQTT_HOST_DISCOVERY
#endif

// USE_TIMERS              [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
//   Up to 16 timers
#ifndef USE_TIMERS
#define USE_TIMERS
#endif

// USE_TIMERS_WEB          [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
//   Timer webpage support
#ifndef USE_TIMERS_WEB
#define USE_TIMERS_WEB
#endif

// USE_SUNRISE             [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
//   Sunrise and sunset tools
#ifndef USE_SUNRISE
#define USE_SUNRISE
#endif

// USE_RULES               [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
//   Rules
#ifndef USE_RULES
#define USE_RULES
#endif

// USE_SCRIPT              [-, - / -, -, -, -, -]  -> disable
//   Tasmota scripting language (basic-like scripts)
#ifdef USE_SCRIPT
#undef USE_SCRIPT
#endif

// USE_EXPRESSION          [-, x / x, -, -, -, -]  -> no longer a compile-time
//   option in v15, always part of the rules engine
//   Expressions in the rules engine (compiled in with USE_RULES since v15)

// SUPPORT_IF_STATEMENT    [-, x / x, -, -, -, -]  -> no longer a compile-time
//   option in v15, always part of the rules engine

// USE_HOTPLUG             [-, - / -, -, -, -, -]  -> disable
//   HotPlug: periodically rescan the sensor bus to detect newly connected sensors
#ifdef USE_HOTPLUG
#undef USE_HOTPLUG
#endif

// USE_INFLUXDB            [-, - / x, -, -, -, -]  -> disable (ESP32 default)
//   Report telemetry to an InfluxDB time-series database
#ifdef USE_INFLUXDB
#undef USE_INFLUXDB
#endif

// USE_PROMETHEUS          [-, - / -, -, -, -, -]  -> enable (requested)
//   Prometheus metrics exporter (HTTP /metrics endpoint)
#ifndef USE_PROMETHEUS
#define USE_PROMETHEUS
#endif

// USE_PING                [-, - / -, -, -, -, -]  -> disable
//   Ping command
#ifdef USE_PING
#undef USE_PING
#endif

// USE_HDMI_CEC            [-, - / -, -, -, -, -]  -> disable
//   HDMI CEC bus
#ifdef USE_HDMI_CEC
#undef USE_HDMI_CEC
#endif

// USE_MAGIC_SWITCH        [-, - / x, -, -, -, -]  -> disable (ESP32 default)
//   Sonoff MagicSwitch, a magnetic reed switch as in Sonoff Basic R4
#ifdef USE_MAGIC_SWITCH
#undef USE_MAGIC_SWITCH
#endif

// USE_GPIO_VIEWER         [-, - / x, -, -, -, -]  -> disable (ESP32 default)
//   GPIO Viewer to see realtime GPIO states
#ifdef USE_GPIO_VIEWER
#undef USE_GPIO_VIEWER
#endif

// -- Optional modules (dimmers, relays, ...) ------

// ROTARY_V1               [-, x / x, -, x, -, -]  -> keep (ESP8266 default)
//   Rotary Encoder as used in MI Desk Lamp
#ifndef ROTARY_V1
#define ROTARY_V1
#endif

// USE_SONOFF_RF           [-, x / -, x, x, -, -]  -> keep (ESP8266 default)
//   Sonoff RF Bridge (433 MHz RF transmitter/receiver)
#ifndef USE_SONOFF_RF
#undef USE_SONOFF_RF
#endif

// USE_RF_FLASH            [-, x / -, x, x, -, -]  -> keep (ESP8266 default)
//   Flash the EFM8BB1 MCU of the Sonoff RF Bridge (C2CK=GPIO4, C2D=GPIO5)
#ifndef USE_RF_FLASH
#undef USE_RF_FLASH
#endif

// USE_SONOFF_SC           [-, x / -, x, x, -, -]  -> keep (ESP8266 default)
//   Sonoff SC environment sensor (temp/humidity/light/noise/air quality) over serial
#ifndef USE_SONOFF_SC
#undef USE_SONOFF_SC
#endif

// USE_TUYA_MCU            [x, x / -, x, x, -, x]  -> keep (ESP8266 default)
//   Tuya Serial MCU
#ifndef USE_TUYA_MCU
#undef USE_TUYA_MCU
#endif

// USE_ARMTRONIX_DIMMERS   [-, x / -, x, -, -, -]  -> keep (ESP8266 default)
//   Armtronix Dimmers
#ifndef USE_ARMTRONIX_DIMMERS
#undef USE_ARMTRONIX_DIMMERS
#endif

// USE_PS_16_DZ            [-, x / -, x, -, -, -]  -> keep (ESP8266 default)
//   PS-16-DZ Dimmer
#ifndef USE_PS_16_DZ
#undef USE_PS_16_DZ
#endif

// USE_SONOFF_IFAN         [-, x / -, x, -, -, -]  -> keep (ESP8266 default)
//   Sonoff iFan02 and iFan03
#ifndef USE_SONOFF_IFAN
#undef USE_SONOFF_IFAN
#endif

// USE_BUZZER              [-, x / x, x, x, -, -]  -> keep (ESP8266 default)
//   A buzzer
#ifndef USE_BUZZER
#undef USE_BUZZER
#endif

// USE_ARILUX_RF           [-, x / -, x, -, -, -]  -> keep (ESP8266 default)
//   Arilux RF remote controller
#ifndef USE_ARILUX_RF
#undef USE_ARILUX_RF
#endif

// USE_SHUTTER             [-, x / x, x, -, -, -]  -> keep (ESP8266 default)
//   Shutters: up to 4, various motor types
#ifndef USE_SHUTTER
#undef USE_SHUTTER
#endif

// USE_DEEPSLEEP           [-, x / x, -, x, -, -]  -> keep (ESP8266 default)
//   Deepsleep
#ifndef USE_DEEPSLEEP
#define USE_DEEPSLEEP
#endif

// USE_EXS_DIMMER          [-, x / -, x, -, -, -]  -> keep (ESP8266 default)
//   ES-Store Wi-Fi Dimmer
#ifndef USE_EXS_DIMMER
#undef USE_EXS_DIMMER
#endif

// USE_DEVICE_GROUPS       [-, x / x, -, -, -, -]  -> keep (ESP8266 default)
//   Device groups (DevGroup): sync switches/relays with other Tasmota devices on the LAN
#ifndef USE_DEVICE_GROUPS
#define USE_DEVICE_GROUPS
#endif

// USE_PWM_DIMMER          [-, x / -, x, -, -, -]  -> keep (ESP8266 default)
//   MJ-SD01/acenx/NTONPOWER PWM dimmers
#ifndef USE_PWM_DIMMER
#undef USE_PWM_DIMMER
#endif

// USE_KEELOQ              [-, - / -, -, -, -, -]  -> disable
//   Jarolift rollers by Keeloq algorithm
#ifdef USE_KEELOQ
#undef USE_KEELOQ
#endif

// USE_SONOFF_D1           [-, x / -, x, -, -, -]  -> keep (ESP8266 default)
//   Sonoff D1 Dimmer
#ifndef USE_SONOFF_D1
#undef USE_SONOFF_D1
#endif

// USE_SHELLY_DIMMER       [-, x / -, -, -, -, -]  -> keep (ESP8266 default)
//   Shelly Dimmer
#ifndef USE_SHELLY_DIMMER
#undef USE_SHELLY_DIMMER
#endif

// USE_AC_ZERO_CROSS_DIMMER [-, x / x, x, x, x, x] -> keep (ESP8266 default)
//   AC zero-cross detection for triac dimmers (needs USE_COUNTER and USE_LIGHT)
#ifndef USE_AC_ZERO_CROSS_DIMMER
#undef USE_AC_ZERO_CROSS_DIMMER
#endif

// -- Light modules --------------------------------

// USE_LIGHT               [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
//   Light control
#ifndef USE_LIGHT
#undef USE_LIGHT
#endif

// USE_WS2812              [-, x / x, x, x, -, x]  -> disable: the Nous A8T has
//   no addressable LEDs (its status LED is a plain Led_i). Additionally, on
//   ESP32 with Tasmota v15 the WS2812 driver (xlgt_01_ws2812_esp32.ino) relies
//   on the TasmotaLEDPusher type that is only pulled in by the Berry LED driver
//   (xdrv_52_3_berry_leds.ino), so with Berry disabled (see extras section) the
//   build would not compile with USE_WS2812 enabled.
//   Addressable RGB LED strips (WS2812/SK6812/...) via NeoPixelBus
#ifdef USE_WS2812
#undef USE_WS2812
#endif

// USE_WS2812_DMA          [-, - / -, -, -, -, -]  -> disable
//   WS2812 via DMA (ESP8266 only, GPIO3 = Serial RXD)
#ifdef USE_WS2812_DMA
#undef USE_WS2812_DMA
#endif

// USE_MY92X1              [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
//   MY92X1 RGBCW led controller as used in Sonoff B1, Ailight and Lohas
#ifndef USE_MY92X1
#undef USE_MY92X1
#endif

// USE_SM16716             [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
//   SM16716 RGB LED controller
#ifndef USE_SM16716
#undef USE_SM16716
#endif

// USE_SM2135              [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
//   SM2135 RGBCW led control as used in Action LSC
#ifndef USE_SM2135
#undef USE_SM2135
#endif

// USE_SM2335              [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
//   SM2335 RGBCW led control as used in SwitchBot Color Bulb
#ifndef USE_SM2335
#undef USE_SM2335
#endif

// USE_BP5758D             [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
//   BP5758D RGBCW led control as used in some Tuya lightbulbs
#ifndef USE_BP5758D
#undef USE_BP5758D
#endif

// USE_BP1658CJ            [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
//   BP1658CJ RGBCW led control as used in Orein OS0100411267 Bulb
#ifndef USE_BP1658CJ
#undef USE_BP1658CJ
#endif

// USE_SONOFF_L1           [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
//   Sonoff L1 led control
#ifndef USE_SONOFF_L1
#undef USE_SONOFF_L1
#endif

// USE_ELECTRIQ_MOODL      [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
//   ElectriQ iQ-wifiMOODL RGBW LED controller
#ifndef USE_ELECTRIQ_MOODL
#undef USE_ELECTRIQ_MOODL
#endif

// -- Energy monitors ------------------------------

// USE_ENERGY_SENSOR       [-, x / x, x, x, -, -]  -> keep (ESP8266 default;
//   required for the BL0937 energy monitor of the Nous A8T, along with the
//   default-enabled USE_HLW8012 which covers HLW8012/BL0937/HJL-01)
//   Energy monitoring framework (power/voltage/current sensors)
#ifndef USE_ENERGY_SENSOR
#define USE_ENERGY_SENSOR
#endif

// USE_ENERGY_DUMMY        [-, x / x, x, x, -, -]  -> keep (ESP8266 default)
//   Dummy Energy monitor allowing user values
#ifndef USE_ENERGY_DUMMY
#define USE_ENERGY_DUMMY
#endif

// USE_PZEM004T            [-, x / x, x, x, -, -]  -> keep (ESP8266 default)
//   PZEM004T Energy monitor
#ifndef USE_PZEM004T
#undef USE_PZEM004T
#endif

// USE_PZEM_AC             [-, x / x, x, x, -, -]  -> keep (ESP8266 default)
//   PZEM-014/PZEM-016 AC energy monitor (serial)
#ifndef USE_PZEM_AC
#undef USE_PZEM_AC
#endif

// USE_PZEM_DC             [-, x / x, x, x, -, -]  -> keep (ESP8266 default)
//   PZEM-003/PZEM-017 DC energy monitor (serial)
#ifndef USE_PZEM_DC
#undef USE_PZEM_DC
#endif

// USE_MCP39F501           [-, x / -, x, x, -, -]  -> keep (ESP8266 default)
//   MCP39F501 Energy monitor as used in Shelly 2
#ifndef USE_MCP39F501
#undef USE_MCP39F501
#endif

// USE_SDM72               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Eastron SDM72-Modbus energy monitor
#ifdef USE_SDM72
#undef USE_SDM72
#endif

// USE_SDM120              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Eastron SDM120-Modbus energy monitor
#ifdef USE_SDM120
#undef USE_SDM120
#endif

// USE_SDM230              [-, - / x, -, -, -, -]  -> disable (ESP32 default)
//   Eastron SDM230-Modbus energy monitor
#ifdef USE_SDM230
#undef USE_SDM230
#endif

// USE_SDM630              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Eastron SDM630-Modbus energy monitor
#ifdef USE_SDM630
#undef USE_SDM630
#endif

// USE_DDS2382             [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Hiking DDS2382 Modbus energy monitor
#ifdef USE_DDS2382
#undef USE_DDS2382
#endif

// USE_DDSU666             [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Chint DDSU666 Modbus energy monitor
#ifdef USE_DDSU666
#undef USE_DDSU666
#endif

// USE_SOLAX_X1            [-, - / -, -, -, -, -]  -> disable
//   Solax X1 series Modbus log info
#ifdef USE_SOLAX_X1
#undef USE_SOLAX_X1
#endif

// USE_LE01MR              [-, - / -, -, -, -, -]  -> disable
//   F&F LE-01MR Modbus energy monitor
#ifdef USE_LE01MR
#undef USE_LE01MR
#endif

// USE_BL09XX              [-, x / x, x, x, -, -]  -> keep (ESP8266 default)
//   Various BL09XX Energy monitor as used in Blitzwolf SHP-10 or Sonoff Dual R3 v2
#ifndef USE_BL09XX
#undef USE_BL09XX
#endif

// USE_TELEINFO            [-, - / -, -, -, -, -]  -> disable
//   EDF Linky Teleinfo smart meter via serial RX
#ifdef USE_TELEINFO
#undef USE_TELEINFO
#endif

// USE_IEM3000             [-, - / -, -, -, -, -]  -> disable
//   Schneider Electric iEM3000-Modbus series energy monitor
#ifdef USE_IEM3000
#undef USE_IEM3000
#endif

// USE_WE517               [-, - / x, -, -, -, -]  -> disable (ESP32 default)
//   Orno WE517-Modbus energy monitor
#ifdef USE_WE517
#undef USE_WE517
#endif

// USE_MODBUS_ENERGY       [-, - / x, -, -, -, -]  -> disable (ESP32 default)
//   Generic modbus energy monitor using a user file in rule space
#ifdef USE_MODBUS_ENERGY
#undef USE_MODBUS_ENERGY
#endif

// -- Sensors --------------------------------------

// USE_ADC_VCC             [x, - / -, -, -, x, -]  -> disable
//   Report supply voltage (Vcc) in the Power status
#ifdef USE_ADC_VCC
#undef USE_ADC_VCC
#endif

// USE_COUNTER             [-, x / x, x, x, -, x]  -> keep (ESP8266 default)
//   Inputs as counter
#ifndef USE_COUNTER
#define USE_COUNTER
#endif

// USE_DS18x20             [-, x / x, x, x, -, x]  -> keep (ESP8266 default)
//   DS18x20 1-Wire temperature sensors
#ifndef USE_DS18x20
#undef USE_DS18x20
#endif

// USE_DHT                 [-, x / x, x, x, -, x]  -> keep (ESP8266 default)
//   DHT11/DHT21/DHT22/AM2301/AM2302/AM2321 and SI7021 temperature & humidity
#ifndef USE_DHT
#undef USE_DHT
#endif

// USE_MAX31855            [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   MAX31855/MAX6675 K-Type thermocouple sensor using softSPI
#ifdef USE_MAX31855
#undef USE_MAX31855
#endif

// USE_MAX31865            [-, - / -, -, -, -, -]  -> disable
//   MAX31865 RTD sensors using softSPI
#ifdef USE_MAX31865
#undef USE_MAX31865
#endif

// USE_THERMOSTAT          [-, - / -, -, -, -, -]  -> disable
//   Thermostat: switch relays based on temperature readings
#ifdef USE_THERMOSTAT
#undef USE_THERMOSTAT
#endif

// USE_LMT01               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   TI LMT01 temperature sensor, count pulses on single GPIO
#ifdef USE_LMT01
#undef USE_LMT01
#endif

// -- I2C sensors ----------------------------------

// USE_I2C                 [-, x / x, x, x, -, x]  -> keep (ESP8266 default)
//   I2C bus (Wire library) for I2C sensors
#ifndef USE_I2C
#undef USE_I2C
#endif

// USE_RTC_CHIPS           [-, - / x, -, -, -, -]  -> disable (ESP32 default)
//   RTC chip support plus NTP server; select exactly one chip below
#ifdef USE_RTC_CHIPS
#undef USE_RTC_CHIPS
#endif

// USE_BM8563              [-, - / x, -, -, -, -]  -> disable (ESP32 default)
//   BM8563 RTC - used by M5Stack - support both I2C buses on ESP32 (I2C address 0x51)
#ifdef USE_BM8563
#undef USE_BM8563
#endif

// USE_DS3231              [-, - / -, -, -, -, -]  -> disable
//   DS3231 RTC - used by Ulanzi TC001 (I2C address 0x68)
#ifdef USE_DS3231
#undef USE_DS3231
#endif

// USE_PCF85063            [-, - / -, -, -, -, -]  -> disable
//   PCF85063 RTC support (I2C address 0x51)
#ifdef USE_PCF85063
#undef USE_PCF85063
#endif

// USE_PCF85363            [-, - / -, -, -, -, -]  -> disable
//   PCF85363 RTC - used by Shelly 3EM (I2C address 0x51)
#ifdef USE_PCF85363
#undef USE_PCF85363
#endif

// USE_RX8010              [-, - / -, -, -, -, -]  -> disable
//   RX8010 RTC - used by IOTTIMER - support both I2C buses on ESP32 (I2C address 0x32)
#ifdef USE_RX8010
#undef USE_RX8010
#endif

// USE_RX8030              [-, - / -, -, -, -, -]  -> disable
//   RX8030 RTC, supports both I2C buses on ESP32 (I2C address 0x32)
#ifdef USE_RX8030
#undef USE_RX8030
#endif

// USE_SHT                 [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   SHT1X sensor
#ifdef USE_SHT
#undef USE_SHT
#endif

// USE_HTU                 [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   HTU21/SI7013/SI7020/SI7021 sensor (I2C address 0x40)
#ifdef USE_HTU
#undef USE_HTU
#endif

// USE_BMP                 [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   BMP085/BMP180/BMP280/BME280 sensors (I2C addresses 0x76 and 0x77)
#ifdef USE_BMP
#undef USE_BMP
#endif

// USE_BME68X              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   BME680/BME688 pressure, humidity and air quality sensor
#ifdef USE_BME68X
#undef USE_BME68X
#endif

// USE_AMSX915             [-, - / -, -, -, -, -]  -> disable
//   AMS5915/AMS6915 pressure/temperature sensor
#ifdef USE_AMSX915
#undef USE_AMSX915
#endif

// USE_SPL06_007           [-, - / -, -, -, -, -]  -> disable
//   SPL06_007 pressure and temperature sensor (I2C addresses 0x76)
#ifdef USE_SPL06_007
#undef USE_SPL06_007
#endif

// USE_QMP6988             [-, - / -, -, -, -, -]  -> disable
//   QMP6988 pressure and temperature sensor (I2C address 0x56 or 0x70)
#ifdef USE_QMP6988
#undef USE_QMP6988
#endif

// USE_BH1750              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   BH1750 sensor (I2C address 0x23 or 0x5C)
#ifdef USE_BH1750
#undef USE_BH1750
#endif

// USE_VEML6070            [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   VEML6070 sensor (I2C addresses 0x38 and 0x39)
#ifdef USE_VEML6070
#undef USE_VEML6070
#endif

// USE_ADS1115             [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   ADS1115 16-bit A/D converter (I2C address 0x48-0x4B)
#ifdef USE_ADS1115
#undef USE_ADS1115
#endif

// USE_INA219              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   INA219 (I2C address 0x40, 0x41 0x44 or 0x45) Low voltage and current sensor
#ifdef USE_INA219
#undef USE_INA219
#endif

// USE_INA226              [-, - / -, -, -, -, -]  -> disable
//   INA226 (I2C address 0x40, 0x41 0x44 or 0x45) Low voltage and current sensor
#ifdef USE_INA226
#undef USE_INA226
#endif

// USE_INA3221             [-, - / -, -, -, -, -]  -> disable
//   INA3221 3-channel DC voltage and current sensor (I2C address 0x40-0x44)
#ifdef USE_INA3221
#undef USE_INA3221
#endif

// USE_SHT3X               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Sensiron SHT3x (I2C address 0x44 or 0x45) or SHTC3 (I2C address 0x70) sensor
#ifdef USE_SHT3X
#undef USE_SHT3X
#endif

// USE_TSL2561             [-, - / -, -, -, -, -]  -> disable
//   TSL2561 sensor (I2C address 0x29, 0x39 or 0x49)
#ifdef USE_TSL2561
#undef USE_TSL2561
#endif

// USE_TSL2591             [-, - / -, -, -, -, -]  -> disable
//   TSL2591 sensor (I2C address 0x29)
#ifdef USE_TSL2591
#undef USE_TSL2591
#endif

// USE_MGS                 [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Xadow/Grove multi-channel gas sensor
#ifdef USE_MGS
#undef USE_MGS
#endif

// USE_SGP30               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Sensiron SGP30 sensor (I2C address 0x58)
#ifdef USE_SGP30
#undef USE_SGP30
#endif

// USE_SGP40               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Sensiron SGP40 sensor (I2C address 0x59)
#ifdef USE_SGP40
#undef USE_SGP40
#endif

// USE_SGP4X               [-, - / x, -, -, -, -]  -> disable (ESP32 default)
//   Sensiron SGP41 sensor (I2C address 0x59)
#ifdef USE_SGP4X
#undef USE_SGP4X
#endif

// USE_SEN5X               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Sensiron SEN5X sensor (I2C address 0x69)
#ifdef USE_SEN5X
#undef USE_SEN5X
#endif

// USE_SI1145              [-, - / -, -, -, -, -]  -> disable
//   SI1145/46/47 sensor (I2C address 0x60)
#ifdef USE_SI1145
#undef USE_SI1145
#endif

// USE_LM75AD              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   LM75AD sensor (I2C addresses 0x48 - 0x4F)
#ifdef USE_LM75AD
#undef USE_LM75AD
#endif

// USE_APDS9960            [-, - / -, -, -, -, -]  -> disable
//   APDS9960 Proximity Sensor (I2C address 0x39). Disables SHT and VEML6070
#ifdef USE_APDS9960
#undef USE_APDS9960
#endif

// USE_MCP230xx            [-, - / -, -, -, -, -]  -> disable
//   MCP23008/MCP23017 I/O expander over I2C (address 0x20-0x27)
#ifdef USE_MCP230xx
#undef USE_MCP230xx
#endif

// USE_MCP23XXX_DRV        [-, - / -, -, -, -, -]  -> disable
//   MCP23xxx I/O expander as virtual switch/button/relay (I2C or SPI)
#ifdef USE_MCP23XXX_DRV
#undef USE_MCP23XXX_DRV
#endif

// USE_PCA9632             [-, - / -, -, -, -, -]  -> disable
//   PCA9632 I2C HW PWM Driver
#ifdef USE_PCA9632
#undef USE_PCA9632
#endif

// USE_PCA9685             [-, - / -, -, -, -, -]  -> disable
//   PCA9685 16-channel I2C PWM driver (address 0x40-0x47)
#ifdef USE_PCA9685
#undef USE_PCA9685
#endif

// USE_PCA9685_V2          [-, - / -, -, -, -, -]  -> disable
//   PCA9685 16-channel I2C PWM driver, v2 (address 0x40-0x47)
#ifdef USE_PCA9685_V2
#undef USE_PCA9685_V2
#endif

// USE_MPR121              [-, - / -, -, -, -, -]  -> disable
//   MPR121 controller (I2C addresses 0x5A, 0x5B, 0x5C and 0x5D) in input mode for touch buttons
#ifdef USE_MPR121
#undef USE_MPR121
#endif

// USE_CCS811              [-, - / -, -, x, -, -]  -> disable
//   CCS811 sensor (I2C address 0x5A)
#ifdef USE_CCS811
#undef USE_CCS811
#endif

// USE_CCS811_V2           [-, - / x, -, -, -, -]  -> disable (ESP32 default)
//   CCS811 sensor (I2C addresses 0x5A and 0x5B)
#ifdef USE_CCS811_V2
#undef USE_CCS811_V2
#endif

// USE_ENS16x              [-, - / -, -, -, -, -]  -> disable
//   ENS160 and ENS161 sensor (I2C addresses 0x52 and 0x53)
#ifdef USE_ENS16x
#undef USE_ENS16x
#endif

// USE_ENS210              [-, - / -, -, -, -, -]  -> disable
//   ENS210 sensor (I2C addresses 0x43)
#ifdef USE_ENS210
#undef USE_ENS210
#endif

// USE_MPU6050             [-, - / -, -, -, -, -]  -> disable
//   MPU6050 sensor (I2C address 0x68 AD0 low or 0x69 AD0 high)
#ifdef USE_MPU6050
#undef USE_MPU6050
#endif

// USE_MGC3130             [-, - / -, -, -, -, -]  -> disable
//   MGC3130 Electric Field Effect Sensor (I2C address 0x42)
#ifdef USE_MGC3130
#undef USE_MGC3130
#endif

// USE_MAX44009            [-, - / -, -, -, -, -]  -> disable
//   MAX44009 Ambient Light sensor (I2C addresses 0x4A and 0x4B)
#ifdef USE_MAX44009
#undef USE_MAX44009
#endif

// USE_SCD30               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Sensiron SCd30 CO2 sensor (I2C address 0x61)
#ifdef USE_SCD30
#undef USE_SCD30
#endif

// USE_SCD40               [-, - / x, -, -, -, -]  -> disable (ESP32 default)
//   Sensiron SCd40/Scd41 CO2 sensor (I2C address 0x62)
#ifdef USE_SCD40
#undef USE_SCD40
#endif

// USE_SPS30               [-, - / -, -, -, -, -]  -> disable
//   Sensiron SPS30 particle sensor (I2C address 0x69)
#ifdef USE_SPS30
#undef USE_SPS30
#endif

// USE_ADE7880             [-, - / -, -, -, -, -]  -> disable
//   ADE7880 Energy monitor as used on Shelly 3EM (I2C address 0x38)
#ifdef USE_ADE7880
#undef USE_ADE7880
#endif

// USE_ADE7953             [-, x / x, x, x, -, x]  -> keep (ESP8266 default)
//   ADE7953 Energy monitor as used on Shelly 2.5 (I2C address 0x38)
#ifndef USE_ADE7953
#undef USE_ADE7953
#endif

// USE_VL53L0X             [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   VL53L0x time of flight sensor (I2C address 0x29)
#ifdef USE_VL53L0X
#undef USE_VL53L0X
#endif

// USE_VL53L1X             [-, - / -, -, -, -, -]  -> disable
//   VL53L1X time of flight sensor (I2C address 0x29)
#ifdef USE_VL53L1X
#undef USE_VL53L1X
#endif

// USE_MLX90614            [-, - / -, -, -, -, -]  -> disable
//   MLX90614 ir temp sensor (I2C address 0x5a)
#ifdef USE_MLX90614
#undef USE_MLX90614
#endif

// USE_CHIRP               [-, - / -, -, -, -, -]  -> disable
//   CHIRP soil moisture sensor (variable I2C address, default 0x20)
#ifdef USE_CHIRP
#undef USE_CHIRP
#endif

// USE_PAJ7620             [-, - / -, -, -, -, -]  -> disable
//   PAJ7620 gesture sensor (I2C address 0x73)
#ifdef USE_PAJ7620
#undef USE_PAJ7620
#endif

// USE_PCF8574             [-, - / -, -, -, -, -]  -> disable
//   PCF8574 I/O Expander (I2C addresses 0x20 - 0x26 and 0x39 - 0x3F)
#ifdef USE_PCF8574
#undef USE_PCF8574
#endif

// USE_PMSA003I            [-, - / -, -, -, -, -]  -> disable
//   PMSA003I Air Quality Sensor (I2C address 0x12)
#ifdef USE_PMSA003I
#undef USE_PMSA003I
#endif

// USE_LOX_O2              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   LuminOx LOX O2 Sensor
#ifdef USE_LOX_O2
#undef USE_LOX_O2
#endif

// USE_GDK101              [-, - / -, -, -, -, -]  -> disable
//   GDK101 sensor (I2C addresses 0x18 - 0x1B)
#ifdef USE_GDK101
#undef USE_GDK101
#endif

// USE_TC74                [-, - / -, -, -, -, -]  -> disable
//   TC74 sensor (I2C addresses 0x48 - 0x4F)
#ifdef USE_TC74
#undef USE_TC74
#endif

// USE_PCA9557             [-, - / -, -, -, -, -]  -> disable
//   PCA9557 8-bit I/O Expander (I2C addresses 0x18 - 0x1F)
#ifdef USE_PCA9557
#undef USE_PCA9557
#endif

// USE_HIH6                [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Honeywell HIH Humidity and Temperature sensor (I2C address 0x27)
#ifdef USE_HIH6
#undef USE_HIH6
#endif

// USE_DHT12               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   DHT12 humidity and temperature sensor (I2C address 0x5C)
#ifdef USE_DHT12
#undef USE_DHT12
#endif

// USE_DS1624              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   DS1624, DS1621 temperature sensor (I2C addresses 0x48 - 0x4F)
#ifdef USE_DS1624
#undef USE_DS1624
#endif

// USE_AHT1x               [-, - / -, -, -, -, -]  -> disable
//   AHT10/15 humidity and temperature sensor (I2C address 0x38, 0x39)
#ifdef USE_AHT1x
#undef USE_AHT1x
#endif

// USE_HDC1080             [-, - / -, -, -, -, -]  -> disable
//   HDC1080 temperature/humidity sensor (I2C address 0x40)
#ifdef USE_HDC1080
#undef USE_HDC1080
#endif

// USE_WEMOS_MOTOR_V1      [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Wemos motor driver V1 (I2C addresses 0x2D - 0x30)
#ifdef USE_WEMOS_MOTOR_V1
#undef USE_WEMOS_MOTOR_V1
#endif

// USE_IAQ                 [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   IAQ-core air quality sensor (I2C address 0x5a)
#ifdef USE_IAQ
#undef USE_IAQ
#endif

// USE_AS3935              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   AS3935 Franklin Lightning Sensor (I2C address 0x03)
#ifdef USE_AS3935
#undef USE_AS3935
#endif

// USE_VEML6075            [-, - / -, -, -, -, -]  -> disable
//   VEML6075 UVA/UVB/UVINDEX Sensor (I2C address 0x10)
#ifdef USE_VEML6075
#undef USE_VEML6075
#endif

// USE_VEML7700            [-, - / -, -, -, -, -]  -> disable
//   VEML7700 Ambient Light sensor (I2C addresses 0x10)
#ifdef USE_VEML7700
#undef USE_VEML7700
#endif

// USE_MCP9808             [-, - / -, -, -, -, -]  -> disable
//   MCP9808 temperature sensor (I2C addresses 0x18 - 0x1F)
#ifdef USE_MCP9808
#undef USE_MCP9808
#endif

// USE_MLX90640            [-, - / -, -, -, -, -]  -> disable
//   MLX90640 IR array temperature sensor (I2C address 0x33)
#ifdef USE_MLX90640
#undef USE_MLX90640
#endif

// USE_HP303B              [-, - / -, -, -, -, -]  -> disable
//   HP303B temperature and pressure sensor (I2C address 0x76 or 0x77)
#ifdef USE_HP303B
#undef USE_HP303B
#endif

// USE_EZOCO2              [-, - / -, -, -, -, -]  -> disable (no EZO devices)
//   Atlas Scientific EZO CO2 sensor (I2C)
#ifdef USE_EZOCO2
#undef USE_EZOCO2
#endif

// USE_EZODO               [-, - / -, -, -, -, -]  -> disable
//   Atlas Scientific EZO DO sensor (I2C)
#ifdef USE_EZODO
#undef USE_EZODO
#endif

// USE_EZOEC               [-, - / -, -, -, -, -]  -> disable
//   Atlas Scientific EZO EC sensor (I2C)
#ifdef USE_EZOEC
#undef USE_EZOEC
#endif

// USE_EZOFLO              [-, - / -, -, -, -, -]  -> disable
//   Atlas Scientific EZO FLO sensor (I2C)
#ifdef USE_EZOFLO
#undef USE_EZOFLO
#endif

// USE_EZOHUM              [-, - / -, -, -, -, -]  -> disable
//   Atlas Scientific EZO HUM sensor (I2C)
#ifdef USE_EZOHUM
#undef USE_EZOHUM
#endif

// USE_EZOO2               [-, - / -, -, -, -, -]  -> disable
//   Atlas Scientific EZO O2 sensor (I2C)
#ifdef USE_EZOO2
#undef USE_EZOO2
#endif

// USE_EZOORP              [-, - / -, -, -, -, -]  -> disable
//   Atlas Scientific EZO ORP sensor (I2C)
#ifdef USE_EZOORP
#undef USE_EZOORP
#endif

// USE_EZOPH               [-, - / -, -, -, -, -]  -> disable
//   Atlas Scientific EZO pH sensor (I2C)
#ifdef USE_EZOPH
#undef USE_EZOPH
#endif

// USE_EZOPMP              [-, - / -, -, -, -, -]  -> disable
//   Atlas Scientific EZO PMP sensor (I2C)
#ifdef USE_EZOPMP
#undef USE_EZOPMP
#endif

// USE_EZOPRS              [-, - / -, -, -, -, -]  -> disable
//   Atlas Scientific EZO PRS sensor (I2C)
#ifdef USE_EZOPRS
#undef USE_EZOPRS
#endif

// USE_EZORTD              [-, - / -, -, -, -, -]  -> disable
//   Atlas Scientific EZO RTD sensor (I2C)
#ifdef USE_EZORTD
#undef USE_EZORTD
#endif

// USE_EZORGB              [-, - / -, -, -, -, -]  -> disable
//   Atlas Scientific EZO RGB sensor (I2C)
#ifdef USE_EZORGB
#undef USE_EZORGB
#endif

// USE_SEESAW_SOIL         [-, - / -, -, -, -, -]  -> disable
//   Adafruit Soil Moisture & Temp Sensor (I2C addresses 0x36 - 0x39)
#ifdef USE_SEESAW_SOIL
#undef USE_SEESAW_SOIL
#endif

// USE_TOF10120            [-, - / -, -, -, -, -]  -> disable
//   TOF10120 time of flight sensor (I2C address 0x52)
#ifdef USE_TOF10120
#undef USE_TOF10120
#endif

// USE_AM2320              [-, - / -, -, -, -, -]  -> disable
//   AM2320 temperature and humidity Sensor (I2C address 0x5C)
#ifdef USE_AM2320
#undef USE_AM2320
#endif

// USE_T67XX               [-, - / -, -, -, -, -]  -> disable
//   Telaire T67XX CO2 sensor (I2C address 0x15)
#ifdef USE_T67XX
#undef USE_T67XX
#endif

// USE_HM330X              [-, - / -, -, -, -, -]  -> disable
//   Seeed Grove HM330X particle sensor (I2C address 0x40)
#ifdef USE_HM330X
#undef USE_HM330X
#endif

// USE_HDC2010             [-, - / -, -, -, -, -]  -> disable
//   HDC2010 temperature/humidity sensor (I2C address 0x40)
#ifdef USE_HDC2010
#undef USE_HDC2010
#endif

// USE_DS3502              [-, - / -, -, -, -, -]  -> disable
//   DS3502 digital potentiometer (I2C address 0x28 - 0x2B)
#ifdef USE_DS3502
#undef USE_DS3502
#endif

// USE_HYT                 [-, - / -, -, -, -, -]  -> disable
//   HYTxxx temperature and humidity sensor (I2C address 0x28)
#ifdef USE_HYT
#undef USE_HYT
#endif

// USE_LUXV30B             [-, - / -, -, -, -, -]  -> disable
//   RFRobot SEN0390 LuxV30b ambient light sensor (I2C address 0x4A)
#ifdef USE_LUXV30B
#undef USE_LUXV30B
#endif

// USE_HMC5883L            [-, - / -, -, -, -, -]  -> disable
//   HMC5883L magnetic induction sensor (I2C address 0x1E)
#ifdef USE_HMC5883L
#undef USE_HMC5883L
#endif

// USE_QMC5883L            [-, - / -, -, -, -, -]  -> disable
//   QMC5883L magnetic induction sensor (I2C address 0x0D)
#ifdef USE_QMC5883L
#undef USE_QMC5883L
#endif

// USE_MAX17043            [-, - / -, -, -, -, -]  -> disable
//   MAX17043 fuel-gauge systems Lipo batteries sensor (I2C address 0x36)
#ifdef USE_MAX17043
#undef USE_MAX17043
#endif

// -- SPI and serial sensors -----------------------

// USE_SPI                 [-, - / x, -, -, -, x]  -> disable (ESP32 default)
//   Hardware SPI bus (GPIO12 MISO, GPIO13 MOSI, GPIO14 CLK + selectable CS/DC)
#ifdef USE_SPI
#undef USE_SPI
#endif

// USE_RC522               [-, - / -, -, -, -, -]  -> disable
//   MFRC522 13.56Mhz Rfid reader
#ifdef USE_RC522
#undef USE_RC522
#endif

// USE_CANSNIFFER          [-, - / -, -, -, -, -]  -> disable
//   Can bus sniffer using MCP2515
#ifdef USE_CANSNIFFER
#undef USE_CANSNIFFER
#endif

// USE_SPI_LORA            [-, - / x, -, -, -, -]  -> disable (ESP32 default)
//   LoRa RF transceiver (LoRaSend/LoRaCommand)
#ifdef USE_SPI_LORA
#undef USE_SPI_LORA
#endif

// USE_MHZ19               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   MH-Z19 CO2 sensor
#ifdef USE_MHZ19
#undef USE_MHZ19
#endif

// USE_SENSEAIR            [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   SenseAir K30, K70 and S8 CO2 sensor
#ifdef USE_SENSEAIR
#undef USE_SENSEAIR
#endif

// USE_PMS5003             [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   PMS5003 and PMS7003 particle concentration sensor
#ifdef USE_PMS5003
#undef USE_PMS5003
#endif

// USE_NOVA_SDS            [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   SDS011 and SDS021 particle concentration sensor
#ifdef USE_NOVA_SDS
#undef USE_NOVA_SDS
#endif

// USE_HPMA                [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Honeywell HPMA115S0 particle concentration sensor
#ifdef USE_HPMA
#undef USE_HPMA
#endif

// USE_SERIAL_BRIDGE       [-, x / x, x, x, -, x]  -> keep (ESP8266 default)
//   Software Serial Bridge
#ifndef USE_SERIAL_BRIDGE
#undef USE_SERIAL_BRIDGE
#endif

// USE_MODBUS_BRIDGE       [-, - / x, -, -, -, -]  -> disable (ESP32 default)
//   Software Modbus Bridge
#ifdef USE_MODBUS_BRIDGE
#undef USE_MODBUS_BRIDGE
#endif

// USE_MP3_PLAYER          [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   DFPlayer Mini MP3 player control (play/pause/stop/track/volume/reset)
#ifdef USE_MP3_PLAYER
#undef USE_MP3_PLAYER
#endif

// USE_AZ7798              [-, - / -, -, -, -, -]  -> disable
//   AZ-Instrument 7798 CO2 datalogger
#ifdef USE_AZ7798
#undef USE_AZ7798
#endif

// USE_PN532_HSU           [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   PN532 using HSU (Serial) interface
#ifdef USE_PN532_HSU
#undef USE_PN532_HSU
#endif

// USE_RDM6300             [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   RDM6300 125kHz RFID Reader
#ifdef USE_RDM6300
#undef USE_RDM6300
#endif

// USE_IBEACON             [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Bluetooth LE passive scan of ibeacon devices (uses HM17 module)
#ifdef USE_IBEACON
#undef USE_IBEACON
#endif

// USE_GPS                 [-, - / -, -, -, -, -]  -> disable
//   GPS receiver (NMEA) used as NTP time source
#ifdef USE_GPS
#undef USE_GPS
#endif

// USE_HM10                [-, - / -, -, x, -, -]  -> disable
//   HM-10 as a BLE-bridge
#ifdef USE_HM10
#undef USE_HM10
#endif

// USE_HRXL                [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   MaxBotix HRXL-MaxSonar ultrasonic range finders
#ifdef USE_HRXL
#undef USE_HRXL
#endif

// USE_TASMOTA_CLIENT      [-, - / -, -, -, -, -]  -> disable
//   Arduino Uno/Pro Mini via serial interface including flashing
#ifdef USE_TASMOTA_CLIENT
#undef USE_TASMOTA_CLIENT
#endif

// USE_OPENTHERM           [-, - / -, -, -, -, -]  -> disable
//   OpenTherm boiler/thermostat communication protocol
#ifdef USE_OPENTHERM
#undef USE_OPENTHERM
#endif

// USE_MIEL_HVAC           [-, - / -, -, -, -, -]  -> disable
//   Mitsubishi Electric HVAC serial interface
#ifdef USE_MIEL_HVAC
#undef USE_MIEL_HVAC
#endif

// USE_PROJECTOR_CTRL      [-, - / -, -, -, -, -]  -> disable
//   LCD/DLP Projector serial control interface
#ifdef USE_PROJECTOR_CTRL
#undef USE_PROJECTOR_CTRL
#endif

// USE_AS608               [-, - / -, -, -, -, -]  -> disable
//   AS608 optical and R503 capacitive fingerprint sensor
#ifdef USE_AS608
#undef USE_AS608
#endif

// USE_LD2402              [-, - / -, -, -, -, -]  -> disable
//   HLK-LD2402 24GHz human presence sensor module
#ifdef USE_LD2402
#undef USE_LD2402
#endif

// USE_LD2410              [-, - / -, -, -, -, -]  -> disable
//   HLK-LD2410 24GHz smart wave motion sensor
#ifdef USE_LD2410
#undef USE_LD2410
#endif

// USE_LD2410S             [-, - / -, -, -, -, -]  -> disable
//   HLK-LD2410S Ultra Low-power 24GHz smart wave motion sensor
#ifdef USE_LD2410S
#undef USE_LD2410S
#endif

// USE_GM861               [-, - / -, -, -, -, -]  -> disable
//   GM861 1D and 2D Bar Code Reader
#ifdef USE_GM861
#undef USE_GM861
#endif

// USE_TCP_BRIDGE          [-, - / -, -, -, -, -]  -> disable
//   Serial to TCP bridge
#ifdef USE_TCP_BRIDGE
#undef USE_TCP_BRIDGE
#endif

// USE_HC8                 [-, - / -, -, -, -, -]  -> disable
//   HC8 CO2 sensor over serial
#ifdef USE_HC8
#undef USE_HC8
#endif

// USE_PIPSOLAR            [-, - / -, -, -, -, -]  -> disable
//   PipSolar / MPP-Solar (Voltronic) inverter monitoring over serial
#ifdef USE_PIPSOLAR
#undef USE_PIPSOLAR
#endif

// USE_WOOLIIS             [-, - / -, -, -, -, -]  -> disable
//   Wooliis Hall Effect Coulometer or Battery capacity monitor
#ifdef USE_WOOLIIS
#undef USE_WOOLIIS
#endif

// USE_C8_CO2_5K           [-, - / -, -, -, -, -]  -> disable
//   SC8-CO2-5K CO2 sensor over serial
#ifdef USE_C8_CO2_5K
#undef USE_C8_CO2_5K
#endif

// -- Wireless (RF, Zigbee, ...) -------------------

// USE_NRF24               [-, - / -, -, -, -, -]  -> disable
//   SPI support for NRF24L01
#ifdef USE_NRF24
#undef USE_NRF24
#endif

// USE_MIBLE               [-, - / -, -, -, -, -]  -> disable
//   BLE-bridge for some Mijia-BLE-sensors
#ifdef USE_MIBLE
#undef USE_MIBLE
#endif

// USE_ZIGBEE              [-, - / -, -, -, -, -]  -> disable
//   Serial communication with Zigbee CC2530/CC2652 flashed with ZNP or EFR32 flashed with EZSP
#ifdef USE_ZIGBEE
#undef USE_ZIGBEE
#endif

// USE_ZIGBEE_ZNP          [-, - / -, -, -, -, -]  -> disable
//   ZNP protocol, needed for CC2530/CC2652 based devices
#ifdef USE_ZIGBEE_ZNP
#undef USE_ZIGBEE_ZNP
#endif

// USE_ZIGBEE_EZSP         [-, - / -, -, -, -, -]  -> disable
//   EZSP protocol, needed for EFR32 EmberZNet based devices, like Sonoff Zigbee bridge
#ifdef USE_ZIGBEE_EZSP
#undef USE_ZIGBEE_EZSP
#endif

// -- IR -------------------------------------------

// USE_IR_REMOTE           [-, x / -, x, x, x, x]  -> keep (ESP8266 default)
//   Send IR remote commands
#ifndef USE_IR_REMOTE
#undef USE_IR_REMOTE
#endif

// USE_IR_RECEIVE          [-, x / -, x, x, x, x]  -> keep (ESP8266 default)
//   IR receiver
#ifndef USE_IR_RECEIVE
#undef USE_IR_RECEIVE
#endif

// USE_IR_REMOTE_FULL      [-, - / -, -, -, x, -]  -> disable (all protocols)
//   Support all IR protocols from IRremoteESP8266
#ifdef USE_IR_REMOTE_FULL
#undef USE_IR_REMOTE_FULL
#endif

// USE_WIZMOTE             [-, - / -, -, -, -, -]  -> disable
//   WiZ Smart Remote (uses ESP-NOW)
#ifdef USE_WIZMOTE
#undef USE_WIZMOTE
#endif

// -- Other sensors --------------------------------

// USE_SR04                [-, - / -, -, x, -, -]  -> disable
//   HC-SR04 ultrasonic devices
#ifdef USE_SR04
#undef USE_SR04
#endif

// USE_ME007               [-, - / -, -, -, -, -]  -> disable
//   ME007 ultrasonic devices
#ifdef USE_ME007
#undef USE_ME007
#endif

// USE_DYP                 [-, - / -, -, -, -, -]  -> disable
//   DYP ME-007 ultrasonic distance sensor, serial port version
#ifdef USE_DYP
#undef USE_DYP
#endif

// USE_TM1638              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   TM1638 key/7-segment module exposed as Switch1..Switch8
#ifdef USE_TM1638
#undef USE_TM1638
#endif

// USE_HX711               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   HX711 load cell
#ifdef USE_HX711
#undef USE_HX711
#endif

// USE_HX711_M5SCALES      [-, - / -, -, -, -, -]  -> disable
//   M5Unit (Mini)Scales (I2C address 0x26)
#ifdef USE_HX711_M5SCALES
#undef USE_HX711_M5SCALES
#endif

// USE_TX2x_WIND_SENSOR    [-, - / -, -, -, -, -]  -> disable
//   La Crosse TX20/TX23 anemometer (wind speed/direction) over serial
#ifdef USE_TX20_WIND_SENSOR
#undef USE_TX20_WIND_SENSOR
#endif
#ifdef USE_TX23_WIND_SENSOR
#undef USE_TX23_WIND_SENSOR
#endif

// USE_WINDMETER           [-, - / -, -, -, -, -]  -> disable
//   Analog anemometer
#ifdef USE_WINDMETER
#undef USE_WINDMETER
#endif

// USE_RC_SWITCH           [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   RF transceiver
#ifdef USE_RC_SWITCH
#undef USE_RC_SWITCH
#endif

// USE_RF_SENSOR           [-, - / x, -, x, -, -]  -> disable (ESP32 default;
//   AlectoV2 only in the stock ESP32 build)
//   RF sensor receiver (434MHz or 868MHz)
#ifdef USE_RF_SENSOR
#undef USE_RF_SENSOR
#endif

// USE_HRE                 [-, - / x, -, x, -, -]  -> disable (ESP32 default)
//   Badger HR-E Water Meter
#ifdef USE_HRE
#undef USE_HRE
#endif

// USE_A4988_STEPPER       [-, - / -, -, -, -, -]  -> disable
//   Stepper motor driver (A4988/DRV8825)
#ifdef USE_A4988_STEPPER
#undef USE_A4988_STEPPER
#endif

// USE_NEOPOOL             [-, - / -, -, -, -, -]  -> disable
//   Sugar Valley NeoPool pool controller (also Hidrolife, Bayrol, ...)
#ifdef USE_NEOPOOL
#undef USE_NEOPOOL
#endif

// USE_FLOWRATEMETER       [-, - / -, -, -, -, -]  -> disable
//   Water flow meter (YF-DN50 and similar)
#ifdef USE_FLOWRATEMETER
#undef USE_FLOWRATEMETER
#endif

// -- Displays -------------------------------------

// USE_DISPLAY             [-, - / -, -, -, -, x]  -> disable (d variant only);
//   all display drivers below are sub-options and are inert once USE_DISPLAY
//   is undefined, but are listed and disabled here for completeness
//   Display framework (I2C LCD, 7-segment, 8x8 matrix, ePaper, RA8876, ...)
#ifdef USE_DISPLAY
#undef USE_DISPLAY
#endif

// USE_DISPLAY_LCD         [-, - / -, -, -, -, x]  -> disable
//   Lcd display (I2C addresses 0x27 and 0x3F)
#ifdef USE_DISPLAY_LCD
#undef USE_DISPLAY_LCD
#endif
// USE_DISPLAY_MATRIX      [-, - / -, -, -, -, x]  -> disable
//   8x8 LED matrix display (I2C)
#ifdef USE_DISPLAY_MATRIX
#undef USE_DISPLAY_MATRIX
#endif

// USE_DISPLAY_EPAPER_29   [-, - / -, -, -, -, x]  -> disable
//   E-paper 2.9 inch display
#ifdef USE_DISPLAY_EPAPER_29
#undef USE_DISPLAY_EPAPER_29
#endif

// USE_DISPLAY_EPAPER_42   [-, - / -, -, -, -, x]  -> disable
//   E-paper 4.2 inch display
#ifdef USE_DISPLAY_EPAPER_42
#undef USE_DISPLAY_EPAPER_42
#endif

// USE_DISPLAY_RA8876      [-, - / -, -, -, -, x]  -> disable
//   RA8876 graphics display controller with touch (I2C)
#ifdef USE_DISPLAY_RA8876
#undef USE_DISPLAY_RA8876
#endif

// USE_DISPLAY_TM1637      [-, - / -, -, -, -, x]  -> disable
//   TM1637 Seven Segment Display Module (4-6 digits)
#ifdef USE_DISPLAY_TM1637
#undef USE_DISPLAY_TM1637
#endif

// USE_DISPLAY_TM1650      [-, - / -, -, -, -, -]  -> disable
//   TM1650 display (I2C addresses 0x24-0x27 and 0x34-0x37)
#ifdef USE_DISPLAY_TM1650
#undef USE_DISPLAY_TM1650
#endif

// USE_FT5206              [-, - / -, -, -, -, -]  -> disable
//   FT5206 capacitive touch controller (touch displays)
#ifdef USE_FT5206
#undef USE_FT5206
#endif

// USE_FTC532              [-, - / -, -, -, -, -]  -> disable
//   FTC532 8-button touch controller
#ifdef USE_FTC532
#undef USE_FTC532
#endif

// USE_BS814A2             [-, - / -, -, -, -, -]  -> disable
//   BS814A2 capacitive touch keypad (8 keys, 2 GPIOs)
#ifdef USE_BS814A2
#undef USE_BS814A2
#endif

// USE_DISPLAY_TM1621_SONOFF [-, - / x, -, -, -, -] -> disable (see above; also
//   listed in the ESP32 features section of the BUILDS docs)
//   TM1621 LCD driver used by Sonoff POWR3xxD/THR3xxD
#ifdef USE_DISPLAY_TM1621_SONOFF
#undef USE_DISPLAY_TM1621_SONOFF
#endif

// -- ESP32 features (BUILDS docs, "ESP32 Feature" column) ----
//   None of them are enabled in the ESP8266 build, so all are disabled.

// USE_HALLEFFECT          [/ x]                  -> no separate macro in v15,
//   part of USE_ESP32_SENSORS which is disabled in the extras section below
//   ESP32 internal hall effect sensor (part of USE_ESP32_SENSORS)

// USE_MI_ESP32            [/ x]                  -> disable (ESP32 BLE-bridge)
//   ESP32 as a BLE-bridge
#ifdef USE_MI_ESP32
#undef USE_MI_ESP32
#endif

// USE_IBEACON_ESP32       [/ -]                  -> disable
//   Bluetooth LE passive scan of iBeacon devices using the internal ESP32 Bluetooth module
#ifdef USE_IBEACON_ESP32
#undef USE_IBEACON_ESP32
#endif

// USE_WEBCAM              [/ -]                  -> disable
//   Webcam
#ifdef USE_WEBCAM
#undef USE_WEBCAM
#endif

// USE_ETHERNET            [/ x]                  -> disable (ESP32 default)
//   Ethernet
#ifdef USE_ETHERNET
#undef USE_ETHERNET
#endif

// USE_I2S_AUDIO           [/ -]                  -> disable (not enabled by
//   default anywhere; only pulled in by USE_I2S_ALL)
//   I2S audio (playback and recording, e.g. MP3/AAC/Opus)
#ifdef USE_I2S_AUDIO
#undef USE_I2S_AUDIO
#endif

// USE_SONOFF_SPM          [/ x]                  -> disable (see energy section)
//   ESP32 based Sonoff Smart Stackable Power Meter
#ifdef USE_SONOFF_SPM
#undef USE_SONOFF_SPM
#endif

// USE_SHELLY_PRO          [/ x]                  -> disable (ESP32 default)
//   Shelly Pro (ESP32-based) devices
#ifdef USE_SHELLY_PRO
#undef USE_SHELLY_PRO
#endif

// USE_ESP32_TWAI          [/ x]                  -> disable (ESP32 default)
//   TWAI/CAN interface
#ifdef USE_ESP32_TWAI
#undef USE_ESP32_TWAI
#endif

// USE_DALI                [/ x]                  -> disable (ESP32 default)
//   DALI gateway
#ifdef USE_DALI
#undef USE_DALI
#endif

// USE_DINGTIAN_RELAY      [/ -]                  -> disable
//   Dingian relay board via 74HC595/74HC165 shift registers
#ifdef USE_DINGTIAN_RELAY
#undef USE_DINGTIAN_RELAY
#endif

// USE_MATTER_DEVICE       [/ x]                  -> disable (ESP32 default,
//   +380KB flash!)
//   Matter smart home device protocol
#ifdef USE_MATTER_DEVICE
#undef USE_MATTER_DEVICE
#endif

/*********************************************************************************************\
 * Extra ESP32-only defaults NOT listed in the BUILDS documentation, disabled to keep
 * the build as small as possible. These are defined by default only for ESP32 in
 * my_user_config.h (Berry ecosystem, ADC, ...). ESP8266 (tasmota) doesn't have them.
\*********************************************************************************************/

// Berry scripting language and everything that drags it in (+several hundred KB
// of compiled scripts and web UI, memory and IRAM allocations)
#ifdef USE_AUTOCONF
#undef USE_AUTOCONF
#endif
#ifdef USE_EXTENSION_MANAGER
#undef USE_EXTENSION_MANAGER
#endif
#ifdef USE_BERRY
#undef USE_BERRY
#endif

// ESP32 internal temperature / hall effect sensors
#ifdef USE_ESP32_SENSORS
#undef USE_ESP32_SENSORS
#endif

// ADC on GPIO32..GPIO39 (not used by the Nous A8T template)
#ifdef USE_ADC
#undef USE_ADC
#endif

// Light schemes via DDP (UDP port 4048); the Nous A8T has no light
#ifdef USE_NETWORK_LIGHT_SCHEMES
#undef USE_NETWORK_LIGHT_SCHEMES
#endif

// CSE7761 energy monitor as used in Sonoff Dual R3 (ESP32-only default);
// the Nous A8T uses a BL0937 which is covered by USE_HLW8012
#ifdef USE_CSE7761
#undef USE_CSE7761
#endif

#endif  // _USER_CONFIG_OVERRIDE_H_
