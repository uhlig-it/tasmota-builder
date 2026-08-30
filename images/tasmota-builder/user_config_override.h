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
#define OTA_URL "http://192.168.10.164:3333/tasmota32-nousa8t.bin.gz"

/*********************************************************************************************\
 * All features and sensors from the BUILDS documentation
 * Legend: [l, t, k, s, i, d] columns, "t" = tasmota (ESP8266 / ESP32)
\*********************************************************************************************/

// -- General features -----------------------------

// MY_LANGUAGE en_GB: leave default (en_GB is enabled by default in every variant)

// USE_IMPROV              [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
#ifndef USE_IMPROV
#define USE_IMPROV
#endif

// USE_UFILESYS            [-, - / x, -, -, -, -]  -> would be disabled, but is
//   unconditionally re-enabled for ESP32 by the post-config in
//   tasmota_configurations.h (file system is not available on the 1M ESP8266
//   which the table describes). No way to disable it from this file; deviation.
#ifdef USE_UFILESYS
#undef USE_UFILESYS
#endif

// USE_ARDUINO_OTA         [-, - / -, -, -, -, -]  -> disable
#ifdef USE_ARDUINO_OTA
#undef USE_ARDUINO_OTA
#endif

// USE_DOMOTICZ            [-, x / x, x, x, x, -]  -> keep (ESP8266 default)
#ifndef USE_DOMOTICZ
#define USE_DOMOTICZ
#endif

// USE_HOME_ASSISTANT      [-, - / -, -, -, -, -]  -> disable
#ifdef USE_HOME_ASSISTANT
#undef USE_HOME_ASSISTANT
#endif

// USE_TASMOTA_DISCOVERY   [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
#ifndef USE_TASMOTA_DISCOVERY
#define USE_TASMOTA_DISCOVERY
#endif

// USE_MQTT_TLS            [-, - / x, -, -, -, -]  -> disable (for ESP8266 too;
//   the BUILDS footnote "enabled by default in every ESP32 variant" is exactly
//   what this build overrides, saving the mbedTLS code)
#ifdef USE_MQTT_TLS
#undef USE_MQTT_TLS
#endif

// USE_MQTT_CLIENT_CERT    [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MQTT_CLIENT_CERT
#undef USE_MQTT_CLIENT_CERT
#endif

// USE_MQTT_AWS_IOT        [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MQTT_AWS_IOT
#undef USE_MQTT_AWS_IOT
#endif

// USE_4K_RSA              [-, - / -, -, -, -, -]  -> disable; only affects TLS
//   certificate size and is passed via platformio build flags. No effect here
//   because TLS is disabled above.
#ifdef USE_4K_RSA
#undef USE_4K_RSA
#endif

// USE_TELEGRAM            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_TELEGRAM
#undef USE_TELEGRAM
#endif

// USE_KNX                 [-, - / x, x, -, -, -]  -> disable (ESP32 default)
#ifdef USE_KNX
#undef USE_KNX
#endif

// USE_TELNET              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_TELNET
#undef USE_TELNET
#endif

// USE_XYZMODEM            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_XYZMODEM
#undef USE_XYZMODEM
#endif

// USE_WEBSERVER           [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
#ifndef USE_WEBSERVER
#define USE_WEBSERVER
#endif

// USE_WEBSEND_RESPONSE    [-, - / -, -, -, -, -]  -> disable
#ifdef USE_WEBSEND_RESPONSE
#undef USE_WEBSEND_RESPONSE
#endif

// USE_EMULATION_HUE       [x, x / x, -, x, -, -]  -> keep (ESP8266 default)
#ifndef USE_EMULATION_HUE
#define USE_EMULATION_HUE
#endif

// USE_EMULATION_WEMO      [x, x / x, -, x, -, -]  -> keep (ESP8266 default)
#ifndef USE_EMULATION_WEMO
#define USE_EMULATION_WEMO
#endif

// USE_DISCOVERY           [-, - / -, -, -, -, -]  -> not enabled by default and
//   derived from emulation/OTA; no action needed

// WEBSERVER_ADVERTISE     [-, x / -, x, -, -, x]  -> keep (ESP8266 default;
//   enables <Hostname>.local in the webserver)
#ifndef WEBSERVER_ADVERTISE
#define WEBSERVER_ADVERTISE
#endif

// MQTT_HOST_DISCOVERY     [-, - / -, -, -, -, -]  -> disable
#ifdef MQTT_HOST_DISCOVERY
#undef MQTT_HOST_DISCOVERY
#endif

// USE_TIMERS              [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
#ifndef USE_TIMERS
#define USE_TIMERS
#endif

// USE_TIMERS_WEB          [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
#ifndef USE_TIMERS_WEB
#define USE_TIMERS_WEB
#endif

// USE_SUNRISE             [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
#ifndef USE_SUNRISE
#define USE_SUNRISE
#endif

// USE_RULES               [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
#ifndef USE_RULES
#define USE_RULES
#endif

// USE_SCRIPT              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_SCRIPT
#undef USE_SCRIPT
#endif

// USE_EXPRESSION          [-, x / x, -, -, -, -]  -> no longer a compile-time
//   option in v15, always part of the rules engine

// SUPPORT_IF_STATEMENT    [-, x / x, -, -, -, -]  -> no longer a compile-time
//   option in v15, always part of the rules engine

// USE_HOTPLUG             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_HOTPLUG
#undef USE_HOTPLUG
#endif

// USE_INFLUXDB            [-, - / x, -, -, -, -]  -> disable (ESP32 default)
#ifdef USE_INFLUXDB
#undef USE_INFLUXDB
#endif

// USE_PROMETHEUS          [-, - / -, -, -, -, -]  -> enable (requested)
#ifndef USE_PROMETHEUS
#define USE_PROMETHEUS
#endif

// USE_PING                [-, - / -, -, -, -, -]  -> disable
#ifdef USE_PING
#undef USE_PING
#endif

// USE_HDMI_CEC            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_HDMI_CEC
#undef USE_HDMI_CEC
#endif

// USE_MAGIC_SWITCH        [-, - / x, -, -, -, -]  -> disable (ESP32 default)
#ifdef USE_MAGIC_SWITCH
#undef USE_MAGIC_SWITCH
#endif

// USE_GPIO_VIEWER         [-, - / x, -, -, -, -]  -> disable (ESP32 default)
#ifdef USE_GPIO_VIEWER
#undef USE_GPIO_VIEWER
#endif

// -- Optional modules (dimmers, relays, ...) ------

// ROTARY_V1               [-, x / x, -, x, -, -]  -> keep (ESP8266 default)
#ifndef ROTARY_V1
#define ROTARY_V1
#endif

// USE_SONOFF_RF           [-, x / -, x, x, -, -]  -> keep (ESP8266 default)
#ifndef USE_SONOFF_RF
#define USE_SONOFF_RF
#endif

// USE_RF_FLASH            [-, x / -, x, x, -, -]  -> keep (ESP8266 default)
#ifndef USE_RF_FLASH
#define USE_RF_FLASH
#endif

// USE_SONOFF_SC           [-, x / -, x, x, -, -]  -> keep (ESP8266 default)
#ifndef USE_SONOFF_SC
#define USE_SONOFF_SC
#endif

// USE_TUYA_MCU            [x, x / -, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_TUYA_MCU
#define USE_TUYA_MCU
#endif

// USE_ARMTRONIX_DIMMERS   [-, x / -, x, -, -, -]  -> keep (ESP8266 default)
#ifndef USE_ARMTRONIX_DIMMERS
#define USE_ARMTRONIX_DIMMERS
#endif

// USE_PS_16_DZ            [-, x / -, x, -, -, -]  -> keep (ESP8266 default)
#ifndef USE_PS_16_DZ
#define USE_PS_16_DZ
#endif

// USE_SONOFF_IFAN         [-, x / -, x, -, -, -]  -> keep (ESP8266 default)
#ifndef USE_SONOFF_IFAN
#define USE_SONOFF_IFAN
#endif

// USE_BUZZER              [-, x / x, x, x, -, -]  -> keep (ESP8266 default)
#ifndef USE_BUZZER
#define USE_BUZZER
#endif

// USE_ARILUX_RF           [-, x / -, x, -, -, -]  -> keep (ESP8266 default)
#ifndef USE_ARILUX_RF
#define USE_ARILUX_RF
#endif

// USE_SHUTTER             [-, x / x, x, -, -, -]  -> keep (ESP8266 default)
#ifndef USE_SHUTTER
#define USE_SHUTTER
#endif

// USE_DEEPSLEEP           [-, x / x, -, x, -, -]  -> keep (ESP8266 default)
#ifndef USE_DEEPSLEEP
#define USE_DEEPSLEEP
#endif

// USE_EXS_DIMMER          [-, x / -, x, -, -, -]  -> keep (ESP8266 default)
#ifndef USE_EXS_DIMMER
#define USE_EXS_DIMMER
#endif

// USE_DEVICE_GROUPS       [-, x / x, -, -, -, -]  -> keep (ESP8266 default)
#ifndef USE_DEVICE_GROUPS
#define USE_DEVICE_GROUPS
#endif

// USE_PWM_DIMMER          [-, x / -, x, -, -, -]  -> keep (ESP8266 default)
#ifndef USE_PWM_DIMMER
#define USE_PWM_DIMMER
#endif

// USE_KEELOQ              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_KEELOQ
#undef USE_KEELOQ
#endif

// USE_SONOFF_D1           [-, x / -, x, -, -, -]  -> keep (ESP8266 default)
#ifndef USE_SONOFF_D1
#define USE_SONOFF_D1
#endif

// USE_SHELLY_DIMMER       [-, x / -, -, -, -, -]  -> keep (ESP8266 default)
#ifndef USE_SHELLY_DIMMER
#define USE_SHELLY_DIMMER
#endif

// USE_AC_ZERO_CROSS_DIMMER [-, x / x, x, x, x, x] -> keep (ESP8266 default)
#ifndef USE_AC_ZERO_CROSS_DIMMER
#define USE_AC_ZERO_CROSS_DIMMER
#endif

// -- Light modules --------------------------------

// USE_LIGHT               [x, x / x, x, x, x, x]  -> keep (ESP8266 default)
#ifndef USE_LIGHT
#define USE_LIGHT
#endif

// USE_WS2812              [-, x / x, x, x, -, x]  -> disable: the Nous A8T has
//   no addressable LEDs (its status LED is a plain Led_i). Additionally, on
//   ESP32 with Tasmota v15 the WS2812 driver (xlgt_01_ws2812_esp32.ino) relies
//   on the TasmotaLEDPusher type that is only pulled in by the Berry LED driver
//   (xdrv_52_3_berry_leds.ino), so with Berry disabled (see extras section) the
//   build would not compile with USE_WS2812 enabled.
#ifdef USE_WS2812
#undef USE_WS2812
#endif

// USE_WS2812_DMA          [-, - / -, -, -, -, -]  -> disable
#ifdef USE_WS2812_DMA
#undef USE_WS2812_DMA
#endif

// USE_MY92X1              [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_MY92X1
#define USE_MY92X1
#endif

// USE_SM16716             [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_SM16716
#define USE_SM16716
#endif

// USE_SM2135              [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_SM2135
#define USE_SM2135
#endif

// USE_SM2335              [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_SM2335
#define USE_SM2335
#endif

// USE_BP5758D             [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_BP5758D
#define USE_BP5758D
#endif

// USE_BP1658CJ            [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_BP1658CJ
#define USE_BP1658CJ
#endif

// USE_SONOFF_L1           [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_SONOFF_L1
#define USE_SONOFF_L1
#endif

// USE_ELECTRIQ_MOODL      [-, x / -, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_ELECTRIQ_MOODL
#define USE_ELECTRIQ_MOODL
#endif

// -- Energy monitors ------------------------------

// USE_ENERGY_SENSOR       [-, x / x, x, x, -, -]  -> keep (ESP8266 default;
//   required for the BL0937 energy monitor of the Nous A8T, along with the
//   default-enabled USE_HLW8012 which covers HLW8012/BL0937/HJL-01)
#ifndef USE_ENERGY_SENSOR
#define USE_ENERGY_SENSOR
#endif

// USE_ENERGY_DUMMY        [-, x / x, x, x, -, -]  -> keep (ESP8266 default)
#ifndef USE_ENERGY_DUMMY
#define USE_ENERGY_DUMMY
#endif

// USE_PZEM004T            [-, x / x, x, x, -, -]  -> keep (ESP8266 default)
#ifndef USE_PZEM004T
#define USE_PZEM004T
#endif

// USE_PZEM_AC             [-, x / x, x, x, -, -]  -> keep (ESP8266 default)
#ifndef USE_PZEM_AC
#define USE_PZEM_AC
#endif

// USE_PZEM_DC             [-, x / x, x, x, -, -]  -> keep (ESP8266 default)
#ifndef USE_PZEM_DC
#define USE_PZEM_DC
#endif

// USE_MCP39F501           [-, x / -, x, x, -, -]  -> keep (ESP8266 default)
#ifndef USE_MCP39F501
#define USE_MCP39F501
#endif

// USE_SDM72               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_SDM72
#undef USE_SDM72
#endif

// USE_SDM120              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_SDM120
#undef USE_SDM120
#endif

// USE_SDM230              [-, - / x, -, -, -, -]  -> disable (ESP32 default)
#ifdef USE_SDM230
#undef USE_SDM230
#endif

// USE_SDM630              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_SDM630
#undef USE_SDM630
#endif

// USE_DDS2382             [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_DDS2382
#undef USE_DDS2382
#endif

// USE_DDSU666             [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_DDSU666
#undef USE_DDSU666
#endif

// USE_SOLAX_X1            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_SOLAX_X1
#undef USE_SOLAX_X1
#endif

// USE_LE01MR              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_LE01MR
#undef USE_LE01MR
#endif

// USE_BL09XX              [-, x / x, x, x, -, -]  -> keep (ESP8266 default)
#ifndef USE_BL09XX
#define USE_BL09XX
#endif

// USE_TELEINFO            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_TELEINFO
#undef USE_TELEINFO
#endif

// USE_IEM3000             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_IEM3000
#undef USE_IEM3000
#endif

// USE_WE517               [-, - / x, -, -, -, -]  -> disable (ESP32 default)
#ifdef USE_WE517
#undef USE_WE517
#endif

// USE_MODBUS_ENERGY       [-, - / x, -, -, -, -]  -> disable (ESP32 default)
#ifdef USE_MODBUS_ENERGY
#undef USE_MODBUS_ENERGY
#endif

// -- Sensors --------------------------------------

// USE_ADC_VCC             [x, - / -, -, -, x, -]  -> disable
#ifdef USE_ADC_VCC
#undef USE_ADC_VCC
#endif

// USE_COUNTER             [-, x / x, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_COUNTER
#define USE_COUNTER
#endif

// USE_DS18x20             [-, x / x, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_DS18x20
#define USE_DS18x20
#endif

// USE_DHT                 [-, x / x, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_DHT
#define USE_DHT
#endif

// USE_MAX31855            [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_MAX31855
#undef USE_MAX31855
#endif

// USE_MAX31865            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MAX31865
#undef USE_MAX31865
#endif

// USE_THERMOSTAT          [-, - / -, -, -, -, -]  -> disable
#ifdef USE_THERMOSTAT
#undef USE_THERMOSTAT
#endif

// USE_LMT01               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_LMT01
#undef USE_LMT01
#endif

// -- I2C sensors ----------------------------------

// USE_I2C                 [-, x / x, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_I2C
#define USE_I2C
#endif

// USE_RTC_CHIPS           [-, - / x, -, -, -, -]  -> disable (ESP32 default)
#ifdef USE_RTC_CHIPS
#undef USE_RTC_CHIPS
#endif

// USE_BM8563              [-, - / x, -, -, -, -]  -> disable (ESP32 default)
#ifdef USE_BM8563
#undef USE_BM8563
#endif

// USE_DS3231              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_DS3231
#undef USE_DS3231
#endif

// USE_PCF85063            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_PCF85063
#undef USE_PCF85063
#endif

// USE_PCF85363            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_PCF85363
#undef USE_PCF85363
#endif

// USE_RX8010              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_RX8010
#undef USE_RX8010
#endif

// USE_RX8030              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_RX8030
#undef USE_RX8030
#endif

// USE_SHT                 [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_SHT
#undef USE_SHT
#endif

// USE_HTU                 [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_HTU
#undef USE_HTU
#endif

// USE_BMP                 [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_BMP
#undef USE_BMP
#endif

// USE_BME68X              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_BME68X
#undef USE_BME68X
#endif

// USE_AMSX915             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_AMSX915
#undef USE_AMSX915
#endif

// USE_SPL06_007           [-, - / -, -, -, -, -]  -> disable
#ifdef USE_SPL06_007
#undef USE_SPL06_007
#endif

// USE_QMP6988             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_QMP6988
#undef USE_QMP6988
#endif

// USE_BH1750              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_BH1750
#undef USE_BH1750
#endif

// USE_VEML6070            [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_VEML6070
#undef USE_VEML6070
#endif

// USE_ADS1115             [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_ADS1115
#undef USE_ADS1115
#endif

// USE_INA219              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_INA219
#undef USE_INA219
#endif

// USE_INA226              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_INA226
#undef USE_INA226
#endif

// USE_INA3221             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_INA3221
#undef USE_INA3221
#endif

// USE_SHT3X               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_SHT3X
#undef USE_SHT3X
#endif

// USE_TSL2561             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_TSL2561
#undef USE_TSL2561
#endif

// USE_TSL2591             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_TSL2591
#undef USE_TSL2591
#endif

// USE_MGS                 [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_MGS
#undef USE_MGS
#endif

// USE_SGP30               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_SGP30
#undef USE_SGP30
#endif

// USE_SGP40               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_SGP40
#undef USE_SGP40
#endif

// USE_SGP4X               [-, - / x, -, -, -, -]  -> disable (ESP32 default)
#ifdef USE_SGP4X
#undef USE_SGP4X
#endif

// USE_SEN5X               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_SEN5X
#undef USE_SEN5X
#endif

// USE_SI1145              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_SI1145
#undef USE_SI1145
#endif

// USE_LM75AD              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_LM75AD
#undef USE_LM75AD
#endif

// USE_APDS9960            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_APDS9960
#undef USE_APDS9960
#endif

// USE_MCP230xx            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MCP230xx
#undef USE_MCP230xx
#endif

// USE_MCP23XXX_DRV        [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MCP23XXX_DRV
#undef USE_MCP23XXX_DRV
#endif

// USE_PCA9632             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_PCA9632
#undef USE_PCA9632
#endif

// USE_PCA9685             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_PCA9685
#undef USE_PCA9685
#endif

// USE_PCA9685_V2          [-, - / -, -, -, -, -]  -> disable
#ifdef USE_PCA9685_V2
#undef USE_PCA9685_V2
#endif

// USE_MPR121              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MPR121
#undef USE_MPR121
#endif

// USE_CCS811              [-, - / -, -, x, -, -]  -> disable
#ifdef USE_CCS811
#undef USE_CCS811
#endif

// USE_CCS811_V2           [-, - / x, -, -, -, -]  -> disable (ESP32 default)
#ifdef USE_CCS811_V2
#undef USE_CCS811_V2
#endif

// USE_ENS16x              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_ENS16x
#undef USE_ENS16x
#endif

// USE_ENS210              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_ENS210
#undef USE_ENS210
#endif

// USE_MPU6050             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MPU6050
#undef USE_MPU6050
#endif

// USE_MGC3130             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MGC3130
#undef USE_MGC3130
#endif

// USE_MAX44009            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MAX44009
#undef USE_MAX44009
#endif

// USE_SCD30               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_SCD30
#undef USE_SCD30
#endif

// USE_SCD40               [-, - / x, -, -, -, -]  -> disable (ESP32 default)
#ifdef USE_SCD40
#undef USE_SCD40
#endif

// USE_SPS30               [-, - / -, -, -, -, -]  -> disable
#ifdef USE_SPS30
#undef USE_SPS30
#endif

// USE_ADE7880             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_ADE7880
#undef USE_ADE7880
#endif

// USE_ADE7953             [-, x / x, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_ADE7953
#define USE_ADE7953
#endif

// USE_VL53L0X             [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_VL53L0X
#undef USE_VL53L0X
#endif

// USE_VL53L1X             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_VL53L1X
#undef USE_VL53L1X
#endif

// USE_MLX90614            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MLX90614
#undef USE_MLX90614
#endif

// USE_CHIRP               [-, - / -, -, -, -, -]  -> disable
#ifdef USE_CHIRP
#undef USE_CHIRP
#endif

// USE_PAJ7620             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_PAJ7620
#undef USE_PAJ7620
#endif

// USE_PCF8574             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_PCF8574
#undef USE_PCF8574
#endif

// USE_PMSA003I            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_PMSA003I
#undef USE_PMSA003I
#endif

// USE_LOX_O2              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_LOX_O2
#undef USE_LOX_O2
#endif

// USE_GDK101              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_GDK101
#undef USE_GDK101
#endif

// USE_TC74                [-, - / -, -, -, -, -]  -> disable
#ifdef USE_TC74
#undef USE_TC74
#endif

// USE_PCA9557             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_PCA9557
#undef USE_PCA9557
#endif

// USE_HIH6                [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_HIH6
#undef USE_HIH6
#endif

// USE_DHT12               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_DHT12
#undef USE_DHT12
#endif

// USE_DS1624              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_DS1624
#undef USE_DS1624
#endif

// USE_AHT1x               [-, - / -, -, -, -, -]  -> disable
#ifdef USE_AHT1x
#undef USE_AHT1x
#endif

// USE_HDC1080             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_HDC1080
#undef USE_HDC1080
#endif

// USE_WEMOS_MOTOR_V1      [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_WEMOS_MOTOR_V1
#undef USE_WEMOS_MOTOR_V1
#endif

// USE_IAQ                 [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_IAQ
#undef USE_IAQ
#endif

// USE_AS3935              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_AS3935
#undef USE_AS3935
#endif

// USE_VEML6075            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_VEML6075
#undef USE_VEML6075
#endif

// USE_VEML7700            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_VEML7700
#undef USE_VEML7700
#endif

// USE_MCP9808             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MCP9808
#undef USE_MCP9808
#endif

// USE_MLX90640            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MLX90640
#undef USE_MLX90640
#endif

// USE_HP303B              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_HP303B
#undef USE_HP303B
#endif

// USE_EZOCO2              [-, - / -, -, -, -, -]  -> disable (no EZO devices)
#ifdef USE_EZOCO2
#undef USE_EZOCO2
#endif

// USE_EZODO               [-, - / -, -, -, -, -]  -> disable
#ifdef USE_EZODO
#undef USE_EZODO
#endif

// USE_EZOEC               [-, - / -, -, -, -, -]  -> disable
#ifdef USE_EZOEC
#undef USE_EZOEC
#endif

// USE_EZOFLO              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_EZOFLO
#undef USE_EZOFLO
#endif

// USE_EZOHUM              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_EZOHUM
#undef USE_EZOHUM
#endif

// USE_EZOO2               [-, - / -, -, -, -, -]  -> disable
#ifdef USE_EZOO2
#undef USE_EZOO2
#endif

// USE_EZOORP              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_EZOORP
#undef USE_EZOORP
#endif

// USE_EZOPH               [-, - / -, -, -, -, -]  -> disable
#ifdef USE_EZOPH
#undef USE_EZOPH
#endif

// USE_EZOPMP              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_EZOPMP
#undef USE_EZOPMP
#endif

// USE_EZOPRS              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_EZOPRS
#undef USE_EZOPRS
#endif

// USE_EZORTD              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_EZORTD
#undef USE_EZORTD
#endif

// USE_EZORGB              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_EZORGB
#undef USE_EZORGB
#endif

// USE_SEESAW_SOIL         [-, - / -, -, -, -, -]  -> disable
#ifdef USE_SEESAW_SOIL
#undef USE_SEESAW_SOIL
#endif

// USE_TOF10120            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_TOF10120
#undef USE_TOF10120
#endif

// USE_AM2320              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_AM2320
#undef USE_AM2320
#endif

// USE_T67XX               [-, - / -, -, -, -, -]  -> disable
#ifdef USE_T67XX
#undef USE_T67XX
#endif

// USE_HM330X              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_HM330X
#undef USE_HM330X
#endif

// USE_HDC2010             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_HDC2010
#undef USE_HDC2010
#endif

// USE_DS3502              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_DS3502
#undef USE_DS3502
#endif

// USE_HYT                 [-, - / -, -, -, -, -]  -> disable
#ifdef USE_HYT
#undef USE_HYT
#endif

// USE_LUXV30B             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_LUXV30B
#undef USE_LUXV30B
#endif

// USE_HMC5883L            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_HMC5883L
#undef USE_HMC5883L
#endif

// USE_QMC5883L            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_QMC5883L
#undef USE_QMC5883L
#endif

// USE_MAX17043            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MAX17043
#undef USE_MAX17043
#endif

// -- SPI and serial sensors -----------------------

// USE_SPI                 [-, - / x, -, -, -, x]  -> disable (ESP32 default)
#ifdef USE_SPI
#undef USE_SPI
#endif

// USE_RC522               [-, - / -, -, -, -, -]  -> disable
#ifdef USE_RC522
#undef USE_RC522
#endif

// USE_CANSNIFFER          [-, - / -, -, -, -, -]  -> disable
#ifdef USE_CANSNIFFER
#undef USE_CANSNIFFER
#endif

// USE_SPI_LORA            [-, - / x, -, -, -, -]  -> disable (ESP32 default)
#ifdef USE_SPI_LORA
#undef USE_SPI_LORA
#endif

// USE_MHZ19               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_MHZ19
#undef USE_MHZ19
#endif

// USE_SENSEAIR            [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_SENSEAIR
#undef USE_SENSEAIR
#endif

// USE_PMS5003             [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_PMS5003
#undef USE_PMS5003
#endif

// USE_NOVA_SDS            [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_NOVA_SDS
#undef USE_NOVA_SDS
#endif

// USE_HPMA                [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_HPMA
#undef USE_HPMA
#endif

// USE_SERIAL_BRIDGE       [-, x / x, x, x, -, x]  -> keep (ESP8266 default)
#ifndef USE_SERIAL_BRIDGE
#define USE_SERIAL_BRIDGE
#endif

// USE_MODBUS_BRIDGE       [-, - / x, -, -, -, -]  -> disable (ESP32 default)
#ifdef USE_MODBUS_BRIDGE
#undef USE_MODBUS_BRIDGE
#endif

// USE_MP3_PLAYER          [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_MP3_PLAYER
#undef USE_MP3_PLAYER
#endif

// USE_AZ7798              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_AZ7798
#undef USE_AZ7798
#endif

// USE_PN532_HSU           [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_PN532_HSU
#undef USE_PN532_HSU
#endif

// USE_RDM6300             [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_RDM6300
#undef USE_RDM6300
#endif

// USE_IBEACON             [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_IBEACON
#undef USE_IBEACON
#endif

// USE_GPS                 [-, - / -, -, -, -, -]  -> disable
#ifdef USE_GPS
#undef USE_GPS
#endif

// USE_HM10                [-, - / -, -, x, -, -]  -> disable
#ifdef USE_HM10
#undef USE_HM10
#endif

// USE_HRXL                [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_HRXL
#undef USE_HRXL
#endif

// USE_TASMOTA_CLIENT      [-, - / -, -, -, -, -]  -> disable
#ifdef USE_TASMOTA_CLIENT
#undef USE_TASMOTA_CLIENT
#endif

// USE_OPENTHERM           [-, - / -, -, -, -, -]  -> disable
#ifdef USE_OPENTHERM
#undef USE_OPENTHERM
#endif

// USE_MIEL_HVAC           [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MIEL_HVAC
#undef USE_MIEL_HVAC
#endif

// USE_PROJECTOR_CTRL      [-, - / -, -, -, -, -]  -> disable
#ifdef USE_PROJECTOR_CTRL
#undef USE_PROJECTOR_CTRL
#endif

// USE_AS608               [-, - / -, -, -, -, -]  -> disable
#ifdef USE_AS608
#undef USE_AS608
#endif

// USE_LD2402              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_LD2402
#undef USE_LD2402
#endif

// USE_LD2410              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_LD2410
#undef USE_LD2410
#endif

// USE_LD2410S             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_LD2410S
#undef USE_LD2410S
#endif

// USE_GM861               [-, - / -, -, -, -, -]  -> disable
#ifdef USE_GM861
#undef USE_GM861
#endif

// USE_TCP_BRIDGE          [-, - / -, -, -, -, -]  -> disable
#ifdef USE_TCP_BRIDGE
#undef USE_TCP_BRIDGE
#endif

// USE_HC8                 [-, - / -, -, -, -, -]  -> disable
#ifdef USE_HC8
#undef USE_HC8
#endif

// USE_PIPSOLAR            [-, - / -, -, -, -, -]  -> disable
#ifdef USE_PIPSOLAR
#undef USE_PIPSOLAR
#endif

// USE_WOOLIIS             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_WOOLIIS
#undef USE_WOOLIIS
#endif

// USE_C8_CO2_5K           [-, - / -, -, -, -, -]  -> disable
#ifdef USE_C8_CO2_5K
#undef USE_C8_CO2_5K
#endif

// -- Wireless (RF, Zigbee, ...) -------------------

// USE_NRF24               [-, - / -, -, -, -, -]  -> disable
#ifdef USE_NRF24
#undef USE_NRF24
#endif

// USE_MIBLE               [-, - / -, -, -, -, -]  -> disable
#ifdef USE_MIBLE
#undef USE_MIBLE
#endif

// USE_ZIGBEE              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_ZIGBEE
#undef USE_ZIGBEE
#endif

// USE_ZIGBEE_ZNP          [-, - / -, -, -, -, -]  -> disable
#ifdef USE_ZIGBEE_ZNP
#undef USE_ZIGBEE_ZNP
#endif

// USE_ZIGBEE_EZSP         [-, - / -, -, -, -, -]  -> disable
#ifdef USE_ZIGBEE_EZSP
#undef USE_ZIGBEE_EZSP
#endif

// -- IR -------------------------------------------

// USE_IR_REMOTE           [-, x / -, x, x, x, x]  -> keep (ESP8266 default)
#ifndef USE_IR_REMOTE
#define USE_IR_REMOTE
#endif

// USE_IR_RECEIVE          [-, x / -, x, x, x, x]  -> keep (ESP8266 default)
#ifndef USE_IR_RECEIVE
#define USE_IR_RECEIVE
#endif

// USE_IR_REMOTE_FULL      [-, - / -, -, -, x, -]  -> disable (all protocols)
#ifdef USE_IR_REMOTE_FULL
#undef USE_IR_REMOTE_FULL
#endif

// USE_WIZMOTE             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_WIZMOTE
#undef USE_WIZMOTE
#endif

// -- Other sensors --------------------------------

// USE_SR04                [-, - / -, -, x, -, -]  -> disable
#ifdef USE_SR04
#undef USE_SR04
#endif

// USE_ME007               [-, - / -, -, -, -, -]  -> disable
#ifdef USE_ME007
#undef USE_ME007
#endif

// USE_DYP                 [-, - / -, -, -, -, -]  -> disable
#ifdef USE_DYP
#undef USE_DYP
#endif

// USE_TM1638              [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_TM1638
#undef USE_TM1638
#endif

// USE_HX711               [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_HX711
#undef USE_HX711
#endif

// USE_HX711_M5SCALES      [-, - / -, -, -, -, -]  -> disable
#ifdef USE_HX711_M5SCALES
#undef USE_HX711_M5SCALES
#endif

// USE_TX2x_WIND_SENSOR    [-, - / -, -, -, -, -]  -> disable
#ifdef USE_TX20_WIND_SENSOR
#undef USE_TX20_WIND_SENSOR
#endif
#ifdef USE_TX23_WIND_SENSOR
#undef USE_TX23_WIND_SENSOR
#endif

// USE_WINDMETER           [-, - / -, -, -, -, -]  -> disable
#ifdef USE_WINDMETER
#undef USE_WINDMETER
#endif

// USE_RC_SWITCH           [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_RC_SWITCH
#undef USE_RC_SWITCH
#endif

// USE_RF_SENSOR           [-, - / x, -, x, -, -]  -> disable (ESP32 default;
//   AlectoV2 only in the stock ESP32 build)
#ifdef USE_RF_SENSOR
#undef USE_RF_SENSOR
#endif

// USE_HRE                 [-, - / x, -, x, -, -]  -> disable (ESP32 default)
#ifdef USE_HRE
#undef USE_HRE
#endif

// USE_A4988_STEPPER       [-, - / -, -, -, -, -]  -> disable
#ifdef USE_A4988_STEPPER
#undef USE_A4988_STEPPER
#endif

// USE_NEOPOOL             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_NEOPOOL
#undef USE_NEOPOOL
#endif

// USE_FLOWRATEMETER       [-, - / -, -, -, -, -]  -> disable
#ifdef USE_FLOWRATEMETER
#undef USE_FLOWRATEMETER
#endif

// -- Displays -------------------------------------

// USE_DISPLAY             [-, - / -, -, -, -, x]  -> disable (d variant only);
//   all display drivers below are sub-options and are inert once USE_DISPLAY
//   is undefined, but are listed and disabled here for completeness
#ifdef USE_DISPLAY
#undef USE_DISPLAY
#endif

// USE_DISPLAY_LCD         [-, - / -, -, -, -, x]  -> disable
#ifdef USE_DISPLAY_LCD
#undef USE_DISPLAY_LCD
#endif
// USE_DISPLAY_MATRIX      [-, - / -, -, -, -, x]  -> disable
#ifdef USE_DISPLAY_MATRIX
#undef USE_DISPLAY_MATRIX
#endif

// USE_DISPLAY_EPAPER_29   [-, - / -, -, -, -, x]  -> disable
#ifdef USE_DISPLAY_EPAPER_29
#undef USE_DISPLAY_EPAPER_29
#endif

// USE_DISPLAY_EPAPER_42   [-, - / -, -, -, -, x]  -> disable
#ifdef USE_DISPLAY_EPAPER_42
#undef USE_DISPLAY_EPAPER_42
#endif

// USE_DISPLAY_RA8876      [-, - / -, -, -, -, x]  -> disable
#ifdef USE_DISPLAY_RA8876
#undef USE_DISPLAY_RA8876
#endif

// USE_DISPLAY_TM1637      [-, - / -, -, -, -, x]  -> disable
#ifdef USE_DISPLAY_TM1637
#undef USE_DISPLAY_TM1637
#endif

// USE_DISPLAY_TM1650      [-, - / -, -, -, -, -]  -> disable
#ifdef USE_DISPLAY_TM1650
#undef USE_DISPLAY_TM1650
#endif

// USE_FT5206              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_FT5206
#undef USE_FT5206
#endif

// USE_FTC532              [-, - / -, -, -, -, -]  -> disable
#ifdef USE_FTC532
#undef USE_FTC532
#endif

// USE_BS814A2             [-, - / -, -, -, -, -]  -> disable
#ifdef USE_BS814A2
#undef USE_BS814A2
#endif

// USE_DISPLAY_TM1621_SONOFF [-, - / x, -, -, -, -] -> disable (see above; also
//   listed in the ESP32 features section of the BUILDS docs)
#ifdef USE_DISPLAY_TM1621_SONOFF
#undef USE_DISPLAY_TM1621_SONOFF
#endif

// -- ESP32 features (BUILDS docs, "ESP32 Feature" column) ----
//   None of them are enabled in the ESP8266 build, so all are disabled.

// USE_HALLEFFECT          [/ x]                  -> no separate macro in v15,
//   part of USE_ESP32_SENSORS which is disabled in the extras section below

// USE_MI_ESP32            [/ x]                  -> disable (ESP32 BLE-bridge)
#ifdef USE_MI_ESP32
#undef USE_MI_ESP32
#endif

// USE_IBEACON_ESP32       [/ -]                  -> disable
#ifdef USE_IBEACON_ESP32
#undef USE_IBEACON_ESP32
#endif

// USE_WEBCAM              [/ -]                  -> disable
#ifdef USE_WEBCAM
#undef USE_WEBCAM
#endif

// USE_ETHERNET            [/ x]                  -> disable (ESP32 default)
#ifdef USE_ETHERNET
#undef USE_ETHERNET
#endif

// USE_I2S_AUDIO           [/ -]                  -> disable (not enabled by
//   default anywhere; only pulled in by USE_I2S_ALL)
#ifdef USE_I2S_AUDIO
#undef USE_I2S_AUDIO
#endif

// USE_SONOFF_SPM          [/ x]                  -> disable (see energy section)
#ifdef USE_SONOFF_SPM
#undef USE_SONOFF_SPM
#endif

// USE_SHELLY_PRO          [/ x]                  -> disable (ESP32 default)
#ifdef USE_SHELLY_PRO
#undef USE_SHELLY_PRO
#endif

// USE_ESP32_TWAI          [/ x]                  -> disable (ESP32 default)
#ifdef USE_ESP32_TWAI
#undef USE_ESP32_TWAI
#endif

// USE_DALI                [/ x]                  -> disable (ESP32 default)
#ifdef USE_DALI
#undef USE_DALI
#endif

// USE_DINGTIAN_RELAY      [/ -]                  -> disable
#ifdef USE_DINGTIAN_RELAY
#undef USE_DINGTIAN_RELAY
#endif

// USE_MATTER_DEVICE       [/ x]                  -> disable (ESP32 default,
//   +380KB flash!)
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
