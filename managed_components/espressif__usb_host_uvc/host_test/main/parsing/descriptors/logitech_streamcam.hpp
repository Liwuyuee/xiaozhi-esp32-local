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
Device Description       : USB Composite Device
Device ID                : USB\VID_046D&PID_0893\5079EB25
Hardware IDs             : USB\VID_046D&PID_0893&REV_0017 USB\VID_046D&PID_0893
Driver KeyName           : {36fc9e60-c465-11cf-8056-444553540000}\0098 (GUID_DEVCLASS_USB)
Driver                   : \SystemRoot\System32\drivers\usbccgp.sys (Version: 10.0.19041.4474  Date: 2024-06-13)
Driver Inf               : C:\Windows\inf\usb.inf
Legacy BusType           : PNPBus
Class                    : USB
Class GUID               : {36fc9e60-c465-11cf-8056-444553540000} (GUID_DEVCLASS_USB)
Service                  : usbccgp
Enumerator               : USB
Location Info            : Port_#0004.Hub_#0009
Location IDs             : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(4), ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(4)
Container ID             : {6d7059ae-e6ab-5490-b0a5-ee8acac7dd52}
Manufacturer Info        : (Standard USB Host Controller)
Capabilities             : 0x94 (Removable, UniqueID, SurpriseRemovalOK)
Status                   : 0x0180600A (DN_DRIVER_LOADED, DN_STARTED, DN_DISABLEABLE, DN_REMOVABLE, DN_NT_ENUMERATOR, DN_NT_DRIVER)
Problem Code             : 0
Address                  : 4
HcDisableSelectiveSuspend: 0
EnableSelectiveSuspend   : 0
SelectiveSuspendEnabled  : 0
EnhancedPowerMgmtEnabled : 0
IdleInWorkingState       : 0
WakeFromSleepState       : 0
Power State              : D0 (supported: D0, D3, wake from D0)
 Child Device 1          : Logitech StreamCam
  Device Path            : \\?\USB#VID_046D&PID_0893&MI_00#8&35e311c5&0&0000#{e5323777-f976-4f5b-9b55-b94699c46e44}\global (STATIC_KSCATEGORY_VIDEO_CAMERA)
  Kernel Name            : \Device\00000379
  Device ID              : USB\VID_046D&PID_0893&MI_00\8&35E311C5&0&0000
  Class                  : Image
  Driver KeyName         : {6bdd1fc6-810f-11d0-bec7-08002be2092f}\0002 (GUID_DEVCLASS_IMAGE)
  Service                : usbvideo
  Location               : 0005.0000.0004.001.004.000.000.000.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(4)#USBMI(0)  PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(4)#USB(4)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(4)#USBMI(0)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(4)#USB(4)
 Child Device 2          : Logitech StreamCam (USB Audio Device)
  Device Path            : \\?\USB#VID_046D&PID_0893&MI_02#8&35e311c5&0&0002#{6994ad04-93ef-11d0-a3cc-00a0c9223196}\global (AM_KSCATEGORY_AUDIO)
  Kernel Name            : \Device\0000037a
  Device ID              : USB\VID_046D&PID_0893&MI_02\8&35E311C5&0&0002
  Class                  : MEDIA
  Driver KeyName         : {4d36e96c-e325-11ce-bfc1-08002be10318}\0013 (GUID_DEVCLASS_MEDIA)
  Service                : usbaudio
  Location               : 0005.0000.0004.001.004.000.000.000.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(4)#USBMI(2)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(4)#USBMI(2)
   Child Device 1        : Microphone (Logitech StreamCam) (Audio Endpoint)
    Device ID            : SWD\MMDEVAPI\{0.0.1.00000000}.{05B0DFB8-996D-4E3F-8A5B-183A37F30CD8}
    Class                : AudioEndpoint
    Driver KeyName       : {c166523c-fe0c-4a94-a586-f1a80cfbbf3e}\0039 (AUDIOENDPOINT_CLASS_UUID)
 Child Device 3          : Logitech StreamCam
  Device ID              : USB\VID_046D&PID_0893&MI_04\8&35E311C5&0&0004
  Location               : 0005.0000.0004.001.004.000.000.000.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(4)#USBMI(4)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(4)#USBMI(4)
  Problem                : 28 (CM_PROB_FAILED_INSTALL)
 Child Device 4          : USB Input Device
  Device ID              : USB\VID_046D&PID_0893&MI_05\8&35E311C5&0&0005
  Class                  : HIDClass
  Driver KeyName         : {745a17a0-74d3-11d0-b6fe-00a0c90f57da}\0048 (GUID_DEVCLASS_HIDCLASS)
  Service                : HidUsb
  Location               : 0005.0000.0004.001.004.000.000.000.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(4)#USBMI(5)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(4)#USBMI(5)
   Child Device 1        : HID-compliant vendor-defined device
    Device Path          : \\?\HID#VID_046D&PID_0893&MI_05#9&3b5eb197&0&0000#{4d1e55b2-f16f-11cf-88cb-001111000030} (GUID_DEVINTERFACE_HID)
    Kernel Name          : \Device\0000037f
    Device ID            : HID\VID_046D&PID_0893&MI_05\9&3B5EB197&0&0000
    Class                : HIDClass
    Driver KeyName       : {745a17a0-74d3-11d0-b6fe-00a0c90f57da}\0049 (GUID_DEVCLASS_HIDCLASS)

        +++++++++++++++++ Registry USB Flags +++++++++++++++++
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\usbflags\046D08930017
 osvc                    : REG_BINARY 00 00

        ---------------- Connection Information ---------------
Connection Index         : 0x04 (Port 4)
Connection Status        : 0x01 (DeviceConnected)
Current Config Value     : 0x01 (Configuration 1)
Device Address           : 0x04 (4)
Is Hub                   : 0x00 (no)
Device Bus Speed         : 0x02 (High-Speed)
Number Of Open Pipes     : 0x03 (3 pipes to data endpoints)
Pipe[0]                  : EndpointID=5  Direction=IN   ScheduleOffset=0  Type=Interrupt
Pipe[1]                  : EndpointID=3  Direction=IN   ScheduleOffset=0  Type=Bulk
Pipe[2]                  : EndpointID=7  Direction=IN   ScheduleOffset=0  Type=Interrupt
Data (HexDump)           : 04 00 00 00 12 01 10 02 EF 02 01 40 6D 04 93 08   ...........@m...
                           17 00 00 02 03 01 01 02 00 04 00 03 00 00 00 01   ................
                           00 00 00 07 05 85 03 40 00 08 00 00 00 00 07 05   .......@........
                           83 02 00 02 00 00 00 00 00 07 05 87 03 02 00 06   ................
                           00 00 00 00                                       ....

        --------------- Connection Information V2 -------------
Connection Index         : 0x04 (4)
Length                   : 0x10 (16 bytes)
SupportedUsbProtocols    : 0x03
 Usb110                  : 1 (yes, port supports USB 1.1)
 Usb200                  : 1 (yes, port supports USB 2.0)
 Usb300                  : 0 (no, port not supports USB 3.0)
 ReservedMBZ             : 0x00
Flags                    : 0x02
 DevIsOpAtSsOrHigher     : 0 (Device is not operating at SuperSpeed or higher)
 DevIsSsCapOrHigher      : 1 (Device is SuperSpeed capable or higher)
 DevIsOpAtSsPlusOrHigher : 0 (Device is not operating at SuperSpeedPlus or higher)
 DevIsSsPlusCapOrHigher  : 0 (Device is not SuperSpeedPlus capable or higher)
 ReservedMBZ             : 0x00
Data (HexDump)           : 04 00 00 00 10 00 00 00 03 00 00 00 02 00 00 00   ................

    ---------------------- Device Descriptor ----------------------
bLength                  : 0x12 (18 bytes)
bDescriptorType          : 0x01 (Device Descriptor)
bcdUSB                   : 0x210 (USB Version 2.10)
bDeviceClass             : 0xEF (Miscellaneous)
bDeviceSubClass          : 0x02
bDeviceProtocol          : 0x01 (IAD - Interface Association Descriptor)
bMaxPacketSize0          : 0x40 (64 bytes)
idVendor                 : 0x046D (Logitech Inc.)
idProduct                : 0x0893
bcdDevice                : 0x0017
iManufacturer            : 0x00 (No String Descriptor)
iProduct                 : 0x02 (String Descriptor 2)
 Language 0x0409         : "Logitech StreamCam"
iSerialNumber            : 0x03 (String Descriptor 3)
 Language 0x0409         : "5079EB25"
bNumConfigurations       : 0x01 (1 Configuration)
Data (HexDump)           : 12 01 10 02 EF 02 01 40 6D 04 93 08 17 00 00 02   .......@m.......
                           03 01                                             ..

    ------------------ Configuration Descriptor -------------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x02 (Configuration Descriptor)
wTotalLength             : 0x0709 (1801 bytes)
bNumInterfaces           : 0x06 (6 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x00 (No String Descriptor)
bmAttributes             : 0x80
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x00 (no)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0xFA (500 mA)
Data (HexDump)           : 09 02 09 07 06 01 00 80 FA 08 0B 00 02 0E 03 00   ................
                           00 09 04 00 00 01 0E 01 00 00 0D 24 01 00 01 D8   ...........$....
                           00 80 C3 C9 01 01 01 12 24 02 01 01 02 00 00 00   ........$.......
                           00 00 00 00 00 03 2E 2A 02 0B 24 05 03 01 00 40   .......*..$....@
                           02 5B 17 00 1B 24 06 0E 6A D1 49 2C B8 32 85 44   .[...$..j.I,.2.D
                           3E A8 64 3A 15 23 62 F2 06 01 03 02 3F 00 00 1B   >.d:.#b.....?...
                           24 06 06 D0 9E E4 23 78 11 31 4F AE 52 D2 FB 8A   $.....#x.1O.R...
                           8D 3B 48 0E 01 03 02 FF 6F 00 1B 24 06 08 E4 8E   .;H.....o..$....
                           67 69 0F 41 DB 40 A8 50 74 20 D7 D8 24 0E 08 01   gi.A.@.Pt ..$...
                           03 02 3F 0F 00 1C 24 06 09 A9 4C 5D 1F 11 DE 87   ..?...$...L]....
                           44 84 0D 50 93 3C 8E C8 D1 12 01 03 03 FF FF 03   D..P.<..........
                           00 1C 24 06 0A 15 02 E4 49 34 F4 FE 47 B1 58 0E   ..$.....I4..G.X.
                           88 50 23 E5 1B 0B 01 03 03 FA FF 01 00 1C 24 06   .P#...........$.
                           0B 21 2D E5 FF 30 80 2C 4E 82 D9 F5 87 D0 05 40   .!-..0.,N......@
                           BD 04 01 03 03 00 41 01 00 09 24 03 04 01 01 00   ......A...$.....
                           03 00 07 05 85 03 40 00 08 05 25 03 40 00 09 04   ......@...%.@...
                           01 00 00 0E 02 00 00 0F 24 01 02 31 04 81 00 04   ........$..1....
                           00 00 00 01 00 00 1B 24 04 01 0A 59 55 59 32 00   .......$...YUY2.
                           00 10 00 80 00 00 AA 00 38 9B 71 10 01 00 00 00   ........8.q.....
                           00 36 24 05 01 00 80 02 E0 01 00 00 77 01 00 00   .6$.........w...
                           CA 08 00 60 09 00 15 16 05 00 07 15 16 05 00 9A   ...`............
                           5B 06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55   [.. ...*,..@B..U
                           58 14 00 80 84 1E 00 36 24 05 02 00 B0 00 90 00   X......6$.......
                           00 F0 1E 00 00 A0 B9 00 00 C6 00 00 15 16 05 00   ................
                           07 15 16 05 00 9A 5B 06 00 20 A1 07 00 2A 2C 0A   ......[.. ...*,.
                           00 40 42 0F 00 55 58 14 00 80 84 1E 00 36 24 05   .@B..UX......6$.
                           03 00 40 01 F0 00 00 C0 5D 00 00 80 32 02 00 58   ..@.....]...2..X
                           02 00 15 16 05 00 07 15 16 05 00 9A 5B 06 00 20   ............[..
                           A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58 14 00 80   ...*,..@B..UX...
                           84 1E 00 36 24 05 04 00 A8 01 F0 00 00 38 7C 00   ...6$........8|.
                           00 50 E9 02 00 1B 03 00 15 16 05 00 07 15 16 05   .P..............
                           00 9A 5B 06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F   ..[.. ...*,..@B.
                           00 55 58 14 00 80 84 1E 00 36 24 05 05 00 80 02   .UX......6$.....
                           68 01 00 40 19 01 00 80 97 06 00 08 07 00 15 16   h..@............
                           05 00 07 15 16 05 00 9A 5B 06 00 20 A1 07 00 2A   ........[.. ...*
                           2C 0A 00 40 42 0F 00 55 58 14 00 80 84 1E 00 36   ,..@B..UX......6
                           24 05 06 00 50 03 E0 01 00 E0 F0 01 00 40 A5 0B   $...P........@..
                           00 6C 0C 00 15 16 05 00 07 15 16 05 00 9A 5B 06   .l............[.
                           00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58 14   . ...*,..@B..UX.
                           00 80 84 1E 00 2A 24 05 07 00 C0 03 1C 02 00 D0   .....*$.........
                           78 02 00 70 6A 07 00 D2 0F 00 2A 2C 0A 00 04 2A   x..pj.....*,...*
                           2C 0A 00 40 42 0F 00 55 58 14 00 80 84 1E 00 26   ,..@B..UX......&
                           24 05 08 00 00 05 D0 02 00 00 65 04 00 00 CA 08   $.........e.....
                           00 20 1C 00 40 42 0F 00 03 40 42 0F 00 55 58 14   . ..@B...@B..UX.
                           00 80 84 1E 00 22 24 05 09 00 40 06 80 03 00 00   ....."$...@.....
                           D6 06 00 00 41 0A 00 C0 2B 00 55 58 14 00 02 55   ....A...+.UX...U
                           58 14 00 80 84 1E 00 1E 24 05 0A 00 80 07 38 04   X.......$.....8.
                           00 40 E3 09 00 40 E3 09 00 48 3F 00 80 84 1E 00   .@...@...H?.....
                           01 80 84 1E 00 06 24 0D 01 01 04 0B 24 06 02 0A   ......$.....$...
                           01 01 00 00 00 00 36 24 07 01 00 80 02 E0 01 00   ......6$........
                           00 77 01 00 00 CA 08 00 60 09 00 15 16 05 00 07   .w......`.......
                           15 16 05 00 9A 5B 06 00 20 A1 07 00 2A 2C 0A 00   .....[.. ...*,..
                           40 42 0F 00 55 58 14 00 80 84 1E 00 36 24 07 02   @B..UX......6$..
                           00 B0 00 90 00 00 F0 1E 00 00 A0 B9 00 00 C6 00   ................
                           00 15 16 05 00 07 15 16 05 00 9A 5B 06 00 20 A1   ...........[.. .
                           07 00 2A 2C 0A 00 40 42 0F 00 55 58 14 00 80 84   ..*,..@B..UX....
                           1E 00 36 24 07 03 00 40 01 F0 00 00 C0 5D 00 00   ..6$...@.....]..
                           80 32 02 00 58 02 00 15 16 05 00 07 15 16 05 00   .2..X...........
                           9A 5B 06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00   .[.. ...*,..@B..
                           55 58 14 00 80 84 1E 00 36 24 07 04 00 A8 01 F0   UX......6$......
                           00 00 38 7C 00 00 50 E9 02 00 1B 03 00 15 16 05   ..8|..P.........
                           00 07 15 16 05 00 9A 5B 06 00 20 A1 07 00 2A 2C   .......[.. ...*,
                           0A 00 40 42 0F 00 55 58 14 00 80 84 1E 00 36 24   ..@B..UX......6$
                           07 05 00 80 02 68 01 00 40 19 01 00 80 97 06 00   .....h..@.......
                           08 07 00 15 16 05 00 07 15 16 05 00 9A 5B 06 00   .............[..
                           20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58 14 00    ...*,..@B..UX..
                           80 84 1E 00 36 24 07 06 00 50 03 E0 01 00 E0 F0   ....6$...P......
                           01 00 40 A5 0B 00 6C 0C 00 15 16 05 00 07 15 16   ..@...l.........
                           05 00 9A 5B 06 00 20 A1 07 00 2A 2C 0A 00 40 42   ...[.. ...*,..@B
                           0F 00 55 58 14 00 80 84 1E 00 36 24 07 07 00 C0   ..UX......6$....
                           03 1C 02 00 D0 78 02 00 E0 D4 0E 00 D2 0F 00 15   .....x..........
                           16 05 00 07 15 16 05 00 9A 5B 06 00 20 A1 07 00   .........[.. ...
                           2A 2C 0A 00 40 42 0F 00 55 58 14 00 80 84 1E 00   *,..@B..UX......
                           36 24 07 08 00 00 05 D0 02 00 00 65 04 00 00 5E   6$.........e...^
                           1A 00 20 1C 00 15 16 05 00 07 15 16 05 00 9A 5B   .. ............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00 36 24 07 09 00 40 06 80 03 00   ......6$...@....
                           00 D6 06 00 00 04 29 00 C0 2B 00 15 16 05 00 07   ......)..+......
                           15 16 05 00 9A 5B 06 00 20 A1 07 00 2A 2C 0A 00   .....[.. ...*,..
                           40 42 0F 00 55 58 14 00 80 84 1E 00 36 24 07 0A   @B..UX......6$..
                           00 80 07 38 04 00 40 E3 09 00 80 53 3B 00 48 3F   ...8..@....S;.H?
                           00 15 16 05 00 07 15 16 05 00 9A 5B 06 00 20 A1   ...........[.. .
                           07 00 2A 2C 0A 00 40 42 0F 00 55 58 14 00 80 84   ..*,..@B..UX....
                           1E 00 06 24 0D 01 01 04 09 04 01 01 01 0E 02 00   ...$............
                           00 07 05 81 05 C0 00 01 09 04 01 02 01 0E 02 00   ................
                           00 07 05 81 05 80 01 01 09 04 01 03 01 0E 02 00   ................
                           00 07 05 81 05 00 02 01 09 04 01 04 01 0E 02 00   ................
                           00 07 05 81 05 80 02 01 09 04 01 05 01 0E 02 00   ................
                           00 07 05 81 05 20 03 01 09 04 01 06 01 0E 02 00   ..... ..........
                           00 07 05 81 05 B0 03 01 09 04 01 07 01 0E 02 00   ................
                           00 07 05 81 05 80 0A 01 09 04 01 08 01 0E 02 00   ................
                           00 07 05 81 05 20 0B 01 09 04 01 09 01 0E 02 00   ..... ..........
                           00 07 05 81 05 E0 0B 01 09 04 01 0A 01 0E 02 00   ................
                           00 07 05 81 05 80 13 01 09 04 01 0B 01 0E 02 00   ................
                           00 07 05 81 05 00 14 01 08 0B 02 02 01 02 00 00   ................
                           09 04 02 00 00 01 01 00 00 09 24 01 00 01 26 00   ..........$...&.
                           01 03 0C 24 02 01 01 02 00 02 03 00 00 00 09 24   ...$...........$
                           03 03 01 01 00 05 00 08 24 06 05 01 01 03 00 09   ........$.......
                           04 03 00 00 01 02 00 00 09 04 03 01 01 01 02 00   ................
                           00 07 24 01 03 01 01 00 0B 24 02 01 02 02 10 01   ..$......$......
                           80 3E 00 09 05 84 05 44 00 04 00 00 07 25 01 01   .>.....D.....%..
                           00 00 00 09 04 03 02 01 01 02 00 00 07 24 01 03   .............$..
                           01 01 00 0B 24 02 01 02 02 10 01 C0 5D 00 09 05   ....$.......]...
                           84 05 64 00 04 00 00 07 25 01 01 00 00 00 09 04   ..d.....%.......
                           03 03 01 01 02 00 00 07 24 01 03 01 01 00 0B 24   ........$......$
                           02 01 02 02 10 01 00 7D 00 09 05 84 05 84 00 04   .......}........
                           00 00 07 25 01 01 00 00 00 09 04 03 04 01 01 02   ...%............
                           00 00 07 24 01 03 01 01 00 0B 24 02 01 02 02 10   ...$......$.....
                           01 80 BB 00 09 05 84 05 C4 00 04 00 00 07 25 01   ..............%.
                           01 00 00 00 09 04 04 00 01 FF FF 00 00 07 05 83   ................
                           02 00 02 00 06 30 00 00 00 00 09 04 05 00 01 03   .....0..........
                           00 00 00 09 21 11 01 00 01 22 6C 00 07 05 87 03   ....!...."l.....
                           02 00 06 06 30 00 00 02 00                        ....0....

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
wTotalLength             : 0x00D8 (216 bytes)
dwClockFreq              : 0x01C9C380 (30 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x01
Data (HexDump)           : 0D 24 01 00 01 D8 00 80 C3 C9 01 01 01            .$...........

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
bmControls               : 0x2E, 0x2A, 0x02
 D0                      : 0   no -  Scanning Mode
 D1                      : 1  yes -  Auto-Exposure Mode
 D2                      : 1  yes -  Auto-Exposure Priority
 D3                      : 1  yes -  Exposure Time (Absolute)
 D4                      : 0   no -  Exposure Time (Relative)
 D5                      : 1  yes -  Focus (Absolute)
 D6                      : 0   no -  Focus (Relative)
 D7                      : 0   no -  Iris (Absolute)
 D8                      : 0   no -  Iris (Relative)
 D9                      : 1  yes -  Zoom (Absolute)
 D10                     : 0   no -  Zoom (Relative)
 D11                     : 1  yes -  Pan (Absolute)
 D12                     : 0   no -  Pan (Relative)
 D13                     : 1  yes -  Roll (Absolute)
 D14                     : 0   no -  Roll (Relative)
 D15                     : 0   no -  Tilt (Absolute)
 D16                     : 0   no -  Tilt (Relative)
 D17                     : 1  yes -  Focus Auto
 D18                     : 0   no -  Reserved
 D19                     : 0   no -  Reserved
 D20                     : 0   no -  Reserved
 D21                     : 0   no -  Reserved
 D22                     : 0   no -  Reserved
 D23                     : 0   no -  Reserved
Data (HexDump)           : 12 24 02 01 01 02 00 00 00 00 00 00 00 00 03 2E   .$..............
                           2A 02                                             *.

        -------- Video Control Processing Unit Descriptor -----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x05 (Processing Unit)
bUnitID                  : 0x03
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
Data (HexDump)           : 0B 24 05 03 01 00 40 02 5B 17 00                  .$....@.[..

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x0E
guidExtensionCode        : {2C49D16A-32B8-4485-3EA8-643A152362F2}
bNumControls             : 0x06
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x03
bControlSize             : 0x02
bmControls               : 0x3F, 0x00
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 1  yes -  Vendor-Specific (Optional)
 D3                      : 1  yes -  Vendor-Specific (Optional)
 D4                      : 1  yes -  Vendor-Specific (Optional)
 D5                      : 1  yes -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
 D8                      : 0   no -  Vendor-Specific (Optional)
 D9                      : 0   no -  Vendor-Specific (Optional)
 D10                     : 0   no -  Vendor-Specific (Optional)
 D11                     : 0   no -  Vendor-Specific (Optional)
 D12                     : 0   no -  Vendor-Specific (Optional)
 D13                     : 0   no -  Vendor-Specific (Optional)
 D14                     : 0   no -  Vendor-Specific (Optional)
 D15                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1B 24 06 0E 6A D1 49 2C B8 32 85 44 3E A8 64 3A   .$..j.I,.2.D>.d:
                           15 23 62 F2 06 01 03 02 3F 00 00                  .#b.....?..

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x06
guidExtensionCode        : {23E49ED0-1178-4F31-AE52-D2FB8A8D3B48}
bNumControls             : 0x0E
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x03
bControlSize             : 0x02
bmControls               : 0xFF, 0x6F
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
 D12                     : 0   no -  Vendor-Specific (Optional)
 D13                     : 1  yes -  Vendor-Specific (Optional)
 D14                     : 1  yes -  Vendor-Specific (Optional)
 D15                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1B 24 06 06 D0 9E E4 23 78 11 31 4F AE 52 D2 FB   .$.....#x.1O.R..
                           8A 8D 3B 48 0E 01 03 02 FF 6F 00                  ..;H.....o.

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x08
guidExtensionCode        : {69678EE4-410F-40DB-A850-7420D7D8240E}
bNumControls             : 0x08
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x03
bControlSize             : 0x02
bmControls               : 0x3F, 0x0F
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
 D10                     : 1  yes -  Vendor-Specific (Optional)
 D11                     : 1  yes -  Vendor-Specific (Optional)
 D12                     : 0   no -  Vendor-Specific (Optional)
 D13                     : 0   no -  Vendor-Specific (Optional)
 D14                     : 0   no -  Vendor-Specific (Optional)
 D15                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1B 24 06 08 E4 8E 67 69 0F 41 DB 40 A8 50 74 20   .$....gi.A.@.Pt
                           D7 D8 24 0E 08 01 03 02 3F 0F 00                  ..$.....?..

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x09
guidExtensionCode        : {1F5D4CA9-DE11-4487-840D-50933C8EC8D1}
bNumControls             : 0x12
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x03
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
Data (HexDump)           : 1C 24 06 09 A9 4C 5D 1F 11 DE 87 44 84 0D 50 93   .$...L]....D..P.
                           3C 8E C8 D1 12 01 03 03 FF FF 03 00               <...........

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x0A
guidExtensionCode        : {49E40215-F434-47FE-B158-0E885023E51B}
bNumControls             : 0x0B
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x03
bControlSize             : 0x03
bmControls               : 0xFA, 0xFF, 0x01
 D0                      : 0   no -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 0   no -  Vendor-Specific (Optional)
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
 D17                     : 0   no -  Vendor-Specific (Optional)
 D18                     : 0   no -  Vendor-Specific (Optional)
 D19                     : 0   no -  Vendor-Specific (Optional)
 D20                     : 0   no -  Vendor-Specific (Optional)
 D21                     : 0   no -  Vendor-Specific (Optional)
 D22                     : 0   no -  Vendor-Specific (Optional)
 D23                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1C 24 06 0A 15 02 E4 49 34 F4 FE 47 B1 58 0E 88   .$.....I4..G.X..
                           50 23 E5 1B 0B 01 03 03 FA FF 01 00               P#..........

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x0B
guidExtensionCode        : {FFE52D21-8030-4E2C-82D9-F587D00540BD}
bNumControls             : 0x04
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x03
bControlSize             : 0x03
bmControls               : 0x00, 0x41, 0x01
 D0                      : 0   no -  Vendor-Specific (Optional)
 D1                      : 0   no -  Vendor-Specific (Optional)
 D2                      : 0   no -  Vendor-Specific (Optional)
 D3                      : 0   no -  Vendor-Specific (Optional)
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
 D14                     : 1  yes -  Vendor-Specific (Optional)
 D15                     : 0   no -  Vendor-Specific (Optional)
 D16                     : 1  yes -  Vendor-Specific (Optional)
 D17                     : 0   no -  Vendor-Specific (Optional)
 D18                     : 0   no -  Vendor-Specific (Optional)
 D19                     : 0   no -  Vendor-Specific (Optional)
 D20                     : 0   no -  Vendor-Specific (Optional)
 D21                     : 0   no -  Vendor-Specific (Optional)
 D22                     : 0   no -  Vendor-Specific (Optional)
 D23                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1C 24 06 0B 21 2D E5 FF 30 80 2C 4E 82 D9 F5 87   .$..!-..0.,N....
                           D0 05 40 BD 04 01 03 03 00 41 01 00               ..@......A..

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x04
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x03
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 04 01 01 00 03 00                        .$.......

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x85 (Direction=IN EndpointID=5)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0040
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x40 (64 bytes per packet)
bInterval                : 0x08 (8 ms)
Data (HexDump)           : 07 05 85 03 40 00 08                              ....@..

        --- Class-specific VC Interrupt Endpoint Descriptor ---
bLength                  : 0x05 (5 bytes)
bDescriptorType          : 0x25 (Video Control Endpoint)
bDescriptorSubtype       : 0x03 (Interrupt)
wMaxTransferSize         : 0x0040 (64 bytes)
Data (HexDump)           : 05 25 03 40 00                                    .%.@.

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
bLength                  : 0x0F (15 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x02
wTotalLength             : 0x0431 (1073 bytes)
bEndpointAddress         : 0x81 (Direction=IN  EndpointID=1)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x04
bStillCaptureMethod      : 0x00 (No Still Capture)
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
Video Payload Format 2   : 0x00
 D0                      : 0   no -  Key Frame Rate
 D1                      : 0   no -  P Frame Rate
 D2                      : 0   no -  Compression Quality
 D3                      : 0   no -  Compression Window Size
 D4                      : 0   no -  Generate Key Frame
 D5                      : 0   no -  Update Frame Segment
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Data (HexDump)           : 0F 24 01 02 31 04 81 00 04 00 00 00 01 00 00      .$..1..........

        ------- VS Uncompressed Format Type Descriptor --------
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x04 (Uncompressed Format Type)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x0A (10)
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
Data (HexDump)           : 1B 24 04 01 0A 59 55 59 32 00 00 10 00 80 00 00   .$...YUY2.......
                           AA 00 38 9B 71 10 01 00 00 00 00                  ..8.q......

        -------- VS Uncompressed Frame Type Descriptor --------
---> This is the Default (optimum) Frame index
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x01770000 (24576000 bps -> 3.72 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x00096000 (614400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 05 01 00 80 02 E0 01 00 00 77 01 00 00 CA   6$.........w....
                           08 00 60 09 00 15 16 05 00 07 15 16 05 00 9A 5B   ..`............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x00B0 (176)
wHeight                  : 0x0090 (144)
dwMinBitRate             : 0x001EF000 (2027520 bps -> 253.375 KB/s)
dwMaxBitRate             : 0x00B9A000 (12165120 bps -> 1.520 MB/s)
dwMaxVideoFrameBufferSize: 0x0000C600 (50688 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 05 02 00 B0 00 90 00 00 F0 1E 00 00 A0 B9   6$..............
                           00 00 C6 00 00 15 16 05 00 07 15 16 05 00 9A 5B   ...............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x0140 (320)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x005DC000 (6144000 bps -> 768 KB/s)
dwMaxBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwMaxVideoFrameBufferSize: 0x00025800 (153600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 05 03 00 40 01 F0 00 00 C0 5D 00 00 80 32   6$...@.....]...2
                           02 00 58 02 00 15 16 05 00 07 15 16 05 00 9A 5B   ..X............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x01A8 (424)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x007C3800 (8140800 bps -> 1.17 MB/s)
dwMaxBitRate             : 0x02E95000 (48844800 bps -> 6.105 MB/s)
dwMaxVideoFrameBufferSize: 0x00031B00 (203520 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 05 04 00 A8 01 F0 00 00 38 7C 00 00 50 E9   6$........8|..P.
                           02 00 1B 03 00 15 16 05 00 07 15 16 05 00 9A 5B   ...............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxVideoFrameBufferSize: 0x00070800 (460800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 05 05 00 80 02 68 01 00 40 19 01 00 80 97   6$.....h..@.....
                           06 00 08 07 00 15 16 05 00 07 15 16 05 00 9A 5B   ...............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0350 (848)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x01F0E000 (32563200 bps -> 4.70 MB/s)
dwMaxBitRate             : 0x0BA54000 (195379200 bps -> 24.422 MB/s)
dwMaxVideoFrameBufferSize: 0x000C6C00 (814080 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 05 06 00 50 03 E0 01 00 E0 F0 01 00 40 A5   6$...P........@.
                           0B 00 6C 0C 00 15 16 05 00 07 15 16 05 00 9A 5B   ..l............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x07
bmCapabilities           : 0x00
wWidth                   : 0x03C0 (960)
wHeight                  : 0x021C (540)
dwMinBitRate             : 0x0278D000 (41472000 bps -> 5.184 MB/s)
dwMaxBitRate             : 0x076A7000 (124416000 bps -> 15.552 MB/s)
dwMaxVideoFrameBufferSize: 0x000FD200 (1036800 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[2]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[3]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[4]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 2A 24 05 07 00 C0 03 1C 02 00 D0 78 02 00 70 6A   *$.........x..pj
                           07 00 D2 0F 00 2A 2C 0A 00 04 2A 2C 0A 00 40 42   .....*,...*,..@B
                           0F 00 55 58 14 00 80 84 1E 00                     ..UX......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x08
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x04650000 (73728000 bps -> 9.216 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x001C2000 (1843200 bytes)
dwDefaultFrameInterval   : 0x000F4240 (100.0000 ms -> 10.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[2]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[3]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 26 24 05 08 00 00 05 D0 02 00 00 65 04 00 00 CA   &$.........e....
                           08 00 20 1C 00 40 42 0F 00 03 40 42 0F 00 55 58   .. ..@B...@B..UX
                           14 00 80 84 1E 00                                 ......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x09
bmCapabilities           : 0x00
wWidth                   : 0x0640 (1600)
wHeight                  : 0x0380 (896)
dwMinBitRate             : 0x06D60000 (114688000 bps -> 14.336 MB/s)
dwMaxBitRate             : 0x0A410000 (172032000 bps -> 21.504 MB/s)
dwMaxVideoFrameBufferSize: 0x002BC000 (2867200 bytes)
dwDefaultFrameInterval   : 0x00145855 (133.3333 ms -> 7.500 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[2]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 22 24 05 09 00 40 06 80 03 00 00 D6 06 00 00 41   "$...@.........A
                           0A 00 C0 2B 00 55 58 14 00 02 55 58 14 00 80 84   ...+.UX...UX....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x0A
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x09E34000 (165888000 bps -> 20.736 MB/s)
dwMaxBitRate             : 0x09E34000 (165888000 bps -> 20.736 MB/s)
dwMaxVideoFrameBufferSize: 0x003F4800 (4147200 bytes)
dwDefaultFrameInterval   : 0x001E8480 (200.0000 ms -> 5.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
adwFrameInterval[1]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 1E 24 05 0A 00 80 07 38 04 00 40 E3 09 00 40 E3   .$.....8..@...@.
                           09 00 48 3F 00 80 84 1E 00 01 80 84 1E 00         ..H?..........

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
bNumFrameDescriptors     : 0x0A (10)
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
Data (HexDump)           : 0B 24 06 02 0A 01 01 00 00 00 00                  .$.........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
---> This is the Default (optimum) Frame index
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x01770000 (24576000 bps -> 3.72 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x00096000 (614400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 01 00 80 02 E0 01 00 00 77 01 00 00 CA   6$.........w....
                           08 00 60 09 00 15 16 05 00 07 15 16 05 00 9A 5B   ..`............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x00B0 (176)
wHeight                  : 0x0090 (144)
dwMinBitRate             : 0x001EF000 (2027520 bps -> 253.375 KB/s)
dwMaxBitRate             : 0x00B9A000 (12165120 bps -> 1.520 MB/s)
dwMaxVideoFrameBufferSize: 0x0000C600 (50688 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 02 00 B0 00 90 00 00 F0 1E 00 00 A0 B9   6$..............
                           00 00 C6 00 00 15 16 05 00 07 15 16 05 00 9A 5B   ...............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x0140 (320)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x005DC000 (6144000 bps -> 768 KB/s)
dwMaxBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwMaxVideoFrameBufferSize: 0x00025800 (153600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 03 00 40 01 F0 00 00 C0 5D 00 00 80 32   6$...@.....]...2
                           02 00 58 02 00 15 16 05 00 07 15 16 05 00 9A 5B   ..X............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x01A8 (424)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x007C3800 (8140800 bps -> 1.17 MB/s)
dwMaxBitRate             : 0x02E95000 (48844800 bps -> 6.105 MB/s)
dwMaxVideoFrameBufferSize: 0x00031B00 (203520 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 04 00 A8 01 F0 00 00 38 7C 00 00 50 E9   6$........8|..P.
                           02 00 1B 03 00 15 16 05 00 07 15 16 05 00 9A 5B   ...............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxVideoFrameBufferSize: 0x00070800 (460800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 05 00 80 02 68 01 00 40 19 01 00 80 97   6$.....h..@.....
                           06 00 08 07 00 15 16 05 00 07 15 16 05 00 9A 5B   ...............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0350 (848)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x01F0E000 (32563200 bps -> 4.70 MB/s)
dwMaxBitRate             : 0x0BA54000 (195379200 bps -> 24.422 MB/s)
dwMaxVideoFrameBufferSize: 0x000C6C00 (814080 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 06 00 50 03 E0 01 00 E0 F0 01 00 40 A5   6$...P........@.
                           0B 00 6C 0C 00 15 16 05 00 07 15 16 05 00 9A 5B   ..l............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x07
bmCapabilities           : 0x00
wWidth                   : 0x03C0 (960)
wHeight                  : 0x021C (540)
dwMinBitRate             : 0x0278D000 (41472000 bps -> 5.184 MB/s)
dwMaxBitRate             : 0x0ED4E000 (248832000 bps -> 31.104 MB/s)
dwMaxVideoFrameBufferSize: 0x000FD200 (1036800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 07 00 C0 03 1C 02 00 D0 78 02 00 E0 D4   6$.........x....
                           0E 00 D2 0F 00 15 16 05 00 07 15 16 05 00 9A 5B   ...............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x08
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x04650000 (73728000 bps -> 9.216 MB/s)
dwMaxBitRate             : 0x1A5E0000 (442368000 bps -> 55.296 MB/s)
dwMaxVideoFrameBufferSize: 0x001C2000 (1843200 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 08 00 00 05 D0 02 00 00 65 04 00 00 5E   6$.........e...^
                           1A 00 20 1C 00 15 16 05 00 07 15 16 05 00 9A 5B   .. ............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x09
bmCapabilities           : 0x00
wWidth                   : 0x0640 (1600)
wHeight                  : 0x0380 (896)
dwMinBitRate             : 0x06D60000 (114688000 bps -> 14.336 MB/s)
dwMaxBitRate             : 0x29040000 (688128000 bps -> 86.16 MB/s)
dwMaxVideoFrameBufferSize: 0x002BC000 (2867200 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 09 00 40 06 80 03 00 00 D6 06 00 00 04   6$...@..........
                           29 00 C0 2B 00 15 16 05 00 07 15 16 05 00 9A 5B   )..+...........[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x0A
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x09E34000 (165888000 bps -> 20.736 MB/s)
dwMaxBitRate             : 0x3B538000 (995328000 bps -> 124.416 MB/s)
dwMaxVideoFrameBufferSize: 0x003F4800 (4147200 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 0A 00 80 07 38 04 00 40 E3 09 00 80 53   6$.....8..@....S
                           3B 00 48 3F 00 15 16 05 00 07 15 16 05 00 9A 5B   ;.H?...........[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

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
wMaxPacketSize           : 0x1400
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x02 (2 additional transactions per microframe -> allows 683..1024 bytes per packet)
 Bits 10..0              : 0x400 (1024 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 00 14 01                              .......

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
bNrChannels              : 0x02 (2 channels)
wChannelConfig           : 0x0003 (L, R)
iChannelNames            : 0x00 (No String Descriptor)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 0C 24 02 01 01 02 00 02 03 00 00 00               .$..........

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x03
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x00 (0)
bSourceID                : 0x05 (5)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 03 03 01 01 00 05 00                        .$.......

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x08 (8 bytes)
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
iFeature                 : 0x00 (No String Descriptor)
Data (HexDump)           : 08 24 06 05 01 01 03 00                           .$......

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
bNrChannels              : 0x02 (2 channels)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x01 (supports 1 sample frequency)
tSamFreq[1]              : 0x03E80 (16000 Hz)
Data (HexDump)           : 0B 24 02 01 02 02 10 01 80 3E 00                  .$.......>.

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x84 (Direction=IN EndpointID=4)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0044
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x44 (68 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 84 05 44 00 04 00 00                        ....D....

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
bNrChannels              : 0x02 (2 channels)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x01 (supports 1 sample frequency)
tSamFreq[1]              : 0x05DC0 (24000 Hz)
Data (HexDump)           : 0B 24 02 01 02 02 10 01 C0 5D 00                  .$.......].

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x84 (Direction=IN EndpointID=4)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0064
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x64 (100 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 84 05 64 00 04 00 00                        ....d....

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
bNrChannels              : 0x02 (2 channels)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x01 (supports 1 sample frequency)
tSamFreq[1]              : 0x07D00 (32000 Hz)
Data (HexDump)           : 0B 24 02 01 02 02 10 01 00 7D 00                  .$.......}.

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x84 (Direction=IN EndpointID=4)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0084
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x84 (132 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 84 05 84 00 04 00 00                        .........

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
bNrChannels              : 0x02 (2 channels)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x01 (supports 1 sample frequency)
tSamFreq[1]              : 0x0BB80 (48000 Hz)
Data (HexDump)           : 0B 24 02 01 02 02 10 01 80 BB 00                  .$.........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x84 (Direction=IN EndpointID=4)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x00C4
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0xC4 (196 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 84 05 C4 00 04 00 00                        .........

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
bInterfaceNumber         : 0x04
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0xFF (Vendor Specific)
bInterfaceSubClass       : 0xFF
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 04 00 01 FF FF 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x83 (Direction=IN EndpointID=3)
bmAttributes             : 0x02 (TransferType=Bulk)
wMaxPacketSize           : 0x0200 (max 512 bytes)
bInterval                : 0x00 (never NAKs)
Data (HexDump)           : 07 05 83 02 00 02 00                              .......

        ------ SuperSpeed Endpoint Companion Descriptor -------
bLength                  : 0x06 (6 bytes)
bDescriptorType          : 0x30 (SuperSpeed Endpoint Companion Descriptor)
bMaxBurst                : 0x00 (up to 1 packets per burst)
bmAttributes             : 0x00
wBytesPerInterval        : 0x0000
Data (HexDump)           : 06 30 00 00 00 00                                 .0....

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x05
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x03 (HID - Human Interface Device)
bInterfaceSubClass       : 0x00 (None)
bInterfaceProtocol       : 0x00 (None)
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 05 00 01 03 00 00 00                        .........

        ------------------- HID Descriptor --------------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x21 (HID Descriptor)
bcdHID                   : 0x0111 (HID Version 1.11)
bCountryCode             : 0x00 (00 = not localized)
bNumDescriptors          : 0x01
Data (HexDump)           : 09 21 11 01 00 01 22 6C 00                        .!...."l.
Descriptor 1:
bDescriptorType          : 0x22 (Class=Report)
wDescriptorLength        : 0x006C (108 bytes)
Error reading descriptor : ERROR_INVALID_PARAMETER (due to a obscure limitation of the Win32 USB API, see UsbTreeView.txt)

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x87 (Direction=IN EndpointID=7)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0002
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x02 (2 bytes per packet)
bInterval                : 0x06 (6 ms)
Data (HexDump)           : 07 05 87 03 02 00 06                              .......

        ------ SuperSpeed Endpoint Companion Descriptor -------
bLength                  : 0x06 (6 bytes)
bDescriptorType          : 0x30 (SuperSpeed Endpoint Companion Descriptor)
bMaxBurst                : 0x00 (up to 1 packets per burst)
bmAttributes             : 0x00
wBytesPerInterval        : 0x0002 (*!*ERROR  must be 0 for control and bulk endpoints)
Data (HexDump)           : 06 30 00 00 02 00                                 .0....

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
wTotalLength             : 0x035A (858 bytes)
bNumInterfaces           : 0x05 (5 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x00 (No String Descriptor)
bmAttributes             : 0x80
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x00 (no)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0xFA (500 mA)
Data (HexDump)           : 09 07 5A 03 05 01 00 80 FA 08 0B 00 02 0E 03 00   ..Z.............
                           00 09 04 00 00 01 0E 01 00 00 0D 24 01 00 01 D8   ...........$....
                           00 80 C3 C9 01 01 01 12 24 02 01 01 02 00 00 00   ........$.......
                           00 00 00 00 00 03 2E 2A 02 0B 24 05 03 01 00 40   .......*..$....@
                           02 5B 17 00 1B 24 06 0E 6A D1 49 2C B8 32 85 44   .[...$..j.I,.2.D
                           3E A8 64 3A 15 23 62 F2 06 01 03 02 3F 00 00 1B   >.d:.#b.....?...
                           24 06 06 D0 9E E4 23 78 11 31 4F AE 52 D2 FB 8A   $.....#x.1O.R...
                           8D 3B 48 0E 01 03 02 FF 6F 00 1B 24 06 08 E4 8E   .;H.....o..$....
                           67 69 0F 41 DB 40 A8 50 74 20 D7 D8 24 0E 08 01   gi.A.@.Pt ..$...
                           03 02 3F 0F 00 1C 24 06 09 A9 4C 5D 1F 11 DE 87   ..?...$...L]....
                           44 84 0D 50 93 3C 8E C8 D1 12 01 03 03 FF FF 03   D..P.<..........
                           00 1C 24 06 0A 15 02 E4 49 34 F4 FE 47 B1 58 0E   ..$.....I4..G.X.
                           88 50 23 E5 1B 0B 01 03 03 FA FF 01 00 1C 24 06   .P#...........$.
                           0B 21 2D E5 FF 30 80 2C 4E 82 D9 F5 87 D0 05 40   .!-..0.,N......@
                           BD 04 01 03 03 00 41 01 00 09 24 03 04 01 01 00   ......A...$.....
                           03 00 07 05 85 03 40 00 10 05 25 03 40 00 09 04   ......@...%.@...
                           01 00 00 0E 02 00 00 0F 24 01 02 79 01 81 00 04   ........$..y....
                           00 00 00 01 00 00 1B 24 04 01 01 59 55 59 32 00   .......$...YUY2.
                           00 10 00 80 00 00 AA 00 38 9B 71 10 01 00 00 00   ........8.q.....
                           00 2A 24 05 01 00 B0 00 90 00 00 F0 1E 00 00 D0   .*$.............
                           5C 00 00 C6 00 00 2A 2C 0A 00 04 2A 2C 0A 00 40   \.....*,...*,..@
                           42 0F 00 55 58 14 00 80 84 1E 00 06 24 0D 01 01   B..UX.......$...
                           04 0B 24 06 02 05 01 01 00 00 00 00 36 24 07 01   ..$.........6$..
                           00 80 02 E0 01 00 00 77 01 00 00 CA 08 00 60 09   .......w......`.
                           00 15 16 05 00 07 15 16 05 00 9A 5B 06 00 20 A1   ...........[.. .
                           07 00 2A 2C 0A 00 40 42 0F 00 55 58 14 00 80 84   ..*,..@B..UX....
                           1E 00 36 24 07 02 00 B0 00 90 00 00 F0 1E 00 00   ..6$............
                           A0 B9 00 00 C6 00 00 15 16 05 00 07 15 16 05 00   ................
                           9A 5B 06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00   .[.. ...*,..@B..
                           55 58 14 00 80 84 1E 00 36 24 07 03 00 40 01 F0   UX......6$...@..
                           00 00 C0 5D 00 00 80 32 02 00 58 02 00 15 16 05   ...]...2..X.....
                           00 07 15 16 05 00 9A 5B 06 00 20 A1 07 00 2A 2C   .......[.. ...*,
                           0A 00 40 42 0F 00 55 58 14 00 80 84 1E 00 36 24   ..@B..UX......6$
                           07 04 00 A8 01 F0 00 00 38 7C 00 00 50 E9 02 00   ........8|..P...
                           1B 03 00 15 16 05 00 07 15 16 05 00 9A 5B 06 00   .............[..
                           20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58 14 00    ...*,..@B..UX..
                           80 84 1E 00 36 24 07 05 00 80 02 68 01 00 40 19   ....6$.....h..@.
                           01 00 80 97 06 00 08 07 00 15 16 05 00 07 15 16   ................
                           05 00 9A 5B 06 00 20 A1 07 00 2A 2C 0A 00 40 42   ...[.. ...*,..@B
                           0F 00 55 58 14 00 80 84 1E 00 06 24 0D 01 01 04   ..UX.......$....
                           09 04 01 01 01 0E 02 00 00 07 05 81 05 C0 00 01   ................
                           09 04 01 02 01 0E 02 00 00 07 05 81 05 80 01 01   ................
                           09 04 01 03 01 0E 02 00 00 07 05 81 05 00 02 01   ................
                           09 04 01 04 01 0E 02 00 00 07 05 81 05 80 02 01   ................
                           09 04 01 05 01 0E 02 00 00 07 05 81 05 20 03 01   ............. ..
                           08 0B 02 02 01 02 00 00 09 04 02 00 00 01 01 00   ................
                           00 09 24 01 00 01 26 00 01 03 0C 24 02 01 01 02   ..$...&....$....
                           00 02 03 00 00 00 09 24 03 03 01 01 00 05 00 08   .......$........
                           24 06 05 01 01 03 00 09 04 03 00 00 01 02 00 00   $...............
                           09 04 03 01 01 01 02 00 00 07 24 01 03 01 01 00   ..........$.....
                           0B 24 02 01 02 02 10 01 80 3E 00 09 05 84 05 44   .$.......>.....D
                           00 04 00 00 07 25 01 01 00 00 00 09 04 04 00 01   .....%..........
                           03 00 00 00 09 21 11 01 00 01 22 6C 00 07 05 87   .....!...."l....
                           03 02 00 06 06 30 00 00 02 00                     .....0....

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
wTotalLength             : 0x00D8 (216 bytes)
dwClockFreq              : 0x01C9C380 (30 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x01
Data (HexDump)           : 0D 24 01 00 01 D8 00 80 C3 C9 01 01 01            .$...........

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
bmControls               : 0x2E, 0x2A, 0x02
 D0                      : 0   no -  Scanning Mode
 D1                      : 1  yes -  Auto-Exposure Mode
 D2                      : 1  yes -  Auto-Exposure Priority
 D3                      : 1  yes -  Exposure Time (Absolute)
 D4                      : 0   no -  Exposure Time (Relative)
 D5                      : 1  yes -  Focus (Absolute)
 D6                      : 0   no -  Focus (Relative)
 D7                      : 0   no -  Iris (Absolute)
 D8                      : 0   no -  Iris (Relative)
 D9                      : 1  yes -  Zoom (Absolute)
 D10                     : 0   no -  Zoom (Relative)
 D11                     : 1  yes -  Pan (Absolute)
 D12                     : 0   no -  Pan (Relative)
 D13                     : 1  yes -  Roll (Absolute)
 D14                     : 0   no -  Roll (Relative)
 D15                     : 0   no -  Tilt (Absolute)
 D16                     : 0   no -  Tilt (Relative)
 D17                     : 1  yes -  Focus Auto
 D18                     : 0   no -  Reserved
 D19                     : 0   no -  Reserved
 D20                     : 0   no -  Reserved
 D21                     : 0   no -  Reserved
 D22                     : 0   no -  Reserved
 D23                     : 0   no -  Reserved
Data (HexDump)           : 12 24 02 01 01 02 00 00 00 00 00 00 00 00 03 2E   .$..............
                           2A 02                                             *.

        -------- Video Control Processing Unit Descriptor -----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x05 (Processing Unit)
bUnitID                  : 0x03
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
Data (HexDump)           : 0B 24 05 03 01 00 40 02 5B 17 00                  .$....@.[..

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x0E
guidExtensionCode        : {2C49D16A-32B8-4485-3EA8-643A152362F2}
bNumControls             : 0x06
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x03
bControlSize             : 0x02
bmControls               : 0x3F, 0x00
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 1  yes -  Vendor-Specific (Optional)
 D3                      : 1  yes -  Vendor-Specific (Optional)
 D4                      : 1  yes -  Vendor-Specific (Optional)
 D5                      : 1  yes -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
 D8                      : 0   no -  Vendor-Specific (Optional)
 D9                      : 0   no -  Vendor-Specific (Optional)
 D10                     : 0   no -  Vendor-Specific (Optional)
 D11                     : 0   no -  Vendor-Specific (Optional)
 D12                     : 0   no -  Vendor-Specific (Optional)
 D13                     : 0   no -  Vendor-Specific (Optional)
 D14                     : 0   no -  Vendor-Specific (Optional)
 D15                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1B 24 06 0E 6A D1 49 2C B8 32 85 44 3E A8 64 3A   .$..j.I,.2.D>.d:
                           15 23 62 F2 06 01 03 02 3F 00 00                  .#b.....?..

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x06
guidExtensionCode        : {23E49ED0-1178-4F31-AE52-D2FB8A8D3B48}
bNumControls             : 0x0E
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x03
bControlSize             : 0x02
bmControls               : 0xFF, 0x6F
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
 D12                     : 0   no -  Vendor-Specific (Optional)
 D13                     : 1  yes -  Vendor-Specific (Optional)
 D14                     : 1  yes -  Vendor-Specific (Optional)
 D15                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1B 24 06 06 D0 9E E4 23 78 11 31 4F AE 52 D2 FB   .$.....#x.1O.R..
                           8A 8D 3B 48 0E 01 03 02 FF 6F 00                  ..;H.....o.

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x08
guidExtensionCode        : {69678EE4-410F-40DB-A850-7420D7D8240E}
bNumControls             : 0x08
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x03
bControlSize             : 0x02
bmControls               : 0x3F, 0x0F
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
 D10                     : 1  yes -  Vendor-Specific (Optional)
 D11                     : 1  yes -  Vendor-Specific (Optional)
 D12                     : 0   no -  Vendor-Specific (Optional)
 D13                     : 0   no -  Vendor-Specific (Optional)
 D14                     : 0   no -  Vendor-Specific (Optional)
 D15                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1B 24 06 08 E4 8E 67 69 0F 41 DB 40 A8 50 74 20   .$....gi.A.@.Pt
                           D7 D8 24 0E 08 01 03 02 3F 0F 00                  ..$.....?..

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x09
guidExtensionCode        : {1F5D4CA9-DE11-4487-840D-50933C8EC8D1}
bNumControls             : 0x12
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x03
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
Data (HexDump)           : 1C 24 06 09 A9 4C 5D 1F 11 DE 87 44 84 0D 50 93   .$...L]....D..P.
                           3C 8E C8 D1 12 01 03 03 FF FF 03 00               <...........

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x0A
guidExtensionCode        : {49E40215-F434-47FE-B158-0E885023E51B}
bNumControls             : 0x0B
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x03
bControlSize             : 0x03
bmControls               : 0xFA, 0xFF, 0x01
 D0                      : 0   no -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 0   no -  Vendor-Specific (Optional)
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
 D17                     : 0   no -  Vendor-Specific (Optional)
 D18                     : 0   no -  Vendor-Specific (Optional)
 D19                     : 0   no -  Vendor-Specific (Optional)
 D20                     : 0   no -  Vendor-Specific (Optional)
 D21                     : 0   no -  Vendor-Specific (Optional)
 D22                     : 0   no -  Vendor-Specific (Optional)
 D23                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1C 24 06 0A 15 02 E4 49 34 F4 FE 47 B1 58 0E 88   .$.....I4..G.X..
                           50 23 E5 1B 0B 01 03 03 FA FF 01 00               P#..........

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x0B
guidExtensionCode        : {FFE52D21-8030-4E2C-82D9-F587D00540BD}
bNumControls             : 0x04
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x03
bControlSize             : 0x03
bmControls               : 0x00, 0x41, 0x01
 D0                      : 0   no -  Vendor-Specific (Optional)
 D1                      : 0   no -  Vendor-Specific (Optional)
 D2                      : 0   no -  Vendor-Specific (Optional)
 D3                      : 0   no -  Vendor-Specific (Optional)
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
 D14                     : 1  yes -  Vendor-Specific (Optional)
 D15                     : 0   no -  Vendor-Specific (Optional)
 D16                     : 1  yes -  Vendor-Specific (Optional)
 D17                     : 0   no -  Vendor-Specific (Optional)
 D18                     : 0   no -  Vendor-Specific (Optional)
 D19                     : 0   no -  Vendor-Specific (Optional)
 D20                     : 0   no -  Vendor-Specific (Optional)
 D21                     : 0   no -  Vendor-Specific (Optional)
 D22                     : 0   no -  Vendor-Specific (Optional)
 D23                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1C 24 06 0B 21 2D E5 FF 30 80 2C 4E 82 D9 F5 87   .$..!-..0.,N....
                           D0 05 40 BD 04 01 03 03 00 41 01 00               ..@......A..

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x04
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x03
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 04 01 01 00 03 00                        .$.......

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x85 (Direction=IN EndpointID=5)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0040
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x40 (64 bytes per packet)
bInterval                : 0x10 (16 ms)
Data (HexDump)           : 07 05 85 03 40 00 10                              ....@..

        --- Class-specific VC Interrupt Endpoint Descriptor ---
bLength                  : 0x05 (5 bytes)
bDescriptorType          : 0x25 (Video Control Endpoint)
bDescriptorSubtype       : 0x03 (Interrupt)
wMaxTransferSize         : 0x0040 (64 bytes)
Data (HexDump)           : 05 25 03 40 00                                    .%.@.

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
bLength                  : 0x0F (15 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x02
wTotalLength             : 0x0179 (377 bytes)
bEndpointAddress         : 0x81 (Direction=IN  EndpointID=1)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x04
bStillCaptureMethod      : 0x00 (No Still Capture)
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
Video Payload Format 2   : 0x00
 D0                      : 0   no -  Key Frame Rate
 D1                      : 0   no -  P Frame Rate
 D2                      : 0   no -  Compression Quality
 D3                      : 0   no -  Compression Window Size
 D4                      : 0   no -  Generate Key Frame
 D5                      : 0   no -  Update Frame Segment
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Data (HexDump)           : 0F 24 01 02 79 01 81 00 04 00 00 00 01 00 00      .$..y..........

        ------- VS Uncompressed Format Type Descriptor --------
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x04 (Uncompressed Format Type)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x01 (1)
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
Data (HexDump)           : 1B 24 04 01 01 59 55 59 32 00 00 10 00 80 00 00   .$...YUY2.......
                           AA 00 38 9B 71 10 01 00 00 00 00                  ..8.q......

        -------- VS Uncompressed Frame Type Descriptor --------
---> This is the Default (optimum) Frame index
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x00B0 (176)
wHeight                  : 0x0090 (144)
dwMinBitRate             : 0x001EF000 (2027520 bps -> 253.375 KB/s)
dwMaxBitRate             : 0x005CD000 (6082560 bps -> 760.250 KB/s)
dwMaxVideoFrameBufferSize: 0x0000C600 (50688 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[2]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[3]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[4]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 2A 24 05 01 00 B0 00 90 00 00 F0 1E 00 00 D0 5C   *$.............\
                           00 00 C6 00 00 2A 2C 0A 00 04 2A 2C 0A 00 40 42   .....*,...*,..@B
                           0F 00 55 58 14 00 80 84 1E 00                     ..UX......

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
bNumFrameDescriptors     : 0x05 (5)
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
Data (HexDump)           : 0B 24 06 02 05 01 01 00 00 00 00                  .$.........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
---> This is the Default (optimum) Frame index
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x01770000 (24576000 bps -> 3.72 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x00096000 (614400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 01 00 80 02 E0 01 00 00 77 01 00 00 CA   6$.........w....
                           08 00 60 09 00 15 16 05 00 07 15 16 05 00 9A 5B   ..`............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x00B0 (176)
wHeight                  : 0x0090 (144)
dwMinBitRate             : 0x001EF000 (2027520 bps -> 253.375 KB/s)
dwMaxBitRate             : 0x00B9A000 (12165120 bps -> 1.520 MB/s)
dwMaxVideoFrameBufferSize: 0x0000C600 (50688 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 02 00 B0 00 90 00 00 F0 1E 00 00 A0 B9   6$..............
                           00 00 C6 00 00 15 16 05 00 07 15 16 05 00 9A 5B   ...............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x0140 (320)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x005DC000 (6144000 bps -> 768 KB/s)
dwMaxBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwMaxVideoFrameBufferSize: 0x00025800 (153600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 03 00 40 01 F0 00 00 C0 5D 00 00 80 32   6$...@.....]...2
                           02 00 58 02 00 15 16 05 00 07 15 16 05 00 9A 5B   ..X............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x01A8 (424)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x007C3800 (8140800 bps -> 1.17 MB/s)
dwMaxBitRate             : 0x02E95000 (48844800 bps -> 6.105 MB/s)
dwMaxVideoFrameBufferSize: 0x00031B00 (203520 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 04 00 A8 01 F0 00 00 38 7C 00 00 50 E9   6$........8|..P.
                           02 00 1B 03 00 15 16 05 00 07 15 16 05 00 9A 5B   ...............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x36 (54 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxVideoFrameBufferSize: 0x00070800 (460800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x07 (7 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00065B9A (41.6666 ms -> 24.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x00145855 (133.3333 ms -> 7.500 fps)
adwFrameInterval[7]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 36 24 07 05 00 80 02 68 01 00 40 19 01 00 80 97   6$.....h..@.....
                           06 00 08 07 00 15 16 05 00 07 15 16 05 00 9A 5B   ...............[
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 55 58   .. ...*,..@B..UX
                           14 00 80 84 1E 00                                 ......

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
bNrChannels              : 0x02 (2 channels)
wChannelConfig           : 0x0003 (L, R)
iChannelNames            : 0x00 (No String Descriptor)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 0C 24 02 01 01 02 00 02 03 00 00 00               .$..........

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x03
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x00 (0)
bSourceID                : 0x05 (5)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 03 03 01 01 00 05 00                        .$.......

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x08 (8 bytes)
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
iFeature                 : 0x00 (No String Descriptor)
Data (HexDump)           : 08 24 06 05 01 01 03 00                           .$......

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
bNrChannels              : 0x02 (2 channels)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x01 (supports 1 sample frequency)
tSamFreq[1]              : 0x03E80 (16000 Hz)
Data (HexDump)           : 0B 24 02 01 02 02 10 01 80 3E 00                  .$.......>.

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x84 (Direction=IN EndpointID=4)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0044
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x44 (68 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 84 05 44 00 04 00 00                        ....D....

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
bInterfaceNumber         : 0x04
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x03 (HID - Human Interface Device)
bInterfaceSubClass       : 0x00 (None)
bInterfaceProtocol       : 0x00 (None)
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 04 00 01 03 00 00 00                        .........

        ------------------- HID Descriptor --------------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x21 (HID Descriptor)
bcdHID                   : 0x0111 (HID Version 1.11)
bCountryCode             : 0x00 (00 = not localized)
bNumDescriptors          : 0x01
Data (HexDump)           : 09 21 11 01 00 01 22 6C 00                        .!...."l.
Descriptor 1:
bDescriptorType          : 0x22 (Class=Report)
wDescriptorLength        : 0x006C (108 bytes)
Error reading descriptor : ERROR_INVALID_PARAMETER (due to a obscure limitation of the Win32 USB API, see UsbTreeView.txt)

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x87 (Direction=IN EndpointID=7)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0002
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x02 (2 bytes per packet)
bInterval                : 0x06 (6 ms)
Data (HexDump)           : 07 05 87 03 02 00 06                              .......

        ------ SuperSpeed Endpoint Companion Descriptor -------
bLength                  : 0x06 (6 bytes)
bDescriptorType          : 0x30 (SuperSpeed Endpoint Companion Descriptor)
bMaxBurst                : 0x00 (up to 1 packets per burst)
bmAttributes             : 0x00
wBytesPerInterval        : 0x0002 (*!*ERROR  must be 0 for control and bulk endpoints)
Data (HexDump)           : 06 30 00 00 02 00                                 .0....

      ---------- Binary Object Store (BOS) Descriptor -----------
bLength                  : 0x05 (5 bytes)
bDescriptorType          : 0x0F (Binary Object Store)
wTotalLength             : 0x0016 (22 bytes)
bNumDeviceCaps           : 0x02
Data (HexDump)           : 05 0F 16 00 02                                    .....

        ------------- USB 2.0 Extension Descriptor ------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x10 (Device Capability Descriptor)
bDevCapabilityType       : 0x02 (USB 2.0 Extension)
bmAttributes             : 0x02
 LPMCapable              : 1 (Link Power Management protocol is supported)
 BESLAndAlternateHIRD    : 0 (BESL & Alternate HIRD definitions are not supported)
 BaselineBESLValid       : 0 (not valid)
 DeepBESLValid           : 0 (not valid)
 BaselineBESL            : 0
 DeepBESL                : 0
Data (HexDump)           : 07 10 02 02 00 00 00                              .......

        ----- SuperSpeed USB Device Capability Descriptor -----
bLength                  : 0x0A (10 bytes)
bDescriptorType          : 0x10 (Device Capability Descriptor)
bDevCapabilityType       : 0x03 (SuperSpeed USB Device Capability)
bmAttributes             : 0x00
 Bit 0 Reserved          : 0x00
 Bit 1 LTM Capable       : 0x00 (no)
 Bit 7:2 Reserved        : 0x00
wSpeedsSupported         : 0x0E (Full-Speed, High-Speed, SuperSpeed)
bFunctionalitySupport    : 0x02 (lowest speed with all the functionality is 'High-Speed')
bU1DevExitLat            : 0x0A   (less than 10 µs)
wU2DevExitLat            : 0x0100 (less than 256 µs)
Data (HexDump)           : 0A 10 03 00 0E 00 02 0A 00 01                     ..........

      -------------------- String Descriptors -------------------
             ------ String Descriptor 0 ------
bLength                  : 0x04 (4 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language ID[0]           : 0x0409 (English - United States)
Data (HexDump)           : 04 03 09 04                                       ....
             ------ String Descriptor 2 ------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Logitech StreamCam"
Data (HexDump)           : 26 03 4C 00 6F 00 67 00 69 00 74 00 65 00 63 00   &.L.o.g.i.t.e.c.
                           68 00 20 00 53 00 74 00 72 00 65 00 61 00 6D 00   h. .S.t.r.e.a.m.
                           43 00 61 00 6D 00                                 C.a.m.
             ------ String Descriptor 3 ------
bLength                  : 0x12 (18 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "5079EB25"
Data (HexDump)           : 12 03 35 00 30 00 37 00 39 00 45 00 42 00 32 00   ..5.0.7.9.E.B.2.
                           35 00                                             5.

*/
namespace logitech_streamcam {
const uint8_t dev_desc[] = {
    0x12, 0x01, 0x10, 0x02, 0xEF, 0x02, 0x01, 0x40, 0x6D, 0x04, 0x93, 0x08, 0x17, 0x00, 0x00, 0x02,
    0x03, 0x01
};
const uint8_t cfg_desc[] = {
    0x09, 0x02, 0x09, 0x07, 0x06, 0x01, 0x00, 0x80, 0xFA, 0x08, 0x0B, 0x00, 0x02, 0x0E, 0x03, 0x00,
    0x00, 0x09, 0x04, 0x00, 0x00, 0x01, 0x0E, 0x01, 0x00, 0x00, 0x0D, 0x24, 0x01, 0x00, 0x01, 0xD8,
    0x00, 0x80, 0xC3, 0xC9, 0x01, 0x01, 0x01, 0x12, 0x24, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x2E, 0x2A, 0x02, 0x0B, 0x24, 0x05, 0x03, 0x01, 0x00, 0x40,
    0x02, 0x5B, 0x17, 0x00, 0x1B, 0x24, 0x06, 0x0E, 0x6A, 0xD1, 0x49, 0x2C, 0xB8, 0x32, 0x85, 0x44,
    0x3E, 0xA8, 0x64, 0x3A, 0x15, 0x23, 0x62, 0xF2, 0x06, 0x01, 0x03, 0x02, 0x3F, 0x00, 0x00, 0x1B,
    0x24, 0x06, 0x06, 0xD0, 0x9E, 0xE4, 0x23, 0x78, 0x11, 0x31, 0x4F, 0xAE, 0x52, 0xD2, 0xFB, 0x8A,
    0x8D, 0x3B, 0x48, 0x0E, 0x01, 0x03, 0x02, 0xFF, 0x6F, 0x00, 0x1B, 0x24, 0x06, 0x08, 0xE4, 0x8E,
    0x67, 0x69, 0x0F, 0x41, 0xDB, 0x40, 0xA8, 0x50, 0x74, 0x20, 0xD7, 0xD8, 0x24, 0x0E, 0x08, 0x01,
    0x03, 0x02, 0x3F, 0x0F, 0x00, 0x1C, 0x24, 0x06, 0x09, 0xA9, 0x4C, 0x5D, 0x1F, 0x11, 0xDE, 0x87,
    0x44, 0x84, 0x0D, 0x50, 0x93, 0x3C, 0x8E, 0xC8, 0xD1, 0x12, 0x01, 0x03, 0x03, 0xFF, 0xFF, 0x03,
    0x00, 0x1C, 0x24, 0x06, 0x0A, 0x15, 0x02, 0xE4, 0x49, 0x34, 0xF4, 0xFE, 0x47, 0xB1, 0x58, 0x0E,
    0x88, 0x50, 0x23, 0xE5, 0x1B, 0x0B, 0x01, 0x03, 0x03, 0xFA, 0xFF, 0x01, 0x00, 0x1C, 0x24, 0x06,
    0x0B, 0x21, 0x2D, 0xE5, 0xFF, 0x30, 0x80, 0x2C, 0x4E, 0x82, 0xD9, 0xF5, 0x87, 0xD0, 0x05, 0x40,
    0xBD, 0x04, 0x01, 0x03, 0x03, 0x00, 0x41, 0x01, 0x00, 0x09, 0x24, 0x03, 0x04, 0x01, 0x01, 0x00,
    0x03, 0x00, 0x07, 0x05, 0x85, 0x03, 0x40, 0x00, 0x08, 0x05, 0x25, 0x03, 0x40, 0x00, 0x09, 0x04,
    0x01, 0x00, 0x00, 0x0E, 0x02, 0x00, 0x00, 0x0F, 0x24, 0x01, 0x02, 0x31, 0x04, 0x81, 0x00, 0x04,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x1B, 0x24, 0x04, 0x01, 0x0A, 0x59, 0x55, 0x59, 0x32, 0x00,
    0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71, 0x10, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x36, 0x24, 0x05, 0x01, 0x00, 0x80, 0x02, 0xE0, 0x01, 0x00, 0x00, 0x77, 0x01, 0x00, 0x00,
    0xCA, 0x08, 0x00, 0x60, 0x09, 0x00, 0x15, 0x16, 0x05, 0x00, 0x07, 0x15, 0x16, 0x05, 0x00, 0x9A,
    0x5B, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x55,
    0x58, 0x14, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x36, 0x24, 0x05, 0x02, 0x00, 0xB0, 0x00, 0x90, 0x00,
    0x00, 0xF0, 0x1E, 0x00, 0x00, 0xA0, 0xB9, 0x00, 0x00, 0xC6, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00,
    0x07, 0x15, 0x16, 0x05, 0x00, 0x9A, 0x5B, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A,
    0x00, 0x40, 0x42, 0x0F, 0x00, 0x55, 0x58, 0x14, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x36, 0x24, 0x05,
    0x03, 0x00, 0x40, 0x01, 0xF0, 0x00, 0x00, 0xC0, 0x5D, 0x00, 0x00, 0x80, 0x32, 0x02, 0x00, 0x58,
    0x02, 0x00, 0x15, 0x16, 0x05, 0x00, 0x07, 0x15, 0x16, 0x05, 0x00, 0x9A, 0x5B, 0x06, 0x00, 0x20,
    0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x55, 0x58, 0x14, 0x00, 0x80,
    0x84, 0x1E, 0x00, 0x36, 0x24, 0x05, 0x04, 0x00, 0xA8, 0x01, 0xF0, 0x00, 0x00, 0x38, 0x7C, 0x00,
    0x00, 0x50, 0xE9, 0x02, 0x00, 0x1B, 0x03, 0x00, 0x15, 0x16, 0x05, 0x00, 0x07, 0x15, 0x16, 0x05,
    0x00, 0x9A, 0x5B, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F,
    0x00, 0x55, 0x58, 0x14, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x36, 0x24, 0x05, 0x05, 0x00, 0x80, 0x02,
    0x68, 0x01, 0x00, 0x40, 0x19, 0x01, 0x00, 0x80, 0x97, 0x06, 0x00, 0x08, 0x07, 0x00, 0x15, 0x16,
    0x05, 0x00, 0x07, 0x15, 0x16, 0x05, 0x00, 0x9A, 0x5B, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A,
    0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x55, 0x58, 0x14, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x36,
    0x24, 0x05, 0x06, 0x00, 0x50, 0x03, 0xE0, 0x01, 0x00, 0xE0, 0xF0, 0x01, 0x00, 0x40, 0xA5, 0x0B,
    0x00, 0x6C, 0x0C, 0x00, 0x15, 0x16, 0x05, 0x00, 0x07, 0x15, 0x16, 0x05, 0x00, 0x9A, 0x5B, 0x06,
    0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x55, 0x58, 0x14,
    0x00, 0x80, 0x84, 0x1E, 0x00, 0x2A, 0x24, 0x05, 0x07, 0x00, 0xC0, 0x03, 0x1C, 0x02, 0x00, 0xD0,
    0x78, 0x02, 0x00, 0x70, 0x6A, 0x07, 0x00, 0xD2, 0x0F, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x04, 0x2A,
    0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x55, 0x58, 0x14, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x26,
    0x24, 0x05, 0x08, 0x00, 0x00, 0x05, 0xD0, 0x02, 0x00, 0x00, 0x65, 0x04, 0x00, 0x00, 0xCA, 0x08,
    0x00, 0x20, 0x1C, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x03, 0x40, 0x42, 0x0F, 0x00, 0x55, 0x58, 0x14,
    0x00, 0x80, 0x84, 0x1E, 0x00, 0x22, 0x24, 0x05, 0x09, 0x00, 0x40, 0x06, 0x80, 0x03, 0x00, 0x00,
    0xD6, 0x06, 0x00, 0x00, 0x41, 0x0A, 0x00, 0xC0, 0x2B, 0x00, 0x55, 0x58, 0x14, 0x00, 0x02, 0x55,
    0x58, 0x14, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x1E, 0x24, 0x05, 0x0A, 0x00, 0x80, 0x07, 0x38, 0x04,
    0x00, 0x40, 0xE3, 0x09, 0x00, 0x40, 0xE3, 0x09, 0x00, 0x48, 0x3F, 0x00, 0x80, 0x84, 0x1E, 0x00,
    0x01, 0x80, 0x84, 0x1E, 0x00, 0x06, 0x24, 0x0D, 0x01, 0x01, 0x04, 0x0B, 0x24, 0x06, 0x02, 0x0A,
    0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x36, 0x24, 0x07, 0x01, 0x00, 0x80, 0x02, 0xE0, 0x01, 0x00,
    0x00, 0x77, 0x01, 0x00, 0x00, 0xCA, 0x08, 0x00, 0x60, 0x09, 0x00, 0x15, 0x16, 0x05, 0x00, 0x07,
    0x15, 0x16, 0x05, 0x00, 0x9A, 0x5B, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00,
    0x40, 0x42, 0x0F, 0x00, 0x55, 0x58, 0x14, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x36, 0x24, 0x07, 0x02,
    0x00, 0xB0, 0x00, 0x90, 0x00, 0x00, 0xF0, 0x1E, 0x00, 0x00, 0xA0, 0xB9, 0x00, 0x00, 0xC6, 0x00,
    0x00, 0x15, 0x16, 0x05, 0x00, 0x07, 0x15, 0x16, 0x05, 0x00, 0x9A, 0x5B, 0x06, 0x00, 0x20, 0xA1,
    0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x55, 0x58, 0x14, 0x00, 0x80, 0x84,
    0x1E, 0x00, 0x36, 0x24, 0x07, 0x03, 0x00, 0x40, 0x01, 0xF0, 0x00, 0x00, 0xC0, 0x5D, 0x00, 0x00,
    0x80, 0x32, 0x02, 0x00, 0x58, 0x02, 0x00, 0x15, 0x16, 0x05, 0x00, 0x07, 0x15, 0x16, 0x05, 0x00,
    0x9A, 0x5B, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00,
    0x55, 0x58, 0x14, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x36, 0x24, 0x07, 0x04, 0x00, 0xA8, 0x01, 0xF0,
    0x00, 0x00, 0x38, 0x7C, 0x00, 0x00, 0x50, 0xE9, 0x02, 0x00, 0x1B, 0x03, 0x00, 0x15, 0x16, 0x05,
    0x00, 0x07, 0x15, 0x16, 0x05, 0x00, 0x9A, 0x5B, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C,
    0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x55, 0x58, 0x14, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x36, 0x24,
    0x07, 0x05, 0x00, 0x80, 0x02, 0x68, 0x01, 0x00, 0x40, 0x19, 0x01, 0x00, 0x80, 0x97, 0x06, 0x00,
    0x08, 0x07, 0x00, 0x15, 0x16, 0x05, 0x00, 0x07, 0x15, 0x16, 0x05, 0x00, 0x9A, 0x5B, 0x06, 0x00,
    0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x55, 0x58, 0x14, 0x00,
    0x80, 0x84, 0x1E, 0x00, 0x36, 0x24, 0x07, 0x06, 0x00, 0x50, 0x03, 0xE0, 0x01, 0x00, 0xE0, 0xF0,
    0x01, 0x00, 0x40, 0xA5, 0x0B, 0x00, 0x6C, 0x0C, 0x00, 0x15, 0x16, 0x05, 0x00, 0x07, 0x15, 0x16,
    0x05, 0x00, 0x9A, 0x5B, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42,
    0x0F, 0x00, 0x55, 0x58, 0x14, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x36, 0x24, 0x07, 0x07, 0x00, 0xC0,
    0x03, 0x1C, 0x02, 0x00, 0xD0, 0x78, 0x02, 0x00, 0xE0, 0xD4, 0x0E, 0x00, 0xD2, 0x0F, 0x00, 0x15,
    0x16, 0x05, 0x00, 0x07, 0x15, 0x16, 0x05, 0x00, 0x9A, 0x5B, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00,
    0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x55, 0x58, 0x14, 0x00, 0x80, 0x84, 0x1E, 0x00,
    0x36, 0x24, 0x07, 0x08, 0x00, 0x00, 0x05, 0xD0, 0x02, 0x00, 0x00, 0x65, 0x04, 0x00, 0x00, 0x5E,
    0x1A, 0x00, 0x20, 0x1C, 0x00, 0x15, 0x16, 0x05, 0x00, 0x07, 0x15, 0x16, 0x05, 0x00, 0x9A, 0x5B,
    0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x55, 0x58,
    0x14, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x36, 0x24, 0x07, 0x09, 0x00, 0x40, 0x06, 0x80, 0x03, 0x00,
    0x00, 0xD6, 0x06, 0x00, 0x00, 0x04, 0x29, 0x00, 0xC0, 0x2B, 0x00, 0x15, 0x16, 0x05, 0x00, 0x07,
    0x15, 0x16, 0x05, 0x00, 0x9A, 0x5B, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00,
    0x40, 0x42, 0x0F, 0x00, 0x55, 0x58, 0x14, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x36, 0x24, 0x07, 0x0A,
    0x00, 0x80, 0x07, 0x38, 0x04, 0x00, 0x40, 0xE3, 0x09, 0x00, 0x80, 0x53, 0x3B, 0x00, 0x48, 0x3F,
    0x00, 0x15, 0x16, 0x05, 0x00, 0x07, 0x15, 0x16, 0x05, 0x00, 0x9A, 0x5B, 0x06, 0x00, 0x20, 0xA1,
    0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x55, 0x58, 0x14, 0x00, 0x80, 0x84,
    0x1E, 0x00, 0x06, 0x24, 0x0D, 0x01, 0x01, 0x04, 0x09, 0x04, 0x01, 0x01, 0x01, 0x0E, 0x02, 0x00,
    0x00, 0x07, 0x05, 0x81, 0x05, 0xC0, 0x00, 0x01, 0x09, 0x04, 0x01, 0x02, 0x01, 0x0E, 0x02, 0x00,
    0x00, 0x07, 0x05, 0x81, 0x05, 0x80, 0x01, 0x01, 0x09, 0x04, 0x01, 0x03, 0x01, 0x0E, 0x02, 0x00,
    0x00, 0x07, 0x05, 0x81, 0x05, 0x00, 0x02, 0x01, 0x09, 0x04, 0x01, 0x04, 0x01, 0x0E, 0x02, 0x00,
    0x00, 0x07, 0x05, 0x81, 0x05, 0x80, 0x02, 0x01, 0x09, 0x04, 0x01, 0x05, 0x01, 0x0E, 0x02, 0x00,
    0x00, 0x07, 0x05, 0x81, 0x05, 0x20, 0x03, 0x01, 0x09, 0x04, 0x01, 0x06, 0x01, 0x0E, 0x02, 0x00,
    0x00, 0x07, 0x05, 0x81, 0x05, 0xB0, 0x03, 0x01, 0x09, 0x04, 0x01, 0x07, 0x01, 0x0E, 0x02, 0x00,
    0x00, 0x07, 0x05, 0x81, 0x05, 0x80, 0x0A, 0x01, 0x09, 0x04, 0x01, 0x08, 0x01, 0x0E, 0x02, 0x00,
    0x00, 0x07, 0x05, 0x81, 0x05, 0x20, 0x0B, 0x01, 0x09, 0x04, 0x01, 0x09, 0x01, 0x0E, 0x02, 0x00,
    0x00, 0x07, 0x05, 0x81, 0x05, 0xE0, 0x0B, 0x01, 0x09, 0x04, 0x01, 0x0A, 0x01, 0x0E, 0x02, 0x00,
    0x00, 0x07, 0x05, 0x81, 0x05, 0x80, 0x13, 0x01, 0x09, 0x04, 0x01, 0x0B, 0x01, 0x0E, 0x02, 0x00,
    0x00, 0x07, 0x05, 0x81, 0x05, 0x00, 0x14, 0x01, 0x08, 0x0B, 0x02, 0x02, 0x01, 0x02, 0x00, 0x00,
    0x09, 0x04, 0x02, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x09, 0x24, 0x01, 0x00, 0x01, 0x26, 0x00,
    0x01, 0x03, 0x0C, 0x24, 0x02, 0x01, 0x01, 0x02, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x09, 0x24,
    0x03, 0x03, 0x01, 0x01, 0x00, 0x05, 0x00, 0x08, 0x24, 0x06, 0x05, 0x01, 0x01, 0x03, 0x00, 0x09,
    0x04, 0x03, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x09, 0x04, 0x03, 0x01, 0x01, 0x01, 0x02, 0x00,
    0x00, 0x07, 0x24, 0x01, 0x03, 0x01, 0x01, 0x00, 0x0B, 0x24, 0x02, 0x01, 0x02, 0x02, 0x10, 0x01,
    0x80, 0x3E, 0x00, 0x09, 0x05, 0x84, 0x05, 0x44, 0x00, 0x04, 0x00, 0x00, 0x07, 0x25, 0x01, 0x01,
    0x00, 0x00, 0x00, 0x09, 0x04, 0x03, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x07, 0x24, 0x01, 0x03,
    0x01, 0x01, 0x00, 0x0B, 0x24, 0x02, 0x01, 0x02, 0x02, 0x10, 0x01, 0xC0, 0x5D, 0x00, 0x09, 0x05,
    0x84, 0x05, 0x64, 0x00, 0x04, 0x00, 0x00, 0x07, 0x25, 0x01, 0x01, 0x00, 0x00, 0x00, 0x09, 0x04,
    0x03, 0x03, 0x01, 0x01, 0x02, 0x00, 0x00, 0x07, 0x24, 0x01, 0x03, 0x01, 0x01, 0x00, 0x0B, 0x24,
    0x02, 0x01, 0x02, 0x02, 0x10, 0x01, 0x00, 0x7D, 0x00, 0x09, 0x05, 0x84, 0x05, 0x84, 0x00, 0x04,
    0x00, 0x00, 0x07, 0x25, 0x01, 0x01, 0x00, 0x00, 0x00, 0x09, 0x04, 0x03, 0x04, 0x01, 0x01, 0x02,
    0x00, 0x00, 0x07, 0x24, 0x01, 0x03, 0x01, 0x01, 0x00, 0x0B, 0x24, 0x02, 0x01, 0x02, 0x02, 0x10,
    0x01, 0x80, 0xBB, 0x00, 0x09, 0x05, 0x84, 0x05, 0xC4, 0x00, 0x04, 0x00, 0x00, 0x07, 0x25, 0x01,
    0x01, 0x00, 0x00, 0x00, 0x09, 0x04, 0x04, 0x00, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x07, 0x05, 0x83,
    0x02, 0x00, 0x02, 0x00, 0x06, 0x30, 0x00, 0x00, 0x00, 0x00, 0x09, 0x04, 0x05, 0x00, 0x01, 0x03,
    0x00, 0x00, 0x00, 0x09, 0x21, 0x11, 0x01, 0x00, 0x01, 0x22, 0x6C, 0x00, 0x07, 0x05, 0x87, 0x03,
    0x02, 0x00, 0x06, 0x06, 0x30, 0x00, 0x00, 0x02, 0x00
};
}
