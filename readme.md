# Hacking/Customising the electronics of the Mitsubishi iMiev/Citroen C-Zero/Peugeot iOn
We used the electronics of a Citroen C-Zero to convert a class VW Bus T2 to electric. There were and are many challenges while adding an additional battery and stripping down the wiring, so I will try to collect everything  I discovered about the electronics in one place. Maybe it`s usefull for somebody else. 

Most information was found in forums and on github, some I found out myself. I will try to quote everything correctly.

## Fundamentals
### CAN-Bus messages and timing
created by: [plaes](https://github.com/plaes/i-miev-obd2)

Periodically occurring PIDs:

    1000ms (1 fps): 01C [1]
    200ms (5 fps): 568 [1]
    100ms (10 fps): 101, 286, 298, 29A, 2F2, 374, 375, 384, 385, 389 [1], 38A [1], 3A4, 408, 412, 695, 696, 697, 6FA, 75A, 75B
    50ms (20 fps): 38D, 564, 565, 5A1, 6D0, 6D1, 6D2, 6D3, 6D4, 6D5, 6D6, 6DA
    40ms (25 fps): 424, 6E1, 6E2, 6E3, 6E4
    20ms (50 fps): 119, 149, 156, 200, 208, 210, 212, 215, 231, 300, 308, 325, 346, 418
    10ms (100fps): 236, 285, 288, 373

[1]	(1, 2, 3, 4) Possibly only sent in debug mode.

### CAN-Bus messages description 1
Mostly found on [myimiev Forum](https://myimiev.com/threads/decyphering-imiev-and-ion-car-can-message-data.763/page-7)
(Incomplete)

| Message (HEX) | timing (FPS) | Origin (ECU) | Byte 0 | Byte 1 | Byte 2 | Byte 3 | Byte 4 | Byte 5 | Byte 6 | Byte 7 |
|---------------|--------------|--------------|--------|--------|--------|--------|--------|--------|--------|--------|
| 01C           | 1            | -            | —      | —      | —      | —      | —      | —      | —      | —      |
| 101           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 119           | 50           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 149           | 50           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 156           | 50           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 200           | 50           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 208           | 50           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 210           | 50           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 212           | 50           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 215           | 50           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 231           | 50           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 236           | 100          | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 285           | 100          | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 286           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 288           | 100          | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 298           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 29A           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 2F2           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 300           | 50           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 308           | 50           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 325           | 50           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 346           | 50           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 373           | 100          | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 374           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 375           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 384           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 385           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 389           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 38A           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 38D           | 20           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 3A4           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 408           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 412           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 418           | 50           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 424           | 25           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 564           | 20           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 565           | 20           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 568           | 5            | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 5A1           | 20           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 695           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 696           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 697           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 6D0           | 20           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 6D1           | 20           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 6D2           | 20           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 6D3           | 20           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 6D4           | 20           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 6D5           | 20           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 6D6           | 20           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 6DA           | 20           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 6E1           | 25           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 6E2           | 25           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 6E3           | 25           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 6E4           | 25           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 6FA           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 75A           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 75B           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |


### CAN-Bus messages description 2

Posted by [CZeroOwner](https://myimiev.com/members/czeroowner.2564/) on [myimiev Forum](https://myimiev.com/threads/decyphering-imiev-and-ion-car-can-message-data.763/page-7)

| Description                         | Units     | PID  | Conversion (from forum rules)                                  | Notes |
|-------------------------------------|-----------|------|------------------------------------------------------------------|-------|
| Acceleration                        | m/s^2     | 285  | (byte(6) * 256 + byte(7) - 2000) / 400.0                         | 1     |
| Accelerator Pedal                   | number    | 210  | byte(2) * byte(4) / 256.0                                       |       |
| Air direction control position      | number    | 344  | byte(2) low nibble                                              |       |
| Air fan speed                       | number    | 344  | byte(2) high nibble                                             |       |
| Air heater amps                     | amps      | 389  | byte(4) / 2.0                                                   |       |
| Air max fan                         | on/off    | 344  | byte(3) bit 3                                                   |       |
| Air recirculation                   | on/off    | 344  | byte(3) bit 2                                                   |       |
| Air temperature control position    | number    | 344  | byte(1) high nibble                                             |       |
| Airconditioning on/off              | on/off    | 344  | byte(1) bit 6                                                   |       |
| Airconditioning level               | number    | 344  | (byte(1) * 256 + byte(2)) / 1000.0                              |       |
| Airconditioning on/off              | on/off    | 384  | byte(2) bit 5                                                   |       |
| Aux battery voltage                 | volts     | 374  | (byte(4) * 256 + byte(5)) / 100.0                               |       |
| Battery amps in                     | amps      | 373  | (byte(4) * 256 + byte(5) - 32768) / 100.0                       |       |
| Battery amps out calibrated         | amps      | 373  | —                                                               | 6     |
| Battery voltage                     | volts     | 374  | (byte(4) * 256 + byte(5)) / 10.0                                |       |
| Brake                               | on/off    | 385  | byte(5)                                                         |       |
| Brake pressure                      | unknown   | —    | byte(6)                                                         |       |
| Cell maximum temperature            | °C        | 377  | byte(3) - 50.0                                                  |       |
| Cell maximum voltage                | volts     | 377  | byte(2) / 100.0                                                 |       |
| Cell minimum temperature            | °C        | 377  | byte(5) - 50.0                                                  |       |
| Cell minimum voltage                | volts     | 377  | byte(4) / 100.0                                                 |       |
| Chademo connected                   | on/off    | 697  | byte(1)                                                         |       |
| Chademo current                     | amps      | 697  | byte(3)                                                         |       |
| Charging 12V battery (high voltage) | amps      | 389  | byte(3) / 2.0                                                   | 2     |
| Charging unit amps to mains        | amps      | 389  | byte(5)                                                         |       |
| Charging unit amps to battery      | amps      | 389  | byte(4)                                                         |       |
| Charging unit temperature 1        | °C        | 38D  | byte(5) - 50.0                                                  |       |
| Charging unit temperature 2        | °C        | 38D  | byte(6) - 50.0                                                  |       |
| Charging unit volts to mains       | volts     | 389  | byte(2)                                                         |       |
| Charging unit volts to battery     | volts     | 389  | byte(1)                                                         |       |
| Gear (P, R, N, D)                   | —         | 2F2  | 2 = P, 1 = Reverse, 4 = Drive                                   | 8     |
| Ignition (ready and not ready)     | on/off    | 412  | (byte(2) & 254) != 0                                            |       |
| Lights front fog on                 | on/off    | 424  | byte(3) bit 2                                                   |       |
| Lights headlights                   | on/off    | 424  | byte(3) bit 3                                                   |       |
| Lights Highbeams                    | on/off    | 424  | byte(3) bit 4                                                   |       |
| Lights Left                         | on/off    | 424  | byte(3) bit 5                                                   |       |
| Lights Parking                      | on/off    | 424  | byte(3) bit 1                                                   |       |
| Lights Right                        | on/off    | 424  | byte(3) bit 6                                                   |       |
| Motor current                       | amps      | 6D0  | (byte(6) * 256 + byte(5) - 5000) / 20.0                         | 3     |
| Motor rpm                           | rpm       | 6D0  | (byte(4) * 256 + byte(3)) - 10000                              |       |
| Motor temperature 0                | °C        | 6D1  | byte(2) - 50                                                    |       |
| Motor temperature 1                | °C        | 6D2  | byte(2) - 50                                                    |       |
| Motor temperature 2                | °C        | 6D3  | byte(2) - 50                                                    |       |
| Motor temperature 3                | °C        | 6D4  | byte(2) - 50                                                    |       |
| Motor temperature 4                | °C        | 6D5  | (byte(4) * 256 + byte(5)) / 10.0 - 50                           | 7     |
| Outdoor air temperature             | °C        | 6D6  | byte(2) - 50                                                    |       |
| Rear window defrost                 | on/off    | 424  | byte(3) bit 7                                                   |       |
| Regenerative amps (negative)       | amps      | 373  | —                                                               |       |
| Regeneration range                  | —         | 346  | (byte(1) * 256 + byte(2)) / 32.934                             | 1     |
| Rotation ESC                        | —         | 288  | byte(6)                                                         |       |
| Speed                               | km/h      | 215  | byte(3) / 2.0                                                   |       |
| Speed wheel 0                       | km/h      | 208  | byte(1) / 2.0                                                   |       |
| Speed wheel 1                       | km/h      | 208  | byte(3) / 2.0                                                   |       |
| Speed wheel 2                       | km/h      | 208  | byte(5) / 2.0                                                   |       |
| Speed wheel 3                       | km/h      | 208  | byte(7) / 2.0                                                   |       |
| State of Charge 1                   | %         | 346  | byte(5) / 2.0                                                   |       |
| State of Charge 2                   | %         | 296  | byte(6)                                                         |       |
| Steering wheel position             | degrees   | 236  | (byte(3) * 256 + byte(2) - 4096) / 30.0                         | 1     |

