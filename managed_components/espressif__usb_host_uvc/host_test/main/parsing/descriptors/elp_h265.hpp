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
Device Path              : \\?\USB#VID_32E4&PID_9415#10ac120458586223#{a5dcbf10-6530-11d2-901f-00c04fb951ed} (GUID_DEVINTERFACE_USB_DEVICE)
Kernel Name              : \Device\USBPDO-36
Device ID                : USB\VID_32E4&PID_9415\10AC120458586223
Hardware IDs             : USB\VID_32E4&PID_9415&REV_0419 USB\VID_32E4&PID_9415
Driver KeyName           : {36fc9e60-c465-11cf-8056-444553540000}\0100 (GUID_DEVCLASS_USB)
Driver                   : \SystemRoot\System32\drivers\usbccgp.sys (Version: 10.0.19041.4355  Date: 2024-05-01)
Driver Inf               : C:\Windows\inf\usb.inf
Legacy BusType           : PNPBus
Class                    : USB
Class GUID               : {36fc9e60-c465-11cf-8056-444553540000} (GUID_DEVCLASS_USB)
Service                  : usbccgp
Enumerator               : USB
Location Info            : Port_#0003.Hub_#0019
Location IDs             : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(2)#USB(1)#USB(3), ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(2)#USB(1)#USB(3)
Container ID             : {a14fe21c-3879-5b34-a760-46be5e7e733a}
Manufacturer Info        : (Standard USB Host Controller)
Capabilities             : 0x94 (Removable, UniqueID, SurpriseRemovalOK)
Status                   : 0x0180600A (DN_DRIVER_LOADED, DN_STARTED, DN_DISABLEABLE, DN_REMOVABLE, DN_NT_ENUMERATOR, DN_NT_DRIVER)
Problem Code             : 0
Address                  : 3
HcDisableSelectiveSuspend: 0
EnableSelectiveSuspend   : 0
SelectiveSuspendEnabled  : 0
EnhancedPowerMgmtEnabled : 0
IdleInWorkingState       : 0
WakeFromSleepState       : 0
Power State              : D0 (supported: D0, D3, wake from D0)
 Child Device 1          : HDMI USB Camera (USB Video Device)
  Device Path            : \\?\USB#VID_32E4&PID_9415&MI_00#b&288ef1eb&0&0000#{e5323777-f976-4f5b-9b55-b94699c46e44}\global (STATIC_KSCATEGORY_VIDEO_CAMERA)
  Kernel Name            : \Device\000002dc
  Device ID              : USB\VID_32E4&PID_9415&MI_00\B&288EF1EB&0&0000
  Class                  : Camera
  Driver KeyName         : {ca3e7ab9-b4c3-4ae6-8251-579ef933890f}\0010 (GUID_DEVCLASS_CAMERA)
  Service                : usbvideo
  Location               : 0005.0000.0004.001.003.002.001.003.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(2)#USB(1)#USB(3)#USBMI(0)  PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(2)#USB(1)#USB(3)#USB(3)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(2)#USB(1)#USB(3)#USBMI(0)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(2)#USB(1)#USB(3)#USB(3)

        +++++++++++++++++ Registry USB Flags +++++++++++++++++
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\usbflags\32E494150419
 osvc                    : REG_BINARY 00 00

        ---------------- Connection Information ---------------
Connection Index         : 0x03 (Port 3)
Connection Status        : 0x01 (DeviceConnected)
Current Config Value     : 0x01 (Configuration 1)
Device Address           : 0x11 (17)
Is Hub                   : 0x00 (no)
Device Bus Speed         : 0x02 (High-Speed)
Number Of Open Pipes     : 0x00 (0 pipes to data endpoints)
Data (HexDump)           : 03 00 00 00 12 01 00 02 EF 02 01 40 E4 32 15 94   ...........@.2..
                           19 04 01 02 03 01 01 02 00 11 00 00 00 00 00 01   ................
                           00 00 00                                          ...

        --------------- Connection Information V2 -------------
Connection Index         : 0x03 (3)
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
Data (HexDump)           : 03 00 00 00 10 00 00 00 03 00 00 00 00 00 00 00   ................

    ---------------------- Device Descriptor ----------------------
bLength                  : 0x12 (18 bytes)
bDescriptorType          : 0x01 (Device Descriptor)
bcdUSB                   : 0x200 (USB Version 2.00)
bDeviceClass             : 0xEF (Miscellaneous)
bDeviceSubClass          : 0x02
bDeviceProtocol          : 0x01 (IAD - Interface Association Descriptor)
bMaxPacketSize0          : 0x40 (64 bytes)
idVendor                 : 0x32E4 (Ailipu Technology Co., Ltd.)
idProduct                : 0x9415
bcdDevice                : 0x0419
iManufacturer            : 0x01 (String Descriptor 1)
 *!*ERROR  String descriptor not found
iProduct                 : 0x02 (String Descriptor 2)
 *!*ERROR  String descriptor not found
iSerialNumber            : 0x03 (String Descriptor 3)
 *!*ERROR  String descriptor not found
bNumConfigurations       : 0x01 (1 Configuration)
Data (HexDump)           : 12 01 00 02 EF 02 01 40 E4 32 15 94 19 04 01 02   .......@.2......
                           03 01                                             ..

    ------------------ Configuration Descriptor -------------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x02 (Configuration Descriptor)
wTotalLength             : 0x05B0 (1456 bytes)
bNumInterfaces           : 0x02 (2 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x04 (String Descriptor 4)
 *!*ERROR  String descriptor not found
bmAttributes             : 0x80
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x00 (no)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0xFA (500 mA)
Data (HexDump)           : 09 02 B0 05 02 01 04 80 FA 08 0B 00 02 0E 03 00   ................
                           05 09 04 00 00 00 0E 01 00 08 0D 24 01 10 01 68   ...........$...h
                           00 00 6C DC 02 01 01 12 24 02 01 01 02 00 00 00   ..l.....$.......
                           00 00 00 00 00 03 0E 22 00 0C 24 05 02 01 00 40   ......."..$....@
                           02 7F 17 00 00 1A 24 06 03 18 20 2E 30 11 63 2E   ......$... .0.c.
                           4A BA 2C 68 90 EB 33 40 16 02 01 02 01 03 06 1A   J.,h..3@........
                           24 06 04 A4 FB CB 33 26 FD E4 4C 90 76 A1 93 1F   $.....3&..L.v...
                           E7 4C 5E 02 01 02 01 03 07 09 24 03 04 01 01 00   .L^.......$.....
                           03 00 09 04 01 00 00 0E 02 00 09 11 24 01 04 E5   ............$...
                           04 85 00 04 00 00 00 01 00 00 00 00 0B 24 06 01   .............$..
                           08 00 08 00 00 00 00 26 24 07 01 00 80 02 68 01   .......&$.....h.
                           00 D0 78 02 00 A0 F1 04 00 46 05 00 15 16 05 00   ..x......F......
                           03 15 16 05 00 20 A1 07 00 2A 2C 0A 00 26 24 07   ..... ...*,..&$.
                           02 00 80 02 E0 01 00 C0 4B 03 00 80 97 06 00 08   ........K.......
                           07 00 15 16 05 00 03 15 16 05 00 20 A1 07 00 2A   ........... ...*
                           2C 0A 00 26 24 07 03 00 C0 03 1C 02 00 D4 8F 05   ,..&$...........
                           00 A8 1F 0B 80 DD 0B 00 15 16 05 00 03 15 16 05   ................
                           00 20 A1 07 00 2A 2C 0A 00 26 24 07 04 00 00 04   . ...*,..&$.....
                           40 02 00 00 54 06 00 00 A8 0C 00 80 0D 00 15 16   @...T...........
                           05 00 03 15 16 05 00 20 A1 07 00 2A 2C 0A 00 26   ....... ...*,..&
                           24 07 05 00 00 05 D0 02 00 40 E3 09 00 80 C6 13   $........@......
                           00 18 15 00 15 16 05 00 03 15 16 05 00 20 A1 07   ............. ..
                           00 2A 2C 0A 00 26 24 07 06 00 80 07 38 04 00 50   .*,..&$.....8..P
                           3F 16 00 A0 7E 2C 00 76 2F 00 15 16 05 00 03 15   ?...~,.v/.......
                           16 05 00 20 A1 07 00 2A 2C 0A 00 26 24 07 07 00   ... ...*,..&$...
                           00 0A A0 05 00 00 8D 27 00 00 1A 4F 00 60 54 00   .......'...O.`T.
                           15 16 05 00 03 15 16 05 00 20 A1 07 00 2A 2C 0A   ......... ...*,.
                           00 26 24 07 08 00 00 0F 70 08 00 40 FD 58 00 80   .&$.....p..@.X..
                           FA B1 00 D8 BD 00 15 16 05 00 03 15 16 05 00 20   ...............
                           A1 07 00 2A 2C 0A 00 1C 24 10 02 08 48 32 36 34   ...*,...$...H264
                           00 00 10 00 80 00 00 AA 00 38 9B 71 10 08 00 00   .........8.q....
                           00 00 01 26 24 11 01 00 80 02 68 01 00 D0 78 02   ...&$.....h...x.
                           00 A0 F1 04 15 16 05 00 03 2C 0A 00 00 15 16 05   .........,......
                           00 20 A1 07 00 2A 2C 0A 00 26 24 11 02 00 80 02   . ...*,..&$.....
                           E0 01 00 C0 4B 03 00 80 97 06 15 16 05 00 03 2C   ....K..........,
                           0A 00 00 15 16 05 00 20 A1 07 00 2A 2C 0A 00 26   ....... ...*,..&
                           24 11 03 00 C0 03 1C 02 00 D4 8F 05 00 A8 1F 0B   $...............
                           15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1 07   .....,....... ..
                           00 2A 2C 0A 00 26 24 11 04 00 00 04 40 02 00 00   .*,..&$.....@...
                           54 06 00 00 A8 0C 15 16 05 00 03 2C 0A 00 00 15   T..........,....
                           16 05 00 20 A1 07 00 2A 2C 0A 00 26 24 11 05 00   ... ...*,..&$...
                           00 05 D0 02 00 40 E3 09 00 80 C6 13 15 16 05 00   .....@..........
                           03 2C 0A 00 00 15 16 05 00 20 A1 07 00 2A 2C 0A   .,....... ...*,.
                           00 26 24 11 06 00 80 07 38 04 00 50 3F 16 00 A0   .&$.....8..P?...
                           7E 2C 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20   ~,.....,.......
                           A1 07 00 2A 2C 0A 00 26 24 11 07 00 00 0A A0 05   ...*,..&$.......
                           00 00 8D 27 00 00 1A 4F 15 16 05 00 03 2C 0A 00   ...'...O.....,..
                           00 15 16 05 00 20 A1 07 00 2A 2C 0A 00 26 24 11   ..... ...*,..&$.
                           08 00 00 0F 70 08 00 40 FD 58 00 80 FA B1 15 16   ....p..@.X......
                           05 00 03 2C 0A 00 00 15 16 05 00 20 A1 07 00 2A   ...,....... ...*
                           2C 0A 00 1C 24 10 03 08 48 32 36 35 00 00 10 00   ,...$...H265....
                           80 00 00 AA 00 38 9B 71 10 08 00 00 00 00 01 26   .....8.q.......&
                           24 11 01 00 80 02 68 01 00 D0 78 02 00 A0 F1 04   $.....h...x.....
                           15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1 07   .....,....... ..
                           00 2A 2C 0A 00 26 24 11 02 00 80 02 E0 01 00 C0   .*,..&$.........
                           4B 03 00 80 97 06 15 16 05 00 03 2C 0A 00 00 15   K..........,....
                           16 05 00 20 A1 07 00 2A 2C 0A 00 26 24 11 03 00   ... ...*,..&$...
                           C0 03 1C 02 00 D4 8F 05 00 A8 1F 0B 15 16 05 00   ................
                           03 2C 0A 00 00 15 16 05 00 20 A1 07 00 2A 2C 0A   .,....... ...*,.
                           00 26 24 11 04 00 00 04 40 02 00 00 54 06 00 00   .&$.....@...T...
                           A8 0C 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20   .......,.......
                           A1 07 00 2A 2C 0A 00 26 24 11 05 00 00 05 D0 02   ...*,..&$.......
                           00 40 E3 09 00 80 C6 13 15 16 05 00 03 2C 0A 00   .@...........,..
                           00 15 16 05 00 20 A1 07 00 2A 2C 0A 00 26 24 11   ..... ...*,..&$.
                           06 00 80 07 38 04 00 50 3F 16 00 A0 7E 2C 15 16   ....8..P?...~,..
                           05 00 03 2C 0A 00 00 15 16 05 00 20 A1 07 00 2A   ...,....... ...*
                           2C 0A 00 26 24 11 07 00 00 0A A0 05 00 00 8D 27   ,..&$..........'
                           00 00 1A 4F 15 16 05 00 03 2C 0A 00 00 15 16 05   ...O.....,......
                           00 20 A1 07 00 2A 2C 0A 00 26 24 11 08 00 00 0F   . ...*,..&$.....
                           70 08 00 40 FD 58 00 80 FA B1 15 16 05 00 03 2C   p..@.X.........,
                           0A 00 00 15 16 05 00 20 A1 07 00 2A 2C 0A 00 1B   ....... ...*,...
                           24 04 04 06 59 55 59 32 00 00 10 00 80 00 00 AA   $...YUY2........
                           00 38 9B 71 10 06 00 00 00 00 26 24 05 01 00 80   .8.q......&$....
                           02 68 01 00 C0 4B 03 00 80 97 06 00 08 07 00 15   .h...K..........
                           16 05 00 03 15 16 05 00 20 A1 07 00 2A 2C 0A 00   ........ ...*,..
                           26 24 05 02 00 80 02 E0 01 00 00 65 04 00 00 CA   &$.........e....
                           08 00 60 09 00 15 16 05 00 03 15 16 05 00 20 A1   ..`........... .
                           07 00 2A 2C 0A 00 26 24 05 03 00 C0 03 1C 02 00   ..*,..&$........
                           D0 78 02 00 70 6A 07 00 D2 0F 00 2A 2C 0A 00 03   .x..pj.....*,...
                           2A 2C 0A 00 40 42 0F 00 80 84 1E 00 26 24 05 04   *,..@B......&$..
                           00 00 04 40 02 00 00 D0 02 00 00 70 08 00 00 12   ...@.......p....
                           00 2A 2C 0A 00 03 2A 2C 0A 00 40 42 0F 00 80 84   .*,...*,..@B....
                           1E 00 26 24 05 05 00 00 05 D0 02 00 00 C2 01 00   ..&$............
                           00 CA 08 00 20 1C 00 40 42 0F 00 03 40 42 0F 00   .... ..@B...@B..
                           80 84 1E 00 40 4B 4C 00 22 24 05 06 00 80 07 38   ....@KL."$.....8
                           04 00 80 F4 03 00 40 E3 09 00 48 3F 00 80 84 1E   ......@...H?....
                           00 02 80 84 1E 00 40 4B 4C 00 06 24 0D 01 01 04   ......@KL..$....
                           09 04 01 01 01 0E 02 00 0A 07 05 85 05 00 02 01   ................
                           09 04 01 02 01 0E 02 00 0B 07 05 85 05 00 04 01   ................
                           09 04 01 03 01 0E 02 00 0C 07 05 85 05 00 0C 01   ................
                           09 04 01 04 01 0E 02 00 0D 07 05 85 05 00 14 01   ................

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x00
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x05 (String Descriptor 5)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 08 0B 00 02 0E 03 00 05                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x00
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x08 (String Descriptor 8)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 09 04 00 00 00 0E 01 00 08                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0110 (UVC Version 1.10)
wTotalLength             : 0x0068 (104 bytes)
dwClockFreq              : 0x02DC6C00 (48 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x01
Data (HexDump)           : 0D 24 01 10 01 68 00 00 6C DC 02 01 01            .$...h..l....

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
bmControls               : 0x0E, 0x22, 0x00
 D0                      : 0   no -  Scanning Mode
 D1                      : 1  yes -  Auto-Exposure Mode
 D2                      : 1  yes -  Auto-Exposure Priority
 D3                      : 1  yes -  Exposure Time (Absolute)
 D4                      : 0   no -  Exposure Time (Relative)
 D5                      : 0   no -  Focus (Absolute)
 D6                      : 0   no -  Focus (Relative)
 D7                      : 0   no -  Iris (Absolute)
 D8                      : 0   no -  Iris (Relative)
 D9                      : 1  yes -  Zoom (Absolute)
 D10                     : 0   no -  Zoom (Relative)
 D11                     : 0   no -  Pan (Absolute)
 D12                     : 0   no -  Pan (Relative)
 D13                     : 1  yes -  Roll (Absolute)
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
                           22 00                                             ".

        -------- Video Control Processing Unit Descriptor -----
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x05 (Processing Unit)
bUnitID                  : 0x02
bSourceID                : 0x01
wMaxMultiplier           : 0x4000 (163.84x Zoom)
bControlSize             : 0x02
bmControls               : 0x7F, 0x17
 D0                      : 1  yes -  Brightness
 D1                      : 1  yes -  Contrast
 D2                      : 1  yes -  Hue
 D3                      : 1  yes -  Saturation
 D4                      : 1  yes -  Sharpness
 D5                      : 1  yes -  Gamma
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
bmVideoStandards         : 0x00
 D0                      : 0   no -  None
 D1                      : 0   no -  NTSC  - 525/60
 D2                      : 0   no -  PAL   - 625/50
 D3                      : 0   no -  SECAM - 625/50
 D4                      : 0   no -  NTSC  - 625/50
 D5                      : 0   no -  PAL   - 525/60
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Data (HexDump)           : 0C 24 05 02 01 00 40 02 7F 17 00 00               .$....@.....

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x03
guidExtensionCode        : {302E2018-6311-4A2E-BA2C-6890EB334016}
bNumControls             : 0x02
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x01
bmControls               : 0x03
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 0   no -  Vendor-Specific (Optional)
 D3                      : 0   no -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x06
 *!*ERROR  String descriptor not found
Data (HexDump)           : 1A 24 06 03 18 20 2E 30 11 63 2E 4A BA 2C 68 90   .$... .0.c.J.,h.
                           EB 33 40 16 02 01 02 01 03 06                     .3@.......

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x04
guidExtensionCode        : {33CBFBA4-FD26-4CE4-9076-A1931FE74C5E}
bNumControls             : 0x02
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x01
bmControls               : 0x03
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 0   no -  Vendor-Specific (Optional)
 D3                      : 0   no -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x07
 *!*ERROR  String descriptor not found
Data (HexDump)           : 1A 24 06 04 A4 FB CB 33 26 FD E4 4C 90 76 A1 93   .$.....3&..L.v..
                           1F E7 4C 5E 02 01 02 01 03 07                     ..L^......

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

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x09 (String Descriptor 9)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 09 04 01 00 00 0E 02 00 09                        .........

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x11 (17 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x04
wTotalLength             : 0x04E5 (1253 bytes)
bEndpointAddress         : 0x85 (Direction=IN  EndpointID=5)
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
Video Payload Format 3   : 0x00
 D0                      : 0   no -  Key Frame Rate
 D1                      : 0   no -  P Frame Rate
 D2                      : 0   no -  Compression Quality
 D3                      : 0   no -  Compression Window Size
 D4                      : 0   no -  Generate Key Frame
 D5                      : 0   no -  Update Frame Segment
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Video Payload Format 4   : 0x00
 D0                      : 0   no -  Key Frame Rate
 D1                      : 0   no -  P Frame Rate
 D2                      : 0   no -  Compression Quality
 D3                      : 0   no -  Compression Window Size
 D4                      : 0   no -  Generate Key Frame
 D5                      : 0   no -  Update Frame Segment
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Data (HexDump)           : 11 24 01 04 E5 04 85 00 04 00 00 00 01 00 00 00   .$..............
                           00                                                .

        ----- Video Streaming MJPEG Format Type Descriptor ----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x06 (Format MJPEG)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x08 (8)
bmFlags                  : 0x00 (Sample size is not fixed)
bDefaultFrameIndex       : 0x08 (8)
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
*!*ERROR:  no Color Matching Descriptor for this format
Data (HexDump)           : 0B 24 06 01 08 00 08 00 00 00 00                  .$.........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x0278D000 (41472000 bps -> 5.184 MB/s)
dwMaxBitRate             : 0x04F1A000 (82944000 bps -> 10.368 MB/s)
dwMaxVideoFrameBufferSize: 0x00054600 (345600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 01 00 80 02 68 01 00 D0 78 02 00 A0 F1   &$.....h...x....
                           04 00 46 05 00 15 16 05 00 03 15 16 05 00 20 A1   ..F........... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x034BC000 (55296000 bps -> 6.912 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxVideoFrameBufferSize: 0x00070800 (460800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 02 00 80 02 E0 01 00 C0 4B 03 00 80 97   &$.........K....
                           06 00 08 07 00 15 16 05 00 03 15 16 05 00 20 A1   .............. .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x03C0 (960)
wHeight                  : 0x021C (540)
dwMinBitRate             : 0x058FD400 (93312000 bps -> 11.664 MB/s)
dwMaxBitRate             : 0x0B1FA800 (186624000 bps -> 23.328 MB/s)
dwMaxVideoFrameBufferSize: 0x000BDD80 (777600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 03 00 C0 03 1C 02 00 D4 8F 05 00 A8 1F   &$..............
                           0B 80 DD 0B 00 15 16 05 00 03 15 16 05 00 20 A1   .............. .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0400 (1024)
wHeight                  : 0x0240 (576)
dwMinBitRate             : 0x06540000 (106168320 bps -> 13.271 MB/s)
dwMaxBitRate             : 0x0CA80000 (212336640 bps -> 26.542 MB/s)
dwMaxVideoFrameBufferSize: 0x000D8000 (884736 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 04 00 00 04 40 02 00 00 54 06 00 00 A8   &$.....@...T....
                           0C 00 80 0D 00 15 16 05 00 03 15 16 05 00 20 A1   .............. .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x09E34000 (165888000 bps -> 20.736 MB/s)
dwMaxBitRate             : 0x13C68000 (331776000 bps -> 41.472 MB/s)
dwMaxVideoFrameBufferSize: 0x00151800 (1382400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 05 00 00 05 D0 02 00 40 E3 09 00 80 C6   &$........@.....
                           13 00 18 15 00 15 16 05 00 03 15 16 05 00 20 A1   .............. .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x163F5000 (373248000 bps -> 46.656 MB/s)
dwMaxBitRate             : 0x2C7EA000 (746496000 bps -> 93.312 MB/s)
dwMaxVideoFrameBufferSize: 0x002F7600 (3110400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 06 00 80 07 38 04 00 50 3F 16 00 A0 7E   &$.....8..P?...~
                           2C 00 76 2F 00 15 16 05 00 03 15 16 05 00 20 A1   ,.v/.......... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x07
bmCapabilities           : 0x00
wWidth                   : 0x0A00 (2560)
wHeight                  : 0x05A0 (1440)
dwMinBitRate             : 0x278D0000 (663552000 bps -> 82.944 MB/s)
dwMaxBitRate             : 0x4F1A0000 (1327104000 bps -> 165.888 MB/s)
dwMaxVideoFrameBufferSize: 0x00546000 (5529600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 07 00 00 0A A0 05 00 00 8D 27 00 00 1A   &$..........'...
                           4F 00 60 54 00 15 16 05 00 03 15 16 05 00 20 A1   O.`T.......... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
---> This is the Default (optimum) Frame index
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x08
bmCapabilities           : 0x00
wWidth                   : 0x0F00 (3840)
wHeight                  : 0x0870 (2160)
dwMinBitRate             : 0x58FD4000 (1492992000 bps -> 186.624 MB/s)
dwMaxBitRate             : 0xB1FA8000 (2985984000 bps -> 373.248 MB/s)
dwMaxVideoFrameBufferSize: 0x00BDD800 (12441600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 08 00 00 0F 70 08 00 40 FD 58 00 80 FA   &$.....p..@.X...
                           B1 00 D8 BD 00 15 16 05 00 03 15 16 05 00 20 A1   .............. .
                           07 00 2A 2C 0A 00                                 ..*,..

        ---- VS Frame Based Payload Format Type Descriptor ----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x10 (Frame Based Format Type)
bFormatIndex             : 0x02 (2)
bNumFrameDescriptors     : 0x08 (8)
guidFormat               : {34363248-0000-0010-8000-00AA00389B71} (H264)
bBitsPerPixel            : 0x10 (16 bits)
bDefaultFrameIndex       : 0x08 (8)
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
bVariableSize            : 0x01 (Variable Size)
*!*ERROR:  Found 16 frame descriptors (should be 8)
*!*ERROR:  no Color Matching Descriptor for this format
Data (HexDump)           : 1C 24 10 02 08 48 32 36 34 00 00 10 00 80 00 00   .$...H264.......
                           AA 00 38 9B 71 10 08 00 00 00 00 01               ..8.q.......

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x0278D000 (41472000 bps -> 5.184 MB/s)
dwMaxBitRate             : 0x04F1A000 (82944000 bps -> 10.368 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 01 00 80 02 68 01 00 D0 78 02 00 A0 F1   &$.....h...x....
                           04 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x034BC000 (55296000 bps -> 6.912 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 02 00 80 02 E0 01 00 C0 4B 03 00 80 97   &$.........K....
                           06 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x03C0 (960)
wHeight                  : 0x021C (540)
dwMinBitRate             : 0x058FD400 (93312000 bps -> 11.664 MB/s)
dwMaxBitRate             : 0x0B1FA800 (186624000 bps -> 23.328 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 03 00 C0 03 1C 02 00 D4 8F 05 00 A8 1F   &$..............
                           0B 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0400 (1024)
wHeight                  : 0x0240 (576)
dwMinBitRate             : 0x06540000 (106168320 bps -> 13.271 MB/s)
dwMaxBitRate             : 0x0CA80000 (212336640 bps -> 26.542 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 04 00 00 04 40 02 00 00 54 06 00 00 A8   &$.....@...T....
                           0C 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x09E34000 (165888000 bps -> 20.736 MB/s)
dwMaxBitRate             : 0x13C68000 (331776000 bps -> 41.472 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 05 00 00 05 D0 02 00 40 E3 09 00 80 C6   &$........@.....
                           13 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x163F5000 (373248000 bps -> 46.656 MB/s)
dwMaxBitRate             : 0x2C7EA000 (746496000 bps -> 93.312 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 06 00 80 07 38 04 00 50 3F 16 00 A0 7E   &$.....8..P?...~
                           2C 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ,.....,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x07
bmCapabilities           : 0x00
wWidth                   : 0x0A00 (2560)
wHeight                  : 0x05A0 (1440)
dwMinBitRate             : 0x278D0000 (663552000 bps -> 82.944 MB/s)
dwMaxBitRate             : 0x4F1A0000 (1327104000 bps -> 165.888 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 07 00 00 0A A0 05 00 00 8D 27 00 00 1A   &$..........'...
                           4F 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   O.....,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x08
bmCapabilities           : 0x00
wWidth                   : 0x0F00 (3840)
wHeight                  : 0x0870 (2160)
dwMinBitRate             : 0x58FD4000 (1492992000 bps -> 186.624 MB/s)
dwMaxBitRate             : 0xB1FA8000 (2985984000 bps -> 373.248 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 08 00 00 0F 70 08 00 40 FD 58 00 80 FA   &$.....p..@.X...
                           B1 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ---- VS Frame Based Payload Format Type Descriptor ----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x10 (Frame Based Format Type)
bFormatIndex             : 0x03 (3)
bNumFrameDescriptors     : 0x08 (8)
guidFormat               : {35363248-0000-0010-8000-00AA00389B71} (H265)
bBitsPerPixel            : 0x10 (16 bits)
bDefaultFrameIndex       : 0x08 (8)
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
bVariableSize            : 0x01 (Variable Size)
*!*ERROR:  no Color Matching Descriptor for this format
Data (HexDump)           : 1C 24 10 03 08 48 32 36 35 00 00 10 00 80 00 00   .$...H265.......
                           AA 00 38 9B 71 10 08 00 00 00 00 01               ..8.q.......

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x0278D000 (41472000 bps -> 5.184 MB/s)
dwMaxBitRate             : 0x04F1A000 (82944000 bps -> 10.368 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 01 00 80 02 68 01 00 D0 78 02 00 A0 F1   &$.....h...x....
                           04 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x034BC000 (55296000 bps -> 6.912 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 02 00 80 02 E0 01 00 C0 4B 03 00 80 97   &$.........K....
                           06 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x03C0 (960)
wHeight                  : 0x021C (540)
dwMinBitRate             : 0x058FD400 (93312000 bps -> 11.664 MB/s)
dwMaxBitRate             : 0x0B1FA800 (186624000 bps -> 23.328 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 03 00 C0 03 1C 02 00 D4 8F 05 00 A8 1F   &$..............
                           0B 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0400 (1024)
wHeight                  : 0x0240 (576)
dwMinBitRate             : 0x06540000 (106168320 bps -> 13.271 MB/s)
dwMaxBitRate             : 0x0CA80000 (212336640 bps -> 26.542 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 04 00 00 04 40 02 00 00 54 06 00 00 A8   &$.....@...T....
                           0C 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x09E34000 (165888000 bps -> 20.736 MB/s)
dwMaxBitRate             : 0x13C68000 (331776000 bps -> 41.472 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 05 00 00 05 D0 02 00 40 E3 09 00 80 C6   &$........@.....
                           13 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x163F5000 (373248000 bps -> 46.656 MB/s)
dwMaxBitRate             : 0x2C7EA000 (746496000 bps -> 93.312 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 06 00 80 07 38 04 00 50 3F 16 00 A0 7E   &$.....8..P?...~
                           2C 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ,.....,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x07
bmCapabilities           : 0x00
wWidth                   : 0x0A00 (2560)
wHeight                  : 0x05A0 (1440)
dwMinBitRate             : 0x278D0000 (663552000 bps -> 82.944 MB/s)
dwMaxBitRate             : 0x4F1A0000 (1327104000 bps -> 165.888 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 07 00 00 0A A0 05 00 00 8D 27 00 00 1A   &$..........'...
                           4F 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   O.....,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x08
bmCapabilities           : 0x00
wWidth                   : 0x0F00 (3840)
wHeight                  : 0x0870 (2160)
dwMinBitRate             : 0x58FD4000 (1492992000 bps -> 186.624 MB/s)
dwMaxBitRate             : 0xB1FA8000 (2985984000 bps -> 373.248 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 08 00 00 0F 70 08 00 40 FD 58 00 80 FA   &$.....p..@.X...
                           B1 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ------- VS Uncompressed Format Type Descriptor --------
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x04 (Uncompressed Format Type)
bFormatIndex             : 0x04 (4)
bNumFrameDescriptors     : 0x06 (6)
guidFormat               : {32595559-0000-0010-8000-00AA00389B71} (YUY2)
bBitsPerPixel            : 0x10 (16 bits)
bDefaultFrameIndex       : 0x06 (6)
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
Data (HexDump)           : 1B 24 04 04 06 59 55 59 32 00 00 10 00 80 00 00   .$...YUY2.......
                           AA 00 38 9B 71 10 06 00 00 00 00                  ..8.q......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x034BC000 (55296000 bps -> 6.912 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxVideoFrameBufferSize: 0x00070800 (460800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 05 01 00 80 02 68 01 00 C0 4B 03 00 80 97   &$.....h...K....
                           06 00 08 07 00 15 16 05 00 03 15 16 05 00 20 A1   .............. .
                           07 00 2A 2C 0A 00                                 ..*,..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x04650000 (73728000 bps -> 9.216 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x00096000 (614400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 05 02 00 80 02 E0 01 00 00 65 04 00 00 CA   &$.........e....
                           08 00 60 09 00 15 16 05 00 03 15 16 05 00 20 A1   ..`........... .
                           07 00 2A 2C 0A 00                                 ..*,..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x03C0 (960)
wHeight                  : 0x021C (540)
dwMinBitRate             : 0x0278D000 (41472000 bps -> 5.184 MB/s)
dwMaxBitRate             : 0x076A7000 (124416000 bps -> 15.552 MB/s)
dwMaxVideoFrameBufferSize: 0x000FD200 (1036800 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[2]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[3]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 26 24 05 03 00 C0 03 1C 02 00 D0 78 02 00 70 6A   &$.........x..pj
                           07 00 D2 0F 00 2A 2C 0A 00 03 2A 2C 0A 00 40 42   .....*,...*,..@B
                           0F 00 80 84 1E 00                                 ......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0400 (1024)
wHeight                  : 0x0240 (576)
dwMinBitRate             : 0x02D00000 (47185920 bps -> 5.898 MB/s)
dwMaxBitRate             : 0x08700000 (141557760 bps -> 17.694 MB/s)
dwMaxVideoFrameBufferSize: 0x00120000 (1179648 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[2]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[3]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 26 24 05 04 00 00 04 40 02 00 00 D0 02 00 00 70   &$.....@.......p
                           08 00 00 12 00 2A 2C 0A 00 03 2A 2C 0A 00 40 42   .....*,...*,..@B
                           0F 00 80 84 1E 00                                 ......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x01C20000 (29491200 bps -> 3.686 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x001C2000 (1843200 bytes)
dwDefaultFrameInterval   : 0x000F4240 (100.0000 ms -> 10.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[2]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
adwFrameInterval[3]      : 0x004C4B40 (500.0000 ms -> 2.000 fps)
Data (HexDump)           : 26 24 05 05 00 00 05 D0 02 00 00 C2 01 00 00 CA   &$..............
                           08 00 20 1C 00 40 42 0F 00 03 40 42 0F 00 80 84   .. ..@B...@B....
                           1E 00 40 4B 4C 00                                 ..@KL.

        -------- VS Uncompressed Frame Type Descriptor --------
---> This is the Default (optimum) Frame index
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x03F48000 (66355200 bps -> 8.294 MB/s)
dwMaxBitRate             : 0x09E34000 (165888000 bps -> 20.736 MB/s)
dwMaxVideoFrameBufferSize: 0x003F4800 (4147200 bytes)
dwDefaultFrameInterval   : 0x001E8480 (200.0000 ms -> 5.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
adwFrameInterval[2]      : 0x004C4B40 (500.0000 ms -> 2.000 fps)
Data (HexDump)           : 22 24 05 06 00 80 07 38 04 00 80 F4 03 00 40 E3   "$.....8......@.
                           09 00 48 3F 00 80 84 1E 00 02 80 84 1E 00 40 4B   ..H?..........@K
                           4C 00                                             L.

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
iInterface               : 0x0A (String Descriptor 10)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 09 04 01 01 01 0E 02 00 0A                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x85 (Direction=IN EndpointID=5)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0200
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x200 (512 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 85 05 00 02 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x02
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x0B (String Descriptor 11)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 09 04 01 02 01 0E 02 00 0B                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x85 (Direction=IN EndpointID=5)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0400
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x400 (1024 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 85 05 00 04 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x03
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x0C (String Descriptor 12)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 09 04 01 03 01 0E 02 00 0C                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x85 (Direction=IN EndpointID=5)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0C00
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x01 (1 additional transactions per microframe -> allows 513..1024 byte per packet)
 Bits 10..0              : 0x400 (1024 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 85 05 00 0C 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x04
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x0D (String Descriptor 13)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 09 04 01 04 01 0E 02 00 0D                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x85 (Direction=IN EndpointID=5)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x1400
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x02 (2 additional transactions per microframe -> allows 683..1024 bytes per packet)
 Bits 10..0              : 0x400 (1024 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 85 05 00 14 01                              .......

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
wTotalLength             : 0x0580 (1408 bytes)
bNumInterfaces           : 0x02 (2 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x04 (String Descriptor 4)
 *!*ERROR  String descriptor not found
bmAttributes             : 0x80
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x00 (no)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0xFA (500 mA)
Data (HexDump)           : 09 07 80 05 02 01 04 80 FA 08 0B 00 02 0E 03 00   ................
                           05 09 04 00 00 00 0E 01 00 08 0D 24 01 10 01 68   ...........$...h
                           00 00 6C DC 02 01 01 12 24 02 01 01 02 00 00 00   ..l.....$.......
                           00 00 00 00 00 03 0E 22 00 0C 24 05 02 01 00 40   ......."..$....@
                           02 7F 17 00 00 1A 24 06 03 18 20 2E 30 11 63 2E   ......$... .0.c.
                           4A BA 2C 68 90 EB 33 40 16 02 01 02 01 03 06 1A   J.,h..3@........
                           24 06 04 A4 FB CB 33 26 FD E4 4C 90 76 A1 93 1F   $.....3&..L.v...
                           E7 4C 5E 02 01 02 01 03 07 09 24 03 04 01 01 00   .L^.......$.....
                           03 00 09 04 01 00 00 0E 02 00 09 11 24 01 04 E5   ............$...
                           04 85 00 04 00 00 00 01 00 00 00 00 0B 24 06 01   .............$..
                           08 00 08 00 00 00 00 26 24 07 01 00 80 02 68 01   .......&$.....h.
                           00 D0 78 02 00 A0 F1 04 00 46 05 00 15 16 05 00   ..x......F......
                           03 15 16 05 00 20 A1 07 00 2A 2C 0A 00 26 24 07   ..... ...*,..&$.
                           02 00 80 02 E0 01 00 C0 4B 03 00 80 97 06 00 08   ........K.......
                           07 00 15 16 05 00 03 15 16 05 00 20 A1 07 00 2A   ........... ...*
                           2C 0A 00 26 24 07 03 00 C0 03 1C 02 00 D4 8F 05   ,..&$...........
                           00 A8 1F 0B 80 DD 0B 00 15 16 05 00 03 15 16 05   ................
                           00 20 A1 07 00 2A 2C 0A 00 26 24 07 04 00 00 04   . ...*,..&$.....
                           40 02 00 00 54 06 00 00 A8 0C 00 80 0D 00 15 16   @...T...........
                           05 00 03 15 16 05 00 20 A1 07 00 2A 2C 0A 00 26   ....... ...*,..&
                           24 07 05 00 00 05 D0 02 00 40 E3 09 00 80 C6 13   $........@......
                           00 18 15 00 15 16 05 00 03 15 16 05 00 20 A1 07   ............. ..
                           00 2A 2C 0A 00 26 24 07 06 00 80 07 38 04 00 50   .*,..&$.....8..P
                           3F 16 00 A0 7E 2C 00 76 2F 00 15 16 05 00 03 15   ?...~,.v/.......
                           16 05 00 20 A1 07 00 2A 2C 0A 00 26 24 07 07 00   ... ...*,..&$...
                           00 0A A0 05 00 00 8D 27 00 00 1A 4F 00 60 54 00   .......'...O.`T.
                           15 16 05 00 03 15 16 05 00 20 A1 07 00 2A 2C 0A   ......... ...*,.
                           00 26 24 07 08 00 00 0F 70 08 00 40 FD 58 00 80   .&$.....p..@.X..
                           FA B1 00 D8 BD 00 15 16 05 00 03 15 16 05 00 20   ...............
                           A1 07 00 2A 2C 0A 00 1C 24 10 02 08 48 32 36 34   ...*,...$...H264
                           00 00 10 00 80 00 00 AA 00 38 9B 71 10 08 00 00   .........8.q....
                           00 00 01 26 24 11 01 00 80 02 68 01 00 D0 78 02   ...&$.....h...x.
                           00 A0 F1 04 15 16 05 00 03 2C 0A 00 00 15 16 05   .........,......
                           00 20 A1 07 00 2A 2C 0A 00 26 24 11 02 00 80 02   . ...*,..&$.....
                           E0 01 00 C0 4B 03 00 80 97 06 15 16 05 00 03 2C   ....K..........,
                           0A 00 00 15 16 05 00 20 A1 07 00 2A 2C 0A 00 26   ....... ...*,..&
                           24 11 03 00 C0 03 1C 02 00 D4 8F 05 00 A8 1F 0B   $...............
                           15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1 07   .....,....... ..
                           00 2A 2C 0A 00 26 24 11 04 00 00 04 40 02 00 00   .*,..&$.....@...
                           54 06 00 00 A8 0C 15 16 05 00 03 2C 0A 00 00 15   T..........,....
                           16 05 00 20 A1 07 00 2A 2C 0A 00 26 24 11 05 00   ... ...*,..&$...
                           00 05 D0 02 00 40 E3 09 00 80 C6 13 15 16 05 00   .....@..........
                           03 2C 0A 00 00 15 16 05 00 20 A1 07 00 2A 2C 0A   .,....... ...*,.
                           00 26 24 11 06 00 80 07 38 04 00 50 3F 16 00 A0   .&$.....8..P?...
                           7E 2C 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20   ~,.....,.......
                           A1 07 00 2A 2C 0A 00 26 24 11 07 00 00 0A A0 05   ...*,..&$.......
                           00 00 8D 27 00 00 1A 4F 15 16 05 00 03 2C 0A 00   ...'...O.....,..
                           00 15 16 05 00 20 A1 07 00 2A 2C 0A 00 26 24 11   ..... ...*,..&$.
                           08 00 00 0F 70 08 00 40 FD 58 00 80 FA B1 15 16   ....p..@.X......
                           05 00 03 2C 0A 00 00 15 16 05 00 20 A1 07 00 2A   ...,....... ...*
                           2C 0A 00 1C 24 10 03 08 48 32 36 35 00 00 10 00   ,...$...H265....
                           80 00 00 AA 00 38 9B 71 10 08 00 00 00 00 01 26   .....8.q.......&
                           24 11 01 00 80 02 68 01 00 D0 78 02 00 A0 F1 04   $.....h...x.....
                           15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1 07   .....,....... ..
                           00 2A 2C 0A 00 26 24 11 02 00 80 02 E0 01 00 C0   .*,..&$.........
                           4B 03 00 80 97 06 15 16 05 00 03 2C 0A 00 00 15   K..........,....
                           16 05 00 20 A1 07 00 2A 2C 0A 00 26 24 11 03 00   ... ...*,..&$...
                           C0 03 1C 02 00 D4 8F 05 00 A8 1F 0B 15 16 05 00   ................
                           03 2C 0A 00 00 15 16 05 00 20 A1 07 00 2A 2C 0A   .,....... ...*,.
                           00 26 24 11 04 00 00 04 40 02 00 00 54 06 00 00   .&$.....@...T...
                           A8 0C 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20   .......,.......
                           A1 07 00 2A 2C 0A 00 26 24 11 05 00 00 05 D0 02   ...*,..&$.......
                           00 40 E3 09 00 80 C6 13 15 16 05 00 03 2C 0A 00   .@...........,..
                           00 15 16 05 00 20 A1 07 00 2A 2C 0A 00 26 24 11   ..... ...*,..&$.
                           06 00 80 07 38 04 00 50 3F 16 00 A0 7E 2C 15 16   ....8..P?...~,..
                           05 00 03 2C 0A 00 00 15 16 05 00 20 A1 07 00 2A   ...,....... ...*
                           2C 0A 00 26 24 11 07 00 00 0A A0 05 00 00 8D 27   ,..&$..........'
                           00 00 1A 4F 15 16 05 00 03 2C 0A 00 00 15 16 05   ...O.....,......
                           00 20 A1 07 00 2A 2C 0A 00 26 24 11 08 00 00 0F   . ...*,..&$.....
                           70 08 00 40 FD 58 00 80 FA B1 15 16 05 00 03 2C   p..@.X.........,
                           0A 00 00 15 16 05 00 20 A1 07 00 2A 2C 0A 00 1B   ....... ...*,...
                           24 04 04 06 59 55 59 32 00 00 10 00 80 00 00 AA   $...YUY2........
                           00 38 9B 71 10 06 00 00 00 00 26 24 05 01 00 80   .8.q......&$....
                           02 68 01 00 C0 4B 03 00 80 97 06 00 08 07 00 15   .h...K..........
                           16 05 00 03 15 16 05 00 20 A1 07 00 2A 2C 0A 00   ........ ...*,..
                           26 24 05 02 00 80 02 E0 01 00 00 65 04 00 00 CA   &$.........e....
                           08 00 60 09 00 15 16 05 00 03 15 16 05 00 20 A1   ..`........... .
                           07 00 2A 2C 0A 00 26 24 05 03 00 C0 03 1C 02 00   ..*,..&$........
                           D0 78 02 00 70 6A 07 00 D2 0F 00 2A 2C 0A 00 03   .x..pj.....*,...
                           2A 2C 0A 00 40 42 0F 00 80 84 1E 00 26 24 05 04   *,..@B......&$..
                           00 00 04 40 02 00 00 D0 02 00 00 70 08 00 00 12   ...@.......p....
                           00 2A 2C 0A 00 03 2A 2C 0A 00 40 42 0F 00 80 84   .*,...*,..@B....
                           1E 00 26 24 05 05 00 00 05 D0 02 00 00 C2 01 00   ..&$............
                           00 CA 08 00 20 1C 00 40 42 0F 00 03 40 42 0F 00   .... ..@B...@B..
                           80 84 1E 00 40 4B 4C 00 22 24 05 06 00 80 07 38   ....@KL."$.....8
                           04 00 80 F4 03 00 40 E3 09 00 48 3F 00 80 84 1E   ......@...H?....
                           00 02 80 84 1E 00 40 4B 4C 00 06 24 0D 01 01 04   ......@KL..$....
                           09 04 01 01 01 0E 02 00 0A 07 05 85 05 01 00 01   ................

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x00
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x05 (String Descriptor 5)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 08 0B 00 02 0E 03 00 05                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x00
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x08 (String Descriptor 8)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 09 04 00 00 00 0E 01 00 08                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0110 (UVC Version 1.10)
wTotalLength             : 0x0068 (104 bytes)
dwClockFreq              : 0x02DC6C00 (48 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x01
Data (HexDump)           : 0D 24 01 10 01 68 00 00 6C DC 02 01 01            .$...h..l....

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
bmControls               : 0x0E, 0x22, 0x00
 D0                      : 0   no -  Scanning Mode
 D1                      : 1  yes -  Auto-Exposure Mode
 D2                      : 1  yes -  Auto-Exposure Priority
 D3                      : 1  yes -  Exposure Time (Absolute)
 D4                      : 0   no -  Exposure Time (Relative)
 D5                      : 0   no -  Focus (Absolute)
 D6                      : 0   no -  Focus (Relative)
 D7                      : 0   no -  Iris (Absolute)
 D8                      : 0   no -  Iris (Relative)
 D9                      : 1  yes -  Zoom (Absolute)
 D10                     : 0   no -  Zoom (Relative)
 D11                     : 0   no -  Pan (Absolute)
 D12                     : 0   no -  Pan (Relative)
 D13                     : 1  yes -  Roll (Absolute)
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
                           22 00                                             ".

        -------- Video Control Processing Unit Descriptor -----
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x05 (Processing Unit)
bUnitID                  : 0x02
bSourceID                : 0x01
wMaxMultiplier           : 0x4000 (163.84x Zoom)
bControlSize             : 0x02
bmControls               : 0x7F, 0x17
 D0                      : 1  yes -  Brightness
 D1                      : 1  yes -  Contrast
 D2                      : 1  yes -  Hue
 D3                      : 1  yes -  Saturation
 D4                      : 1  yes -  Sharpness
 D5                      : 1  yes -  Gamma
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
bmVideoStandards         : 0x00
 D0                      : 0   no -  None
 D1                      : 0   no -  NTSC  - 525/60
 D2                      : 0   no -  PAL   - 625/50
 D3                      : 0   no -  SECAM - 625/50
 D4                      : 0   no -  NTSC  - 625/50
 D5                      : 0   no -  PAL   - 525/60
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Data (HexDump)           : 0C 24 05 02 01 00 40 02 7F 17 00 00               .$....@.....

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x03
guidExtensionCode        : {302E2018-6311-4A2E-BA2C-6890EB334016}
bNumControls             : 0x02
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x01
bmControls               : 0x03
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 0   no -  Vendor-Specific (Optional)
 D3                      : 0   no -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x06
 *!*ERROR  String descriptor not found
Data (HexDump)           : 1A 24 06 03 18 20 2E 30 11 63 2E 4A BA 2C 68 90   .$... .0.c.J.,h.
                           EB 33 40 16 02 01 02 01 03 06                     .3@.......

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x04
guidExtensionCode        : {33CBFBA4-FD26-4CE4-9076-A1931FE74C5E}
bNumControls             : 0x02
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x01
bmControls               : 0x03
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 0   no -  Vendor-Specific (Optional)
 D3                      : 0   no -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x07
 *!*ERROR  String descriptor not found
Data (HexDump)           : 1A 24 06 04 A4 FB CB 33 26 FD E4 4C 90 76 A1 93   .$.....3&..L.v..
                           1F E7 4C 5E 02 01 02 01 03 07                     ..L^......

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

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x09 (String Descriptor 9)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 09 04 01 00 00 0E 02 00 09                        .........

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x11 (17 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x04
wTotalLength             : 0x04E5 (1253 bytes)
bEndpointAddress         : 0x85 (Direction=IN  EndpointID=5)
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
Video Payload Format 3   : 0x00
 D0                      : 0   no -  Key Frame Rate
 D1                      : 0   no -  P Frame Rate
 D2                      : 0   no -  Compression Quality
 D3                      : 0   no -  Compression Window Size
 D4                      : 0   no -  Generate Key Frame
 D5                      : 0   no -  Update Frame Segment
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Video Payload Format 4   : 0x00
 D0                      : 0   no -  Key Frame Rate
 D1                      : 0   no -  P Frame Rate
 D2                      : 0   no -  Compression Quality
 D3                      : 0   no -  Compression Window Size
 D4                      : 0   no -  Generate Key Frame
 D5                      : 0   no -  Update Frame Segment
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Data (HexDump)           : 11 24 01 04 E5 04 85 00 04 00 00 00 01 00 00 00   .$..............
                           00                                                .

        ----- Video Streaming MJPEG Format Type Descriptor ----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x06 (Format MJPEG)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x08 (8)
bmFlags                  : 0x00 (Sample size is not fixed)
bDefaultFrameIndex       : 0x08 (8)
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
*!*ERROR:  no Color Matching Descriptor for this format
Data (HexDump)           : 0B 24 06 01 08 00 08 00 00 00 00                  .$.........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x0278D000 (41472000 bps -> 5.184 MB/s)
dwMaxBitRate             : 0x04F1A000 (82944000 bps -> 10.368 MB/s)
dwMaxVideoFrameBufferSize: 0x00054600 (345600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 01 00 80 02 68 01 00 D0 78 02 00 A0 F1   &$.....h...x....
                           04 00 46 05 00 15 16 05 00 03 15 16 05 00 20 A1   ..F........... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x034BC000 (55296000 bps -> 6.912 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxVideoFrameBufferSize: 0x00070800 (460800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 02 00 80 02 E0 01 00 C0 4B 03 00 80 97   &$.........K....
                           06 00 08 07 00 15 16 05 00 03 15 16 05 00 20 A1   .............. .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x03C0 (960)
wHeight                  : 0x021C (540)
dwMinBitRate             : 0x058FD400 (93312000 bps -> 11.664 MB/s)
dwMaxBitRate             : 0x0B1FA800 (186624000 bps -> 23.328 MB/s)
dwMaxVideoFrameBufferSize: 0x000BDD80 (777600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 03 00 C0 03 1C 02 00 D4 8F 05 00 A8 1F   &$..............
                           0B 80 DD 0B 00 15 16 05 00 03 15 16 05 00 20 A1   .............. .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0400 (1024)
wHeight                  : 0x0240 (576)
dwMinBitRate             : 0x06540000 (106168320 bps -> 13.271 MB/s)
dwMaxBitRate             : 0x0CA80000 (212336640 bps -> 26.542 MB/s)
dwMaxVideoFrameBufferSize: 0x000D8000 (884736 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 04 00 00 04 40 02 00 00 54 06 00 00 A8   &$.....@...T....
                           0C 00 80 0D 00 15 16 05 00 03 15 16 05 00 20 A1   .............. .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x09E34000 (165888000 bps -> 20.736 MB/s)
dwMaxBitRate             : 0x13C68000 (331776000 bps -> 41.472 MB/s)
dwMaxVideoFrameBufferSize: 0x00151800 (1382400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 05 00 00 05 D0 02 00 40 E3 09 00 80 C6   &$........@.....
                           13 00 18 15 00 15 16 05 00 03 15 16 05 00 20 A1   .............. .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x163F5000 (373248000 bps -> 46.656 MB/s)
dwMaxBitRate             : 0x2C7EA000 (746496000 bps -> 93.312 MB/s)
dwMaxVideoFrameBufferSize: 0x002F7600 (3110400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 06 00 80 07 38 04 00 50 3F 16 00 A0 7E   &$.....8..P?...~
                           2C 00 76 2F 00 15 16 05 00 03 15 16 05 00 20 A1   ,.v/.......... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x07
bmCapabilities           : 0x00
wWidth                   : 0x0A00 (2560)
wHeight                  : 0x05A0 (1440)
dwMinBitRate             : 0x278D0000 (663552000 bps -> 82.944 MB/s)
dwMaxBitRate             : 0x4F1A0000 (1327104000 bps -> 165.888 MB/s)
dwMaxVideoFrameBufferSize: 0x00546000 (5529600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 07 00 00 0A A0 05 00 00 8D 27 00 00 1A   &$..........'...
                           4F 00 60 54 00 15 16 05 00 03 15 16 05 00 20 A1   O.`T.......... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
---> This is the Default (optimum) Frame index
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x08
bmCapabilities           : 0x00
wWidth                   : 0x0F00 (3840)
wHeight                  : 0x0870 (2160)
dwMinBitRate             : 0x58FD4000 (1492992000 bps -> 186.624 MB/s)
dwMaxBitRate             : 0xB1FA8000 (2985984000 bps -> 373.248 MB/s)
dwMaxVideoFrameBufferSize: 0x00BDD800 (12441600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 08 00 00 0F 70 08 00 40 FD 58 00 80 FA   &$.....p..@.X...
                           B1 00 D8 BD 00 15 16 05 00 03 15 16 05 00 20 A1   .............. .
                           07 00 2A 2C 0A 00                                 ..*,..

        ---- VS Frame Based Payload Format Type Descriptor ----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x10 (Frame Based Format Type)
bFormatIndex             : 0x02 (2)
bNumFrameDescriptors     : 0x08 (8)
guidFormat               : {34363248-0000-0010-8000-00AA00389B71} (H264)
bBitsPerPixel            : 0x10 (16 bits)
bDefaultFrameIndex       : 0x08 (8)
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
bVariableSize            : 0x01 (Variable Size)
*!*ERROR:  Found 16 frame descriptors (should be 8)
*!*ERROR:  no Color Matching Descriptor for this format
Data (HexDump)           : 1C 24 10 02 08 48 32 36 34 00 00 10 00 80 00 00   .$...H264.......
                           AA 00 38 9B 71 10 08 00 00 00 00 01               ..8.q.......

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x0278D000 (41472000 bps -> 5.184 MB/s)
dwMaxBitRate             : 0x04F1A000 (82944000 bps -> 10.368 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 01 00 80 02 68 01 00 D0 78 02 00 A0 F1   &$.....h...x....
                           04 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x034BC000 (55296000 bps -> 6.912 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 02 00 80 02 E0 01 00 C0 4B 03 00 80 97   &$.........K....
                           06 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x03C0 (960)
wHeight                  : 0x021C (540)
dwMinBitRate             : 0x058FD400 (93312000 bps -> 11.664 MB/s)
dwMaxBitRate             : 0x0B1FA800 (186624000 bps -> 23.328 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 03 00 C0 03 1C 02 00 D4 8F 05 00 A8 1F   &$..............
                           0B 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0400 (1024)
wHeight                  : 0x0240 (576)
dwMinBitRate             : 0x06540000 (106168320 bps -> 13.271 MB/s)
dwMaxBitRate             : 0x0CA80000 (212336640 bps -> 26.542 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 04 00 00 04 40 02 00 00 54 06 00 00 A8   &$.....@...T....
                           0C 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x09E34000 (165888000 bps -> 20.736 MB/s)
dwMaxBitRate             : 0x13C68000 (331776000 bps -> 41.472 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 05 00 00 05 D0 02 00 40 E3 09 00 80 C6   &$........@.....
                           13 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x163F5000 (373248000 bps -> 46.656 MB/s)
dwMaxBitRate             : 0x2C7EA000 (746496000 bps -> 93.312 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 06 00 80 07 38 04 00 50 3F 16 00 A0 7E   &$.....8..P?...~
                           2C 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ,.....,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x07
bmCapabilities           : 0x00
wWidth                   : 0x0A00 (2560)
wHeight                  : 0x05A0 (1440)
dwMinBitRate             : 0x278D0000 (663552000 bps -> 82.944 MB/s)
dwMaxBitRate             : 0x4F1A0000 (1327104000 bps -> 165.888 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 07 00 00 0A A0 05 00 00 8D 27 00 00 1A   &$..........'...
                           4F 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   O.....,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x08
bmCapabilities           : 0x00
wWidth                   : 0x0F00 (3840)
wHeight                  : 0x0870 (2160)
dwMinBitRate             : 0x58FD4000 (1492992000 bps -> 186.624 MB/s)
dwMaxBitRate             : 0xB1FA8000 (2985984000 bps -> 373.248 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 08 00 00 0F 70 08 00 40 FD 58 00 80 FA   &$.....p..@.X...
                           B1 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ---- VS Frame Based Payload Format Type Descriptor ----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x10 (Frame Based Format Type)
bFormatIndex             : 0x03 (3)
bNumFrameDescriptors     : 0x08 (8)
guidFormat               : {35363248-0000-0010-8000-00AA00389B71} (H265)
bBitsPerPixel            : 0x10 (16 bits)
bDefaultFrameIndex       : 0x08 (8)
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
bVariableSize            : 0x01 (Variable Size)
*!*ERROR:  no Color Matching Descriptor for this format
Data (HexDump)           : 1C 24 10 03 08 48 32 36 35 00 00 10 00 80 00 00   .$...H265.......
                           AA 00 38 9B 71 10 08 00 00 00 00 01               ..8.q.......

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x0278D000 (41472000 bps -> 5.184 MB/s)
dwMaxBitRate             : 0x04F1A000 (82944000 bps -> 10.368 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 01 00 80 02 68 01 00 D0 78 02 00 A0 F1   &$.....h...x....
                           04 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x034BC000 (55296000 bps -> 6.912 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 02 00 80 02 E0 01 00 C0 4B 03 00 80 97   &$.........K....
                           06 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x03C0 (960)
wHeight                  : 0x021C (540)
dwMinBitRate             : 0x058FD400 (93312000 bps -> 11.664 MB/s)
dwMaxBitRate             : 0x0B1FA800 (186624000 bps -> 23.328 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 03 00 C0 03 1C 02 00 D4 8F 05 00 A8 1F   &$..............
                           0B 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0400 (1024)
wHeight                  : 0x0240 (576)
dwMinBitRate             : 0x06540000 (106168320 bps -> 13.271 MB/s)
dwMaxBitRate             : 0x0CA80000 (212336640 bps -> 26.542 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 04 00 00 04 40 02 00 00 54 06 00 00 A8   &$.....@...T....
                           0C 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x09E34000 (165888000 bps -> 20.736 MB/s)
dwMaxBitRate             : 0x13C68000 (331776000 bps -> 41.472 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 05 00 00 05 D0 02 00 40 E3 09 00 80 C6   &$........@.....
                           13 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x163F5000 (373248000 bps -> 46.656 MB/s)
dwMaxBitRate             : 0x2C7EA000 (746496000 bps -> 93.312 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 06 00 80 07 38 04 00 50 3F 16 00 A0 7E   &$.....8..P?...~
                           2C 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ,.....,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x07
bmCapabilities           : 0x00
wWidth                   : 0x0A00 (2560)
wHeight                  : 0x05A0 (1440)
dwMinBitRate             : 0x278D0000 (663552000 bps -> 82.944 MB/s)
dwMaxBitRate             : 0x4F1A0000 (1327104000 bps -> 165.888 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 07 00 00 0A A0 05 00 00 8D 27 00 00 1A   &$..........'...
                           4F 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   O.....,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x08
bmCapabilities           : 0x00
wWidth                   : 0x0F00 (3840)
wHeight                  : 0x0870 (2160)
dwMinBitRate             : 0x58FD4000 (1492992000 bps -> 186.624 MB/s)
dwMaxBitRate             : 0xB1FA8000 (2985984000 bps -> 373.248 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0xA2C (2604 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 08 00 00 0F 70 08 00 40 FD 58 00 80 FA   &$.....p..@.X...
                           B1 15 16 05 00 03 2C 0A 00 00 15 16 05 00 20 A1   ......,....... .
                           07 00 2A 2C 0A 00                                 ..*,..

        ------- VS Uncompressed Format Type Descriptor --------
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x04 (Uncompressed Format Type)
bFormatIndex             : 0x04 (4)
bNumFrameDescriptors     : 0x06 (6)
guidFormat               : {32595559-0000-0010-8000-00AA00389B71} (YUY2)
bBitsPerPixel            : 0x10 (16 bits)
bDefaultFrameIndex       : 0x06 (6)
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
Data (HexDump)           : 1B 24 04 04 06 59 55 59 32 00 00 10 00 80 00 00   .$...YUY2.......
                           AA 00 38 9B 71 10 06 00 00 00 00                  ..8.q......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x034BC000 (55296000 bps -> 6.912 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxVideoFrameBufferSize: 0x00070800 (460800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 05 01 00 80 02 68 01 00 C0 4B 03 00 80 97   &$.....h...K....
                           06 00 08 07 00 15 16 05 00 03 15 16 05 00 20 A1   .............. .
                           07 00 2A 2C 0A 00                                 ..*,..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x04650000 (73728000 bps -> 9.216 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x00096000 (614400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 05 02 00 80 02 E0 01 00 00 65 04 00 00 CA   &$.........e....
                           08 00 60 09 00 15 16 05 00 03 15 16 05 00 20 A1   ..`........... .
                           07 00 2A 2C 0A 00                                 ..*,..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x03C0 (960)
wHeight                  : 0x021C (540)
dwMinBitRate             : 0x0278D000 (41472000 bps -> 5.184 MB/s)
dwMaxBitRate             : 0x076A7000 (124416000 bps -> 15.552 MB/s)
dwMaxVideoFrameBufferSize: 0x000FD200 (1036800 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[2]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[3]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 26 24 05 03 00 C0 03 1C 02 00 D0 78 02 00 70 6A   &$.........x..pj
                           07 00 D2 0F 00 2A 2C 0A 00 03 2A 2C 0A 00 40 42   .....*,...*,..@B
                           0F 00 80 84 1E 00                                 ......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0400 (1024)
wHeight                  : 0x0240 (576)
dwMinBitRate             : 0x02D00000 (47185920 bps -> 5.898 MB/s)
dwMaxBitRate             : 0x08700000 (141557760 bps -> 17.694 MB/s)
dwMaxVideoFrameBufferSize: 0x00120000 (1179648 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[2]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[3]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 26 24 05 04 00 00 04 40 02 00 00 D0 02 00 00 70   &$.....@.......p
                           08 00 00 12 00 2A 2C 0A 00 03 2A 2C 0A 00 40 42   .....*,...*,..@B
                           0F 00 80 84 1E 00                                 ......

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x01C20000 (29491200 bps -> 3.686 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x001C2000 (1843200 bytes)
dwDefaultFrameInterval   : 0x000F4240 (100.0000 ms -> 10.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[2]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
adwFrameInterval[3]      : 0x004C4B40 (500.0000 ms -> 2.000 fps)
Data (HexDump)           : 26 24 05 05 00 00 05 D0 02 00 00 C2 01 00 00 CA   &$..............
                           08 00 20 1C 00 40 42 0F 00 03 40 42 0F 00 80 84   .. ..@B...@B....
                           1E 00 40 4B 4C 00                                 ..@KL.

        -------- VS Uncompressed Frame Type Descriptor --------
---> This is the Default (optimum) Frame index
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x03F48000 (66355200 bps -> 8.294 MB/s)
dwMaxBitRate             : 0x09E34000 (165888000 bps -> 20.736 MB/s)
dwMaxVideoFrameBufferSize: 0x003F4800 (4147200 bytes)
dwDefaultFrameInterval   : 0x001E8480 (200.0000 ms -> 5.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
adwFrameInterval[2]      : 0x004C4B40 (500.0000 ms -> 2.000 fps)
Data (HexDump)           : 22 24 05 06 00 80 07 38 04 00 80 F4 03 00 40 E3   "$.....8......@.
                           09 00 48 3F 00 80 84 1E 00 02 80 84 1E 00 40 4B   ..H?..........@K
                           4C 00                                             L.

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
iInterface               : 0x0A (String Descriptor 10)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 09 04 01 01 01 0E 02 00 0A                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x85 (Direction=IN EndpointID=5)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0001
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x01 (1 byte per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 85 05 01 00 01                              .......

      -------------------- String Descriptors -------------------
none
*/

namespace elp_h265 {
const uint8_t dev_desc[] = {
    0x12, 0x01, 0x00, 0x02, 0xEF, 0x02, 0x01, 0x40, 0xE4, 0x32, 0x15, 0x94, 0x19, 0x04, 0x01, 0x02,
    0x03, 0x01
};
const uint8_t cfg_desc[] = {
    0x09, 0x02, 0xB0, 0x05, 0x02, 0x01, 0x04, 0x80, 0xFA, 0x08, 0x0B, 0x00, 0x02, 0x0E, 0x03, 0x00,
    0x05, 0x09, 0x04, 0x00, 0x00, 0x00, 0x0E, 0x01, 0x00, 0x08, 0x0D, 0x24, 0x01, 0x10, 0x01, 0x68,
    0x00, 0x00, 0x6C, 0xDC, 0x02, 0x01, 0x01, 0x12, 0x24, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0E, 0x22, 0x00, 0x0C, 0x24, 0x05, 0x02, 0x01, 0x00, 0x40,
    0x02, 0x7F, 0x17, 0x00, 0x00, 0x1A, 0x24, 0x06, 0x03, 0x18, 0x20, 0x2E, 0x30, 0x11, 0x63, 0x2E,
    0x4A, 0xBA, 0x2C, 0x68, 0x90, 0xEB, 0x33, 0x40, 0x16, 0x02, 0x01, 0x02, 0x01, 0x03, 0x06, 0x1A,
    0x24, 0x06, 0x04, 0xA4, 0xFB, 0xCB, 0x33, 0x26, 0xFD, 0xE4, 0x4C, 0x90, 0x76, 0xA1, 0x93, 0x1F,
    0xE7, 0x4C, 0x5E, 0x02, 0x01, 0x02, 0x01, 0x03, 0x07, 0x09, 0x24, 0x03, 0x04, 0x01, 0x01, 0x00,
    0x03, 0x00, 0x09, 0x04, 0x01, 0x00, 0x00, 0x0E, 0x02, 0x00, 0x09, 0x11, 0x24, 0x01, 0x04, 0xE5,
    0x04, 0x85, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x24, 0x06, 0x01,
    0x08, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x26, 0x24, 0x07, 0x01, 0x00, 0x80, 0x02, 0x68, 0x01,
    0x00, 0xD0, 0x78, 0x02, 0x00, 0xA0, 0xF1, 0x04, 0x00, 0x46, 0x05, 0x00, 0x15, 0x16, 0x05, 0x00,
    0x03, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x07,
    0x02, 0x00, 0x80, 0x02, 0xE0, 0x01, 0x00, 0xC0, 0x4B, 0x03, 0x00, 0x80, 0x97, 0x06, 0x00, 0x08,
    0x07, 0x00, 0x15, 0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A,
    0x2C, 0x0A, 0x00, 0x26, 0x24, 0x07, 0x03, 0x00, 0xC0, 0x03, 0x1C, 0x02, 0x00, 0xD4, 0x8F, 0x05,
    0x00, 0xA8, 0x1F, 0x0B, 0x80, 0xDD, 0x0B, 0x00, 0x15, 0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05,
    0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x07, 0x04, 0x00, 0x00, 0x04,
    0x40, 0x02, 0x00, 0x00, 0x54, 0x06, 0x00, 0x00, 0xA8, 0x0C, 0x00, 0x80, 0x0D, 0x00, 0x15, 0x16,
    0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26,
    0x24, 0x07, 0x05, 0x00, 0x00, 0x05, 0xD0, 0x02, 0x00, 0x40, 0xE3, 0x09, 0x00, 0x80, 0xC6, 0x13,
    0x00, 0x18, 0x15, 0x00, 0x15, 0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07,
    0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x07, 0x06, 0x00, 0x80, 0x07, 0x38, 0x04, 0x00, 0x50,
    0x3F, 0x16, 0x00, 0xA0, 0x7E, 0x2C, 0x00, 0x76, 0x2F, 0x00, 0x15, 0x16, 0x05, 0x00, 0x03, 0x15,
    0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x07, 0x07, 0x00,
    0x00, 0x0A, 0xA0, 0x05, 0x00, 0x00, 0x8D, 0x27, 0x00, 0x00, 0x1A, 0x4F, 0x00, 0x60, 0x54, 0x00,
    0x15, 0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A,
    0x00, 0x26, 0x24, 0x07, 0x08, 0x00, 0x00, 0x0F, 0x70, 0x08, 0x00, 0x40, 0xFD, 0x58, 0x00, 0x80,
    0xFA, 0xB1, 0x00, 0xD8, 0xBD, 0x00, 0x15, 0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x20,
    0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x1C, 0x24, 0x10, 0x02, 0x08, 0x48, 0x32, 0x36, 0x34,
    0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71, 0x10, 0x08, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x26, 0x24, 0x11, 0x01, 0x00, 0x80, 0x02, 0x68, 0x01, 0x00, 0xD0, 0x78, 0x02,
    0x00, 0xA0, 0xF1, 0x04, 0x15, 0x16, 0x05, 0x00, 0x03, 0x2C, 0x0A, 0x00, 0x00, 0x15, 0x16, 0x05,
    0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11, 0x02, 0x00, 0x80, 0x02,
    0xE0, 0x01, 0x00, 0xC0, 0x4B, 0x03, 0x00, 0x80, 0x97, 0x06, 0x15, 0x16, 0x05, 0x00, 0x03, 0x2C,
    0x0A, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26,
    0x24, 0x11, 0x03, 0x00, 0xC0, 0x03, 0x1C, 0x02, 0x00, 0xD4, 0x8F, 0x05, 0x00, 0xA8, 0x1F, 0x0B,
    0x15, 0x16, 0x05, 0x00, 0x03, 0x2C, 0x0A, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07,
    0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11, 0x04, 0x00, 0x00, 0x04, 0x40, 0x02, 0x00, 0x00,
    0x54, 0x06, 0x00, 0x00, 0xA8, 0x0C, 0x15, 0x16, 0x05, 0x00, 0x03, 0x2C, 0x0A, 0x00, 0x00, 0x15,
    0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11, 0x05, 0x00,
    0x00, 0x05, 0xD0, 0x02, 0x00, 0x40, 0xE3, 0x09, 0x00, 0x80, 0xC6, 0x13, 0x15, 0x16, 0x05, 0x00,
    0x03, 0x2C, 0x0A, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A,
    0x00, 0x26, 0x24, 0x11, 0x06, 0x00, 0x80, 0x07, 0x38, 0x04, 0x00, 0x50, 0x3F, 0x16, 0x00, 0xA0,
    0x7E, 0x2C, 0x15, 0x16, 0x05, 0x00, 0x03, 0x2C, 0x0A, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x20,
    0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11, 0x07, 0x00, 0x00, 0x0A, 0xA0, 0x05,
    0x00, 0x00, 0x8D, 0x27, 0x00, 0x00, 0x1A, 0x4F, 0x15, 0x16, 0x05, 0x00, 0x03, 0x2C, 0x0A, 0x00,
    0x00, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11,
    0x08, 0x00, 0x00, 0x0F, 0x70, 0x08, 0x00, 0x40, 0xFD, 0x58, 0x00, 0x80, 0xFA, 0xB1, 0x15, 0x16,
    0x05, 0x00, 0x03, 0x2C, 0x0A, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A,
    0x2C, 0x0A, 0x00, 0x1C, 0x24, 0x10, 0x03, 0x08, 0x48, 0x32, 0x36, 0x35, 0x00, 0x00, 0x10, 0x00,
    0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x01, 0x26,
    0x24, 0x11, 0x01, 0x00, 0x80, 0x02, 0x68, 0x01, 0x00, 0xD0, 0x78, 0x02, 0x00, 0xA0, 0xF1, 0x04,
    0x15, 0x16, 0x05, 0x00, 0x03, 0x2C, 0x0A, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07,
    0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11, 0x02, 0x00, 0x80, 0x02, 0xE0, 0x01, 0x00, 0xC0,
    0x4B, 0x03, 0x00, 0x80, 0x97, 0x06, 0x15, 0x16, 0x05, 0x00, 0x03, 0x2C, 0x0A, 0x00, 0x00, 0x15,
    0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11, 0x03, 0x00,
    0xC0, 0x03, 0x1C, 0x02, 0x00, 0xD4, 0x8F, 0x05, 0x00, 0xA8, 0x1F, 0x0B, 0x15, 0x16, 0x05, 0x00,
    0x03, 0x2C, 0x0A, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A,
    0x00, 0x26, 0x24, 0x11, 0x04, 0x00, 0x00, 0x04, 0x40, 0x02, 0x00, 0x00, 0x54, 0x06, 0x00, 0x00,
    0xA8, 0x0C, 0x15, 0x16, 0x05, 0x00, 0x03, 0x2C, 0x0A, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x20,
    0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11, 0x05, 0x00, 0x00, 0x05, 0xD0, 0x02,
    0x00, 0x40, 0xE3, 0x09, 0x00, 0x80, 0xC6, 0x13, 0x15, 0x16, 0x05, 0x00, 0x03, 0x2C, 0x0A, 0x00,
    0x00, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11,
    0x06, 0x00, 0x80, 0x07, 0x38, 0x04, 0x00, 0x50, 0x3F, 0x16, 0x00, 0xA0, 0x7E, 0x2C, 0x15, 0x16,
    0x05, 0x00, 0x03, 0x2C, 0x0A, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A,
    0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11, 0x07, 0x00, 0x00, 0x0A, 0xA0, 0x05, 0x00, 0x00, 0x8D, 0x27,
    0x00, 0x00, 0x1A, 0x4F, 0x15, 0x16, 0x05, 0x00, 0x03, 0x2C, 0x0A, 0x00, 0x00, 0x15, 0x16, 0x05,
    0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11, 0x08, 0x00, 0x00, 0x0F,
    0x70, 0x08, 0x00, 0x40, 0xFD, 0x58, 0x00, 0x80, 0xFA, 0xB1, 0x15, 0x16, 0x05, 0x00, 0x03, 0x2C,
    0x0A, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x1B,
    0x24, 0x04, 0x04, 0x06, 0x59, 0x55, 0x59, 0x32, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0xAA,
    0x00, 0x38, 0x9B, 0x71, 0x10, 0x06, 0x00, 0x00, 0x00, 0x00, 0x26, 0x24, 0x05, 0x01, 0x00, 0x80,
    0x02, 0x68, 0x01, 0x00, 0xC0, 0x4B, 0x03, 0x00, 0x80, 0x97, 0x06, 0x00, 0x08, 0x07, 0x00, 0x15,
    0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00,
    0x26, 0x24, 0x05, 0x02, 0x00, 0x80, 0x02, 0xE0, 0x01, 0x00, 0x00, 0x65, 0x04, 0x00, 0x00, 0xCA,
    0x08, 0x00, 0x60, 0x09, 0x00, 0x15, 0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x20, 0xA1,
    0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x05, 0x03, 0x00, 0xC0, 0x03, 0x1C, 0x02, 0x00,
    0xD0, 0x78, 0x02, 0x00, 0x70, 0x6A, 0x07, 0x00, 0xD2, 0x0F, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x03,
    0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x26, 0x24, 0x05, 0x04,
    0x00, 0x00, 0x04, 0x40, 0x02, 0x00, 0x00, 0xD0, 0x02, 0x00, 0x00, 0x70, 0x08, 0x00, 0x00, 0x12,
    0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x03, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84,
    0x1E, 0x00, 0x26, 0x24, 0x05, 0x05, 0x00, 0x00, 0x05, 0xD0, 0x02, 0x00, 0x00, 0xC2, 0x01, 0x00,
    0x00, 0xCA, 0x08, 0x00, 0x20, 0x1C, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x03, 0x40, 0x42, 0x0F, 0x00,
    0x80, 0x84, 0x1E, 0x00, 0x40, 0x4B, 0x4C, 0x00, 0x22, 0x24, 0x05, 0x06, 0x00, 0x80, 0x07, 0x38,
    0x04, 0x00, 0x80, 0xF4, 0x03, 0x00, 0x40, 0xE3, 0x09, 0x00, 0x48, 0x3F, 0x00, 0x80, 0x84, 0x1E,
    0x00, 0x02, 0x80, 0x84, 0x1E, 0x00, 0x40, 0x4B, 0x4C, 0x00, 0x06, 0x24, 0x0D, 0x01, 0x01, 0x04,
    0x09, 0x04, 0x01, 0x01, 0x01, 0x0E, 0x02, 0x00, 0x0A, 0x07, 0x05, 0x85, 0x05, 0x00, 0x02, 0x01,
    0x09, 0x04, 0x01, 0x02, 0x01, 0x0E, 0x02, 0x00, 0x0B, 0x07, 0x05, 0x85, 0x05, 0x00, 0x04, 0x01,
    0x09, 0x04, 0x01, 0x03, 0x01, 0x0E, 0x02, 0x00, 0x0C, 0x07, 0x05, 0x85, 0x05, 0x00, 0x0C, 0x01,
    0x09, 0x04, 0x01, 0x04, 0x01, 0x0E, 0x02, 0x00, 0x0D, 0x07, 0x05, 0x85, 0x05, 0x00, 0x14, 0x01
};
}
