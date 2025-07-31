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

### CAN-Bus messages description
Mostly found on [myimiev Forum](https://myimiev.com/threads/decyphering-imiev-and-ion-car-can-message-data.763/page-7)

| Message (HEX) | timing (FPS) | Origin (ECU) | Byte 0 | Byte 1 | Byte 2 | Byte 3 | Byte 4 | Byte 5 | Byte 6 | Byte 7 |
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| Header | Title | Title | Title | Title | Title | Title | Title | Title | Title |
| Paragraph | Text | Title | Title | Title | Title | Title | Title | Title | Title |
