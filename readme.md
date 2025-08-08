# Hacking/Customising the electronics of the Mitsubishi iMiev/Citroen C-Zero/Peugeot iOn
We used the electronics of a Citroen C-Zero to convert a class VW Bus T2 to electric. There were and are many challenges while adding an additional battery and stripping down the wiring, so I will try to collect everything  I discovered about the electronics in one place. Maybe it`s usefull for somebody else. 

Most information was found in forums and on github, some I found out myself. I will try to quote everything correctly.

Everything you do is on your own risk. I am not responsible if you damage or burn down your car using the provided code :)
Always be aware that you can change or bypass safety features by manipulating the CAN-messages and that this can lead to burning batteries.

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
| 373           | 100          | BMU          | —      | —      | —      | —      | —      | —      | —      | —      |
| 374           | 10           | BMU          | —      | —      | —      | —      | —      | —      | —      | —      |
| 375           | 10           | BMU          | —      | —      | —      | —      | —      | —      | —      | —      |
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
| 5A1           | 20           | BMU          | —      | —      | —      | —      | —      | —      | —      | —      |
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
| 6E1           | 25           | BMU          | —      | —      | —      | —      | —      | —      | —      | —      |
| 6E2           | 25           | BMU          | —      | —      | —      | —      | —      | —      | —      | —      |
| 6E3           | 25           | BMU          | —      | —      | —      | —      | —      | —      | —      | —      |
| 6E4           | 25           | BMU          | —      | —      | —      | —      | —      | —      | —      | —      |
| 6FA           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 75A           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |
| 75B           | 10           | —            | —      | —      | —      | —      | —      | —      | —      | —      |


### CAN-Bus messages description 2

Posted by [CZeroOwner](https://myimiev.com/members/czeroowner.2564/) on [myimiev Forum](https://myimiev.com/threads/decyphering-imiev-and-ion-car-can-message-data.763/page-7)

New insights discovered by myself: **bold**

Bytes are counted from byte 0 to byte 7



| Description                         | Units     | PID  | Conversion (from forum rules)                                  | Notes |
|-------------------------------------|-----------|------|------------------------------------------------------------------|-------|
| Acceleration                        | m/s^2     | 285  | (byte(0) * 256 + byte(1) - 2000) / 400.0                         | 1     |
| Accelerator Pedal                   | %         | 210  | 100 * byte(2) / 256.0                                       |       |
| Air direction control position      | number    | 3A4  | byte(1) low nibble                                              |       |
| Air fan speed                       | number    | 3A4  | byte(1) high nibble                                             |       |
| Air heater amps                     | amps      | 384  | byte(4) / 10.0                                                   |       |
| Air max fan                         | on/off    | 3A4  | byte(0) bit 32                                                   |       |
| Air recirculation                   | on/off    | 3A4  | byte(0) bit 64                                                   |       |
| Air temperature control position    | number    | 3A4  | byte(0) low nibble                                             |       |
| Airconditioning amps                | amps      | 384  | (byte(0) * 256 + byte(1))/1000.0                                                  |       |
| Airconditioning on/off              | on/off    | 3A4  | byte(0) bit 128                                                   |       |
| Battery 100% capacity               | amp-hours | 373  | byte(6) / 2.0                       |       |
| Battery amps in                     | amps      | 373  | (byte(2) * 256 + byte(3) - 32768) / 100.0                       |       |
| Battery amps out calibrated         | amps      | 373  | BatteryAmps + 0.66                                                               | 6     |
| Battery voltage                     | volts     | 373  | (byte(4) * 256 + byte(5)) / 10.0                                |       |
| Brake                               | on/off    | 231  | byte(4)                                                         |       |
| Brake pressure                      | bar?      | 208  | byte(3)                                                         |       |
| Cell maximum temperature            | °C        | 374  | byte(4) - 50.0                                                  |       |
| Cell maximum voltage                | volts     | 373  | (byte(0) + 210) / 100.0                                                 |       |
| Cell minimum temperature            | °C        | 374  | byte(5) - 50.0                                                  |       |
| Cell minimum voltage                | volts     | 373  | (byte(1) + 210) / 100.0                                                 |       |
| Chademo connected                   | on/off    | 697  | byte(0)                                                         |       |
| Chademo current                     | amps      | 697  | byte(2)                                                         |       |
| Chademo percent                     | %         | 697  | byte(1)                                                         |       |
| Charging 12V battery (high voltage) | amps      | 384  | byte(3) / 100.0                                                   | 2     |
| Charging unit amps from mains        | amps      | 389  | byte(6) / 10.0                                                         |       |
| Charging unit amps to battery      | amps      | 389  | byte(2) / 10.0                                                         |       |
| Charging unit temperature 1        | °C        | 389  | byte(3) - 50.0                                                  |       |
| Charging unit temperature 2        | °C        | 389  | byte(4) - 50.0                                                  |       |
| Charging unit volts from mains       | volts     | 389  | byte(1)                                                         |       |
| Charging unit volts to battery     | volts     | 389  | 2 * (byte(0) + 0.5)                                                         |       |
| **Gear (P, R, N, D, B, C)**                   | **—**         | **418**  | **Byte(0) Decimal: P=80, R=82, N=78, D=68, B=131 C=50**                                   | 8     |
| **Insulation fault**                   | —         | **5A1**  | **Byte(0) No fault: 00(HEX) New fault: 30,3C?,34? No fault, but saved faultcode: 14 New fault with saved fault: 1C?**|   |
| Key on (ready and not ready)     | on/off    | 412  | if(byte(0)=254) then on(1) else off(0)                                            |       |
| Lights front fog                 | on/off    | 424  | byte(0) bit 8                                                   |       |
| Lights headlights                   | on/off    | 424  | byte(1) bit 32                                                   |       |
| Lights Highbeams                    | on/off    | 424  | byte(2) bit 4                                                   |       |
| Lights Parking                      | on/off    | 424  | byte(1) bit 64                                                   |       |
| Lights Rear Fog                        | on/off    | 424  | byte(0) bit 16                                                   |       |
| Motor current                       | amps      | 696  | (byte(2) * 256 + byte(3) - 500) / 20.0                         | 3     |
| Motor rpm                           | rpm       | 298  | byte(6) * 256 + byte(7) - 10000                              |       |
| Motor temperature 0                | °C        | 298  | byte(0) - 50                                                    |       |
| Motor temperature 1                | °C        | 298  | byte(1) - 50                                                    |       |
| Motor temperature 2                | °C        | 298  | byte(2) - 50                                                    |       |
| Motor temperature 3                | °C        | 298  | byte(3) - 50                                                    |       |
| Odometer                            | km        | 412  | (byte(2) * 256 + byte(3)) * 256 + byte(4)                           | 7     |
| Outdoor air temperature             | °C        | 286  | byte(3) - 50                                                    |       |
| Rear window defrost                 | on/off    | 424  | byte(6) bit 8                                                   |       |
| Regenerative amps (negative)       | amps      | 696  | (byte(6) * 256 + byte(7) - 10000) / 5.0                                                               |       |
| Remaining range                  | km         | 346  | byte(7)                             | 1     |
| Rotation ESC                        | %         | 149  | (byte(5) * 256 + byte(4) - 32934) / 32.934                                                         |       |
| Speed                               | km/h      | 215  | (256 * byte(0) + byte(1)) / 128.0                                                   |       |
| Speed displayed                       | km/h      | 412  | byte(1)                                                   |       |
| Speed wheel 1                       | km/h      | 200  | byte(2) * 256 + byte(3) - 49152 / 19.0                                                   |       |
| Speed wheel 2                       | km/h      | 200  | byte(4) * 256 + byte(5) - 49152 / 19.0                                                    |       |
| Speed wheel 3                       | km/h      | 208  | byte(4) * 256 + byte(5) - 49152 / 19.0                                                    |       |
| Speed wheel 4                       | km/h      | 208  | byte(6) * 256 + byte(7) - 49152 / 19.0                                                    |       |
| State of Charge 1                   | %         | 374  | (byte(0) - 10.0) / 2.0                                                  |       |
| State of Charge 2                   | %         | 374  | (byte(1) - 10.0) / 2.0                                                         |       |
| Steering wheel position             | degrees   | 236  | (byte(0) * 256 + byte(1) - 4096) / 30.0                         | 1     |
| Windshield wipers             | on/off   | 424  | byte(1) bit 8                         | 1     |

## Technical tools
I use an arduino CAN-bridge to manipulate the CAN-messages. First, I had many problems with to slow transmitting rates and thus errors with the car. 
Then I discovered, that the used MCP2515 library has a huge impact on the transmitting-rate ([Performance Testing on Youtube]( https://www.youtube.com/watch?v=z1H2rj_VaRw&t=301s&pp=ygUZYXJkdWlubyBjYW4gbGlicmFyeSBzcGVlZA%3D%3D)) so i now use the [autowp-library](https://github.com/autowp/arduino-mcp2515) and everything works fine.
Just use an Arduino and two MCP2515 CAN Bus Shields and connect the ground to the car.
If you want to manipulate messages from the BMU, you have to cut the CAN-Bus wires between the BMU and the rest of the CAN-Bus wiring. You find the BMU under the rear seats on the left side.

|                        |     | 
|-------------------------------------|-----------|
|![IMG_20250807_210944 Bearbeitet](https://github.com/user-attachments/assets/a8348ba4-96c2-43db-ab68-5add5cdf1ccc)|![IMG_20250807_210956 Kopie](https://github.com/user-attachments/assets/6113c815-8952-4030-9fb4-ac29af269f82)|

## Hacking/Customisation

### Change Charging Voltage
If you want to change the maximum charging-voltage, you can use the "cell maximum voltage" for that. It seems as if the charger gets the charging current command from the ECU and alway tries to charge to 4.1 volt on the max cell. If you only want to charge till 3.9 Volt, you can use the CAN-bridge and change the "cell maximum voltage" by using the provided code.

### Change max. regenerative current/charging current
To change the charging and regenerative braking current it's possible to manipulate the battery min or max temperature PID. That is very important if you have upgraded the battery to for example CATL 93 Ah cells, because these cells are not made for charging below 0 °C and can be damaged. 
Normaly, the car charges the battery till -24 °C:
| Table "Regen current"                         |  Graph "Regen current"    | 
|-------------------------------------|-----------|
| <img width="331" height="294" alt="Bildschirmfoto 2025-08-05 um 23 22 15" src="https://github.com/user-attachments/assets/d455c6cc-3274-43b5-8453-d4adda832c38" /> | <img width="520" height="294" alt="Bildschirmfoto 2025-08-05 um 23 09 38" src="https://github.com/user-attachments/assets/67093c09-abf3-4d72-89ef-a3735e128bd3" />
  |

| Table "Chademo current"                         |  Graph "Chademo current"    | 
|-------------------------------------|-----------|
| <img width="331" height="294" alt="Bildschirmfoto 2025-08-06 um 15 23 50" src="https://github.com/user-attachments/assets/23e6b7be-eecd-4174-b8dc-c9f8f283f046" />| <img width="520" height="294" alt="Bildschirmfoto 2025-08-06 um 15 25 37" src="https://github.com/user-attachments/assets/abab608b-695c-42f3-99b7-c210a2a95886" />
 |
You can use the provided code to change the CAN-messages. Be carefull: If you change the bytes, the battery is no longer supervised and and can overheat or overcool. So change the code for your needs and always be sure, that the battery temperature stays on a save level!
