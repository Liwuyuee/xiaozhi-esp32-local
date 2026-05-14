/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>

/*
      ======================== USB Device ========================

        +++++++++++++++++ Device Information ++++++++++++++++++
Device Description       : Logi USB Camera (C270 HD WebCam)
Device ID                : USB\VID_046D&PID_0825\E190CC90
Hardware IDs             : USB\VID_046D&PID_0825&REV_0012 USB\VID_046D&PID_0825
Driver KeyName           : {36fc9e60-c465-11cf-8056-444553540000}\0084 (GUID_DEVCLASS_USB)
Driver                   : \SystemRoot\System32\drivers\usbccgp.sys (Version: 10.0.19041.4474  Date: 2024-06-13)
Driver Inf               : C:\Windows\inf\oem102.inf
Legacy BusType           : PNPBus
Class                    : USB
Class GUID               : {36fc9e60-c465-11cf-8056-444553540000} (GUID_DEVCLASS_USB)
Service                  : usbccgp
Enumerator               : USB
Location Info            : Port_#0007.Hub_#0013
Location IDs             : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(1)#USB(3)#USB(7), ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(1)#USB(3)#USB(7)
Container ID             : {3e8be164-67c8-544f-83b8-ffdd10fc0add}
Manufacturer Info        : Logitech
Capabilities             : 0x94 (Removable, UniqueID, SurpriseRemovalOK)
Status                   : 0x0180600A (DN_DRIVER_LOADED, DN_STARTED, DN_DISABLEABLE, DN_REMOVABLE, DN_NT_ENUMERATOR, DN_NT_DRIVER)
Problem Code             : 0
Address                  : 7
HcDisableSelectiveSuspend: 0
EnableSelectiveSuspend   : 0
SelectiveSuspendEnabled  : 0
EnhancedPowerMgmtEnabled : 0
IdleInWorkingState       : 0
WakeFromSleepState       : 0
Power State              : D0 (supported: D0, D3, wake from D0)
 Child Device 1          : Logi C270 HD WebCam
  Device Path            : \\?\USB#VID_046D&PID_0825&MI_00#7&40544e5&1&0000#{e5323777-f976-4f5b-9b55-b94699c46e44}\global (STATIC_KSCATEGORY_VIDEO_CAMERA)
  Kernel Name            : \Device\00000358
  Device ID              : USB\VID_046D&PID_0825&MI_00\7&40544E5&1&0000
  Class                  : Camera
  Driver KeyName         : {ca3e7ab9-b4c3-4ae6-8251-579ef933890f}\0002 (GUID_DEVCLASS_CAMERA)
  Service                : usbvideo
  Location               : 0005.0000.0004.001.003.001.003.007.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(1)#USB(3)#USB(7)#USBMI(0)  PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(1)#USB(3)#USB(7)#USB(7)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(1)#USB(3)#USB(7)#USBMI(0)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(1)#USB(3)#USB(7)#USB(7)
 Child Device 2          : Logi C270 HD WebCam
  Device Path            : \\?\USB#VID_046D&PID_0825&MI_02#7&40544e5&1&0002#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global (AM_KSCATEGORY_CAPTURE)
  Kernel Name            : \Device\00000359
  Device ID              : USB\VID_046D&PID_0825&MI_02\7&40544E5&1&0002
  Class                  : MEDIA
  Driver KeyName         : {4d36e96c-e325-11ce-bfc1-08002be10318}\0007 (GUID_DEVCLASS_MEDIA)
  Service                : usbaudio
  Location               : 0005.0000.0004.001.003.001.003.007.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(1)#USB(3)#USB(7)#USBMI(2)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(1)#USB(3)#USB(7)#USBMI(2)
   Child Device 1        : Microphone (Logi C270 HD WebCam) (Audio Endpoint)
    Device ID            : SWD\MMDEVAPI\{0.0.1.00000000}.{1F697205-E0F8-4820-97E4-7E3AB271EEDD}
    Class                : AudioEndpoint
    Driver KeyName       : {c166523c-fe0c-4a94-a586-f1a80cfbbf3e}\0027 (AUDIOENDPOINT_CLASS_UUID)

        +++++++++++++++++ Registry USB Flags +++++++++++++++++
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\usbflags\046D08250012
 osvc                    : REG_BINARY 00 00
 NewInterfaceUsage       : REG_DWORD 00000000 (0)

        ---------------- Connection Information ---------------
Connection Index         : 0x07 (Port 7)
Connection Status        : 0x01 (DeviceConnected)
Current Config Value     : 0x01 (Configuration 1)
Device Address           : 0x0F (15)
Is Hub                   : 0x00 (no)
Device Bus Speed         : 0x02 (High-Speed)
Number Of Open Pipes     : 0x01 (1 pipe to data endpoints)
Pipe[0]                  : EndpointID=7  Direction=IN   ScheduleOffset=0  Type=Interrupt
Data (HexDump)           : 07 00 00 00 12 01 00 02 EF 02 01 40 6D 04 25 08   ...........@m.%.
                           12 00 00 00 02 01 01 02 00 0F 00 01 00 00 00 01   ................
                           00 00 00 07 05 87 03 10 00 08 00 00 00 00         ..............

        --------------- Connection Information V2 -------------
Connection Index         : 0x07 (7)
Length                   : 0x10 (16 bytes)
SupportedUsbProtocols    : 0x03
 Usb110                  : 1 (yes, port supports USB 1.1)
 Usb200                  : 1 (yes, port supports USB 2.0)
 Usb300                  : 0 (no, port not supports USB 3.0)
 ReservedMBZ             : 0x00
Flags                    : 0x00
 DevIsOpAtSsOrHigher     : 0 (Device is not operating at SuperSpeed or higher)
 DevIsSsCapOrHigher      : 0 (Device is not SuperSpeed capable or higher)
 DevIsOpAtSsPlusOrHigher : 0 (Device is not operating at SuperSpeedPlus or higher)
 DevIsSsPlusCapOrHigher  : 0 (Device is not SuperSpeedPlus capable or higher)
 ReservedMBZ             : 0x00
Data (HexDump)           : 07 00 00 00 10 00 00 00 03 00 00 00 00 00 00 00   ................

    ---------------------- Device Descriptor ----------------------
bLength                  : 0x12 (18 bytes)
bDescriptorType          : 0x01 (Device Descriptor)
bcdUSB                   : 0x200 (USB Version 2.00)
bDeviceClass             : 0xEF (Miscellaneous)
bDeviceSubClass          : 0x02
bDeviceProtocol          : 0x01 (IAD - Interface Association Descriptor)
bMaxPacketSize0          : 0x40 (64 bytes)
idVendor                 : 0x046D (Logitech Inc.)
idProduct                : 0x0825
bcdDevice                : 0x0012
iManufacturer            : 0x00 (No String Descriptor)
iProduct                 : 0x00 (No String Descriptor)
iSerialNumber            : 0x02 (String Descriptor 2)
 Language 0x0409         : "E190CC90"
bNumConfigurations       : 0x01 (1 Configuration)
Data (HexDump)           : 12 01 00 02 EF 02 01 40 6D 04 25 08 12 00 00 00   .......@m.%.....
                           02 01                                             ..

    ------------------ Configuration Descriptor -------------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x02 (Configuration Descriptor)
wTotalLength             : 0x09A2 (2466 bytes)
bNumInterfaces           : 0x04 (4 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x00 (No String Descriptor)
bmAttributes             : 0x80
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x00 (no)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0xFA (500 mA)
Data (HexDump)           : 09 02 A2 09 04 01 00 80 FA 08 0B 00 02 0E 03 00   ................
                           00 09 04 00 00 01 0E 01 00 00 0D 24 01 00 01 A0   ...........$....
                           00 00 6C DC 02 01 01 12 24 02 01 01 02 00 00 00   ..l.....$.......
                           00 00 00 00 00 03 0E 00 00 0B 24 05 02 01 00 40   ..........$....@
                           02 5B 17 00 1B 24 06 03 E4 8E 67 69 0F 41 DB 40   .[...$....gi.A.@
                           A8 50 74 20 D7 D8 24 0E 08 01 02 02 3F 03 00 1B   .Pt ..$.....?...
                           24 06 04 15 02 E4 49 34 F4 FE 47 B1 58 0E 88 50   $.....I4..G.X..P
                           23 E5 1B 03 01 02 02 09 01 00 1C 24 06 06 A9 4C   #..........$...L
                           5D 1F 11 DE 87 44 84 0D 50 93 3C 8E C8 D1 12 01   ]....D..P.<.....
                           04 03 FF FF 03 00 1B 24 06 07 21 2D E5 FF 30 80   .......$..!-..0.
                           2C 4E 82 D9 F5 87 D0 05 40 BD 02 01 04 02 00 03   ,N......@.......
                           00 09 24 03 05 01 01 00 04 00 07 05 87 03 10 00   ..$.............
                           08 05 25 03 10 00 09 04 01 00 00 0E 02 00 00 10   ..%.............
                           24 01 03 36 07 81 00 05 01 00 00 01 00 04 04 1B   $..6............
                           24 04 01 13 59 55 59 32 00 00 10 00 80 00 00 AA   $...YUY2........
                           00 38 9B 71 10 01 00 00 00 00 32 24 05 01 01 80   .8.q......2$....
                           02 E0 01 00 00 77 01 00 00 CA 08 00 60 09 00 15   .....w......`...
                           16 05 00 06 15 16 05 00 80 1A 06 00 20 A1 07 00   ............ ...
                           2A 2C 0A 00 40 42 0F 00 80 84 1E 00 32 24 05 02   *,..@B......2$..
                           01 A0 00 78 00 00 70 17 00 00 A0 8C 00 00 96 00   ...x..p.........
                           00 15 16 05 00 06 15 16 05 00 80 1A 06 00 20 A1   .............. .
                           07 00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00 32 24   ..*,..@B......2$
                           05 03 01 B0 00 90 00 00 F0 1E 00 00 A0 B9 00 00   ................
                           C6 00 00 15 16 05 00 06 15 16 05 00 80 1A 06 00   ................
                           20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00    ...*,..@B......
                           32 24 05 04 01 40 01 B0 00 00 C0 44 00 00 80 9C   2$...@.....D....
                           01 00 B8 01 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00 32 24 05 05 01 40 01 F0 00 00 C0 5D 00 00   ..2$...@.....]..
                           80 32 02 00 58 02 00 15 16 05 00 06 15 16 05 00   .2..X...........
                           80 1A 06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00   .... ...*,..@B..
                           80 84 1E 00 32 24 05 06 01 60 01 20 01 00 C0 7B   ....2$...`. ...{
                           00 00 80 E6 02 00 18 03 00 15 16 05 00 06 15 16   ................
                           05 00 80 1A 06 00 20 A1 07 00 2A 2C 0A 00 40 42   ...... ...*,..@B
                           0F 00 80 84 1E 00 32 24 05 07 01 B0 01 F0 00 00   ......2$........
                           90 7E 00 00 60 F7 02 00 2A 03 00 15 16 05 00 06   .~..`...*.......
                           15 16 05 00 80 1A 06 00 20 A1 07 00 2A 2C 0A 00   ........ ...*,..
                           40 42 0F 00 80 84 1E 00 32 24 05 08 01 20 02 20   @B......2$... .
                           01 00 40 BF 00 00 80 7B 04 00 C8 04 00 15 16 05   ..@....{........
                           00 06 15 16 05 00 80 1A 06 00 20 A1 07 00 2A 2C   .......... ...*,
                           0A 00 40 42 0F 00 80 84 1E 00 32 24 05 09 01 80   ..@B......2$....
                           02 68 01 00 40 19 01 00 80 97 06 00 08 07 00 15   .h..@...........
                           16 05 00 06 15 16 05 00 80 1A 06 00 20 A1 07 00   ............ ...
                           2A 2C 0A 00 40 42 0F 00 80 84 1E 00 2E 24 05 0A   *,..@B.......$..
                           01 F0 02 A0 01 00 E0 7D 01 00 60 75 07 00 8C 09   .......}..`u....
                           00 80 1A 06 00 05 80 1A 06 00 20 A1 07 00 2A 2C   .......... ...*,
                           0A 00 40 42 0F 00 80 84 1E 00 2A 24 05 0B 01 20   ..@B......*$...
                           03 C0 01 00 80 B5 01 00 00 D6 06 00 F0 0A 00 20   ...............
                           A1 07 00 04 20 A1 07 00 2A 2C 0A 00 40 42 0F 00   .... ...*,..@B..
                           80 84 1E 00 2A 24 05 0C 01 20 03 58 02 00 F0 49   ....*$... .X...I
                           02 00 C0 27 09 00 A6 0E 00 20 A1 07 00 04 20 A1   ...'..... .... .
                           07 00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00 2A 24   ..*,..@B......*$
                           05 0D 01 60 03 E0 01 00 40 FA 01 00 00 E9 07 00   ...`....@.......
                           A8 0C 00 20 A1 07 00 04 20 A1 07 00 2A 2C 0A 00   ... .... ...*,..
                           40 42 0F 00 80 84 1E 00 26 24 05 0E 01 C0 03 20   @B......&$.....
                           02 00 80 7D 02 00 80 78 07 00 F0 0F 00 2A 2C 0A   ...}...x.....*,.
                           00 03 2A 2C 0A 00 40 42 0F 00 80 84 1E 00 22 24   ..*,..@B......"$
                           05 0F 01 C0 03 D0 02 00 C0 4B 03 00 80 97 06 00   .........K......
                           18 15 00 40 42 0F 00 02 40 42 0F 00 80 84 1E 00   ...@B...@B......
                           22 24 05 10 01 00 04 40 02 00 00 D0 02 00 00 A0   "$.....@........
                           05 00 00 12 00 40 42 0F 00 02 40 42 0F 00 80 84   .....@B...@B....
                           1E 00 22 24 05 11 01 A0 04 90 02 00 20 B4 03 00   .."$........ ...
                           40 68 07 00 B4 17 00 40 42 0F 00 02 40 42 0F 00   @h.....@B...@B..
                           80 84 1E 00 22 24 05 12 01 00 05 D0 02 00 00 65   ...."$.........e
                           04 00 00 CA 08 00 20 1C 00 80 84 1E 00 02 55 58   ...... .......UX
                           14 00 80 84 1E 00 22 24 05 13 01 00 05 C0 03 00   ......"$........
                           00 DC 05 00 00 B8 0B 00 80 25 00 80 84 1E 00 02   .........%......
                           55 58 14 00 80 84 1E 00 06 24 0D 01 01 04 0B 24   UX.......$.....$
                           06 02 13 01 01 00 00 00 00 32 24 07 01 01 80 02   .........2$.....
                           E0 01 00 00 77 01 00 00 CA 08 00 60 09 00 15 16   ....w......`....
                           05 00 06 15 16 05 00 80 1A 06 00 20 A1 07 00 2A   ........... ...*
                           2C 0A 00 40 42 0F 00 80 84 1E 00 32 24 07 02 01   ,..@B......2$...
                           A0 00 78 00 00 70 17 00 00 A0 8C 00 00 96 00 00   ..x..p..........
                           15 16 05 00 06 15 16 05 00 80 1A 06 00 20 A1 07   ............. ..
                           00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00 32 24 07   .*,..@B......2$.
                           03 01 B0 00 90 00 00 F0 1E 00 00 A0 B9 00 00 C6   ................
                           00 00 15 16 05 00 06 15 16 05 00 80 1A 06 00 20   ...............
                           A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00 32   ...*,..@B......2
                           24 07 04 01 40 01 B0 00 00 C0 44 00 00 80 9C 01   $...@.....D.....
                           00 B8 01 00 15 16 05 00 06 15 16 05 00 80 1A 06   ................
                           00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84 1E   . ...*,..@B.....
                           00 32 24 07 05 01 40 01 F0 00 00 C0 5D 00 00 80   .2$...@.....]...
                           32 02 00 58 02 00 15 16 05 00 06 15 16 05 00 80   2..X............
                           1A 06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80   ... ...*,..@B...
                           84 1E 00 32 24 07 06 01 60 01 20 01 00 C0 7B 00   ...2$...`. ...{.
                           00 80 E6 02 00 18 03 00 15 16 05 00 06 15 16 05   ................
                           00 80 1A 06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F   ..... ...*,..@B.
                           00 80 84 1E 00 32 24 07 07 01 B0 01 F0 00 00 90   .....2$.........
                           7E 00 00 60 F7 02 00 2A 03 00 15 16 05 00 06 15   ~..`...*........
                           16 05 00 80 1A 06 00 20 A1 07 00 2A 2C 0A 00 40   ....... ...*,..@
                           42 0F 00 80 84 1E 00 32 24 07 08 01 20 02 20 01   B......2$... . .
                           00 40 BF 00 00 80 7B 04 00 C8 04 00 15 16 05 00   .@....{.........
                           06 15 16 05 00 80 1A 06 00 20 A1 07 00 2A 2C 0A   ......... ...*,.
                           00 40 42 0F 00 80 84 1E 00 32 24 07 09 01 80 02   .@B......2$.....
                           68 01 00 40 19 01 00 80 97 06 00 08 07 00 15 16   h..@............
                           05 00 06 15 16 05 00 80 1A 06 00 20 A1 07 00 2A   ........... ...*
                           2C 0A 00 40 42 0F 00 80 84 1E 00 32 24 07 0A 01   ,..@B......2$...
                           F0 02 A0 01 00 E0 7D 01 00 40 F3 08 00 8C 09 00   ......}..@......
                           15 16 05 00 06 15 16 05 00 80 1A 06 00 20 A1 07   ............. ..
                           00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00 32 24 07   .*,..@B......2$.
                           0B 01 20 03 C0 01 00 80 B5 01 00 00 41 0A 00 F0   .. .........A...
                           0A 00 15 16 05 00 06 15 16 05 00 80 1A 06 00 20   ...............
                           A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00 32   ...*,..@B......2
                           24 07 0C 01 20 03 58 02 00 F0 49 02 00 A0 BB 0D   $... .X...I.....
                           00 A6 0E 00 15 16 05 00 06 15 16 05 00 80 1A 06   ................
                           00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84 1E   . ...*,..@B.....
                           00 32 24 07 0D 01 60 03 E0 01 00 40 FA 01 00 80   .2$...`....@....
                           DD 0B 00 A8 0C 00 15 16 05 00 06 15 16 05 00 80   ................
                           1A 06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80   ... ...*,..@B...
                           84 1E 00 32 24 07 0E 01 C0 03 20 02 00 80 7D 02   ...2$..... ...}.
                           00 00 F1 0E 00 F0 0F 00 15 16 05 00 06 15 16 05   ................
                           00 80 1A 06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F   ..... ...*,..@B.
                           00 80 84 1E 00 32 24 07 0F 01 C0 03 D0 02 00 C0   .....2$.........
                           4B 03 00 80 C6 13 00 18 15 00 15 16 05 00 06 15   K...............
                           16 05 00 80 1A 06 00 20 A1 07 00 2A 2C 0A 00 40   ....... ...*,..@
                           42 0F 00 80 84 1E 00 32 24 07 10 01 00 04 40 02   B......2$.....@.
                           00 00 D0 02 00 00 E0 10 00 00 12 00 15 16 05 00   ................
                           06 15 16 05 00 80 1A 06 00 20 A1 07 00 2A 2C 0A   ......... ...*,.
                           00 40 42 0F 00 80 84 1E 00 32 24 07 11 01 A0 04   .@B......2$.....
                           90 02 00 20 B4 03 00 C0 38 16 00 B4 17 00 15 16   ... ....8.......
                           05 00 06 15 16 05 00 80 1A 06 00 20 A1 07 00 2A   ........... ...*
                           2C 0A 00 40 42 0F 00 80 84 1E 00 32 24 07 12 01   ,..@B......2$...
                           00 05 D0 02 00 00 65 04 00 00 5E 1A 00 20 1C 00   ......e...^.. ..
                           15 16 05 00 06 15 16 05 00 80 1A 06 00 20 A1 07   ............. ..
                           00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00 32 24 07   .*,..@B......2$.
                           13 01 00 05 C0 03 00 00 DC 05 00 00 28 23 00 80   ............(#..
                           25 00 15 16 05 00 06 15 16 05 00 80 1A 06 00 20   %..............
                           A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00 06   ...*,..@B.......
                           24 0D 01 01 04 09 04 01 01 01 0E 02 00 00 07 05   $...............
                           81 05 C0 00 01 09 04 01 02 01 0E 02 00 00 07 05   ................
                           81 05 80 01 01 09 04 01 03 01 0E 02 00 00 07 05   ................
                           81 05 00 02 01 09 04 01 04 01 0E 02 00 00 07 05   ................
                           81 05 80 02 01 09 04 01 05 01 0E 02 00 00 07 05   ................
                           81 05 20 03 01 09 04 01 06 01 0E 02 00 00 07 05   .. .............
                           81 05 B0 03 01 09 04 01 07 01 0E 02 00 00 07 05   ................
                           81 05 80 0A 01 09 04 01 08 01 0E 02 00 00 07 05   ................
                           81 05 20 0B 01 09 04 01 09 01 0E 02 00 00 07 05   .. .............
                           81 05 E0 0B 01 09 04 01 0A 01 0E 02 00 00 07 05   ................
                           81 05 80 13 01 09 04 01 0B 01 0E 02 00 00 07 05   ................
                           81 05 FC 13 01 08 0B 02 02 01 02 00 00 09 04 02   ................
                           00 00 01 01 00 00 09 24 01 00 01 26 00 01 03 0C   .......$...&....
                           24 02 01 01 02 00 01 00 00 00 00 09 24 03 03 01   $...........$...
                           01 01 05 00 09 24 06 05 01 01 03 00 00 09 04 03   .....$..........
                           00 00 01 02 00 00 09 04 03 01 01 01 02 00 00 07   ................
                           24 01 03 01 01 00 0B 24 02 01 01 02 10 01 80 3E   $......$.......>
                           00 09 05 86 05 44 00 04 00 00 07 25 01 01 00 00   .....D.....%....
                           00 09 04 03 02 01 01 02 00 00 07 24 01 03 01 01   ...........$....
                           00 0B 24 02 01 01 02 10 01 C0 5D 00 09 05 86 05   ..$.......].....
                           64 00 04 00 00 07 25 01 01 00 00 00 09 04 03 03   d.....%.........
                           01 01 02 00 00 07 24 01 03 01 01 00 0B 24 02 01   ......$......$..
                           01 02 10 01 00 7D 00 09 05 86 05 84 00 04 00 00   .....}..........
                           07 25 01 01 00 00 00 09 04 03 04 01 01 02 00 00   .%..............
                           07 24 01 03 01 01 00 0B 24 02 01 01 02 10 01 80   .$......$.......
                           BB 00 09 05 86 05 C4 00 04 00 00 07 25 01 01 00   ............%...
                           00 00                                             ..

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x00
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x00 (No String Descriptor)
Data (HexDump)           : 08 0B 00 02 0E 03 00 00                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x00
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 00 00 01 0E 01 00 00                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0100 (UVC Version 1.00)
wTotalLength             : 0x00A0 (160 bytes)
dwClockFreq              : 0x02DC6C00 (48 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x01
Data (HexDump)           : 0D 24 01 00 01 A0 00 00 6C DC 02 01 01            .$......l....

        -------- Video Control Input Terminal Descriptor ------
bLength                  : 0x12 (18 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x02 (Input Terminal)
bTerminalID              : 0x01
wTerminalType            : 0x0201 (ITT_CAMERA)
bAssocTerminal           : 0x00 (Not associated with an Output Terminal)
iTerminal                : 0x00
Camera Input Terminal Data:
wObjectiveFocalLengthMin : 0x0000
wObjectiveFocalLengthMax : 0x0000
wOcularFocalLength       : 0x0000
bControlSize             : 0x03
bmControls               : 0x0E, 0x00, 0x00
 D0                      : 0   no -  Scanning Mode
 D1                      : 1  yes -  Auto-Exposure Mode
 D2                      : 1  yes -  Auto-Exposure Priority
 D3                      : 1  yes -  Exposure Time (Absolute)
 D4                      : 0   no -  Exposure Time (Relative)
 D5                      : 0   no -  Focus (Absolute)
 D6                      : 0   no -  Focus (Relative)
 D7                      : 0   no -  Iris (Absolute)
 D8                      : 0   no -  Iris (Relative)
 D9                      : 0   no -  Zoom (Absolute)
 D10                     : 0   no -  Zoom (Relative)
 D11                     : 0   no -  Pan (Absolute)
 D12                     : 0   no -  Pan (Relative)
 D13                     : 0   no -  Roll (Absolute)
 D14                     : 0   no -  Roll (Relative)
 D15                     : 0   no -  Tilt (Absolute)
 D16                     : 0   no -  Tilt (Relative)
 D17                     : 0   no -  Focus Auto
 D18                     : 0   no -  Reserved
 D19                     : 0   no -  Reserved
 D20                     : 0   no -  Reserved
 D21                     : 0   no -  Reserved
 D22                     : 0   no -  Reserved
 D23                     : 0   no -  Reserved
Data (HexDump)           : 12 24 02 01 01 02 00 00 00 00 00 00 00 00 03 0E   .$..............
                           00 00                                             ..

        -------- Video Control Processing Unit Descriptor -----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x05 (Processing Unit)
bUnitID                  : 0x02
bSourceID                : 0x01
wMaxMultiplier           : 0x4000 (163.84x Zoom)
bControlSize             : 0x02
bmControls               : 0x5B, 0x17
 D0                      : 1  yes -  Brightness
 D1                      : 1  yes -  Contrast
 D2                      : 0   no -  Hue
 D3                      : 1  yes -  Saturation
 D4                      : 1  yes -  Sharpness
 D5                      : 0   no -  Gamma
 D6                      : 1  yes -  White Balance Temperature
 D7                      : 0   no -  White Balance Component
 D8                      : 1  yes -  Backlight Compensation
 D9                      : 1  yes -  Gain
 D10                     : 1  yes -  Power Line Frequency
 D11                     : 0   no -  Hue, Auto
 D12                     : 1  yes -  White Balance Temperature, Auto
 D13                     : 0   no -  White Balance Component, Auto
 D14                     : 0   no -  Digital Multiplier
 D15                     : 0   no -  Digital Multiplier Limit
iProcessing              : 0x00
Data (HexDump)           : 0B 24 05 02 01 00 40 02 5B 17 00                  .$....@.[..

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x03
guidExtensionCode        : {69678EE4-410F-40DB-A850-7420D7D8240E}
bNumControls             : 0x08
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x02
bmControls               : 0x3F, 0x03
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 1  yes -  Vendor-Specific (Optional)
 D3                      : 1  yes -  Vendor-Specific (Optional)
 D4                      : 1  yes -  Vendor-Specific (Optional)
 D5                      : 1  yes -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
 D8                      : 1  yes -  Vendor-Specific (Optional)
 D9                      : 1  yes -  Vendor-Specific (Optional)
 D10                     : 0   no -  Vendor-Specific (Optional)
 D11                     : 0   no -  Vendor-Specific (Optional)
 D12                     : 0   no -  Vendor-Specific (Optional)
 D13                     : 0   no -  Vendor-Specific (Optional)
 D14                     : 0   no -  Vendor-Specific (Optional)
 D15                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1B 24 06 03 E4 8E 67 69 0F 41 DB 40 A8 50 74 20   .$....gi.A.@.Pt
                           D7 D8 24 0E 08 01 02 02 3F 03 00                  ..$.....?..

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x04
guidExtensionCode        : {49E40215-F434-47FE-B158-0E885023E51B}
bNumControls             : 0x03
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x02
bmControls               : 0x09, 0x01
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 0   no -  Vendor-Specific (Optional)
 D2                      : 0   no -  Vendor-Specific (Optional)
 D3                      : 1  yes -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
 D8                      : 1  yes -  Vendor-Specific (Optional)
 D9                      : 0   no -  Vendor-Specific (Optional)
 D10                     : 0   no -  Vendor-Specific (Optional)
 D11                     : 0   no -  Vendor-Specific (Optional)
 D12                     : 0   no -  Vendor-Specific (Optional)
 D13                     : 0   no -  Vendor-Specific (Optional)
 D14                     : 0   no -  Vendor-Specific (Optional)
 D15                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1B 24 06 04 15 02 E4 49 34 F4 FE 47 B1 58 0E 88   .$.....I4..G.X..
                           50 23 E5 1B 03 01 02 02 09 01 00                  P#.........

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x06
guidExtensionCode        : {1F5D4CA9-DE11-4487-840D-50933C8EC8D1}
bNumControls             : 0x12
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x04
bControlSize             : 0x03
bmControls               : 0xFF, 0xFF, 0x03
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 1  yes -  Vendor-Specific (Optional)
 D3                      : 1  yes -  Vendor-Specific (Optional)
 D4                      : 1  yes -  Vendor-Specific (Optional)
 D5                      : 1  yes -  Vendor-Specific (Optional)
 D6                      : 1  yes -  Vendor-Specific (Optional)
 D7                      : 1  yes -  Vendor-Specific (Optional)
 D8                      : 1  yes -  Vendor-Specific (Optional)
 D9                      : 1  yes -  Vendor-Specific (Optional)
 D10                     : 1  yes -  Vendor-Specific (Optional)
 D11                     : 1  yes -  Vendor-Specific (Optional)
 D12                     : 1  yes -  Vendor-Specific (Optional)
 D13                     : 1  yes -  Vendor-Specific (Optional)
 D14                     : 1  yes -  Vendor-Specific (Optional)
 D15                     : 1  yes -  Vendor-Specific (Optional)
 D16                     : 1  yes -  Vendor-Specific (Optional)
 D17                     : 1  yes -  Vendor-Specific (Optional)
 D18                     : 0   no -  Vendor-Specific (Optional)
 D19                     : 0   no -  Vendor-Specific (Optional)
 D20                     : 0   no -  Vendor-Specific (Optional)
 D21                     : 0   no -  Vendor-Specific (Optional)
 D22                     : 0   no -  Vendor-Specific (Optional)
 D23                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1C 24 06 06 A9 4C 5D 1F 11 DE 87 44 84 0D 50 93   .$...L]....D..P.
                           3C 8E C8 D1 12 01 04 03 FF FF 03 00               <...........

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x07
guidExtensionCode        : {FFE52D21-8030-4E2C-82D9-F587D00540BD}
bNumControls             : 0x02
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x04
bControlSize             : 0x02
bmControls               : 0x00, 0x03
 D0                      : 0   no -  Vendor-Specific (Optional)
 D1                      : 0   no -  Vendor-Specific (Optional)
 D2                      : 0   no -  Vendor-Specific (Optional)
 D3                      : 0   no -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
 D8                      : 1  yes -  Vendor-Specific (Optional)
 D9                      : 1  yes -  Vendor-Specific (Optional)
 D10                     : 0   no -  Vendor-Specific (Optional)
 D11                     : 0   no -  Vendor-Specific (Optional)
 D12                     : 0   no -  Vendor-Specific (Optional)
 D13                     : 0   no -  Vendor-Specific (Optional)
 D14                     : 0   no -  Vendor-Specific (Optional)
 D15                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1B 24 06 07 21 2D E5 FF 30 80 2C 4E 82 D9 F5 87   .$..!-..0.,N....
                           D0 05 40 BD 02 01 04 02 00 03 00                  ..@........

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x05
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x04
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 05 01 01 00 04 00                        .$.......

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x87 (Direction=IN EndpointID=7)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0010
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x10 (16 bytes per packet)
bInterval                : 0x08 (8 ms)
Data (HexDump)           : 07 05 87 03 10 00 08                              .......

        --- Class-specific VC Interrupt Endpoint Descriptor ---
bLength                  : 0x05 (5 bytes)
bDescriptorType          : 0x25 (Video Control Endpoint)
bDescriptorSubtype       : 0x03 (Interrupt)
wMaxTransferSize         : 0x0010 (16 bytes)
Data (HexDump)           : 05 25 03 10 00                                    .%...

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 00 00 0E 02 00 00                        .........

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x10 (16 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x03
wTotalLength             : 0x0736 (1846 bytes)
bEndpointAddress         : 0x81 (Direction=IN  EndpointID=1)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x05
bStillCaptureMethod      : 0x01 (Still Capture Method 1)
nbTriggerSupport         : 0x00 (Hardware Triggering not supported)
bTriggerUsage            : 0x00 (Host will initiate still image capture)
nbControlSize            : 0x01
Video Payload Format 1   : 0x00
 D0                      : 0   no -  Key Frame Rate
 D1                      : 0   no -  P Frame Rate
 D2                      : 0   no -  Compression Quality
 D3                      : 0   no -  Compression Window Size
 D4                      : 0   no -  Generate Key Frame
 D5                      : 0   no -  Update Frame Segment
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Video Payload Format 2   : 0x04
 D0                      : 0   no -  Key Frame Rate
 D1                      : 0   no -  P Frame Rate
 D2                      : 1  yes -  Compression Quality
 D3                      : 0   no -  Compression Window Size
 D4                      : 0   no -  Generate Key Frame
 D5                      : 0   no -  Update Frame Segment
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Video Payload Format 3   : 0x04
 D0                      : 0   no -  Key Frame Rate
 D1                      : 0   no -  P Frame Rate
 D2                      : 1  yes -  Compression Quality
 D3                      : 0   no -  Compression Window Size
 D4                      : 0   no -  Generate Key Frame
 D5                      : 0   no -  Update Frame Segment
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Data (HexDump)           : 10 24 01 03 36 07 81 00 05 01 00 00 01 00 04 04   .$..6...........

        ------- VS Uncompressed Format Type Descriptor --------
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x04 (Uncompressed Format Type)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x13 (19)
guidFormat               : {32595559-0000-0010-8000-00AA00389B71} (YUY2)
bBitsPerPixel            : 0x10 (16 bits)
bDefaultFrameIndex       : 0x01 (1)
bAspectRatioX            : 0x00
bAspectRatioY            : 0x00
bmInterlaceFlags         : 0x00
 D0 IL stream or variable: 0 (no)
 D1 Fields per frame     : 0 (2 fields)
 D2 Field 1 first        : 0 (no)
 D3 Reserved             : 0
 D4..5 Field pattern     : 0 (Field 1 only)
 D6..7 Display Mode      : 0 (Bob only)
bCopyProtect             : 0x00 (No restrictions)
Data (HexDump)           : 1B 24 04 01 13 59 55 59 32 00 00 10 00 80 00 00   .$...YUY2.......
                           AA 00 38 9B 71 10 01 00 00 00 00                  ..8.q......

        -------- VS Uncompressed Frame Type Descriptor --------
---> This is the Default (optimum) Frame index
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x01
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x01770000 (24576000 bps -> 3.72 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x00096000 (614400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 05 01 01 80 02 E0 01 00 00 77 01 00 00 CA   2$.........w....
                           08 00 60 09 00 15 16 05 00 06 15 16 05 00 80 1A   ..`.............
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x01
wWidth                   : 0x00A0 (160)
wHeight                  : 0x0078 (120)
dwMinBitRate             : 0x00177000 (1536000 bps -> 192 KB/s)
dwMaxBitRate             : 0x008CA000 (9216000 bps -> 1.152 MB/s)
dwMaxVideoFrameBufferSize: 0x00009600 (38400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 05 02 01 A0 00 78 00 00 70 17 00 00 A0 8C   2$.....x..p.....
                           00 00 96 00 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x01
wWidth                   : 0x00B0 (176)
wHeight                  : 0x0090 (144)
dwMinBitRate             : 0x001EF000 (2027520 bps -> 253.375 KB/s)
dwMaxBitRate             : 0x00B9A000 (12165120 bps -> 1.520 MB/s)
dwMaxVideoFrameBufferSize: 0x0000C600 (50688 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 05 03 01 B0 00 90 00 00 F0 1E 00 00 A0 B9   2$..............
                           00 00 C6 00 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x01
wWidth                   : 0x0140 (320)
wHeight                  : 0x00B0 (176)
dwMinBitRate             : 0x0044C000 (4505600 bps -> 563.125 KB/s)
dwMaxBitRate             : 0x019C8000 (27033600 bps -> 3.379 MB/s)
dwMaxVideoFrameBufferSize: 0x0001B800 (112640 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 05 04 01 40 01 B0 00 00 C0 44 00 00 80 9C   2$...@.....D....
                           01 00 B8 01 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x01
wWidth                   : 0x0140 (320)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x005DC000 (6144000 bps -> 768 KB/s)
dwMaxBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwMaxVideoFrameBufferSize: 0x00025800 (153600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 05 05 01 40 01 F0 00 00 C0 5D 00 00 80 32   2$...@.....]...2
                           02 00 58 02 00 15 16 05 00 06 15 16 05 00 80 1A   ..X.............
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x01
wWidth                   : 0x0160 (352)
wHeight                  : 0x0120 (288)
dwMinBitRate             : 0x007BC000 (8110080 bps -> 1.13 MB/s)
dwMaxBitRate             : 0x02E68000 (48660480 bps -> 6.82 MB/s)
dwMaxVideoFrameBufferSize: 0x00031800 (202752 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 05 06 01 60 01 20 01 00 C0 7B 00 00 80 E6   2$...`. ...{....
                           02 00 18 03 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x07
bmCapabilities           : 0x01
wWidth                   : 0x01B0 (432)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x007E9000 (8294400 bps -> 1.36 MB/s)
dwMaxBitRate             : 0x02F76000 (49766400 bps -> 6.220 MB/s)
dwMaxVideoFrameBufferSize: 0x00032A00 (207360 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 05 07 01 B0 01 F0 00 00 90 7E 00 00 60 F7   2$.........~..`.
                           02 00 2A 03 00 15 16 05 00 06 15 16 05 00 80 1A   ..*.............
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x08
bmCapabilities           : 0x01
wWidth                   : 0x0220 (544)
wHeight                  : 0x0120 (288)
dwMinBitRate             : 0x00BF4000 (12533760 bps -> 1.566 MB/s)
dwMaxBitRate             : 0x047B8000 (75202560 bps -> 9.400 MB/s)
dwMaxVideoFrameBufferSize: 0x0004C800 (313344 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 05 08 01 20 02 20 01 00 40 BF 00 00 80 7B   2$... . ..@....{
                           04 00 C8 04 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x09
bmCapabilities           : 0x01
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxVideoFrameBufferSize: 0x00070800 (460800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 05 09 01 80 02 68 01 00 40 19 01 00 80 97   2$.....h..@.....
                           06 00 08 07 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x2E (46 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x0A
bmCapabilities           : 0x01
wWidth                   : 0x02F0 (752)
wHeight                  : 0x01A0 (416)
dwMinBitRate             : 0x017DE000 (25026560 bps -> 3.128 MB/s)
dwMaxBitRate             : 0x07756000 (125132800 bps -> 15.641 MB/s)
dwMaxVideoFrameBufferSize: 0x00098C00 (625664 bytes)
dwDefaultFrameInterval   : 0x00061A80 (40.0000 ms -> 25.000 fps)
bFrameIntervalType       : 0x05 (5 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[4]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[5]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 2E 24 05 0A 01 F0 02 A0 01 00 E0 7D 01 00 60 75   .$.........}..`u
                           07 00 8C 09 00 80 1A 06 00 05 80 1A 06 00 20 A1   .............. .
                           07 00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00         ..*,..@B......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x0B
bmCapabilities           : 0x01
wWidth                   : 0x0320 (800)
wHeight                  : 0x01C0 (448)
dwMinBitRate             : 0x01B58000 (28672000 bps -> 3.584 MB/s)
dwMaxBitRate             : 0x06D60000 (114688000 bps -> 14.336 MB/s)
dwMaxVideoFrameBufferSize: 0x000AF000 (716800 bytes)
dwDefaultFrameInterval   : 0x0007A120 (50.0000 ms -> 20.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
adwFrameInterval[1]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[2]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[3]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[4]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 2A 24 05 0B 01 20 03 C0 01 00 80 B5 01 00 00 D6   *$... ..........
                           06 00 F0 0A 00 20 A1 07 00 04 20 A1 07 00 2A 2C   ..... .... ...*,
                           0A 00 40 42 0F 00 80 84 1E 00                     ..@B......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x0C
bmCapabilities           : 0x01
wWidth                   : 0x0320 (800)
wHeight                  : 0x0258 (600)
dwMinBitRate             : 0x0249F000 (38400000 bps -> 4.800 MB/s)
dwMaxBitRate             : 0x0927C000 (153600000 bps -> 19.200 MB/s)
dwMaxVideoFrameBufferSize: 0x000EA600 (960000 bytes)
dwDefaultFrameInterval   : 0x0007A120 (50.0000 ms -> 20.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
adwFrameInterval[1]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[2]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[3]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[4]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 2A 24 05 0C 01 20 03 58 02 00 F0 49 02 00 C0 27   *$... .X...I...'
                           09 00 A6 0E 00 20 A1 07 00 04 20 A1 07 00 2A 2C   ..... .... ...*,
                           0A 00 40 42 0F 00 80 84 1E 00                     ..@B......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x0D
bmCapabilities           : 0x01
wWidth                   : 0x0360 (864)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x01FA4000 (33177600 bps -> 4.147 MB/s)
dwMaxBitRate             : 0x07E90000 (132710400 bps -> 16.588 MB/s)
dwMaxVideoFrameBufferSize: 0x000CA800 (829440 bytes)
dwDefaultFrameInterval   : 0x0007A120 (50.0000 ms -> 20.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
adwFrameInterval[1]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[2]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[3]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[4]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 2A 24 05 0D 01 60 03 E0 01 00 40 FA 01 00 00 E9   *$...`....@.....
                           07 00 A8 0C 00 20 A1 07 00 04 20 A1 07 00 2A 2C   ..... .... ...*,
                           0A 00 40 42 0F 00 80 84 1E 00                     ..@B......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x0E
bmCapabilities           : 0x01
wWidth                   : 0x03C0 (960)
wHeight                  : 0x0220 (544)
dwMinBitRate             : 0x027D8000 (41779200 bps -> 5.222 MB/s)
dwMaxBitRate             : 0x07788000 (125337600 bps -> 15.667 MB/s)
dwMaxVideoFrameBufferSize: 0x000FF000 (1044480 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[2]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[3]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 26 24 05 0E 01 C0 03 20 02 00 80 7D 02 00 80 78   &$..... ...}...x
                           07 00 F0 0F 00 2A 2C 0A 00 03 2A 2C 0A 00 40 42   .....*,...*,..@B
                           0F 00 80 84 1E 00                                 ......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x0F
bmCapabilities           : 0x01
wWidth                   : 0x03C0 (960)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x034BC000 (55296000 bps -> 6.912 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxVideoFrameBufferSize: 0x00151800 (1382400 bytes)
dwDefaultFrameInterval   : 0x000F4240 (100.0000 ms -> 10.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[2]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 22 24 05 0F 01 C0 03 D0 02 00 C0 4B 03 00 80 97   "$.........K....
                           06 00 18 15 00 40 42 0F 00 02 40 42 0F 00 80 84   .....@B...@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x10
bmCapabilities           : 0x01
wWidth                   : 0x0400 (1024)
wHeight                  : 0x0240 (576)
dwMinBitRate             : 0x02D00000 (47185920 bps -> 5.898 MB/s)
dwMaxBitRate             : 0x05A00000 (94371840 bps -> 11.796 MB/s)
dwMaxVideoFrameBufferSize: 0x00120000 (1179648 bytes)
dwDefaultFrameInterval   : 0x000F4240 (100.0000 ms -> 10.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[2]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 22 24 05 10 01 00 04 40 02 00 00 D0 02 00 00 A0   "$.....@........
                           05 00 00 12 00 40 42 0F 00 02 40 42 0F 00 80 84   .....@B...@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x11
bmCapabilities           : 0x01
wWidth                   : 0x04A0 (1184)
wHeight                  : 0x0290 (656)
dwMinBitRate             : 0x03B42000 (62136320 bps -> 7.767 MB/s)
dwMaxBitRate             : 0x07684000 (124272640 bps -> 15.534 MB/s)
dwMaxVideoFrameBufferSize: 0x0017B400 (1553408 bytes)
dwDefaultFrameInterval   : 0x000F4240 (100.0000 ms -> 10.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[2]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 22 24 05 11 01 A0 04 90 02 00 20 B4 03 00 40 68   "$........ ...@h
                           07 00 B4 17 00 40 42 0F 00 02 40 42 0F 00 80 84   .....@B...@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x12
bmCapabilities           : 0x01
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x04650000 (73728000 bps -> 9.216 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x001C2000 (1843200 bytes)
dwDefaultFrameInterval   : 0x001E8480 (200.0000 ms -> 5.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[2]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 22 24 05 12 01 00 05 D0 02 00 00 65 04 00 00 CA   "$.........e....
                           08 00 20 1C 00 80 84 1E 00 02 55 58 14 00 80 84   .. .......UX....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x13
bmCapabilities           : 0x01
wWidth                   : 0x0500 (1280)
wHeight                  : 0x03C0 (960)
dwMinBitRate             : 0x05DC0000 (98304000 bps -> 12.288 MB/s)
dwMaxBitRate             : 0x0BB80000 (196608000 bps -> 24.576 MB/s)
dwMaxVideoFrameBufferSize: 0x00258000 (2457600 bytes)
dwDefaultFrameInterval   : 0x001E8480 (200.0000 ms -> 5.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[2]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 22 24 05 13 01 00 05 C0 03 00 00 DC 05 00 00 B8   "$..............
                           0B 00 80 25 00 80 84 1E 00 02 55 58 14 00 80 84   ...%......UX....
                           1E 00                                             ..

        ------- VS Color Matching Descriptor Descriptor -------
bLength                  : 0x06 (6 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x0D (Color Matching)
bColorPrimaries          : 0x01 (BT.709, sRGB)
bTransferCharacteristics : 0x01 (BT.709)
bMatrixCoefficients      : 0x04 (SMPTE 170M)
Data (HexDump)           : 06 24 0D 01 01 04                                 .$....

        ----- Video Streaming MJPEG Format Type Descriptor ----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x06 (Format MJPEG)
bFormatIndex             : 0x02 (2)
bNumFrameDescriptors     : 0x13 (19)
bmFlags                  : 0x01 (Sample size is fixed)
bDefaultFrameIndex       : 0x01 (1)
bAspectRatioX            : 0x00
bAspectRatioY            : 0x00
bmInterlaceFlags         : 0x00
 D0 IL stream or variable: 0 (no)
 D1 Fields per frame     : 0 (2 fields)
 D2 Field 1 first        : 0 (no)
 D3 Reserved             : 0
 D4..5 Field pattern     : 0 (Field 1 only)
 D6..7 Display Mode      : 0 (Bob only)
bCopyProtect             : 0x00 (No restrictions)
Data (HexDump)           : 0B 24 06 02 13 01 01 00 00 00 00                  .$.........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
---> This is the Default (optimum) Frame index
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x01
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x01770000 (24576000 bps -> 3.72 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x00096000 (614400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 01 01 80 02 E0 01 00 00 77 01 00 00 CA   2$.........w....
                           08 00 60 09 00 15 16 05 00 06 15 16 05 00 80 1A   ..`.............
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x01
wWidth                   : 0x00A0 (160)
wHeight                  : 0x0078 (120)
dwMinBitRate             : 0x00177000 (1536000 bps -> 192 KB/s)
dwMaxBitRate             : 0x008CA000 (9216000 bps -> 1.152 MB/s)
dwMaxVideoFrameBufferSize: 0x00009600 (38400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 02 01 A0 00 78 00 00 70 17 00 00 A0 8C   2$.....x..p.....
                           00 00 96 00 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x01
wWidth                   : 0x00B0 (176)
wHeight                  : 0x0090 (144)
dwMinBitRate             : 0x001EF000 (2027520 bps -> 253.375 KB/s)
dwMaxBitRate             : 0x00B9A000 (12165120 bps -> 1.520 MB/s)
dwMaxVideoFrameBufferSize: 0x0000C600 (50688 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 03 01 B0 00 90 00 00 F0 1E 00 00 A0 B9   2$..............
                           00 00 C6 00 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x01
wWidth                   : 0x0140 (320)
wHeight                  : 0x00B0 (176)
dwMinBitRate             : 0x0044C000 (4505600 bps -> 563.125 KB/s)
dwMaxBitRate             : 0x019C8000 (27033600 bps -> 3.379 MB/s)
dwMaxVideoFrameBufferSize: 0x0001B800 (112640 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 04 01 40 01 B0 00 00 C0 44 00 00 80 9C   2$...@.....D....
                           01 00 B8 01 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x01
wWidth                   : 0x0140 (320)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x005DC000 (6144000 bps -> 768 KB/s)
dwMaxBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwMaxVideoFrameBufferSize: 0x00025800 (153600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 05 01 40 01 F0 00 00 C0 5D 00 00 80 32   2$...@.....]...2
                           02 00 58 02 00 15 16 05 00 06 15 16 05 00 80 1A   ..X.............
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x01
wWidth                   : 0x0160 (352)
wHeight                  : 0x0120 (288)
dwMinBitRate             : 0x007BC000 (8110080 bps -> 1.13 MB/s)
dwMaxBitRate             : 0x02E68000 (48660480 bps -> 6.82 MB/s)
dwMaxVideoFrameBufferSize: 0x00031800 (202752 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 06 01 60 01 20 01 00 C0 7B 00 00 80 E6   2$...`. ...{....
                           02 00 18 03 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x07
bmCapabilities           : 0x01
wWidth                   : 0x01B0 (432)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x007E9000 (8294400 bps -> 1.36 MB/s)
dwMaxBitRate             : 0x02F76000 (49766400 bps -> 6.220 MB/s)
dwMaxVideoFrameBufferSize: 0x00032A00 (207360 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 07 01 B0 01 F0 00 00 90 7E 00 00 60 F7   2$.........~..`.
                           02 00 2A 03 00 15 16 05 00 06 15 16 05 00 80 1A   ..*.............
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x08
bmCapabilities           : 0x01
wWidth                   : 0x0220 (544)
wHeight                  : 0x0120 (288)
dwMinBitRate             : 0x00BF4000 (12533760 bps -> 1.566 MB/s)
dwMaxBitRate             : 0x047B8000 (75202560 bps -> 9.400 MB/s)
dwMaxVideoFrameBufferSize: 0x0004C800 (313344 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 08 01 20 02 20 01 00 40 BF 00 00 80 7B   2$... . ..@....{
                           04 00 C8 04 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x09
bmCapabilities           : 0x01
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxVideoFrameBufferSize: 0x00070800 (460800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 09 01 80 02 68 01 00 40 19 01 00 80 97   2$.....h..@.....
                           06 00 08 07 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x0A
bmCapabilities           : 0x01
wWidth                   : 0x02F0 (752)
wHeight                  : 0x01A0 (416)
dwMinBitRate             : 0x017DE000 (25026560 bps -> 3.128 MB/s)
dwMaxBitRate             : 0x08F34000 (150159360 bps -> 18.769 MB/s)
dwMaxVideoFrameBufferSize: 0x00098C00 (625664 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 0A 01 F0 02 A0 01 00 E0 7D 01 00 40 F3   2$.........}..@.
                           08 00 8C 09 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x0B
bmCapabilities           : 0x01
wWidth                   : 0x0320 (800)
wHeight                  : 0x01C0 (448)
dwMinBitRate             : 0x01B58000 (28672000 bps -> 3.584 MB/s)
dwMaxBitRate             : 0x0A410000 (172032000 bps -> 21.504 MB/s)
dwMaxVideoFrameBufferSize: 0x000AF000 (716800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 0B 01 20 03 C0 01 00 80 B5 01 00 00 41   2$... .........A
                           0A 00 F0 0A 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x0C
bmCapabilities           : 0x01
wWidth                   : 0x0320 (800)
wHeight                  : 0x0258 (600)
dwMinBitRate             : 0x0249F000 (38400000 bps -> 4.800 MB/s)
dwMaxBitRate             : 0x0DBBA000 (230400000 bps -> 28.800 MB/s)
dwMaxVideoFrameBufferSize: 0x000EA600 (960000 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 0C 01 20 03 58 02 00 F0 49 02 00 A0 BB   2$... .X...I....
                           0D 00 A6 0E 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x0D
bmCapabilities           : 0x01
wWidth                   : 0x0360 (864)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x01FA4000 (33177600 bps -> 4.147 MB/s)
dwMaxBitRate             : 0x0BDD8000 (199065600 bps -> 24.883 MB/s)
dwMaxVideoFrameBufferSize: 0x000CA800 (829440 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 0D 01 60 03 E0 01 00 40 FA 01 00 80 DD   2$...`....@.....
                           0B 00 A8 0C 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x0E
bmCapabilities           : 0x01
wWidth                   : 0x03C0 (960)
wHeight                  : 0x0220 (544)
dwMinBitRate             : 0x027D8000 (41779200 bps -> 5.222 MB/s)
dwMaxBitRate             : 0x0EF10000 (250675200 bps -> 31.334 MB/s)
dwMaxVideoFrameBufferSize: 0x000FF000 (1044480 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 0E 01 C0 03 20 02 00 80 7D 02 00 00 F1   2$..... ...}....
                           0E 00 F0 0F 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x0F
bmCapabilities           : 0x01
wWidth                   : 0x03C0 (960)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x034BC000 (55296000 bps -> 6.912 MB/s)
dwMaxBitRate             : 0x13C68000 (331776000 bps -> 41.472 MB/s)
dwMaxVideoFrameBufferSize: 0x00151800 (1382400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 0F 01 C0 03 D0 02 00 C0 4B 03 00 80 C6   2$.........K....
                           13 00 18 15 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x10
bmCapabilities           : 0x01
wWidth                   : 0x0400 (1024)
wHeight                  : 0x0240 (576)
dwMinBitRate             : 0x02D00000 (47185920 bps -> 5.898 MB/s)
dwMaxBitRate             : 0x10E00000 (283115520 bps -> 35.389 MB/s)
dwMaxVideoFrameBufferSize: 0x00120000 (1179648 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 10 01 00 04 40 02 00 00 D0 02 00 00 E0   2$.....@........
                           10 00 00 12 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x11
bmCapabilities           : 0x01
wWidth                   : 0x04A0 (1184)
wHeight                  : 0x0290 (656)
dwMinBitRate             : 0x03B42000 (62136320 bps -> 7.767 MB/s)
dwMaxBitRate             : 0x1638C000 (372817920 bps -> 46.602 MB/s)
dwMaxVideoFrameBufferSize: 0x0017B400 (1553408 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 11 01 A0 04 90 02 00 20 B4 03 00 C0 38   2$........ ....8
                           16 00 B4 17 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x12
bmCapabilities           : 0x01
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x04650000 (73728000 bps -> 9.216 MB/s)
dwMaxBitRate             : 0x1A5E0000 (442368000 bps -> 55.296 MB/s)
dwMaxVideoFrameBufferSize: 0x001C2000 (1843200 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 12 01 00 05 D0 02 00 00 65 04 00 00 5E   2$.........e...^
                           1A 00 20 1C 00 15 16 05 00 06 15 16 05 00 80 1A   .. .............
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x13
bmCapabilities           : 0x01
wWidth                   : 0x0500 (1280)
wHeight                  : 0x03C0 (960)
dwMinBitRate             : 0x05DC0000 (98304000 bps -> 12.288 MB/s)
dwMaxBitRate             : 0x23280000 (589824000 bps -> 73.728 MB/s)
dwMaxVideoFrameBufferSize: 0x00258000 (2457600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 13 01 00 05 C0 03 00 00 DC 05 00 00 28   2$.............(
                           23 00 80 25 00 15 16 05 00 06 15 16 05 00 80 1A   #..%............
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ------- VS Color Matching Descriptor Descriptor -------
bLength                  : 0x06 (6 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x0D (Color Matching)
bColorPrimaries          : 0x01 (BT.709, sRGB)
bTransferCharacteristics : 0x01 (BT.709)
bMatrixCoefficients      : 0x04 (SMPTE 170M)
Data (HexDump)           : 06 24 0D 01 01 04                                 .$....

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x01
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 01 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x00C0
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0xC0 (192 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 C0 00 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x02
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 02 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0180
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x180 (384 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 80 01 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x03
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 03 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0200
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x200 (512 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 00 02 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x04
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 04 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0280
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x280 (640 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 80 02 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x05
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 05 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0320
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x320 (800 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 20 03 01                              .... ..

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x06
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 06 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x03B0
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x3B0 (944 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 B0 03 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x07
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 07 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0A80
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x01 (1 additional transactions per microframe -> allows 513..1024 byte per packet)
 Bits 10..0              : 0x280 (640 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 80 0A 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x08
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 08 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0B20
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x01 (1 additional transactions per microframe -> allows 513..1024 byte per packet)
 Bits 10..0              : 0x320 (800 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 20 0B 01                              .... ..

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x09
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 09 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0BE0
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x01 (1 additional transactions per microframe -> allows 513..1024 byte per packet)
 Bits 10..0              : 0x3E0 (992 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 E0 0B 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x0A
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 0A 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x1380
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x02 (2 additional transactions per microframe -> allows 683..1024 bytes per packet)
 Bits 10..0              : 0x380 (896 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 80 13 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x0B
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 0B 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x13FC
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x02 (2 additional transactions per microframe -> allows 683..1024 bytes per packet)
 Bits 10..0              : 0x3FC (1020 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 FC 13 01                              .......

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x02
bInterfaceCount          : 0x02
bFunctionClass           : 0x01 (Audio)
bFunctionSubClass        : 0x02 (Audio Streaming)
bFunctionProtocol        : 0x00
iFunction                : 0x00 (No String Descriptor)
Data (HexDump)           : 08 0B 02 02 01 02 00 00                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x01 (Audio Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 02 00 00 01 01 00 00                        .........

        ------ Audio Control Interface Header Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01 (Header)
bcdADC                   : 0x0100
wTotalLength             : 0x0026 (38 bytes)
bInCollection            : 0x01
baInterfaceNr[1]         : 0x03
Data (HexDump)           : 09 24 01 00 01 26 00 01 03                        .$...&...

        ------- Audio Control Input Terminal Descriptor -------
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Input Terminal)
bTerminalID              : 0x01
wTerminalType            : 0x0201 (Microphone)
bAssocTerminal           : 0x00
bNrChannels              : 0x01 (1 channel)
wChannelConfig           : 0x0000 (-)
iChannelNames            : 0x00 (No String Descriptor)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 0C 24 02 01 01 02 00 01 00 00 00 00               .$..........

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x03
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x01 (1)
bSourceID                : 0x05 (5)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 03 03 01 01 01 05 00                        .$.......

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x06 (Feature Unit)
bUnitID                  : 0x05 (5)
bSourceID                : 0x01 (1)
bControlSize             : 0x01 (1 byte per control)
bmaControls[0]           : 0x03
 D0: Mute                : 1
 D1: Volume              : 1
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
bmaControls[1]           : 0x00
 D0: Mute                : 0
 D1: Volume              : 0
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
iFeature                 : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 06 05 01 01 03 00 00                        .$.......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 03 00 00 01 02 00 00                        .........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x01
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 03 01 01 01 02 00 00                        .........

        -------- Audio Streaming Interface Descriptor ---------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01
bTerminalLink            : 0x03
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 03 01 01 00                              .$.....

        ------- Audio Streaming Format Type Descriptor --------
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Format Type)
bFormatType              : 0x01 (FORMAT_TYPE_I)
bNrChannels              : 0x01 (1 channel)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x01 (supports 1 sample frequency)
tSamFreq[1]              : 0x03E80 (16000 Hz)
Data (HexDump)           : 0B 24 02 01 01 02 10 01 80 3E 00                  .$.......>.

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x86 (Direction=IN EndpointID=6)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0044
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x44 (68 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 86 05 44 00 04 00 00                        ....D....

        ----------- Audio Data Endpoint Descriptor ------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x25 (Audio Endpoint Descriptor)
bDescriptorSubtype       : 0x01 (General)
bmAttributes             : 0x01
 D0   : Sampling Freq    : 0x01 (supported)
 D1   : Pitch            : 0x00 (not supported)
 D6..2: Reserved         : 0x00
 D7   : MaxPacketsOnly   : 0x00 (no)
bLockDelayUnits          : 0x00 (Undefined)
wLockDelay               : 0x0000
Data (HexDump)           : 07 25 01 01 00 00 00                              .%.....

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x02
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 03 02 01 01 02 00 00                        .........

        -------- Audio Streaming Interface Descriptor ---------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01
bTerminalLink            : 0x03
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 03 01 01 00                              .$.....

        ------- Audio Streaming Format Type Descriptor --------
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Format Type)
bFormatType              : 0x01 (FORMAT_TYPE_I)
bNrChannels              : 0x01 (1 channel)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x01 (supports 1 sample frequency)
tSamFreq[1]              : 0x05DC0 (24000 Hz)
Data (HexDump)           : 0B 24 02 01 01 02 10 01 C0 5D 00                  .$.......].

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x86 (Direction=IN EndpointID=6)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0064
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x64 (100 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 86 05 64 00 04 00 00                        ....d....

        ----------- Audio Data Endpoint Descriptor ------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x25 (Audio Endpoint Descriptor)
bDescriptorSubtype       : 0x01 (General)
bmAttributes             : 0x01
 D0   : Sampling Freq    : 0x01 (supported)
 D1   : Pitch            : 0x00 (not supported)
 D6..2: Reserved         : 0x00
 D7   : MaxPacketsOnly   : 0x00 (no)
bLockDelayUnits          : 0x00 (Undefined)
wLockDelay               : 0x0000
Data (HexDump)           : 07 25 01 01 00 00 00                              .%.....

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x03
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 03 03 01 01 02 00 00                        .........

        -------- Audio Streaming Interface Descriptor ---------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01
bTerminalLink            : 0x03
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 03 01 01 00                              .$.....

        ------- Audio Streaming Format Type Descriptor --------
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Format Type)
bFormatType              : 0x01 (FORMAT_TYPE_I)
bNrChannels              : 0x01 (1 channel)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x01 (supports 1 sample frequency)
tSamFreq[1]              : 0x07D00 (32000 Hz)
Data (HexDump)           : 0B 24 02 01 01 02 10 01 00 7D 00                  .$.......}.

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x86 (Direction=IN EndpointID=6)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0084
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x84 (132 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 86 05 84 00 04 00 00                        .........

        ----------- Audio Data Endpoint Descriptor ------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x25 (Audio Endpoint Descriptor)
bDescriptorSubtype       : 0x01 (General)
bmAttributes             : 0x01
 D0   : Sampling Freq    : 0x01 (supported)
 D1   : Pitch            : 0x00 (not supported)
 D6..2: Reserved         : 0x00
 D7   : MaxPacketsOnly   : 0x00 (no)
bLockDelayUnits          : 0x00 (Undefined)
wLockDelay               : 0x0000
Data (HexDump)           : 07 25 01 01 00 00 00                              .%.....

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x04
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 03 04 01 01 02 00 00                        .........

        -------- Audio Streaming Interface Descriptor ---------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01
bTerminalLink            : 0x03
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 03 01 01 00                              .$.....

        ------- Audio Streaming Format Type Descriptor --------
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Format Type)
bFormatType              : 0x01 (FORMAT_TYPE_I)
bNrChannels              : 0x01 (1 channel)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x01 (supports 1 sample frequency)
tSamFreq[1]              : 0x0BB80 (48000 Hz)
Data (HexDump)           : 0B 24 02 01 01 02 10 01 80 BB 00                  .$.........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x86 (Direction=IN EndpointID=6)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x00C4
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0xC4 (196 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 86 05 C4 00 04 00 00                        .........

        ----------- Audio Data Endpoint Descriptor ------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x25 (Audio Endpoint Descriptor)
bDescriptorSubtype       : 0x01 (General)
bmAttributes             : 0x01
 D0   : Sampling Freq    : 0x01 (supported)
 D1   : Pitch            : 0x00 (not supported)
 D6..2: Reserved         : 0x00
 D7   : MaxPacketsOnly   : 0x00 (no)
bLockDelayUnits          : 0x00 (Undefined)
wLockDelay               : 0x0000
Data (HexDump)           : 07 25 01 01 00 00 00                              .%.....

    ----------------- Device Qualifier Descriptor -----------------
bLength                  : 0x0A (10 bytes)
bDescriptorType          : 0x06 (Device_qualifier Descriptor)
bcdUSB                   : 0x200 (USB Version 2.00)
bDeviceClass             : 0xEF (Miscellaneous)
bDeviceSubClass          : 0x02
bDeviceProtocol          : 0x01 (IAD - Interface Association Descriptor)
bMaxPacketSize0          : 0x40 (64 Bytes)
bNumConfigurations       : 0x01 (1 other-speed configuration)
bReserved                : 0x00
Data (HexDump)           : 0A 06 00 02 EF 02 01 40 01 00                     .......@..

    ------------ Other Speed Configuration Descriptor -------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x07 (Other_speed_configuration Descriptor)
wTotalLength             : 0x04DE (1246 bytes)
bNumInterfaces           : 0x04 (4 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x00 (No String Descriptor)
bmAttributes             : 0x80
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x00 (no)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0xFA (500 mA)
Data (HexDump)           : 09 07 DE 04 04 01 00 80 FA 08 0B 00 02 0E 03 00   ................
                           00 09 04 00 00 01 0E 01 00 00 0D 24 01 00 01 A0   ...........$....
                           00 00 6C DC 02 01 01 12 24 02 01 01 02 00 00 00   ..l.....$.......
                           00 00 00 00 00 03 0E 00 00 0B 24 05 02 01 00 40   ..........$....@
                           02 5B 17 00 1B 24 06 03 E4 8E 67 69 0F 41 DB 40   .[...$....gi.A.@
                           A8 50 74 20 D7 D8 24 0E 08 01 02 02 3F 03 00 1B   .Pt ..$.....?...
                           24 06 04 15 02 E4 49 34 F4 FE 47 B1 58 0E 88 50   $.....I4..G.X..P
                           23 E5 1B 03 01 02 02 09 01 00 1C 24 06 06 A9 4C   #..........$...L
                           5D 1F 11 DE 87 44 84 0D 50 93 3C 8E C8 D1 12 01   ]....D..P.<.....
                           04 03 FF FF 03 00 1B 24 06 07 21 2D E5 FF 30 80   .......$..!-..0.
                           2C 4E 82 D9 F5 87 D0 05 40 BD 02 01 04 02 00 03   ,N......@.......
                           00 09 24 03 05 01 01 00 04 00 07 05 87 03 10 00   ..$.............
                           10 05 25 03 10 00 09 04 01 00 00 0E 02 00 00 10   ..%.............
                           24 01 03 C2 02 81 00 05 01 00 00 01 00 04 04 1B   $...............
                           24 04 01 02 59 55 59 32 00 00 10 00 80 00 00 AA   $...YUY2........
                           00 38 9B 71 10 02 00 00 00 00 26 24 05 02 01 A0   .8.q......&$....
                           00 78 00 00 70 17 00 00 50 46 00 00 96 00 00 2A   .x..p...PF.....*
                           2C 0A 00 03 2A 2C 0A 00 40 42 0F 00 80 84 1E 00   ,...*,..@B......
                           26 24 05 03 01 B0 00 90 00 00 F0 1E 00 00 D0 5C   &$.............\
                           00 00 C6 00 00 2A 2C 0A 00 03 2A 2C 0A 00 40 42   .....*,...*,..@B
                           0F 00 80 84 1E 00 06 24 0D 01 01 04 0B 24 06 02   .......$.....$..
                           0C 01 01 00 00 00 00 32 24 07 01 01 80 02 E0 01   .......2$.......
                           00 00 77 01 00 00 CA 08 00 60 09 00 15 16 05 00   ..w......`......
                           06 15 16 05 00 80 1A 06 00 20 A1 07 00 2A 2C 0A   ......... ...*,.
                           00 40 42 0F 00 80 84 1E 00 32 24 07 02 01 A0 00   .@B......2$.....
                           78 00 00 70 17 00 00 A0 8C 00 00 96 00 00 15 16   x..p............
                           05 00 06 15 16 05 00 80 1A 06 00 20 A1 07 00 2A   ........... ...*
                           2C 0A 00 40 42 0F 00 80 84 1E 00 32 24 07 03 01   ,..@B......2$...
                           B0 00 90 00 00 F0 1E 00 00 A0 B9 00 00 C6 00 00   ................
                           15 16 05 00 06 15 16 05 00 80 1A 06 00 20 A1 07   ............. ..
                           00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00 32 24 07   .*,..@B......2$.
                           04 01 40 01 B0 00 00 C0 44 00 00 80 9C 01 00 B8   ..@.....D.......
                           01 00 15 16 05 00 06 15 16 05 00 80 1A 06 00 20   ...............
                           A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00 32   ...*,..@B......2
                           24 07 05 01 40 01 F0 00 00 C0 5D 00 00 80 32 02   $...@.....]...2.
                           00 58 02 00 15 16 05 00 06 15 16 05 00 80 1A 06   .X..............
                           00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84 1E   . ...*,..@B.....
                           00 32 24 07 06 01 60 01 20 01 00 C0 7B 00 00 80   .2$...`. ...{...
                           E6 02 00 18 03 00 15 16 05 00 06 15 16 05 00 80   ................
                           1A 06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80   ... ...*,..@B...
                           84 1E 00 32 24 07 07 01 B0 01 F0 00 00 90 7E 00   ...2$.........~.
                           00 60 F7 02 00 2A 03 00 15 16 05 00 06 15 16 05   .`...*..........
                           00 80 1A 06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F   ..... ...*,..@B.
                           00 80 84 1E 00 32 24 07 08 01 20 02 20 01 00 40   .....2$... . ..@
                           BF 00 00 80 7B 04 00 C8 04 00 15 16 05 00 06 15   ....{...........
                           16 05 00 80 1A 06 00 20 A1 07 00 2A 2C 0A 00 40   ....... ...*,..@
                           42 0F 00 80 84 1E 00 32 24 07 09 01 80 02 68 01   B......2$.....h.
                           00 40 19 01 00 80 97 06 00 08 07 00 15 16 05 00   .@..............
                           06 15 16 05 00 80 1A 06 00 20 A1 07 00 2A 2C 0A   ......... ...*,.
                           00 40 42 0F 00 80 84 1E 00 26 24 07 0A 01 F0 02   .@B......&$.....
                           A0 01 00 E0 7D 01 00 A0 79 04 00 8C 09 00 2A 2C   ....}...y.....*,
                           0A 00 03 2A 2C 0A 00 40 42 0F 00 80 84 1E 00 26   ...*,..@B......&
                           24 07 0B 01 20 03 C0 01 00 80 B5 01 00 80 20 05   $... ......... .
                           00 F0 0A 00 2A 2C 0A 00 03 2A 2C 0A 00 40 42 0F   ....*,...*,..@B.
                           00 80 84 1E 00 26 24 07 0C 01 20 03 58 02 00 F0   .....&$... .X...
                           49 02 00 D0 DD 06 00 A6 0E 00 2A 2C 0A 00 03 2A   I.........*,...*
                           2C 0A 00 40 42 0F 00 80 84 1E 00 06 24 0D 01 01   ,..@B.......$...
                           04 09 04 01 01 01 0E 02 00 00 07 05 81 05 C0 00   ................
                           01 09 04 01 02 01 0E 02 00 00 07 05 81 05 80 01   ................
                           01 09 04 01 03 01 0E 02 00 00 07 05 81 05 00 02   ................
                           01 09 04 01 04 01 0E 02 00 00 07 05 81 05 80 02   ................
                           01 09 04 01 05 01 0E 02 00 00 07 05 81 05 20 03   .............. .
                           01 09 04 01 06 01 0E 02 00 00 07 05 81 05 B0 03   ................
                           01 08 0B 02 02 01 02 00 00 09 04 02 00 00 01 01   ................
                           00 00 09 24 01 00 01 26 00 01 03 0C 24 02 01 01   ...$...&....$...
                           02 00 01 00 00 00 00 09 24 03 03 01 01 01 05 00   ........$.......
                           09 24 06 05 01 01 03 00 00 09 04 03 00 00 01 02   .$..............
                           00 00 09 04 03 01 01 01 02 00 00 07 24 01 03 01   ............$...
                           01 00 0B 24 02 01 01 02 10 01 80 3E 00 09 05 86   ...$.......>....
                           05 44 00 01 00 00 07 25 01 01 00 00 00 09 04 03   .D.....%........
                           02 01 01 02 00 00 07 24 01 03 01 01 00 0B 24 02   .......$......$.
                           01 01 02 10 01 C0 5D 00 09 05 86 05 64 00 01 00   ......].....d...
                           00 07 25 01 01 00 00 00 09 04 03 03 01 01 02 00   ..%.............
                           00 07 24 01 03 01 01 00 0B 24 02 01 01 02 10 01   ..$......$......
                           00 7D 00 09 05 86 05 84 00 01 00 00 07 25 01 01   .}...........%..
                           00 00 00 09 04 03 04 01 01 02 00 00 07 24 01 03   .............$..
                           01 01 00 0B 24 02 01 01 02 10 01 80 BB 00 09 05   ....$...........
                           86 05 C4 00 01 00 00 07 25 01 01 00 00 00         ........%.....

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x00
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x00 (No String Descriptor)
Data (HexDump)           : 08 0B 00 02 0E 03 00 00                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x00
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 00 00 01 0E 01 00 00                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0100 (UVC Version 1.00)
wTotalLength             : 0x00A0 (160 bytes)
dwClockFreq              : 0x02DC6C00 (48 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x01
Data (HexDump)           : 0D 24 01 00 01 A0 00 00 6C DC 02 01 01            .$......l....

        -------- Video Control Input Terminal Descriptor ------
bLength                  : 0x12 (18 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x02 (Input Terminal)
bTerminalID              : 0x01
wTerminalType            : 0x0201 (ITT_CAMERA)
bAssocTerminal           : 0x00 (Not associated with an Output Terminal)
iTerminal                : 0x00
Camera Input Terminal Data:
wObjectiveFocalLengthMin : 0x0000
wObjectiveFocalLengthMax : 0x0000
wOcularFocalLength       : 0x0000
bControlSize             : 0x03
bmControls               : 0x0E, 0x00, 0x00
 D0                      : 0   no -  Scanning Mode
 D1                      : 1  yes -  Auto-Exposure Mode
 D2                      : 1  yes -  Auto-Exposure Priority
 D3                      : 1  yes -  Exposure Time (Absolute)
 D4                      : 0   no -  Exposure Time (Relative)
 D5                      : 0   no -  Focus (Absolute)
 D6                      : 0   no -  Focus (Relative)
 D7                      : 0   no -  Iris (Absolute)
 D8                      : 0   no -  Iris (Relative)
 D9                      : 0   no -  Zoom (Absolute)
 D10                     : 0   no -  Zoom (Relative)
 D11                     : 0   no -  Pan (Absolute)
 D12                     : 0   no -  Pan (Relative)
 D13                     : 0   no -  Roll (Absolute)
 D14                     : 0   no -  Roll (Relative)
 D15                     : 0   no -  Tilt (Absolute)
 D16                     : 0   no -  Tilt (Relative)
 D17                     : 0   no -  Focus Auto
 D18                     : 0   no -  Reserved
 D19                     : 0   no -  Reserved
 D20                     : 0   no -  Reserved
 D21                     : 0   no -  Reserved
 D22                     : 0   no -  Reserved
 D23                     : 0   no -  Reserved
Data (HexDump)           : 12 24 02 01 01 02 00 00 00 00 00 00 00 00 03 0E   .$..............
                           00 00                                             ..

        -------- Video Control Processing Unit Descriptor -----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x05 (Processing Unit)
bUnitID                  : 0x02
bSourceID                : 0x01
wMaxMultiplier           : 0x4000 (163.84x Zoom)
bControlSize             : 0x02
bmControls               : 0x5B, 0x17
 D0                      : 1  yes -  Brightness
 D1                      : 1  yes -  Contrast
 D2                      : 0   no -  Hue
 D3                      : 1  yes -  Saturation
 D4                      : 1  yes -  Sharpness
 D5                      : 0   no -  Gamma
 D6                      : 1  yes -  White Balance Temperature
 D7                      : 0   no -  White Balance Component
 D8                      : 1  yes -  Backlight Compensation
 D9                      : 1  yes -  Gain
 D10                     : 1  yes -  Power Line Frequency
 D11                     : 0   no -  Hue, Auto
 D12                     : 1  yes -  White Balance Temperature, Auto
 D13                     : 0   no -  White Balance Component, Auto
 D14                     : 0   no -  Digital Multiplier
 D15                     : 0   no -  Digital Multiplier Limit
iProcessing              : 0x00
Data (HexDump)           : 0B 24 05 02 01 00 40 02 5B 17 00                  .$....@.[..

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x03
guidExtensionCode        : {69678EE4-410F-40DB-A850-7420D7D8240E}
bNumControls             : 0x08
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x02
bmControls               : 0x3F, 0x03
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 1  yes -  Vendor-Specific (Optional)
 D3                      : 1  yes -  Vendor-Specific (Optional)
 D4                      : 1  yes -  Vendor-Specific (Optional)
 D5                      : 1  yes -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
 D8                      : 1  yes -  Vendor-Specific (Optional)
 D9                      : 1  yes -  Vendor-Specific (Optional)
 D10                     : 0   no -  Vendor-Specific (Optional)
 D11                     : 0   no -  Vendor-Specific (Optional)
 D12                     : 0   no -  Vendor-Specific (Optional)
 D13                     : 0   no -  Vendor-Specific (Optional)
 D14                     : 0   no -  Vendor-Specific (Optional)
 D15                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1B 24 06 03 E4 8E 67 69 0F 41 DB 40 A8 50 74 20   .$....gi.A.@.Pt
                           D7 D8 24 0E 08 01 02 02 3F 03 00                  ..$.....?..

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x04
guidExtensionCode        : {49E40215-F434-47FE-B158-0E885023E51B}
bNumControls             : 0x03
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x02
bmControls               : 0x09, 0x01
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 0   no -  Vendor-Specific (Optional)
 D2                      : 0   no -  Vendor-Specific (Optional)
 D3                      : 1  yes -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
 D8                      : 1  yes -  Vendor-Specific (Optional)
 D9                      : 0   no -  Vendor-Specific (Optional)
 D10                     : 0   no -  Vendor-Specific (Optional)
 D11                     : 0   no -  Vendor-Specific (Optional)
 D12                     : 0   no -  Vendor-Specific (Optional)
 D13                     : 0   no -  Vendor-Specific (Optional)
 D14                     : 0   no -  Vendor-Specific (Optional)
 D15                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1B 24 06 04 15 02 E4 49 34 F4 FE 47 B1 58 0E 88   .$.....I4..G.X..
                           50 23 E5 1B 03 01 02 02 09 01 00                  P#.........

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x06
guidExtensionCode        : {1F5D4CA9-DE11-4487-840D-50933C8EC8D1}
bNumControls             : 0x12
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x04
bControlSize             : 0x03
bmControls               : 0xFF, 0xFF, 0x03
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 1  yes -  Vendor-Specific (Optional)
 D3                      : 1  yes -  Vendor-Specific (Optional)
 D4                      : 1  yes -  Vendor-Specific (Optional)
 D5                      : 1  yes -  Vendor-Specific (Optional)
 D6                      : 1  yes -  Vendor-Specific (Optional)
 D7                      : 1  yes -  Vendor-Specific (Optional)
 D8                      : 1  yes -  Vendor-Specific (Optional)
 D9                      : 1  yes -  Vendor-Specific (Optional)
 D10                     : 1  yes -  Vendor-Specific (Optional)
 D11                     : 1  yes -  Vendor-Specific (Optional)
 D12                     : 1  yes -  Vendor-Specific (Optional)
 D13                     : 1  yes -  Vendor-Specific (Optional)
 D14                     : 1  yes -  Vendor-Specific (Optional)
 D15                     : 1  yes -  Vendor-Specific (Optional)
 D16                     : 1  yes -  Vendor-Specific (Optional)
 D17                     : 1  yes -  Vendor-Specific (Optional)
 D18                     : 0   no -  Vendor-Specific (Optional)
 D19                     : 0   no -  Vendor-Specific (Optional)
 D20                     : 0   no -  Vendor-Specific (Optional)
 D21                     : 0   no -  Vendor-Specific (Optional)
 D22                     : 0   no -  Vendor-Specific (Optional)
 D23                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1C 24 06 06 A9 4C 5D 1F 11 DE 87 44 84 0D 50 93   .$...L]....D..P.
                           3C 8E C8 D1 12 01 04 03 FF FF 03 00               <...........

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x07
guidExtensionCode        : {FFE52D21-8030-4E2C-82D9-F587D00540BD}
bNumControls             : 0x02
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x04
bControlSize             : 0x02
bmControls               : 0x00, 0x03
 D0                      : 0   no -  Vendor-Specific (Optional)
 D1                      : 0   no -  Vendor-Specific (Optional)
 D2                      : 0   no -  Vendor-Specific (Optional)
 D3                      : 0   no -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
 D8                      : 1  yes -  Vendor-Specific (Optional)
 D9                      : 1  yes -  Vendor-Specific (Optional)
 D10                     : 0   no -  Vendor-Specific (Optional)
 D11                     : 0   no -  Vendor-Specific (Optional)
 D12                     : 0   no -  Vendor-Specific (Optional)
 D13                     : 0   no -  Vendor-Specific (Optional)
 D14                     : 0   no -  Vendor-Specific (Optional)
 D15                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1B 24 06 07 21 2D E5 FF 30 80 2C 4E 82 D9 F5 87   .$..!-..0.,N....
                           D0 05 40 BD 02 01 04 02 00 03 00                  ..@........

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x05
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x04
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 05 01 01 00 04 00                        .$.......

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x87 (Direction=IN EndpointID=7)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0010
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x10 (16 bytes per packet)
bInterval                : 0x10 (16 ms)
Data (HexDump)           : 07 05 87 03 10 00 10                              .......

        --- Class-specific VC Interrupt Endpoint Descriptor ---
bLength                  : 0x05 (5 bytes)
bDescriptorType          : 0x25 (Video Control Endpoint)
bDescriptorSubtype       : 0x03 (Interrupt)
wMaxTransferSize         : 0x0010 (16 bytes)
Data (HexDump)           : 05 25 03 10 00                                    .%...

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 00 00 0E 02 00 00                        .........

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x10 (16 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x03
wTotalLength             : 0x02C2 (706 bytes)
bEndpointAddress         : 0x81 (Direction=IN  EndpointID=1)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x05
bStillCaptureMethod      : 0x01 (Still Capture Method 1)
nbTriggerSupport         : 0x00 (Hardware Triggering not supported)
bTriggerUsage            : 0x00 (Host will initiate still image capture)
nbControlSize            : 0x01
Video Payload Format 1   : 0x00
 D0                      : 0   no -  Key Frame Rate
 D1                      : 0   no -  P Frame Rate
 D2                      : 0   no -  Compression Quality
 D3                      : 0   no -  Compression Window Size
 D4                      : 0   no -  Generate Key Frame
 D5                      : 0   no -  Update Frame Segment
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Video Payload Format 2   : 0x04
 D0                      : 0   no -  Key Frame Rate
 D1                      : 0   no -  P Frame Rate
 D2                      : 1  yes -  Compression Quality
 D3                      : 0   no -  Compression Window Size
 D4                      : 0   no -  Generate Key Frame
 D5                      : 0   no -  Update Frame Segment
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Video Payload Format 3   : 0x04
 D0                      : 0   no -  Key Frame Rate
 D1                      : 0   no -  P Frame Rate
 D2                      : 1  yes -  Compression Quality
 D3                      : 0   no -  Compression Window Size
 D4                      : 0   no -  Generate Key Frame
 D5                      : 0   no -  Update Frame Segment
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Data (HexDump)           : 10 24 01 03 C2 02 81 00 05 01 00 00 01 00 04 04   .$..............

        ------- VS Uncompressed Format Type Descriptor --------
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x04 (Uncompressed Format Type)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x02 (2)
guidFormat               : {32595559-0000-0010-8000-00AA00389B71} (YUY2)
bBitsPerPixel            : 0x10 (16 bits)
bDefaultFrameIndex       : 0x02 (2)
bAspectRatioX            : 0x00
bAspectRatioY            : 0x00
bmInterlaceFlags         : 0x00
 D0 IL stream or variable: 0 (no)
 D1 Fields per frame     : 0 (2 fields)
 D2 Field 1 first        : 0 (no)
 D3 Reserved             : 0
 D4..5 Field pattern     : 0 (Field 1 only)
 D6..7 Display Mode      : 0 (Bob only)
bCopyProtect             : 0x00 (No restrictions)
Data (HexDump)           : 1B 24 04 01 02 59 55 59 32 00 00 10 00 80 00 00   .$...YUY2.......
                           AA 00 38 9B 71 10 02 00 00 00 00                  ..8.q......

        -------- VS Uncompressed Frame Type Descriptor --------
---> This is the Default (optimum) Frame index
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x01
wWidth                   : 0x00A0 (160)
wHeight                  : 0x0078 (120)
dwMinBitRate             : 0x00177000 (1536000 bps -> 192 KB/s)
dwMaxBitRate             : 0x00465000 (4608000 bps -> 576 KB/s)
dwMaxVideoFrameBufferSize: 0x00009600 (38400 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[2]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[3]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 26 24 05 02 01 A0 00 78 00 00 70 17 00 00 50 46   &$.....x..p...PF
                           00 00 96 00 00 2A 2C 0A 00 03 2A 2C 0A 00 40 42   .....*,...*,..@B
                           0F 00 80 84 1E 00                                 ......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x01
wWidth                   : 0x00B0 (176)
wHeight                  : 0x0090 (144)
dwMinBitRate             : 0x001EF000 (2027520 bps -> 253.375 KB/s)
dwMaxBitRate             : 0x005CD000 (6082560 bps -> 760.250 KB/s)
dwMaxVideoFrameBufferSize: 0x0000C600 (50688 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[2]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[3]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 26 24 05 03 01 B0 00 90 00 00 F0 1E 00 00 D0 5C   &$.............\
                           00 00 C6 00 00 2A 2C 0A 00 03 2A 2C 0A 00 40 42   .....*,...*,..@B
                           0F 00 80 84 1E 00                                 ......

        ------- VS Color Matching Descriptor Descriptor -------
bLength                  : 0x06 (6 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x0D (Color Matching)
bColorPrimaries          : 0x01 (BT.709, sRGB)
bTransferCharacteristics : 0x01 (BT.709)
bMatrixCoefficients      : 0x04 (SMPTE 170M)
Data (HexDump)           : 06 24 0D 01 01 04                                 .$....

        ----- Video Streaming MJPEG Format Type Descriptor ----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x06 (Format MJPEG)
bFormatIndex             : 0x02 (2)
bNumFrameDescriptors     : 0x0C (12)
bmFlags                  : 0x01 (Sample size is fixed)
bDefaultFrameIndex       : 0x01 (1)
bAspectRatioX            : 0x00
bAspectRatioY            : 0x00
bmInterlaceFlags         : 0x00
 D0 IL stream or variable: 0 (no)
 D1 Fields per frame     : 0 (2 fields)
 D2 Field 1 first        : 0 (no)
 D3 Reserved             : 0
 D4..5 Field pattern     : 0 (Field 1 only)
 D6..7 Display Mode      : 0 (Bob only)
bCopyProtect             : 0x00 (No restrictions)
Data (HexDump)           : 0B 24 06 02 0C 01 01 00 00 00 00                  .$.........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
---> This is the Default (optimum) Frame index
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x01
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x01770000 (24576000 bps -> 3.72 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x00096000 (614400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 01 01 80 02 E0 01 00 00 77 01 00 00 CA   2$.........w....
                           08 00 60 09 00 15 16 05 00 06 15 16 05 00 80 1A   ..`.............
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x01
wWidth                   : 0x00A0 (160)
wHeight                  : 0x0078 (120)
dwMinBitRate             : 0x00177000 (1536000 bps -> 192 KB/s)
dwMaxBitRate             : 0x008CA000 (9216000 bps -> 1.152 MB/s)
dwMaxVideoFrameBufferSize: 0x00009600 (38400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 02 01 A0 00 78 00 00 70 17 00 00 A0 8C   2$.....x..p.....
                           00 00 96 00 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x01
wWidth                   : 0x00B0 (176)
wHeight                  : 0x0090 (144)
dwMinBitRate             : 0x001EF000 (2027520 bps -> 253.375 KB/s)
dwMaxBitRate             : 0x00B9A000 (12165120 bps -> 1.520 MB/s)
dwMaxVideoFrameBufferSize: 0x0000C600 (50688 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 03 01 B0 00 90 00 00 F0 1E 00 00 A0 B9   2$..............
                           00 00 C6 00 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x01
wWidth                   : 0x0140 (320)
wHeight                  : 0x00B0 (176)
dwMinBitRate             : 0x0044C000 (4505600 bps -> 563.125 KB/s)
dwMaxBitRate             : 0x019C8000 (27033600 bps -> 3.379 MB/s)
dwMaxVideoFrameBufferSize: 0x0001B800 (112640 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 04 01 40 01 B0 00 00 C0 44 00 00 80 9C   2$...@.....D....
                           01 00 B8 01 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x01
wWidth                   : 0x0140 (320)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x005DC000 (6144000 bps -> 768 KB/s)
dwMaxBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwMaxVideoFrameBufferSize: 0x00025800 (153600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 05 01 40 01 F0 00 00 C0 5D 00 00 80 32   2$...@.....]...2
                           02 00 58 02 00 15 16 05 00 06 15 16 05 00 80 1A   ..X.............
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x01
wWidth                   : 0x0160 (352)
wHeight                  : 0x0120 (288)
dwMinBitRate             : 0x007BC000 (8110080 bps -> 1.13 MB/s)
dwMaxBitRate             : 0x02E68000 (48660480 bps -> 6.82 MB/s)
dwMaxVideoFrameBufferSize: 0x00031800 (202752 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 06 01 60 01 20 01 00 C0 7B 00 00 80 E6   2$...`. ...{....
                           02 00 18 03 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x07
bmCapabilities           : 0x01
wWidth                   : 0x01B0 (432)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x007E9000 (8294400 bps -> 1.36 MB/s)
dwMaxBitRate             : 0x02F76000 (49766400 bps -> 6.220 MB/s)
dwMaxVideoFrameBufferSize: 0x00032A00 (207360 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 07 01 B0 01 F0 00 00 90 7E 00 00 60 F7   2$.........~..`.
                           02 00 2A 03 00 15 16 05 00 06 15 16 05 00 80 1A   ..*.............
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x08
bmCapabilities           : 0x01
wWidth                   : 0x0220 (544)
wHeight                  : 0x0120 (288)
dwMinBitRate             : 0x00BF4000 (12533760 bps -> 1.566 MB/s)
dwMaxBitRate             : 0x047B8000 (75202560 bps -> 9.400 MB/s)
dwMaxVideoFrameBufferSize: 0x0004C800 (313344 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 08 01 20 02 20 01 00 40 BF 00 00 80 7B   2$... . ..@....{
                           04 00 C8 04 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x09
bmCapabilities           : 0x01
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxVideoFrameBufferSize: 0x00070800 (460800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 07 09 01 80 02 68 01 00 40 19 01 00 80 97   2$.....h..@.....
                           06 00 08 07 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x0A
bmCapabilities           : 0x01
wWidth                   : 0x02F0 (752)
wHeight                  : 0x01A0 (416)
dwMinBitRate             : 0x017DE000 (25026560 bps -> 3.128 MB/s)
dwMaxBitRate             : 0x0479A000 (75079680 bps -> 9.384 MB/s)
dwMaxVideoFrameBufferSize: 0x00098C00 (625664 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[2]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[3]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 26 24 07 0A 01 F0 02 A0 01 00 E0 7D 01 00 A0 79   &$.........}...y
                           04 00 8C 09 00 2A 2C 0A 00 03 2A 2C 0A 00 40 42   .....*,...*,..@B
                           0F 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x0B
bmCapabilities           : 0x01
wWidth                   : 0x0320 (800)
wHeight                  : 0x01C0 (448)
dwMinBitRate             : 0x01B58000 (28672000 bps -> 3.584 MB/s)
dwMaxBitRate             : 0x05208000 (86016000 bps -> 10.752 MB/s)
dwMaxVideoFrameBufferSize: 0x000AF000 (716800 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[2]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[3]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 26 24 07 0B 01 20 03 C0 01 00 80 B5 01 00 80 20   &$... .........
                           05 00 F0 0A 00 2A 2C 0A 00 03 2A 2C 0A 00 40 42   .....*,...*,..@B
                           0F 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x0C
bmCapabilities           : 0x01
wWidth                   : 0x0320 (800)
wHeight                  : 0x0258 (600)
dwMinBitRate             : 0x0249F000 (38400000 bps -> 4.800 MB/s)
dwMaxBitRate             : 0x06DDD000 (115200000 bps -> 14.400 MB/s)
dwMaxVideoFrameBufferSize: 0x000EA600 (960000 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[2]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[3]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 26 24 07 0C 01 20 03 58 02 00 F0 49 02 00 D0 DD   &$... .X...I....
                           06 00 A6 0E 00 2A 2C 0A 00 03 2A 2C 0A 00 40 42   .....*,...*,..@B
                           0F 00 80 84 1E 00                                 ......

        ------- VS Color Matching Descriptor Descriptor -------
bLength                  : 0x06 (6 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x0D (Color Matching)
bColorPrimaries          : 0x01 (BT.709, sRGB)
bTransferCharacteristics : 0x01 (BT.709)
bMatrixCoefficients      : 0x04 (SMPTE 170M)
Data (HexDump)           : 06 24 0D 01 01 04                                 .$....

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x01
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 01 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x00C0
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0xC0 (192 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 C0 00 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x02
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 02 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0180
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x180 (384 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 80 01 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x03
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 03 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0200
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x200 (512 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 00 02 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x04
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 04 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0280
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x280 (640 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 80 02 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x05
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 05 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0320
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x320 (800 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 20 03 01                              .... ..

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x06
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 06 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x03B0
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x3B0 (944 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 B0 03 01                              .......

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x02
bInterfaceCount          : 0x02
bFunctionClass           : 0x01 (Audio)
bFunctionSubClass        : 0x02 (Audio Streaming)
bFunctionProtocol        : 0x00
iFunction                : 0x00 (No String Descriptor)
Data (HexDump)           : 08 0B 02 02 01 02 00 00                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x01 (Audio Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 02 00 00 01 01 00 00                        .........

        ------ Audio Control Interface Header Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01 (Header)
bcdADC                   : 0x0100
wTotalLength             : 0x0026 (38 bytes)
bInCollection            : 0x01
baInterfaceNr[1]         : 0x03
Data (HexDump)           : 09 24 01 00 01 26 00 01 03                        .$...&...

        ------- Audio Control Input Terminal Descriptor -------
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Input Terminal)
bTerminalID              : 0x01
wTerminalType            : 0x0201 (Microphone)
bAssocTerminal           : 0x00
bNrChannels              : 0x01 (1 channel)
wChannelConfig           : 0x0000 (-)
iChannelNames            : 0x00 (No String Descriptor)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 0C 24 02 01 01 02 00 01 00 00 00 00               .$..........

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x03
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x01 (1)
bSourceID                : 0x05 (5)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 03 03 01 01 01 05 00                        .$.......

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x06 (Feature Unit)
bUnitID                  : 0x05 (5)
bSourceID                : 0x01 (1)
bControlSize             : 0x01 (1 byte per control)
bmaControls[0]           : 0x03
 D0: Mute                : 1
 D1: Volume              : 1
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
bmaControls[1]           : 0x00
 D0: Mute                : 0
 D1: Volume              : 0
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
iFeature                 : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 06 05 01 01 03 00 00                        .$.......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 03 00 00 01 02 00 00                        .........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x01
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 03 01 01 01 02 00 00                        .........

        -------- Audio Streaming Interface Descriptor ---------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01
bTerminalLink            : 0x03
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 03 01 01 00                              .$.....

        ------- Audio Streaming Format Type Descriptor --------
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Format Type)
bFormatType              : 0x01 (FORMAT_TYPE_I)
bNrChannels              : 0x01 (1 channel)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x01 (supports 1 sample frequency)
tSamFreq[1]              : 0x03E80 (16000 Hz)
Data (HexDump)           : 0B 24 02 01 01 02 10 01 80 3E 00                  .$.......>.

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x86 (Direction=IN EndpointID=6)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0044
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x44 (68 bytes per packet)
bInterval                : 0x01 (1 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 86 05 44 00 01 00 00                        ....D....

        ----------- Audio Data Endpoint Descriptor ------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x25 (Audio Endpoint Descriptor)
bDescriptorSubtype       : 0x01 (General)
bmAttributes             : 0x01
 D0   : Sampling Freq    : 0x01 (supported)
 D1   : Pitch            : 0x00 (not supported)
 D6..2: Reserved         : 0x00
 D7   : MaxPacketsOnly   : 0x00 (no)
bLockDelayUnits          : 0x00 (Undefined)
wLockDelay               : 0x0000
Data (HexDump)           : 07 25 01 01 00 00 00                              .%.....

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x02
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 03 02 01 01 02 00 00                        .........

        -------- Audio Streaming Interface Descriptor ---------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01
bTerminalLink            : 0x03
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 03 01 01 00                              .$.....

        ------- Audio Streaming Format Type Descriptor --------
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Format Type)
bFormatType              : 0x01 (FORMAT_TYPE_I)
bNrChannels              : 0x01 (1 channel)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x01 (supports 1 sample frequency)
tSamFreq[1]              : 0x05DC0 (24000 Hz)
Data (HexDump)           : 0B 24 02 01 01 02 10 01 C0 5D 00                  .$.......].

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x86 (Direction=IN EndpointID=6)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0064
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x64 (100 bytes per packet)
bInterval                : 0x01 (1 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 86 05 64 00 01 00 00                        ....d....

        ----------- Audio Data Endpoint Descriptor ------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x25 (Audio Endpoint Descriptor)
bDescriptorSubtype       : 0x01 (General)
bmAttributes             : 0x01
 D0   : Sampling Freq    : 0x01 (supported)
 D1   : Pitch            : 0x00 (not supported)
 D6..2: Reserved         : 0x00
 D7   : MaxPacketsOnly   : 0x00 (no)
bLockDelayUnits          : 0x00 (Undefined)
wLockDelay               : 0x0000
Data (HexDump)           : 07 25 01 01 00 00 00                              .%.....

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x03
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 03 03 01 01 02 00 00                        .........

        -------- Audio Streaming Interface Descriptor ---------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01
bTerminalLink            : 0x03
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 03 01 01 00                              .$.....

        ------- Audio Streaming Format Type Descriptor --------
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Format Type)
bFormatType              : 0x01 (FORMAT_TYPE_I)
bNrChannels              : 0x01 (1 channel)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x01 (supports 1 sample frequency)
tSamFreq[1]              : 0x07D00 (32000 Hz)
Data (HexDump)           : 0B 24 02 01 01 02 10 01 00 7D 00                  .$.......}.

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x86 (Direction=IN EndpointID=6)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0084
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x84 (132 bytes per packet)
bInterval                : 0x01 (1 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 86 05 84 00 01 00 00                        .........

        ----------- Audio Data Endpoint Descriptor ------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x25 (Audio Endpoint Descriptor)
bDescriptorSubtype       : 0x01 (General)
bmAttributes             : 0x01
 D0   : Sampling Freq    : 0x01 (supported)
 D1   : Pitch            : 0x00 (not supported)
 D6..2: Reserved         : 0x00
 D7   : MaxPacketsOnly   : 0x00 (no)
bLockDelayUnits          : 0x00 (Undefined)
wLockDelay               : 0x0000
Data (HexDump)           : 07 25 01 01 00 00 00                              .%.....

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x04
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 03 04 01 01 02 00 00                        .........

        -------- Audio Streaming Interface Descriptor ---------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01
bTerminalLink            : 0x03
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 03 01 01 00                              .$.....

        ------- Audio Streaming Format Type Descriptor --------
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Format Type)
bFormatType              : 0x01 (FORMAT_TYPE_I)
bNrChannels              : 0x01 (1 channel)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x01 (supports 1 sample frequency)
tSamFreq[1]              : 0x0BB80 (48000 Hz)
Data (HexDump)           : 0B 24 02 01 01 02 10 01 80 BB 00                  .$.........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x86 (Direction=IN EndpointID=6)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x00C4
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0xC4 (196 bytes per packet)
bInterval                : 0x01 (1 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 86 05 C4 00 01 00 00                        .........

        ----------- Audio Data Endpoint Descriptor ------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x25 (Audio Endpoint Descriptor)
bDescriptorSubtype       : 0x01 (General)
bmAttributes             : 0x01
 D0   : Sampling Freq    : 0x01 (supported)
 D1   : Pitch            : 0x00 (not supported)
 D6..2: Reserved         : 0x00
 D7   : MaxPacketsOnly   : 0x00 (no)
bLockDelayUnits          : 0x00 (Undefined)
wLockDelay               : 0x0000
Data (HexDump)           : 07 25 01 01 00 00 00                              .%.....

      -------------------- String Descriptors -------------------
             ------ String Descriptor 0 ------
bLength                  : 0x04 (4 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language ID[0]           : 0x0409 (English - United States)
Data (HexDump)           : 04 03 09 04                                       ....
             ------ String Descriptor 2 ------
bLength                  : 0x12 (18 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "E190CC90"
Data (HexDump)           : 12 03 45 00 31 00 39 00 30 00 43 00 43 00 39 00   ..E.1.9.0.C.C.9.
                           30 00                                             0.
*/

namespace logitech_c270 {
const uint8_t dev_desc[] = {
    0x12, 0x01, 0x00, 0x02, 0xEF, 0x02, 0x01, 0x40, 0x6D, 0x04, 0x25, 0x08, 0x12, 0x00, 0x00, 0x00,
    0x02, 0x01
};
const uint8_t cfg_desc[] = {
    0x09, 0x02, 0xA2, 0x09, 0x04, 0x01, 0x00, 0x80, 0xFA, 0x08, 0x0B, 0x00, 0x02, 0x0E, 0x03, 0x00,
    0x00, 0x09, 0x04, 0x00, 0x00, 0x01, 0x0E, 0x01, 0x00, 0x00, 0x0D, 0x24, 0x01, 0x00, 0x01, 0xA0,
    0x00, 0x00, 0x6C, 0xDC, 0x02, 0x01, 0x01, 0x12, 0x24, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0E, 0x00, 0x00, 0x0B, 0x24, 0x05, 0x02, 0x01, 0x00, 0x40,
    0x02, 0x5B, 0x17, 0x00, 0x1B, 0x24, 0x06, 0x03, 0xE4, 0x8E, 0x67, 0x69, 0x0F, 0x41, 0xDB, 0x40,
    0xA8, 0x50, 0x74, 0x20, 0xD7, 0xD8, 0x24, 0x0E, 0x08, 0x01, 0x02, 0x02, 0x3F, 0x03, 0x00, 0x1B,
    0x24, 0x06, 0x04, 0x15, 0x02, 0xE4, 0x49, 0x34, 0xF4, 0xFE, 0x47, 0xB1, 0x58, 0x0E, 0x88, 0x50,
    0x23, 0xE5, 0x1B, 0x03, 0x01, 0x02, 0x02, 0x09, 0x01, 0x00, 0x1C, 0x24, 0x06, 0x06, 0xA9, 0x4C,
    0x5D, 0x1F, 0x11, 0xDE, 0x87, 0x44, 0x84, 0x0D, 0x50, 0x93, 0x3C, 0x8E, 0xC8, 0xD1, 0x12, 0x01,
    0x04, 0x03, 0xFF, 0xFF, 0x03, 0x00, 0x1B, 0x24, 0x06, 0x07, 0x21, 0x2D, 0xE5, 0xFF, 0x30, 0x80,
    0x2C, 0x4E, 0x82, 0xD9, 0xF5, 0x87, 0xD0, 0x05, 0x40, 0xBD, 0x02, 0x01, 0x04, 0x02, 0x00, 0x03,
    0x00, 0x09, 0x24, 0x03, 0x05, 0x01, 0x01, 0x00, 0x04, 0x00, 0x07, 0x05, 0x87, 0x03, 0x10, 0x00,
    0x08, 0x05, 0x25, 0x03, 0x10, 0x00, 0x09, 0x04, 0x01, 0x00, 0x00, 0x0E, 0x02, 0x00, 0x00, 0x10,
    0x24, 0x01, 0x03, 0x36, 0x07, 0x81, 0x00, 0x05, 0x01, 0x00, 0x00, 0x01, 0x00, 0x04, 0x04, 0x1B,
    0x24, 0x04, 0x01, 0x13, 0x59, 0x55, 0x59, 0x32, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0xAA,
    0x00, 0x38, 0x9B, 0x71, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x32, 0x24, 0x05, 0x01, 0x01, 0x80,
    0x02, 0xE0, 0x01, 0x00, 0x00, 0x77, 0x01, 0x00, 0x00, 0xCA, 0x08, 0x00, 0x60, 0x09, 0x00, 0x15,
    0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00,
    0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x05, 0x02,
    0x01, 0xA0, 0x00, 0x78, 0x00, 0x00, 0x70, 0x17, 0x00, 0x00, 0xA0, 0x8C, 0x00, 0x00, 0x96, 0x00,
    0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1,
    0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24,
    0x05, 0x03, 0x01, 0xB0, 0x00, 0x90, 0x00, 0x00, 0xF0, 0x1E, 0x00, 0x00, 0xA0, 0xB9, 0x00, 0x00,
    0xC6, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00,
    0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00,
    0x32, 0x24, 0x05, 0x04, 0x01, 0x40, 0x01, 0xB0, 0x00, 0x00, 0xC0, 0x44, 0x00, 0x00, 0x80, 0x9C,
    0x01, 0x00, 0xB8, 0x01, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A,
    0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84,
    0x1E, 0x00, 0x32, 0x24, 0x05, 0x05, 0x01, 0x40, 0x01, 0xF0, 0x00, 0x00, 0xC0, 0x5D, 0x00, 0x00,
    0x80, 0x32, 0x02, 0x00, 0x58, 0x02, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00,
    0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00,
    0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x05, 0x06, 0x01, 0x60, 0x01, 0x20, 0x01, 0x00, 0xC0, 0x7B,
    0x00, 0x00, 0x80, 0xE6, 0x02, 0x00, 0x18, 0x03, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16,
    0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42,
    0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x05, 0x07, 0x01, 0xB0, 0x01, 0xF0, 0x00, 0x00,
    0x90, 0x7E, 0x00, 0x00, 0x60, 0xF7, 0x02, 0x00, 0x2A, 0x03, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06,
    0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00,
    0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x05, 0x08, 0x01, 0x20, 0x02, 0x20,
    0x01, 0x00, 0x40, 0xBF, 0x00, 0x00, 0x80, 0x7B, 0x04, 0x00, 0xC8, 0x04, 0x00, 0x15, 0x16, 0x05,
    0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C,
    0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x05, 0x09, 0x01, 0x80,
    0x02, 0x68, 0x01, 0x00, 0x40, 0x19, 0x01, 0x00, 0x80, 0x97, 0x06, 0x00, 0x08, 0x07, 0x00, 0x15,
    0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00,
    0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x2E, 0x24, 0x05, 0x0A,
    0x01, 0xF0, 0x02, 0xA0, 0x01, 0x00, 0xE0, 0x7D, 0x01, 0x00, 0x60, 0x75, 0x07, 0x00, 0x8C, 0x09,
    0x00, 0x80, 0x1A, 0x06, 0x00, 0x05, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C,
    0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x2A, 0x24, 0x05, 0x0B, 0x01, 0x20,
    0x03, 0xC0, 0x01, 0x00, 0x80, 0xB5, 0x01, 0x00, 0x00, 0xD6, 0x06, 0x00, 0xF0, 0x0A, 0x00, 0x20,
    0xA1, 0x07, 0x00, 0x04, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00,
    0x80, 0x84, 0x1E, 0x00, 0x2A, 0x24, 0x05, 0x0C, 0x01, 0x20, 0x03, 0x58, 0x02, 0x00, 0xF0, 0x49,
    0x02, 0x00, 0xC0, 0x27, 0x09, 0x00, 0xA6, 0x0E, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x04, 0x20, 0xA1,
    0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x2A, 0x24,
    0x05, 0x0D, 0x01, 0x60, 0x03, 0xE0, 0x01, 0x00, 0x40, 0xFA, 0x01, 0x00, 0x00, 0xE9, 0x07, 0x00,
    0xA8, 0x0C, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x04, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00,
    0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x26, 0x24, 0x05, 0x0E, 0x01, 0xC0, 0x03, 0x20,
    0x02, 0x00, 0x80, 0x7D, 0x02, 0x00, 0x80, 0x78, 0x07, 0x00, 0xF0, 0x0F, 0x00, 0x2A, 0x2C, 0x0A,
    0x00, 0x03, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x22, 0x24,
    0x05, 0x0F, 0x01, 0xC0, 0x03, 0xD0, 0x02, 0x00, 0xC0, 0x4B, 0x03, 0x00, 0x80, 0x97, 0x06, 0x00,
    0x18, 0x15, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x02, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00,
    0x22, 0x24, 0x05, 0x10, 0x01, 0x00, 0x04, 0x40, 0x02, 0x00, 0x00, 0xD0, 0x02, 0x00, 0x00, 0xA0,
    0x05, 0x00, 0x00, 0x12, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x02, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84,
    0x1E, 0x00, 0x22, 0x24, 0x05, 0x11, 0x01, 0xA0, 0x04, 0x90, 0x02, 0x00, 0x20, 0xB4, 0x03, 0x00,
    0x40, 0x68, 0x07, 0x00, 0xB4, 0x17, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x02, 0x40, 0x42, 0x0F, 0x00,
    0x80, 0x84, 0x1E, 0x00, 0x22, 0x24, 0x05, 0x12, 0x01, 0x00, 0x05, 0xD0, 0x02, 0x00, 0x00, 0x65,
    0x04, 0x00, 0x00, 0xCA, 0x08, 0x00, 0x20, 0x1C, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x02, 0x55, 0x58,
    0x14, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x22, 0x24, 0x05, 0x13, 0x01, 0x00, 0x05, 0xC0, 0x03, 0x00,
    0x00, 0xDC, 0x05, 0x00, 0x00, 0xB8, 0x0B, 0x00, 0x80, 0x25, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x02,
    0x55, 0x58, 0x14, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x06, 0x24, 0x0D, 0x01, 0x01, 0x04, 0x0B, 0x24,
    0x06, 0x02, 0x13, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x32, 0x24, 0x07, 0x01, 0x01, 0x80, 0x02,
    0xE0, 0x01, 0x00, 0x00, 0x77, 0x01, 0x00, 0x00, 0xCA, 0x08, 0x00, 0x60, 0x09, 0x00, 0x15, 0x16,
    0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A,
    0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x07, 0x02, 0x01,
    0xA0, 0x00, 0x78, 0x00, 0x00, 0x70, 0x17, 0x00, 0x00, 0xA0, 0x8C, 0x00, 0x00, 0x96, 0x00, 0x00,
    0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07,
    0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x07,
    0x03, 0x01, 0xB0, 0x00, 0x90, 0x00, 0x00, 0xF0, 0x1E, 0x00, 0x00, 0xA0, 0xB9, 0x00, 0x00, 0xC6,
    0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20,
    0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32,
    0x24, 0x07, 0x04, 0x01, 0x40, 0x01, 0xB0, 0x00, 0x00, 0xC0, 0x44, 0x00, 0x00, 0x80, 0x9C, 0x01,
    0x00, 0xB8, 0x01, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06,
    0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E,
    0x00, 0x32, 0x24, 0x07, 0x05, 0x01, 0x40, 0x01, 0xF0, 0x00, 0x00, 0xC0, 0x5D, 0x00, 0x00, 0x80,
    0x32, 0x02, 0x00, 0x58, 0x02, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80,
    0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80,
    0x84, 0x1E, 0x00, 0x32, 0x24, 0x07, 0x06, 0x01, 0x60, 0x01, 0x20, 0x01, 0x00, 0xC0, 0x7B, 0x00,
    0x00, 0x80, 0xE6, 0x02, 0x00, 0x18, 0x03, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05,
    0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F,
    0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x07, 0x07, 0x01, 0xB0, 0x01, 0xF0, 0x00, 0x00, 0x90,
    0x7E, 0x00, 0x00, 0x60, 0xF7, 0x02, 0x00, 0x2A, 0x03, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15,
    0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40,
    0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x07, 0x08, 0x01, 0x20, 0x02, 0x20, 0x01,
    0x00, 0x40, 0xBF, 0x00, 0x00, 0x80, 0x7B, 0x04, 0x00, 0xC8, 0x04, 0x00, 0x15, 0x16, 0x05, 0x00,
    0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A,
    0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x07, 0x09, 0x01, 0x80, 0x02,
    0x68, 0x01, 0x00, 0x40, 0x19, 0x01, 0x00, 0x80, 0x97, 0x06, 0x00, 0x08, 0x07, 0x00, 0x15, 0x16,
    0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A,
    0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x07, 0x0A, 0x01,
    0xF0, 0x02, 0xA0, 0x01, 0x00, 0xE0, 0x7D, 0x01, 0x00, 0x40, 0xF3, 0x08, 0x00, 0x8C, 0x09, 0x00,
    0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07,
    0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x07,
    0x0B, 0x01, 0x20, 0x03, 0xC0, 0x01, 0x00, 0x80, 0xB5, 0x01, 0x00, 0x00, 0x41, 0x0A, 0x00, 0xF0,
    0x0A, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20,
    0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32,
    0x24, 0x07, 0x0C, 0x01, 0x20, 0x03, 0x58, 0x02, 0x00, 0xF0, 0x49, 0x02, 0x00, 0xA0, 0xBB, 0x0D,
    0x00, 0xA6, 0x0E, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06,
    0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E,
    0x00, 0x32, 0x24, 0x07, 0x0D, 0x01, 0x60, 0x03, 0xE0, 0x01, 0x00, 0x40, 0xFA, 0x01, 0x00, 0x80,
    0xDD, 0x0B, 0x00, 0xA8, 0x0C, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80,
    0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80,
    0x84, 0x1E, 0x00, 0x32, 0x24, 0x07, 0x0E, 0x01, 0xC0, 0x03, 0x20, 0x02, 0x00, 0x80, 0x7D, 0x02,
    0x00, 0x00, 0xF1, 0x0E, 0x00, 0xF0, 0x0F, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05,
    0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F,
    0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x07, 0x0F, 0x01, 0xC0, 0x03, 0xD0, 0x02, 0x00, 0xC0,
    0x4B, 0x03, 0x00, 0x80, 0xC6, 0x13, 0x00, 0x18, 0x15, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15,
    0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40,
    0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x07, 0x10, 0x01, 0x00, 0x04, 0x40, 0x02,
    0x00, 0x00, 0xD0, 0x02, 0x00, 0x00, 0xE0, 0x10, 0x00, 0x00, 0x12, 0x00, 0x15, 0x16, 0x05, 0x00,
    0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A,
    0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x07, 0x11, 0x01, 0xA0, 0x04,
    0x90, 0x02, 0x00, 0x20, 0xB4, 0x03, 0x00, 0xC0, 0x38, 0x16, 0x00, 0xB4, 0x17, 0x00, 0x15, 0x16,
    0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A,
    0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x07, 0x12, 0x01,
    0x00, 0x05, 0xD0, 0x02, 0x00, 0x00, 0x65, 0x04, 0x00, 0x00, 0x5E, 0x1A, 0x00, 0x20, 0x1C, 0x00,
    0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07,
    0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x07,
    0x13, 0x01, 0x00, 0x05, 0xC0, 0x03, 0x00, 0x00, 0xDC, 0x05, 0x00, 0x00, 0x28, 0x23, 0x00, 0x80,
    0x25, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20,
    0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x06,
    0x24, 0x0D, 0x01, 0x01, 0x04, 0x09, 0x04, 0x01, 0x01, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05,
    0x81, 0x05, 0xC0, 0x00, 0x01, 0x09, 0x04, 0x01, 0x02, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05,
    0x81, 0x05, 0x80, 0x01, 0x01, 0x09, 0x04, 0x01, 0x03, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05,
    0x81, 0x05, 0x00, 0x02, 0x01, 0x09, 0x04, 0x01, 0x04, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05,
    0x81, 0x05, 0x80, 0x02, 0x01, 0x09, 0x04, 0x01, 0x05, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05,
    0x81, 0x05, 0x20, 0x03, 0x01, 0x09, 0x04, 0x01, 0x06, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05,
    0x81, 0x05, 0xB0, 0x03, 0x01, 0x09, 0x04, 0x01, 0x07, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05,
    0x81, 0x05, 0x80, 0x0A, 0x01, 0x09, 0x04, 0x01, 0x08, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05,
    0x81, 0x05, 0x20, 0x0B, 0x01, 0x09, 0x04, 0x01, 0x09, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05,
    0x81, 0x05, 0xE0, 0x0B, 0x01, 0x09, 0x04, 0x01, 0x0A, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05,
    0x81, 0x05, 0x80, 0x13, 0x01, 0x09, 0x04, 0x01, 0x0B, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05,
    0x81, 0x05, 0xFC, 0x13, 0x01, 0x08, 0x0B, 0x02, 0x02, 0x01, 0x02, 0x00, 0x00, 0x09, 0x04, 0x02,
    0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x09, 0x24, 0x01, 0x00, 0x01, 0x26, 0x00, 0x01, 0x03, 0x0C,
    0x24, 0x02, 0x01, 0x01, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x09, 0x24, 0x03, 0x03, 0x01,
    0x01, 0x01, 0x05, 0x00, 0x09, 0x24, 0x06, 0x05, 0x01, 0x01, 0x03, 0x00, 0x00, 0x09, 0x04, 0x03,
    0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x09, 0x04, 0x03, 0x01, 0x01, 0x01, 0x02, 0x00, 0x00, 0x07,
    0x24, 0x01, 0x03, 0x01, 0x01, 0x00, 0x0B, 0x24, 0x02, 0x01, 0x01, 0x02, 0x10, 0x01, 0x80, 0x3E,
    0x00, 0x09, 0x05, 0x86, 0x05, 0x44, 0x00, 0x04, 0x00, 0x00, 0x07, 0x25, 0x01, 0x01, 0x00, 0x00,
    0x00, 0x09, 0x04, 0x03, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x07, 0x24, 0x01, 0x03, 0x01, 0x01,
    0x00, 0x0B, 0x24, 0x02, 0x01, 0x01, 0x02, 0x10, 0x01, 0xC0, 0x5D, 0x00, 0x09, 0x05, 0x86, 0x05,
    0x64, 0x00, 0x04, 0x00, 0x00, 0x07, 0x25, 0x01, 0x01, 0x00, 0x00, 0x00, 0x09, 0x04, 0x03, 0x03,
    0x01, 0x01, 0x02, 0x00, 0x00, 0x07, 0x24, 0x01, 0x03, 0x01, 0x01, 0x00, 0x0B, 0x24, 0x02, 0x01,
    0x01, 0x02, 0x10, 0x01, 0x00, 0x7D, 0x00, 0x09, 0x05, 0x86, 0x05, 0x84, 0x00, 0x04, 0x00, 0x00,
    0x07, 0x25, 0x01, 0x01, 0x00, 0x00, 0x00, 0x09, 0x04, 0x03, 0x04, 0x01, 0x01, 0x02, 0x00, 0x00,
    0x07, 0x24, 0x01, 0x03, 0x01, 0x01, 0x00, 0x0B, 0x24, 0x02, 0x01, 0x01, 0x02, 0x10, 0x01, 0x80,
    0xBB, 0x00, 0x09, 0x05, 0x86, 0x05, 0xC4, 0x00, 0x04, 0x00, 0x00, 0x07, 0x25, 0x01, 0x01, 0x00,
    0x00, 0x00
};
}
