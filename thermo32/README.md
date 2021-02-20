# Thermo32 is an esp32 based Thermometer

Thermo32 is an internet connected thermometer, at it's most basic it
periodically measures and transmits the temprature over an internet
connection.

The software was written with the _Espressif_ ESP-IDF built on
FreeRTOS, it is in written in C with a concurrent event driven
design. 

That means it is very efficient and flexible allowing the software
(and hardware) to be extended with relative ease. 

## Current Features

1. Concurrent software with an event loop, tasks and queues
2. Wifi (Internet) connection (needs to be made more robust) 
3. tmp36 temprature sensor used to gather periodic temprature samples 
4. red led to turn on and off (when gathering data)
5. MQTT to advertise temprature settings

## Roadmap

1. History of temprature readings
1. Embedded web interface to view current temprature
2. Configuration: web, rest, mqtt and persistence
3. Logging to elk infrastructure


### Hardware Required

This software can be run on an esp32 development board with:

- TMP36 connected to adc1_channel_6
- LED connected to digital gpio pin 5
- Wifi SSID and PWD
- MQTT broker and topic

### Configure the project

* Open the project configuration menu (`idf.py menuconfig`)
* Configure Wi-Fi or Ethernet under "Example Connection Configuration"
  menu. See "Establishing Wi-Fi or Ethernet Connection" section in
  [examples/protocols/README.md](../../README.md) for more details. 
- Configure the MQTT broker and publish topic
- Subscribe to the configuration topic
* When using Make build system, set `Default serial port` under `Serial flasher config`.

### Build and Flash

Build the project and flash it to the board, then run monitor tool to
view serial output: 

```
idf.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for full steps to configure and use
ESP-IDF to build projects. 

## Example Output

```
I (3714) event: sta ip: 192.168.0.139, mask: 255.255.255.0, gw: 192.168.0.2
I (3714) system_api: Base MAC address is not set, read default base MAC address from BLK0 of EFUSE
 ...

```
