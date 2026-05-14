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
Device ID                : USB\VID_2207&PID_0018\2D312FF4BB1927AF
Hardware IDs             : USB\VID_2207&PID_0018&REV_0310 USB\VID_2207&PID_0018
Driver KeyName           : {36fc9e60-c465-11cf-8056-444553540000}\0097 (GUID_DEVCLASS_USB)
Driver                   : \SystemRoot\System32\drivers\usbccgp.sys (Version: 10.0.19041.4355  Date: 2024-05-01)
Driver Inf               : C:\Windows\inf\usb.inf
Legacy BusType           : PNPBus
Class                    : USB
Class GUID               : {36fc9e60-c465-11cf-8056-444553540000} (GUID_DEVCLASS_USB)
Service                  : usbccgp
Enumerator               : USB
Location Info            : Port_#0002.Hub_#0012
Location IDs             : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(4)#USB(2), ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(4)#USB(2)
Container ID             : {c04c3c33-9149-5d5b-8d47-79610abb2768}
Manufacturer Info        : (Standard USB Host Controller)
Capabilities             : 0x94 (Removable, UniqueID, SurpriseRemovalOK)
Status                   : 0x0180600A (DN_DRIVER_LOADED, DN_STARTED, DN_DISABLEABLE, DN_REMOVABLE, DN_NT_ENUMERATOR, DN_NT_DRIVER)
Problem Code             : 0
Address                  : 2
HcDisableSelectiveSuspend: 0
EnableSelectiveSuspend   : 0
SelectiveSuspendEnabled  : 0
EnhancedPowerMgmtEnabled : 0
IdleInWorkingState       : 0
WakeFromSleepState       : 0
Power State              : D0 (supported: D0, D3, wake from D0)
 Child Device 1          : KAADAS MJPG Carmera
 (USB Video Device)
  Device Path            : \\?\USB#VID_2207&PID_0018&MI_00#a&32306b0d&0&0000#{e5323777-f976-4f5b-9b55-b94699c46e44}\global (STATIC_KSCATEGORY_VIDEO_CAMERA)
  Kernel Name            : \Device\000001d3
  Device ID              : USB\VID_2207&PID_0018&MI_00\A&32306B0D&0&0000
  Class                  : Camera
  Driver KeyName         : {ca3e7ab9-b4c3-4ae6-8251-579ef933890f}\0008 (GUID_DEVCLASS_CAMERA)
  Service                : usbvideo
  Location               : 0005.0000.0004.001.003.004.002.000.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(4)#USB(2)#USBMI(0)  PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(4)#USB(2)#USB(2)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(4)#USB(2)#USBMI(0)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(4)#USB(2)#USB(2)
 Child Device 2          : KAADAS Video Carmera
 (USB Video Device)
  Device Path            : \\?\USB#VID_2207&PID_0018&MI_02#a&32306b0d&0&0002#{6994ad05-93ef-11d0-a3cc-00a0c9223196}\global (AM_KSCATEGORY_VIDEO)
  Kernel Name            : \Device\000001d4
  Device ID              : USB\VID_2207&PID_0018&MI_02\A&32306B0D&0&0002
  Class                  : Camera
  Driver KeyName         : {ca3e7ab9-b4c3-4ae6-8251-579ef933890f}\0009 (GUID_DEVCLASS_CAMERA)
  Service                : usbvideo
  Location               : 0005.0000.0004.001.003.004.002.000.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(4)#USB(2)#USBMI(2)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(4)#USB(2)#USBMI(2)
 Child Device 3          : USB Serial Device
  Device Path            : \\?\USB#VID_2207&PID_0018&MI_04#a&32306b0d&0&0004#{86e0d1e0-8089-11d0-9ce4-08003e301f73} (GUID_DEVINTERFACE_COMPORT)
  Kernel Name            : \Device\000001d5
  Device ID              : USB\VID_2207&PID_0018&MI_04\A&32306B0D&0&0004
  Class                  : Ports
  Driver KeyName         : {4d36e978-e325-11ce-bfc1-08002be10318}\0007 (GUID_DEVCLASS_PORTS)
  Service                : usbser
  Location               : 0005.0000.0004.001.003.004.002.000.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(4)#USB(2)#USBMI(4)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(4)#USB(2)#USBMI(4)
  COM-Port               : COM12 (\Device\USBSER000)
 Child Device 4          : Source/Sink (USB Audio Device)
  Device Path            : \\?\USB#VID_2207&PID_0018&MI_06#a&32306b0d&0&0006#{6994ad04-93ef-11d0-a3cc-00a0c9223196}\global (AM_KSCATEGORY_AUDIO)
  Kernel Name            : \Device\000001d6
  Device ID              : USB\VID_2207&PID_0018&MI_06\A&32306B0D&0&0006
  Class                  : MEDIA
  Driver KeyName         : {4d36e96c-e325-11ce-bfc1-08002be10318}\0013 (GUID_DEVCLASS_MEDIA)
  Service                : usbaudio
  Location               : 0005.0000.0004.001.003.004.002.000.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(4)#USB(2)#USBMI(6)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(4)#USB(2)#USBMI(6)
   Child Device 1        : Speakers (Source/Sink) (Audio Endpoint)
    Device ID            : SWD\MMDEVAPI\{0.0.0.00000000}.{FB9EA8ED-5B90-4156-8500-5E012F8687F3}
    Class                : AudioEndpoint
    Driver KeyName       : {c166523c-fe0c-4a94-a586-f1a80cfbbf3e}\0043 (AUDIOENDPOINT_CLASS_UUID)
   Child Device 2        : Capture Input terminal (Source/Sink) (Audio Endpoint)
    Device ID            : SWD\MMDEVAPI\{0.0.1.00000000}.{2EA6231B-3575-483A-81F1-06E3D25AEFFB}
    Class                : AudioEndpoint
    Driver KeyName       : {c166523c-fe0c-4a94-a586-f1a80cfbbf3e}\0040 (AUDIOENDPOINT_CLASS_UUID)

        +++++++++++++++++ Registry USB Flags +++++++++++++++++
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\usbflags\220700180310
 osvc                    : REG_BINARY 00 00

        ---------------- Connection Information ---------------
Connection Index         : 0x02 (Port 2)
Connection Status        : 0x01 (DeviceConnected)
Current Config Value     : 0x01 (Configuration 1)
Device Address           : 0x09 (9)
Is Hub                   : 0x00 (no)
Device Bus Speed         : 0x02 (High-Speed)
Number Of Open Pipes     : 0x06 (6 pipes to data endpoints)
Pipe[0]                  : EndpointID=1  Direction=IN   ScheduleOffset=0  Type=Interrupt
Pipe[1]                  : EndpointID=3  Direction=IN   ScheduleOffset=0  Type=Interrupt
Pipe[2]                  : EndpointID=6  Direction=IN   ScheduleOffset=0  Type=Interrupt
Pipe[3]                  : EndpointID=5  Direction=IN   ScheduleOffset=0  Type=Bulk
Pipe[4]                  : EndpointID=1  Direction=OUT  ScheduleOffset=0  Type=Bulk
Pipe[5]                  : EndpointID=7  Direction=IN   ScheduleOffset=0  Type=Interrupt
Data (HexDump)           : 02 00 00 00 12 01 00 02 EF 02 01 40 07 22 18 00   ...........@."..
                           10 03 01 02 03 01 01 02 00 09 00 06 00 00 00 01   ................
                           00 00 00 07 05 81 03 10 00 08 00 00 00 00 07 05   ................
                           83 03 10 00 08 00 00 00 00 07 05 86 03 0A 00 09   ................
                           00 00 00 00 07 05 85 02 00 02 00 00 00 00 00 07   ................
                           05 01 02 00 02 00 00 00 00 00 07 05 87 03 02 00   ................
                           04 00 00 00 00                                    .....

        --------------- Connection Information V2 -------------
Connection Index         : 0x02 (2)
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
Data (HexDump)           : 02 00 00 00 10 00 00 00 03 00 00 00 00 00 00 00   ................

    ---------------------- Device Descriptor ----------------------
bLength                  : 0x12 (18 bytes)
bDescriptorType          : 0x01 (Device Descriptor)
bcdUSB                   : 0x200 (USB Version 2.00)
bDeviceClass             : 0xEF (Miscellaneous)
bDeviceSubClass          : 0x02
bDeviceProtocol          : 0x01 (IAD - Interface Association Descriptor)
bMaxPacketSize0          : 0x40 (64 bytes)
idVendor                 : 0x2207 (Rockchip Electronics Co., Ltd.)
idProduct                : 0x0018
bcdDevice                : 0x0310
iManufacturer            : 0x01 (String Descriptor 1)
 Language 0x0409         : "rockchip"
iProduct                 : 0x02 (String Descriptor 2)
 Language 0x0409         : "UVC"
iSerialNumber            : 0x03 (String Descriptor 3)
 Language 0x0409         : "2d312ff4bb1927af"
bNumConfigurations       : 0x01 (1 Configuration)
Data (HexDump)           : 12 01 00 02 EF 02 01 40 07 22 18 00 10 03 01 02   .......@."......
                           03 01                                             ..

    ------------------ Configuration Descriptor -------------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x02 (Configuration Descriptor)
wTotalLength             : 0x037A (890 bytes)
bNumInterfaces           : 0x09 (9 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x04 (String Descriptor 4)
 Language 0x0409         : "uvc_uac1"
bmAttributes             : 0x80
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x00 (no)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0xFA (500 mA)
Data (HexDump)           : 09 02 7A 03 09 01 04 80 FA 08 0B 00 02 0E 03 00   ..z.............
                           05 09 04 00 00 01 0E 01 00 05 0D 24 01 00 01 4E   ...........$...N
                           00 00 6C DC 02 01 01 12 24 02 01 01 02 00 00 00   ..l.....$.......
                           00 00 00 00 00 03 02 00 00 0C 24 05 02 01 00 40   ..........$....@
                           02 01 00 00 00 09 24 03 03 01 01 00 02 00 1A 24   ......$........$
                           06 06 A2 9E 76 41 DE 04 47 E3 8B 2B F4 34 1A FF   ....vA..G..+.4..
                           00 3B 03 01 02 01 07 00 07 05 81 03 10 00 08 05   .;..............
                           25 03 10 00 09 04 01 00 00 0E 02 00 06 0E 24 01   %.............$.
                           01 49 00 82 00 03 00 00 00 01 00 0B 24 06 01 01   .I..........$...
                           00 01 00 00 00 00 2A 24 07 01 00 D0 02 00 05 00   ......*$........
                           40 19 01 00 40 19 01 00 20 1C 00 15 16 05 00 04   @...@... .......
                           15 16 05 00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00   ....*,..@B......
                           06 24 0D 01 01 04 09 04 01 01 01 0E 02 00 06 07   .$..............
                           05 82 05 00 0C 01 08 0B 02 02 0E 03 00 08 09 04   ................
                           02 00 01 0E 01 00 08 0D 24 01 00 01 4E 00 00 6C   ........$...N..l
                           DC 02 01 03 12 24 02 01 01 02 00 00 00 00 00 00   .....$..........
                           00 00 03 02 00 00 0C 24 05 02 01 00 40 02 01 00   .......$....@...
                           00 00 09 24 03 03 01 01 00 02 00 1A 24 06 06 A2   ...$........$...
                           9E 76 41 DE 04 47 E3 8B 2B F4 34 1A FF 00 3B 03   .vA..G..+.4...;.
                           01 02 01 07 00 07 05 83 03 10 00 08 05 25 03 10   .............%..
                           00 09 04 03 00 00 0E 02 00 09 0E 24 01 01 02 01   ...........$....
                           84 00 03 00 00 00 01 00 1C 24 10 01 05 48 32 36   .........$...H26
                           35 00 00 10 00 80 00 00 AA 00 38 9B 71 10 01 00   5.........8.q...
                           00 00 00 01 2A 24 11 01 00 80 02 E0 01 00 E0 2E   ....*$..........
                           00 00 E0 2E 00 2A 2C 0A 00 04 00 00 00 00 15 16   .....*,.........
                           05 00 80 1A 06 00 20 A1 07 00 2A 2C 0A 00 2A 24   ...... ...*,..*$
                           11 02 00 00 05 D0 02 00 A0 8C 00 00 A0 8C 00 2A   ...............*
                           2C 0A 00 04 00 00 00 00 15 16 05 00 80 1A 06 00   ,...............
                           20 A1 07 00 2A 2C 0A 00 2A 24 11 03 00 80 07 38    ...*,..*$.....8
                           04 00 68 3C 01 00 68 3C 01 2A 2C 0A 00 04 00 00   ..h<..h<.*,.....
                           00 00 15 16 05 00 80 1A 06 00 20 A1 07 00 2A 2C   .......... ...*,
                           0A 00 2A 24 11 04 00 00 0A A0 05 00 80 32 02 00   ..*$.........2..
                           80 32 02 2A 2C 0A 00 04 00 00 00 00 15 16 05 00   .2.*,...........
                           80 1A 06 00 20 A1 07 00 2A 2C 0A 00 2A 24 11 05   .... ...*,..*$..
                           00 00 09 10 05 00 A0 C7 01 00 A0 C7 01 2A 2C 0A   .............*,.
                           00 04 00 00 00 00 15 16 05 00 80 1A 06 00 20 A1   .............. .
                           07 00 2A 2C 0A 00 06 24 0D 01 01 04 09 04 03 01   ..*,...$........
                           01 0E 02 00 09 07 05 84 05 00 0C 01 08 0B 04 02   ................
                           02 02 01 0D 09 04 04 00 01 02 02 01 0B 05 24 00   ..............$.
                           10 01 05 24 01 00 05 04 24 02 02 05 24 06 04 05   ...$....$...$...
                           07 05 86 03 0A 00 09 09 04 05 00 02 0A 00 00 0C   ................
                           07 05 85 02 00 02 00 07 05 01 02 00 02 00 08 0B   ................
                           06 03 01 02 00 0F 09 04 06 00 01 01 01 00 10 0A   ................
                           24 01 00 01 4A 00 02 07 08 0C 24 02 01 01 01 00   $...J.....$.....
                           01 01 00 12 11 09 24 03 03 01 03 00 05 13 0B 24   ......$........$
                           06 05 01 02 03 00 00 00 18 0C 24 02 02 01 02 00   ..........$.....
                           01 01 00 15 14 09 24 03 04 01 01 00 06 16 0B 24   ......$........$
                           06 06 02 02 03 00 00 00 17 07 05 87 03 02 00 04   ................
                           09 04 07 00 00 01 02 00 19 09 04 07 01 01 01 02   ................
                           00 1A 07 24 01 01 01 01 00 14 24 02 01 01 02 10   ...$......$.....
                           04 40 1F 00 80 3E 00 44 AC 00 80 BB 00 09 05 02   .@...>.D........
                           09 62 00 04 00 00 07 25 01 01 01 01 00 09 04 08   .b.....%........
                           00 00 01 02 00 1B 09 04 08 01 01 01 02 00 1C 07   ................
                           24 01 04 01 01 00 14 24 02 01 01 02 10 04 40 1F   $......$......@.
                           00 80 3E 00 44 AC 00 80 BB 00 09 05 88 05 62 00   ..>.D.........b.
                           04 00 00 07 25 01 01 00 00 00                     ....%.....

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x00
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x05 (String Descriptor 5)
 Language 0x0409         : "KAADAS MJPG Carmera¶"
Data (HexDump)           : 08 0B 00 02 0E 03 00 05                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x00
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x05 (String Descriptor 5)
 Language 0x0409         : "KAADAS MJPG Carmera¶"
Data (HexDump)           : 09 04 00 00 01 0E 01 00 05                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0100 (UVC Version 1.00)
wTotalLength             : 0x004E (78 bytes)
dwClockFreq              : 0x02DC6C00 (48 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x01
Data (HexDump)           : 0D 24 01 00 01 4E 00 00 6C DC 02 01 01            .$...N..l....

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
bmControls               : 0x02, 0x00, 0x00
 D0                      : 0   no -  Scanning Mode
 D1                      : 1  yes -  Auto-Exposure Mode
 D2                      : 0   no -  Auto-Exposure Priority
 D3                      : 0   no -  Exposure Time (Absolute)
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
Data (HexDump)           : 12 24 02 01 01 02 00 00 00 00 00 00 00 00 03 02   .$..............
                           00 00                                             ..

        -------- Video Control Processing Unit Descriptor -----
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x05 (Processing Unit)
bUnitID                  : 0x02
bSourceID                : 0x01
wMaxMultiplier           : 0x4000 (163.84x Zoom)
bControlSize             : 0x02
bmControls               : 0x01, 0x00
 D0                      : 1  yes -  Brightness
 D1                      : 0   no -  Contrast
 D2                      : 0   no -  Hue
 D3                      : 0   no -  Saturation
 D4                      : 0   no -  Sharpness
 D5                      : 0   no -  Gamma
 D6                      : 0   no -  White Balance Temperature
 D7                      : 0   no -  White Balance Component
 D8                      : 0   no -  Backlight Compensation
 D9                      : 0   no -  Gain
 D10                     : 0   no -  Power Line Frequency
 D11                     : 0   no -  Hue, Auto
 D12                     : 0   no -  White Balance Temperature, Auto
 D13                     : 0   no -  White Balance Component, Auto
 D14                     : 0   no -  Digital Multiplier
 D15                     : 0   no -  Digital Multiplier Limit
iProcessing              : 0x00
*!*ERROR:  bLength of 0x0C incorrect, should be 0x0B
Data (HexDump)           : 0C 24 05 02 01 00 40 02 01 00 00 00               .$....@.....

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x03
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x02
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 03 01 01 00 02 00                        .$.......

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x06
guidExtensionCode        : {41769EA2-04DE-E347-8B2B-F4341AFF003B}
bNumControls             : 0x03
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x01
bmControls               : 0x07
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 1  yes -  Vendor-Specific (Optional)
 D3                      : 0   no -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1A 24 06 06 A2 9E 76 41 DE 04 47 E3 8B 2B F4 34   .$....vA..G..+.4
                           1A FF 00 3B 03 01 02 01 07 00                     ...;......

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0010
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x10 (16 bytes per packet)
bInterval                : 0x08 (8 ms)
Data (HexDump)           : 07 05 81 03 10 00 08                              .......

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
iInterface               : 0x06 (String Descriptor 6)
 Language 0x0409         : "Video Streaming"
Data (HexDump)           : 09 04 01 00 00 0E 02 00 06                        .........

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x0E (14 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x01
wTotalLength             : 0x0049 (73 bytes)
bEndpointAddress         : 0x82 (Direction=IN  EndpointID=2)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x03
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
Data (HexDump)           : 0E 24 01 01 49 00 82 00 03 00 00 00 01 00         .$..I.........

        ----- Video Streaming MJPEG Format Type Descriptor ----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x06 (Format MJPEG)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x01 (1)
bmFlags                  : 0x00 (Sample size is not fixed)
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
Data (HexDump)           : 0B 24 06 01 01 00 01 00 00 00 00                  .$.........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
---> This is the Default (optimum) Frame index
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x02D0 (720)
wHeight                  : 0x0500 (1280)
dwMinBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxVideoFrameBufferSize: 0x001C2000 (1843200 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[3]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[4]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 2A 24 07 01 00 D0 02 00 05 00 40 19 01 00 40 19   *$........@...@.
                           01 00 20 1C 00 15 16 05 00 04 15 16 05 00 2A 2C   .. ...........*,
                           0A 00 40 42 0F 00 80 84 1E 00                     ..@B......

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
iInterface               : 0x06 (String Descriptor 6)
 Language 0x0409         : "Video Streaming"
Data (HexDump)           : 09 04 01 01 01 0E 02 00 06                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x82 (Direction=IN EndpointID=2)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0C00
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x01 (1 additional transactions per microframe -> allows 513..1024 byte per packet)
 Bits 10..0              : 0x400 (1024 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 82 05 00 0C 01                              .......

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x02
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x08 (String Descriptor 8)
 Language 0x0409         : "KAADAS Video Carmera¶"
Data (HexDump)           : 08 0B 02 02 0E 03 00 08                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x08 (String Descriptor 8)
 Language 0x0409         : "KAADAS Video Carmera¶"
Data (HexDump)           : 09 04 02 00 01 0E 01 00 08                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0100 (UVC Version 1.00)
wTotalLength             : 0x004E (78 bytes)
dwClockFreq              : 0x02DC6C00 (48 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x03
Data (HexDump)           : 0D 24 01 00 01 4E 00 00 6C DC 02 01 03            .$...N..l....

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
bmControls               : 0x02, 0x00, 0x00
 D0                      : 0   no -  Scanning Mode
 D1                      : 1  yes -  Auto-Exposure Mode
 D2                      : 0   no -  Auto-Exposure Priority
 D3                      : 0   no -  Exposure Time (Absolute)
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
Data (HexDump)           : 12 24 02 01 01 02 00 00 00 00 00 00 00 00 03 02   .$..............
                           00 00                                             ..

        -------- Video Control Processing Unit Descriptor -----
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x05 (Processing Unit)
bUnitID                  : 0x02
bSourceID                : 0x01
wMaxMultiplier           : 0x4000 (163.84x Zoom)
bControlSize             : 0x02
bmControls               : 0x01, 0x00
 D0                      : 1  yes -  Brightness
 D1                      : 0   no -  Contrast
 D2                      : 0   no -  Hue
 D3                      : 0   no -  Saturation
 D4                      : 0   no -  Sharpness
 D5                      : 0   no -  Gamma
 D6                      : 0   no -  White Balance Temperature
 D7                      : 0   no -  White Balance Component
 D8                      : 0   no -  Backlight Compensation
 D9                      : 0   no -  Gain
 D10                     : 0   no -  Power Line Frequency
 D11                     : 0   no -  Hue, Auto
 D12                     : 0   no -  White Balance Temperature, Auto
 D13                     : 0   no -  White Balance Component, Auto
 D14                     : 0   no -  Digital Multiplier
 D15                     : 0   no -  Digital Multiplier Limit
iProcessing              : 0x00
*!*ERROR:  bLength of 0x0C incorrect, should be 0x0B
Data (HexDump)           : 0C 24 05 02 01 00 40 02 01 00 00 00               .$....@.....

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x03
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x02
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 03 01 01 00 02 00                        .$.......

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x06
guidExtensionCode        : {41769EA2-04DE-E347-8B2B-F4341AFF003B}
bNumControls             : 0x03
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x01
bmControls               : 0x07
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 1  yes -  Vendor-Specific (Optional)
 D3                      : 0   no -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1A 24 06 06 A2 9E 76 41 DE 04 47 E3 8B 2B F4 34   .$....vA..G..+.4
                           1A FF 00 3B 03 01 02 01 07 00                     ...;......

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x83 (Direction=IN EndpointID=3)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0010
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x10 (16 bytes per packet)
bInterval                : 0x08 (8 ms)
Data (HexDump)           : 07 05 83 03 10 00 08                              .......

        --- Class-specific VC Interrupt Endpoint Descriptor ---
bLength                  : 0x05 (5 bytes)
bDescriptorType          : 0x25 (Video Control Endpoint)
bDescriptorSubtype       : 0x03 (Interrupt)
wMaxTransferSize         : 0x0010 (16 bytes)
Data (HexDump)           : 05 25 03 10 00                                    .%...

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x09 (String Descriptor 9)
 Language 0x0409         : "Video Streaming"
Data (HexDump)           : 09 04 03 00 00 0E 02 00 09                        .........

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x0E (14 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x01
wTotalLength             : 0x0102 (258 bytes)
bEndpointAddress         : 0x84 (Direction=IN  EndpointID=4)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x03
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
Data (HexDump)           : 0E 24 01 01 02 01 84 00 03 00 00 00 01 00         .$............

        ---- VS Frame Based Payload Format Type Descriptor ----
*!*ERROR: This format is NOT ALLOWED for UVC 1.0 devices
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x10 (Frame Based Format Type)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x05 (5)
guidFormat               : {35363248-0000-0010-8000-00AA00389B71} (H265)
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
bVariableSize            : 0x01 (Variable Size)
Data (HexDump)           : 1C 24 10 01 05 48 32 36 35 00 00 10 00 80 00 00   .$...H265.......
                           AA 00 38 9B 71 10 01 00 00 00 00 01               ..8.q.......

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x002EE000 (3072000 bps -> 384 KB/s)
dwMaxBitRate             : 0x002EE000 (3072000 bps -> 384 KB/s)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 2A 24 11 01 00 80 02 E0 01 00 E0 2E 00 00 E0 2E   *$..............
                           00 2A 2C 0A 00 04 00 00 00 00 15 16 05 00 80 1A   .*,.............
                           06 00 20 A1 07 00 2A 2C 0A 00                     .. ...*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x008CA000 (9216000 bps -> 1.152 MB/s)
dwMaxBitRate             : 0x008CA000 (9216000 bps -> 1.152 MB/s)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 2A 24 11 02 00 00 05 D0 02 00 A0 8C 00 00 A0 8C   *$..............
                           00 2A 2C 0A 00 04 00 00 00 00 15 16 05 00 80 1A   .*,.............
                           06 00 20 A1 07 00 2A 2C 0A 00                     .. ...*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x013C6800 (20736000 bps -> 2.592 MB/s)
dwMaxBitRate             : 0x013C6800 (20736000 bps -> 2.592 MB/s)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 2A 24 11 03 00 80 07 38 04 00 68 3C 01 00 68 3C   *$.....8..h<..h<
                           01 2A 2C 0A 00 04 00 00 00 00 15 16 05 00 80 1A   .*,.............
                           06 00 20 A1 07 00 2A 2C 0A 00                     .. ...*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0A00 (2560)
wHeight                  : 0x05A0 (1440)
dwMinBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwMaxBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 2A 24 11 04 00 00 0A A0 05 00 80 32 02 00 80 32   *$.........2...2
                           02 2A 2C 0A 00 04 00 00 00 00 15 16 05 00 80 1A   .*,.............
                           06 00 20 A1 07 00 2A 2C 0A 00                     .. ...*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0900 (2304)
wHeight                  : 0x0510 (1296)
dwMinBitRate             : 0x01C7A000 (29859840 bps -> 3.732 MB/s)
dwMaxBitRate             : 0x01C7A000 (29859840 bps -> 3.732 MB/s)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 2A 24 11 05 00 00 09 10 05 00 A0 C7 01 00 A0 C7   *$..............
                           01 2A 2C 0A 00 04 00 00 00 00 15 16 05 00 80 1A   .*,.............
                           06 00 20 A1 07 00 2A 2C 0A 00                     .. ...*,..

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
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x01
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x09 (String Descriptor 9)
 Language 0x0409         : "Video Streaming"
Data (HexDump)           : 09 04 03 01 01 0E 02 00 09                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x84 (Direction=IN EndpointID=4)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0C00
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x01 (1 additional transactions per microframe -> allows 513..1024 byte per packet)
 Bits 10..0              : 0x400 (1024 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 84 05 00 0C 01                              .......

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x04
bInterfaceCount          : 0x02
bFunctionClass           : 0x02 (Communications and CDC Control)
bFunctionSubClass        : 0x02
bFunctionProtocol        : 0x01
iFunction                : 0x0D (String Descriptor 13)
 Language 0x0409         : "CDC Serial"
Data (HexDump)           : 08 0B 04 02 02 02 01 0D                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x04
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x02 (Communications and CDC Control)
bInterfaceSubClass       : 0x02 (Abstract Control Model)
bInterfaceProtocol       : 0x01 (AT Commands defined by ITU-T V.250 etc)
iInterface               : 0x0B (String Descriptor 11)
 Language 0x0409         : "CDC Abstract Control Model (ACM)"
Data (HexDump)           : 09 04 04 00 01 02 02 01 0B                        .........

        -------------- CDC Interface Descriptor ---------------
bFunctionLength          : 0x05 (5 bytes)
bDescriptorType          : 0x24 (Interface)
bDescriptorSubType       : 0x00 (Header Functional Descriptor)
bcdCDC                   : 0x110 (CDC Version 1.10)
Data (HexDump)           : 05 24 00 10 01                                    .$...

        -------------- CDC Interface Descriptor ---------------
bFunctionLength          : 0x05 (5 bytes)
bDescriptorType          : 0x24 (Interface)
bDescriptorSubType       : 0x01 (Call Management Functional Descriptor)
bmCapabilities           : 0x00
 D7..2                   : 0x00 (Reserved)
 D1                      : 0x00 (sends/receives call management information only over the Communication Class interface)
 D0                      : 0x00 (does not handle call management itself)
bDataInterface           : 0x05
Data (HexDump)           : 05 24 01 00 05                                    .$...

        -------------- CDC Interface Descriptor ---------------
bFunctionLength          : 0x04 (4 bytes)
bDescriptorType          : 0x24 (Interface)
bDescriptorSubType       : 0x02 (Abstract Control Management Functional Descriptor)
bmCapabilities           : 0x02
 D7..4                   : 0x00 (Reserved)
 D3                      : 0x00 (not supports the notification Network_Connection)
 D2                      : 0x00 (not supports the request Send_Break)
 D1                      : 0x01 (supports the request combination of Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, and the notification Serial_State)
 D0                      : 0x00 (not supports the request combination of Set_Comm_Feature, Clear_Comm_Feature, and Get_Comm_Feature)
Data (HexDump)           : 04 24 02 02                                       .$..

        -------------- CDC Interface Descriptor ---------------
bFunctionLength          : 0x05 (5 bytes)
bDescriptorType          : 0x24 (Interface)
bDescriptorSubType       : 0x06 (Union Functional Descriptor)
bControlInterface        : 0x04
bSubordinateInterface[0] : 0x05
Data (HexDump)           : 05 24 06 04 05                                    .$...

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x86 (Direction=IN EndpointID=6)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x000A
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x0A (10 bytes per packet)
bInterval                : 0x09 (9 ms)
Data (HexDump)           : 07 05 86 03 0A 00 09                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x05
bAlternateSetting        : 0x00
bNumEndpoints            : 0x02 (2 Endpoints)
bInterfaceClass          : 0x0A (CDC-Data)
bInterfaceSubClass       : 0x00
bInterfaceProtocol       : 0x00
iInterface               : 0x0C (String Descriptor 12)
 Language 0x0409         : "CDC ACM Data"
Data (HexDump)           : 09 04 05 00 02 0A 00 00 0C                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x85 (Direction=IN EndpointID=5)
bmAttributes             : 0x02 (TransferType=Bulk)
wMaxPacketSize           : 0x0200 (max 512 bytes)
bInterval                : 0x00 (never NAKs)
Data (HexDump)           : 07 05 85 02 00 02 00                              .......

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x01 (Direction=OUT EndpointID=1)
bmAttributes             : 0x02 (TransferType=Bulk)
wMaxPacketSize           : 0x0200 (max 512 bytes)
bInterval                : 0x00 (never NAKs)
Data (HexDump)           : 07 05 01 02 00 02 00                              .......

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x06
bInterfaceCount          : 0x03
bFunctionClass           : 0x01 (Audio)
bFunctionSubClass        : 0x02 (Audio Streaming)
bFunctionProtocol        : 0x00
iFunction                : 0x0F (String Descriptor 15)
 Language 0x0409         : "Source/Sink"
Data (HexDump)           : 08 0B 06 03 01 02 00 0F                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x06
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x01 (Audio Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x10 (String Descriptor 16)
 Language 0x0409         : "AC Interface"
Data (HexDump)           : 09 04 06 00 01 01 01 00 10                        .........

        ------ Audio Control Interface Header Descriptor ------
bLength                  : 0x0A (10 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01 (Header)
bcdADC                   : 0x0100
wTotalLength             : 0x004A (74 bytes)
bInCollection            : 0x02
baInterfaceNr[1]         : 0x07
baInterfaceNr[2]         : 0x08
Data (HexDump)           : 0A 24 01 00 01 4A 00 02 07 08                     .$...J....

        ------- Audio Control Input Terminal Descriptor -------
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Input Terminal)
bTerminalID              : 0x01
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x00
bNrChannels              : 0x01 (1 channel)
wChannelConfig           : 0x0001 (L)
iChannelNames            : 0x12 (String Descriptor 18)
 Language 0x0409         : "Playback Channels"
iTerminal                : 0x11 (String Descriptor 17)
 Language 0x0409         : "Playback Input terminal"
Data (HexDump)           : 0C 24 02 01 01 01 00 01 01 00 12 11               .$..........

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x03
wTerminalType            : 0x0301 (Speaker)
bAssocTerminal           : 0x00 (0)
bSourceID                : 0x05 (5)
iTerminal                : 0x13 (String Descriptor 19)
 Language 0x0409         : "Playback Output terminal"
Data (HexDump)           : 09 24 03 03 01 03 00 05 13                        .$.......

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x06 (Feature Unit)
bUnitID                  : 0x05 (5)
bSourceID                : 0x01 (1)
bControlSize             : 0x02 (2 bytes per control)
bmaControls[0]           : 0x03, 0x00
 D0: Mute                : 1
 D1: Volume              : 1
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
 D8: Bass Boost          : 0
 D9: Loudness            : 0
 D10: Reserved           : 0
 D11: Reserved           : 0
 D12: Reserved           : 0
 D13: Reserved           : 0
 D14: Reserved           : 0
 D15: Reserved           : 0
bmaControls[1]           : 0x00, 0x00
 D0: Mute                : 0
 D1: Volume              : 0
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
 D8: Bass Boost          : 0
 D9: Loudness            : 0
 D10: Reserved           : 0
 D11: Reserved           : 0
 D12: Reserved           : 0
 D13: Reserved           : 0
 D14: Reserved           : 0
 D15: Reserved           : 0
iFeature                 : 0x18 (String Descriptor 24)
 Language 0x0409         : "Playback Volume"
Data (HexDump)           : 0B 24 06 05 01 02 03 00 00 00 18                  .$.........

        ------- Audio Control Input Terminal Descriptor -------
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Input Terminal)
bTerminalID              : 0x02
wTerminalType            : 0x0201 (Microphone)
bAssocTerminal           : 0x00
bNrChannels              : 0x01 (1 channel)
wChannelConfig           : 0x0001 (L)
iChannelNames            : 0x15 (String Descriptor 21)
 Language 0x0409         : "Capture Channels"
iTerminal                : 0x14 (String Descriptor 20)
 Language 0x0409         : "Capture Input terminal"
Data (HexDump)           : 0C 24 02 02 01 02 00 01 01 00 15 14               .$..........

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x04
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x00 (0)
bSourceID                : 0x06 (6)
iTerminal                : 0x16 (String Descriptor 22)
 Language 0x0409         : "Capture Output terminal"
Data (HexDump)           : 09 24 03 04 01 01 00 06 16                        .$.......

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x06 (Feature Unit)
bUnitID                  : 0x06 (6)
bSourceID                : 0x02 (2)
bControlSize             : 0x02 (2 bytes per control)
bmaControls[0]           : 0x03, 0x00
 D0: Mute                : 1
 D1: Volume              : 1
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
 D8: Bass Boost          : 0
 D9: Loudness            : 0
 D10: Reserved           : 0
 D11: Reserved           : 0
 D12: Reserved           : 0
 D13: Reserved           : 0
 D14: Reserved           : 0
 D15: Reserved           : 0
bmaControls[1]           : 0x00, 0x00
 D0: Mute                : 0
 D1: Volume              : 0
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
 D8: Bass Boost          : 0
 D9: Loudness            : 0
 D10: Reserved           : 0
 D11: Reserved           : 0
 D12: Reserved           : 0
 D13: Reserved           : 0
 D14: Reserved           : 0
 D15: Reserved           : 0
iFeature                 : 0x17 (String Descriptor 23)
 Language 0x0409         : "Capture Volume"
Data (HexDump)           : 0B 24 06 06 02 02 03 00 00 00 17                  .$.........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x87 (Direction=IN EndpointID=7)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0002
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x02 (2 bytes per packet)
bInterval                : 0x04 (4 ms)
Data (HexDump)           : 07 05 87 03 02 00 04                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x07
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x19 (String Descriptor 25)
 Language 0x0409         : "Playback Inactive"
Data (HexDump)           : 09 04 07 00 00 01 02 00 19                        .........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x07
bAlternateSetting        : 0x01
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x1A (String Descriptor 26)
 Language 0x0409         : "Playback Active"
Data (HexDump)           : 09 04 07 01 01 01 02 00 1A                        .........

        -------- Audio Streaming Interface Descriptor ---------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01
bTerminalLink            : 0x01
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 01 01 01 00                              .$.....

        ------- Audio Streaming Format Type Descriptor --------
bLength                  : 0x14 (20 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Format Type)
bFormatType              : 0x01 (FORMAT_TYPE_I)
bNrChannels              : 0x01 (1 channel)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x04 (supports 4 sample frequencies)
tSamFreq[1]              : 0x01F40 (8000 Hz)
tSamFreq[2]              : 0x03E80 (16000 Hz)
tSamFreq[3]              : 0x0AC44 (44100 Hz)
tSamFreq[4]              : 0x0BB80 (48000 Hz)
Data (HexDump)           : 14 24 02 01 01 02 10 04 40 1F 00 80 3E 00 44 AC   .$......@...>.D.
                           00 80 BB 00                                       ....

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x02 (Direction=OUT EndpointID=2)
bmAttributes             : 0x09 (TransferType=Isochronous  SyncType=Adaptive  EndpointType=Data)
wMaxPacketSize           : 0x0062
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x62 (98 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 02 09 62 00 04 00 00                        ....b....

        ----------- Audio Data Endpoint Descriptor ------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x25 (Audio Endpoint Descriptor)
bDescriptorSubtype       : 0x01 (General)
bmAttributes             : 0x01
 D0   : Sampling Freq    : 0x01 (supported)
 D1   : Pitch            : 0x00 (not supported)
 D6..2: Reserved         : 0x00
 D7   : MaxPacketsOnly   : 0x00 (no)
bLockDelayUnits          : 0x01 (Milliseconds)
wLockDelay               : 0x0001 (1 ms)
Data (HexDump)           : 07 25 01 01 01 01 00                              .%.....

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x08
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x1B (String Descriptor 27)
 Language 0x0409         : "Capture Inactive"
Data (HexDump)           : 09 04 08 00 00 01 02 00 1B                        .........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x08
bAlternateSetting        : 0x01
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x1C (String Descriptor 28)
 Language 0x0409         : "Capture Active"
Data (HexDump)           : 09 04 08 01 01 01 02 00 1C                        .........

        -------- Audio Streaming Interface Descriptor ---------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01
bTerminalLink            : 0x04
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 04 01 01 00                              .$.....

        ------- Audio Streaming Format Type Descriptor --------
bLength                  : 0x14 (20 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Format Type)
bFormatType              : 0x01 (FORMAT_TYPE_I)
bNrChannels              : 0x01 (1 channel)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x04 (supports 4 sample frequencies)
tSamFreq[1]              : 0x01F40 (8000 Hz)
tSamFreq[2]              : 0x03E80 (16000 Hz)
tSamFreq[3]              : 0x0AC44 (44100 Hz)
tSamFreq[4]              : 0x0BB80 (48000 Hz)
Data (HexDump)           : 14 24 02 01 01 02 10 04 40 1F 00 80 3E 00 44 AC   .$......@...>.D.
                           00 80 BB 00                                       ....

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x88 (Direction=IN EndpointID=8)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0062
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x62 (98 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 88 05 62 00 04 00 00                        ....b....

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
wTotalLength             : 0x037A (890 bytes)
bNumInterfaces           : 0x09 (9 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x04 (String Descriptor 4)
 Language 0x0409         : "uvc_uac1"
bmAttributes             : 0x80
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x00 (no)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0xFA (500 mA)
Data (HexDump)           : 09 07 7A 03 09 01 04 80 FA 08 0B 00 02 0E 03 00   ..z.............
                           05 09 04 00 00 01 0E 01 00 05 0D 24 01 00 01 4E   ...........$...N
                           00 00 6C DC 02 01 01 12 24 02 01 01 02 00 00 00   ..l.....$.......
                           00 00 00 00 00 03 02 00 00 0C 24 05 02 01 00 40   ..........$....@
                           02 01 00 00 00 09 24 03 03 01 01 00 02 00 1A 24   ......$........$
                           06 06 A2 9E 76 41 DE 04 47 E3 8B 2B F4 34 1A FF   ....vA..G..+.4..
                           00 3B 03 01 02 01 07 00 07 05 81 03 10 00 08 05   .;..............
                           25 03 10 00 09 04 01 00 00 0E 02 00 06 0E 24 01   %.............$.
                           01 49 00 82 00 03 00 00 00 01 00 0B 24 06 01 01   .I..........$...
                           00 01 00 00 00 00 2A 24 07 01 00 D0 02 00 05 00   ......*$........
                           40 19 01 00 40 19 01 00 20 1C 00 15 16 05 00 04   @...@... .......
                           15 16 05 00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00   ....*,..@B......
                           06 24 0D 01 01 04 09 04 01 01 01 0E 02 00 06 07   .$..............
                           05 82 05 FF 03 01 08 0B 02 02 0E 03 00 08 09 04   ................
                           02 00 01 0E 01 00 08 0D 24 01 00 01 4E 00 00 6C   ........$...N..l
                           DC 02 01 03 12 24 02 01 01 02 00 00 00 00 00 00   .....$..........
                           00 00 03 02 00 00 0C 24 05 02 01 00 40 02 01 00   .......$....@...
                           00 00 09 24 03 03 01 01 00 02 00 1A 24 06 06 A2   ...$........$...
                           9E 76 41 DE 04 47 E3 8B 2B F4 34 1A FF 00 3B 03   .vA..G..+.4...;.
                           01 02 01 07 00 07 05 83 03 10 00 08 05 25 03 10   .............%..
                           00 09 04 03 00 00 0E 02 00 09 0E 24 01 01 02 01   ...........$....
                           84 00 03 00 00 00 01 00 1C 24 10 01 05 48 32 36   .........$...H26
                           35 00 00 10 00 80 00 00 AA 00 38 9B 71 10 01 00   5.........8.q...
                           00 00 00 01 2A 24 11 01 00 80 02 E0 01 00 E0 2E   ....*$..........
                           00 00 E0 2E 00 2A 2C 0A 00 04 00 00 00 00 15 16   .....*,.........
                           05 00 80 1A 06 00 20 A1 07 00 2A 2C 0A 00 2A 24   ...... ...*,..*$
                           11 02 00 00 05 D0 02 00 A0 8C 00 00 A0 8C 00 2A   ...............*
                           2C 0A 00 04 00 00 00 00 15 16 05 00 80 1A 06 00   ,...............
                           20 A1 07 00 2A 2C 0A 00 2A 24 11 03 00 80 07 38    ...*,..*$.....8
                           04 00 68 3C 01 00 68 3C 01 2A 2C 0A 00 04 00 00   ..h<..h<.*,.....
                           00 00 15 16 05 00 80 1A 06 00 20 A1 07 00 2A 2C   .......... ...*,
                           0A 00 2A 24 11 04 00 00 0A A0 05 00 80 32 02 00   ..*$.........2..
                           80 32 02 2A 2C 0A 00 04 00 00 00 00 15 16 05 00   .2.*,...........
                           80 1A 06 00 20 A1 07 00 2A 2C 0A 00 2A 24 11 05   .... ...*,..*$..
                           00 00 09 10 05 00 A0 C7 01 00 A0 C7 01 2A 2C 0A   .............*,.
                           00 04 00 00 00 00 15 16 05 00 80 1A 06 00 20 A1   .............. .
                           07 00 2A 2C 0A 00 06 24 0D 01 01 04 09 04 03 01   ..*,...$........
                           01 0E 02 00 09 07 05 84 05 FF 03 01 08 0B 04 02   ................
                           02 02 01 0D 09 04 04 00 01 02 02 01 0B 05 24 00   ..............$.
                           10 01 05 24 01 00 05 04 24 02 02 05 24 06 04 05   ...$....$...$...
                           07 05 86 03 0A 00 20 09 04 05 00 02 0A 00 00 0C   ...... .........
                           07 05 85 02 40 00 00 07 05 01 02 40 00 00 08 0B   ....@......@....
                           06 03 01 02 00 0F 09 04 06 00 01 01 01 00 10 0A   ................
                           24 01 00 01 4A 00 02 07 08 0C 24 02 01 01 01 00   $...J.....$.....
                           01 01 00 12 11 09 24 03 03 01 03 00 05 13 0B 24   ......$........$
                           06 05 01 02 03 00 00 00 18 0C 24 02 02 01 02 00   ..........$.....
                           01 01 00 15 14 09 24 03 04 01 01 00 06 16 0B 24   ......$........$
                           06 06 02 02 03 00 00 00 17 07 05 87 03 02 00 01   ................
                           09 04 07 00 00 01 02 00 19 09 04 07 01 01 01 02   ................
                           00 1A 07 24 01 01 01 01 00 14 24 02 01 01 02 10   ...$......$.....
                           04 40 1F 00 80 3E 00 44 AC 00 80 BB 00 09 05 02   .@...>.D........
                           09 62 00 01 00 00 07 25 01 01 01 01 00 09 04 08   .b.....%........
                           00 00 01 02 00 1B 09 04 08 01 01 01 02 00 1C 07   ................
                           24 01 04 01 01 00 14 24 02 01 01 02 10 04 40 1F   $......$......@.
                           00 80 3E 00 44 AC 00 80 BB 00 09 05 88 05 62 00   ..>.D.........b.
                           01 00 00 07 25 01 01 00 00 00                     ....%.....

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x00
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x05 (String Descriptor 5)
 Language 0x0409         : "KAADAS MJPG Carmera¶"
Data (HexDump)           : 08 0B 00 02 0E 03 00 05                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x00
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x05 (String Descriptor 5)
 Language 0x0409         : "KAADAS MJPG Carmera¶"
Data (HexDump)           : 09 04 00 00 01 0E 01 00 05                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0100 (UVC Version 1.00)
wTotalLength             : 0x004E (78 bytes)
dwClockFreq              : 0x02DC6C00 (48 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x01
Data (HexDump)           : 0D 24 01 00 01 4E 00 00 6C DC 02 01 01            .$...N..l....

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
bmControls               : 0x02, 0x00, 0x00
 D0                      : 0   no -  Scanning Mode
 D1                      : 1  yes -  Auto-Exposure Mode
 D2                      : 0   no -  Auto-Exposure Priority
 D3                      : 0   no -  Exposure Time (Absolute)
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
Data (HexDump)           : 12 24 02 01 01 02 00 00 00 00 00 00 00 00 03 02   .$..............
                           00 00                                             ..

        -------- Video Control Processing Unit Descriptor -----
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x05 (Processing Unit)
bUnitID                  : 0x02
bSourceID                : 0x01
wMaxMultiplier           : 0x4000 (163.84x Zoom)
bControlSize             : 0x02
bmControls               : 0x01, 0x00
 D0                      : 1  yes -  Brightness
 D1                      : 0   no -  Contrast
 D2                      : 0   no -  Hue
 D3                      : 0   no -  Saturation
 D4                      : 0   no -  Sharpness
 D5                      : 0   no -  Gamma
 D6                      : 0   no -  White Balance Temperature
 D7                      : 0   no -  White Balance Component
 D8                      : 0   no -  Backlight Compensation
 D9                      : 0   no -  Gain
 D10                     : 0   no -  Power Line Frequency
 D11                     : 0   no -  Hue, Auto
 D12                     : 0   no -  White Balance Temperature, Auto
 D13                     : 0   no -  White Balance Component, Auto
 D14                     : 0   no -  Digital Multiplier
 D15                     : 0   no -  Digital Multiplier Limit
iProcessing              : 0x00
*!*ERROR:  bLength of 0x0C incorrect, should be 0x0B
Data (HexDump)           : 0C 24 05 02 01 00 40 02 01 00 00 00               .$....@.....

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x03
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x02
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 03 01 01 00 02 00                        .$.......

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x06
guidExtensionCode        : {41769EA2-04DE-E347-8B2B-F4341AFF003B}
bNumControls             : 0x03
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x01
bmControls               : 0x07
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 1  yes -  Vendor-Specific (Optional)
 D3                      : 0   no -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1A 24 06 06 A2 9E 76 41 DE 04 47 E3 8B 2B F4 34   .$....vA..G..+.4
                           1A FF 00 3B 03 01 02 01 07 00                     ...;......

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0010
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x10 (16 bytes per packet)
bInterval                : 0x08 (8 ms)
Data (HexDump)           : 07 05 81 03 10 00 08                              .......

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
iInterface               : 0x06 (String Descriptor 6)
 Language 0x0409         : "Video Streaming"
Data (HexDump)           : 09 04 01 00 00 0E 02 00 06                        .........

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x0E (14 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x01
wTotalLength             : 0x0049 (73 bytes)
bEndpointAddress         : 0x82 (Direction=IN  EndpointID=2)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x03
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
Data (HexDump)           : 0E 24 01 01 49 00 82 00 03 00 00 00 01 00         .$..I.........

        ----- Video Streaming MJPEG Format Type Descriptor ----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x06 (Format MJPEG)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x01 (1)
bmFlags                  : 0x00 (Sample size is not fixed)
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
Data (HexDump)           : 0B 24 06 01 01 00 01 00 00 00 00                  .$.........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
---> This is the Default (optimum) Frame index
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x02D0 (720)
wHeight                  : 0x0500 (1280)
dwMinBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxVideoFrameBufferSize: 0x001C2000 (1843200 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[3]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[4]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 2A 24 07 01 00 D0 02 00 05 00 40 19 01 00 40 19   *$........@...@.
                           01 00 20 1C 00 15 16 05 00 04 15 16 05 00 2A 2C   .. ...........*,
                           0A 00 40 42 0F 00 80 84 1E 00                     ..@B......

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
iInterface               : 0x06 (String Descriptor 6)
 Language 0x0409         : "Video Streaming"
Data (HexDump)           : 09 04 01 01 01 0E 02 00 06                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x82 (Direction=IN EndpointID=2)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x03FF
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x3FF (1023 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 82 05 FF 03 01                              .......

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x02
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x08 (String Descriptor 8)
 Language 0x0409         : "KAADAS Video Carmera¶"
Data (HexDump)           : 08 0B 02 02 0E 03 00 08                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x08 (String Descriptor 8)
 Language 0x0409         : "KAADAS Video Carmera¶"
Data (HexDump)           : 09 04 02 00 01 0E 01 00 08                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0100 (UVC Version 1.00)
wTotalLength             : 0x004E (78 bytes)
dwClockFreq              : 0x02DC6C00 (48 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x03
Data (HexDump)           : 0D 24 01 00 01 4E 00 00 6C DC 02 01 03            .$...N..l....

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
bmControls               : 0x02, 0x00, 0x00
 D0                      : 0   no -  Scanning Mode
 D1                      : 1  yes -  Auto-Exposure Mode
 D2                      : 0   no -  Auto-Exposure Priority
 D3                      : 0   no -  Exposure Time (Absolute)
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
Data (HexDump)           : 12 24 02 01 01 02 00 00 00 00 00 00 00 00 03 02   .$..............
                           00 00                                             ..

        -------- Video Control Processing Unit Descriptor -----
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x05 (Processing Unit)
bUnitID                  : 0x02
bSourceID                : 0x01
wMaxMultiplier           : 0x4000 (163.84x Zoom)
bControlSize             : 0x02
bmControls               : 0x01, 0x00
 D0                      : 1  yes -  Brightness
 D1                      : 0   no -  Contrast
 D2                      : 0   no -  Hue
 D3                      : 0   no -  Saturation
 D4                      : 0   no -  Sharpness
 D5                      : 0   no -  Gamma
 D6                      : 0   no -  White Balance Temperature
 D7                      : 0   no -  White Balance Component
 D8                      : 0   no -  Backlight Compensation
 D9                      : 0   no -  Gain
 D10                     : 0   no -  Power Line Frequency
 D11                     : 0   no -  Hue, Auto
 D12                     : 0   no -  White Balance Temperature, Auto
 D13                     : 0   no -  White Balance Component, Auto
 D14                     : 0   no -  Digital Multiplier
 D15                     : 0   no -  Digital Multiplier Limit
iProcessing              : 0x00
*!*ERROR:  bLength of 0x0C incorrect, should be 0x0B
Data (HexDump)           : 0C 24 05 02 01 00 40 02 01 00 00 00               .$....@.....

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x03
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x02
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 03 01 01 00 02 00                        .$.......

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x06
guidExtensionCode        : {41769EA2-04DE-E347-8B2B-F4341AFF003B}
bNumControls             : 0x03
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x01
bmControls               : 0x07
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 1  yes -  Vendor-Specific (Optional)
 D3                      : 0   no -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1A 24 06 06 A2 9E 76 41 DE 04 47 E3 8B 2B F4 34   .$....vA..G..+.4
                           1A FF 00 3B 03 01 02 01 07 00                     ...;......

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x83 (Direction=IN EndpointID=3)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0010
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x10 (16 bytes per packet)
bInterval                : 0x08 (8 ms)
Data (HexDump)           : 07 05 83 03 10 00 08                              .......

        --- Class-specific VC Interrupt Endpoint Descriptor ---
bLength                  : 0x05 (5 bytes)
bDescriptorType          : 0x25 (Video Control Endpoint)
bDescriptorSubtype       : 0x03 (Interrupt)
wMaxTransferSize         : 0x0010 (16 bytes)
Data (HexDump)           : 05 25 03 10 00                                    .%...

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x09 (String Descriptor 9)
 Language 0x0409         : "Video Streaming"
Data (HexDump)           : 09 04 03 00 00 0E 02 00 09                        .........

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x0E (14 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x01
wTotalLength             : 0x0102 (258 bytes)
bEndpointAddress         : 0x84 (Direction=IN  EndpointID=4)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x03
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
Data (HexDump)           : 0E 24 01 01 02 01 84 00 03 00 00 00 01 00         .$............

        ---- VS Frame Based Payload Format Type Descriptor ----
*!*ERROR: This format is NOT ALLOWED for UVC 1.0 devices
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x10 (Frame Based Format Type)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x05 (5)
guidFormat               : {35363248-0000-0010-8000-00AA00389B71} (H265)
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
bVariableSize            : 0x01 (Variable Size)
Data (HexDump)           : 1C 24 10 01 05 48 32 36 35 00 00 10 00 80 00 00   .$...H265.......
                           AA 00 38 9B 71 10 01 00 00 00 00 01               ..8.q.......

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x002EE000 (3072000 bps -> 384 KB/s)
dwMaxBitRate             : 0x002EE000 (3072000 bps -> 384 KB/s)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 2A 24 11 01 00 80 02 E0 01 00 E0 2E 00 00 E0 2E   *$..............
                           00 2A 2C 0A 00 04 00 00 00 00 15 16 05 00 80 1A   .*,.............
                           06 00 20 A1 07 00 2A 2C 0A 00                     .. ...*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x008CA000 (9216000 bps -> 1.152 MB/s)
dwMaxBitRate             : 0x008CA000 (9216000 bps -> 1.152 MB/s)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 2A 24 11 02 00 00 05 D0 02 00 A0 8C 00 00 A0 8C   *$..............
                           00 2A 2C 0A 00 04 00 00 00 00 15 16 05 00 80 1A   .*,.............
                           06 00 20 A1 07 00 2A 2C 0A 00                     .. ...*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x013C6800 (20736000 bps -> 2.592 MB/s)
dwMaxBitRate             : 0x013C6800 (20736000 bps -> 2.592 MB/s)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 2A 24 11 03 00 80 07 38 04 00 68 3C 01 00 68 3C   *$.....8..h<..h<
                           01 2A 2C 0A 00 04 00 00 00 00 15 16 05 00 80 1A   .*,.............
                           06 00 20 A1 07 00 2A 2C 0A 00                     .. ...*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0A00 (2560)
wHeight                  : 0x05A0 (1440)
dwMinBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwMaxBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 2A 24 11 04 00 00 0A A0 05 00 80 32 02 00 80 32   *$.........2...2
                           02 2A 2C 0A 00 04 00 00 00 00 15 16 05 00 80 1A   .*,.............
                           06 00 20 A1 07 00 2A 2C 0A 00                     .. ...*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0900 (2304)
wHeight                  : 0x0510 (1296)
dwMinBitRate             : 0x01C7A000 (29859840 bps -> 3.732 MB/s)
dwMaxBitRate             : 0x01C7A000 (29859840 bps -> 3.732 MB/s)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x04 (4 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 2A 24 11 05 00 00 09 10 05 00 A0 C7 01 00 A0 C7   *$..............
                           01 2A 2C 0A 00 04 00 00 00 00 15 16 05 00 80 1A   .*,.............
                           06 00 20 A1 07 00 2A 2C 0A 00                     .. ...*,..

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
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x01
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x09 (String Descriptor 9)
 Language 0x0409         : "Video Streaming"
Data (HexDump)           : 09 04 03 01 01 0E 02 00 09                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x84 (Direction=IN EndpointID=4)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x03FF
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x3FF (1023 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 84 05 FF 03 01                              .......

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x04
bInterfaceCount          : 0x02
bFunctionClass           : 0x02 (Communications and CDC Control)
bFunctionSubClass        : 0x02
bFunctionProtocol        : 0x01
iFunction                : 0x0D (String Descriptor 13)
 Language 0x0409         : "CDC Serial"
Data (HexDump)           : 08 0B 04 02 02 02 01 0D                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x04
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x02 (Communications and CDC Control)
bInterfaceSubClass       : 0x02 (Abstract Control Model)
bInterfaceProtocol       : 0x01 (AT Commands defined by ITU-T V.250 etc)
iInterface               : 0x0B (String Descriptor 11)
 Language 0x0409         : "CDC Abstract Control Model (ACM)"
Data (HexDump)           : 09 04 04 00 01 02 02 01 0B                        .........

        -------------- CDC Interface Descriptor ---------------
bFunctionLength          : 0x05 (5 bytes)
bDescriptorType          : 0x24 (Interface)
bDescriptorSubType       : 0x00 (Header Functional Descriptor)
bcdCDC                   : 0x110 (CDC Version 1.10)
Data (HexDump)           : 05 24 00 10 01                                    .$...

        -------------- CDC Interface Descriptor ---------------
bFunctionLength          : 0x05 (5 bytes)
bDescriptorType          : 0x24 (Interface)
bDescriptorSubType       : 0x01 (Call Management Functional Descriptor)
bmCapabilities           : 0x00
 D7..2                   : 0x00 (Reserved)
 D1                      : 0x00 (sends/receives call management information only over the Communication Class interface)
 D0                      : 0x00 (does not handle call management itself)
bDataInterface           : 0x05
Data (HexDump)           : 05 24 01 00 05                                    .$...

        -------------- CDC Interface Descriptor ---------------
bFunctionLength          : 0x04 (4 bytes)
bDescriptorType          : 0x24 (Interface)
bDescriptorSubType       : 0x02 (Abstract Control Management Functional Descriptor)
bmCapabilities           : 0x02
 D7..4                   : 0x00 (Reserved)
 D3                      : 0x00 (not supports the notification Network_Connection)
 D2                      : 0x00 (not supports the request Send_Break)
 D1                      : 0x01 (supports the request combination of Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, and the notification Serial_State)
 D0                      : 0x00 (not supports the request combination of Set_Comm_Feature, Clear_Comm_Feature, and Get_Comm_Feature)
Data (HexDump)           : 04 24 02 02                                       .$..

        -------------- CDC Interface Descriptor ---------------
bFunctionLength          : 0x05 (5 bytes)
bDescriptorType          : 0x24 (Interface)
bDescriptorSubType       : 0x06 (Union Functional Descriptor)
bControlInterface        : 0x04
bSubordinateInterface[0] : 0x05
Data (HexDump)           : 05 24 06 04 05                                    .$...

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x86 (Direction=IN EndpointID=6)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x000A
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x0A (10 bytes per packet)
bInterval                : 0x20 (32 ms)
Data (HexDump)           : 07 05 86 03 0A 00 20                              ......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x05
bAlternateSetting        : 0x00
bNumEndpoints            : 0x02 (2 Endpoints)
bInterfaceClass          : 0x0A (CDC-Data)
bInterfaceSubClass       : 0x00
bInterfaceProtocol       : 0x00
iInterface               : 0x0C (String Descriptor 12)
 Language 0x0409         : "CDC ACM Data"
Data (HexDump)           : 09 04 05 00 02 0A 00 00 0C                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x85 (Direction=IN EndpointID=5)
bmAttributes             : 0x02 (TransferType=Bulk)
wMaxPacketSize           : 0x0040 (max 64 bytes)
bInterval                : 0x00 (never NAKs)
Data (HexDump)           : 07 05 85 02 40 00 00                              ....@..

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x01 (Direction=OUT EndpointID=1)
bmAttributes             : 0x02 (TransferType=Bulk)
wMaxPacketSize           : 0x0040 (max 64 bytes)
bInterval                : 0x00 (never NAKs)
Data (HexDump)           : 07 05 01 02 40 00 00                              ....@..

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x06
bInterfaceCount          : 0x03
bFunctionClass           : 0x01 (Audio)
bFunctionSubClass        : 0x02 (Audio Streaming)
bFunctionProtocol        : 0x00
iFunction                : 0x0F (String Descriptor 15)
 Language 0x0409         : "Source/Sink"
Data (HexDump)           : 08 0B 06 03 01 02 00 0F                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x06
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x01 (Audio Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x10 (String Descriptor 16)
 Language 0x0409         : "AC Interface"
Data (HexDump)           : 09 04 06 00 01 01 01 00 10                        .........

        ------ Audio Control Interface Header Descriptor ------
bLength                  : 0x0A (10 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01 (Header)
bcdADC                   : 0x0100
wTotalLength             : 0x004A (74 bytes)
bInCollection            : 0x02
baInterfaceNr[1]         : 0x07
baInterfaceNr[2]         : 0x08
Data (HexDump)           : 0A 24 01 00 01 4A 00 02 07 08                     .$...J....

        ------- Audio Control Input Terminal Descriptor -------
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Input Terminal)
bTerminalID              : 0x01
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x00
bNrChannels              : 0x01 (1 channel)
wChannelConfig           : 0x0001 (L)
iChannelNames            : 0x12 (String Descriptor 18)
 Language 0x0409         : "Playback Channels"
iTerminal                : 0x11 (String Descriptor 17)
 Language 0x0409         : "Playback Input terminal"
Data (HexDump)           : 0C 24 02 01 01 01 00 01 01 00 12 11               .$..........

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x03
wTerminalType            : 0x0301 (Speaker)
bAssocTerminal           : 0x00 (0)
bSourceID                : 0x05 (5)
iTerminal                : 0x13 (String Descriptor 19)
 Language 0x0409         : "Playback Output terminal"
Data (HexDump)           : 09 24 03 03 01 03 00 05 13                        .$.......

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x06 (Feature Unit)
bUnitID                  : 0x05 (5)
bSourceID                : 0x01 (1)
bControlSize             : 0x02 (2 bytes per control)
bmaControls[0]           : 0x03, 0x00
 D0: Mute                : 1
 D1: Volume              : 1
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
 D8: Bass Boost          : 0
 D9: Loudness            : 0
 D10: Reserved           : 0
 D11: Reserved           : 0
 D12: Reserved           : 0
 D13: Reserved           : 0
 D14: Reserved           : 0
 D15: Reserved           : 0
bmaControls[1]           : 0x00, 0x00
 D0: Mute                : 0
 D1: Volume              : 0
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
 D8: Bass Boost          : 0
 D9: Loudness            : 0
 D10: Reserved           : 0
 D11: Reserved           : 0
 D12: Reserved           : 0
 D13: Reserved           : 0
 D14: Reserved           : 0
 D15: Reserved           : 0
iFeature                 : 0x18 (String Descriptor 24)
 Language 0x0409         : "Playback Volume"
Data (HexDump)           : 0B 24 06 05 01 02 03 00 00 00 18                  .$.........

        ------- Audio Control Input Terminal Descriptor -------
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Input Terminal)
bTerminalID              : 0x02
wTerminalType            : 0x0201 (Microphone)
bAssocTerminal           : 0x00
bNrChannels              : 0x01 (1 channel)
wChannelConfig           : 0x0001 (L)
iChannelNames            : 0x15 (String Descriptor 21)
 Language 0x0409         : "Capture Channels"
iTerminal                : 0x14 (String Descriptor 20)
 Language 0x0409         : "Capture Input terminal"
Data (HexDump)           : 0C 24 02 02 01 02 00 01 01 00 15 14               .$..........

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x04
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x00 (0)
bSourceID                : 0x06 (6)
iTerminal                : 0x16 (String Descriptor 22)
 Language 0x0409         : "Capture Output terminal"
Data (HexDump)           : 09 24 03 04 01 01 00 06 16                        .$.......

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x06 (Feature Unit)
bUnitID                  : 0x06 (6)
bSourceID                : 0x02 (2)
bControlSize             : 0x02 (2 bytes per control)
bmaControls[0]           : 0x03, 0x00
 D0: Mute                : 1
 D1: Volume              : 1
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
 D8: Bass Boost          : 0
 D9: Loudness            : 0
 D10: Reserved           : 0
 D11: Reserved           : 0
 D12: Reserved           : 0
 D13: Reserved           : 0
 D14: Reserved           : 0
 D15: Reserved           : 0
bmaControls[1]           : 0x00, 0x00
 D0: Mute                : 0
 D1: Volume              : 0
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
 D8: Bass Boost          : 0
 D9: Loudness            : 0
 D10: Reserved           : 0
 D11: Reserved           : 0
 D12: Reserved           : 0
 D13: Reserved           : 0
 D14: Reserved           : 0
 D15: Reserved           : 0
iFeature                 : 0x17 (String Descriptor 23)
 Language 0x0409         : "Capture Volume"
Data (HexDump)           : 0B 24 06 06 02 02 03 00 00 00 17                  .$.........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x87 (Direction=IN EndpointID=7)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0002
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x02 (2 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 87 03 02 00 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x07
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x19 (String Descriptor 25)
 Language 0x0409         : "Playback Inactive"
Data (HexDump)           : 09 04 07 00 00 01 02 00 19                        .........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x07
bAlternateSetting        : 0x01
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x1A (String Descriptor 26)
 Language 0x0409         : "Playback Active"
Data (HexDump)           : 09 04 07 01 01 01 02 00 1A                        .........

        -------- Audio Streaming Interface Descriptor ---------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01
bTerminalLink            : 0x01
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 01 01 01 00                              .$.....

        ------- Audio Streaming Format Type Descriptor --------
bLength                  : 0x14 (20 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Format Type)
bFormatType              : 0x01 (FORMAT_TYPE_I)
bNrChannels              : 0x01 (1 channel)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x04 (supports 4 sample frequencies)
tSamFreq[1]              : 0x01F40 (8000 Hz)
tSamFreq[2]              : 0x03E80 (16000 Hz)
tSamFreq[3]              : 0x0AC44 (44100 Hz)
tSamFreq[4]              : 0x0BB80 (48000 Hz)
Data (HexDump)           : 14 24 02 01 01 02 10 04 40 1F 00 80 3E 00 44 AC   .$......@...>.D.
                           00 80 BB 00                                       ....

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x02 (Direction=OUT EndpointID=2)
bmAttributes             : 0x09 (TransferType=Isochronous  SyncType=Adaptive  EndpointType=Data)
wMaxPacketSize           : 0x0062
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x62 (98 bytes per packet)
bInterval                : 0x01 (1 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 02 09 62 00 01 00 00                        ....b....

        ----------- Audio Data Endpoint Descriptor ------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x25 (Audio Endpoint Descriptor)
bDescriptorSubtype       : 0x01 (General)
bmAttributes             : 0x01
 D0   : Sampling Freq    : 0x01 (supported)
 D1   : Pitch            : 0x00 (not supported)
 D6..2: Reserved         : 0x00
 D7   : MaxPacketsOnly   : 0x00 (no)
bLockDelayUnits          : 0x01 (Milliseconds)
wLockDelay               : 0x0001 (1 ms)
Data (HexDump)           : 07 25 01 01 01 01 00                              .%.....

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x08
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x1B (String Descriptor 27)
 Language 0x0409         : "Capture Inactive"
Data (HexDump)           : 09 04 08 00 00 01 02 00 1B                        .........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x08
bAlternateSetting        : 0x01
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x1C (String Descriptor 28)
 Language 0x0409         : "Capture Active"
Data (HexDump)           : 09 04 08 01 01 01 02 00 1C                        .........

        -------- Audio Streaming Interface Descriptor ---------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01
bTerminalLink            : 0x04
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 04 01 01 00                              .$.....

        ------- Audio Streaming Format Type Descriptor --------
bLength                  : 0x14 (20 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Format Type)
bFormatType              : 0x01 (FORMAT_TYPE_I)
bNrChannels              : 0x01 (1 channel)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x04 (supports 4 sample frequencies)
tSamFreq[1]              : 0x01F40 (8000 Hz)
tSamFreq[2]              : 0x03E80 (16000 Hz)
tSamFreq[3]              : 0x0AC44 (44100 Hz)
tSamFreq[4]              : 0x0BB80 (48000 Hz)
Data (HexDump)           : 14 24 02 01 01 02 10 04 40 1F 00 80 3E 00 44 AC   .$......@...>.D.
                           00 80 BB 00                                       ....

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x88 (Direction=IN EndpointID=8)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0062
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x62 (98 bytes per packet)
bInterval                : 0x01 (1 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 88 05 62 00 01 00 00                        ....b....

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
             ------ String Descriptor 1 ------
bLength                  : 0x12 (18 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "rockchip"
Data (HexDump)           : 12 03 72 00 6F 00 63 00 6B 00 63 00 68 00 69 00   ..r.o.c.k.c.h.i.
                           70 00                                             p.
             ------ String Descriptor 2 ------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "UVC"
Data (HexDump)           : 08 03 55 00 56 00 43 00                           ..U.V.C.
             ------ String Descriptor 3 ------
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "2d312ff4bb1927af"
Data (HexDump)           : 22 03 32 00 64 00 33 00 31 00 32 00 66 00 66 00   ".2.d.3.1.2.f.f.
                           34 00 62 00 62 00 31 00 39 00 32 00 37 00 61 00   4.b.b.1.9.2.7.a.
                           66 00                                             f.
             ------ String Descriptor 4 ------
bLength                  : 0x12 (18 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "uvc_uac1"
Data (HexDump)           : 12 03 75 00 76 00 63 00 5F 00 75 00 61 00 63 00   ..u.v.c._.u.a.c.
                           31 00                                             1.
             ------ String Descriptor 5 ------
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "KAADAS MJPG Carmera¶"  *!*CAUTION  contains character below 0x20
Data (HexDump)           : 2A 03 4B 00 41 00 41 00 44 00 41 00 53 00 20 00   *.K.A.A.D.A.S. .
                           4D 00 4A 00 50 00 47 00 20 00 43 00 61 00 72 00   M.J.P.G. .C.a.r.
                           6D 00 65 00 72 00 61 00 0A 00                     m.e.r.a...
             ------ String Descriptor 6 ------
bLength                  : 0x20 (32 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Video Streaming"
Data (HexDump)           : 20 03 56 00 69 00 64 00 65 00 6F 00 20 00 53 00    .V.i.d.e.o. .S.
                           74 00 72 00 65 00 61 00 6D 00 69 00 6E 00 67 00   t.r.e.a.m.i.n.g.
             ------ String Descriptor 8 ------
bLength                  : 0x2C (44 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "KAADAS Video Carmera¶"  *!*CAUTION  contains character below 0x20
Data (HexDump)           : 2C 03 4B 00 41 00 41 00 44 00 41 00 53 00 20 00   ,.K.A.A.D.A.S. .
                           56 00 69 00 64 00 65 00 6F 00 20 00 43 00 61 00   V.i.d.e.o. .C.a.
                           72 00 6D 00 65 00 72 00 61 00 0A 00               r.m.e.r.a...
             ------ String Descriptor 9 ------
bLength                  : 0x20 (32 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Video Streaming"
Data (HexDump)           : 20 03 56 00 69 00 64 00 65 00 6F 00 20 00 53 00    .V.i.d.e.o. .S.
                           74 00 72 00 65 00 61 00 6D 00 69 00 6E 00 67 00   t.r.e.a.m.i.n.g.
             ------ String Descriptor 11 ------
bLength                  : 0x42 (66 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "CDC Abstract Control Model (ACM)"
Data (HexDump)           : 42 03 43 00 44 00 43 00 20 00 41 00 62 00 73 00   B.C.D.C. .A.b.s.
                           74 00 72 00 61 00 63 00 74 00 20 00 43 00 6F 00   t.r.a.c.t. .C.o.
                           6E 00 74 00 72 00 6F 00 6C 00 20 00 4D 00 6F 00   n.t.r.o.l. .M.o.
                           64 00 65 00 6C 00 20 00 28 00 41 00 43 00 4D 00   d.e.l. .(.A.C.M.
                           29 00                                             ).
             ------ String Descriptor 12 ------
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "CDC ACM Data"
Data (HexDump)           : 1A 03 43 00 44 00 43 00 20 00 41 00 43 00 4D 00   ..C.D.C. .A.C.M.
                           20 00 44 00 61 00 74 00 61 00                      .D.a.t.a.
             ------ String Descriptor 13 ------
bLength                  : 0x16 (22 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "CDC Serial"
Data (HexDump)           : 16 03 43 00 44 00 43 00 20 00 53 00 65 00 72 00   ..C.D.C. .S.e.r.
                           69 00 61 00 6C 00                                 i.a.l.
             ------ String Descriptor 15 ------
bLength                  : 0x18 (24 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Source/Sink"
Data (HexDump)           : 18 03 53 00 6F 00 75 00 72 00 63 00 65 00 2F 00   ..S.o.u.r.c.e./.
                           53 00 69 00 6E 00 6B 00                           S.i.n.k.
             ------ String Descriptor 16 ------
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "AC Interface"
Data (HexDump)           : 1A 03 41 00 43 00 20 00 49 00 6E 00 74 00 65 00   ..A.C. .I.n.t.e.
                           72 00 66 00 61 00 63 00 65 00                     r.f.a.c.e.
             ------ String Descriptor 17 ------
bLength                  : 0x30 (48 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Playback Input terminal"
Data (HexDump)           : 30 03 50 00 6C 00 61 00 79 00 62 00 61 00 63 00   0.P.l.a.y.b.a.c.
                           6B 00 20 00 49 00 6E 00 70 00 75 00 74 00 20 00   k. .I.n.p.u.t. .
                           74 00 65 00 72 00 6D 00 69 00 6E 00 61 00 6C 00   t.e.r.m.i.n.a.l.
             ------ String Descriptor 18 ------
bLength                  : 0x24 (36 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Playback Channels"
Data (HexDump)           : 24 03 50 00 6C 00 61 00 79 00 62 00 61 00 63 00   $.P.l.a.y.b.a.c.
                           6B 00 20 00 43 00 68 00 61 00 6E 00 6E 00 65 00   k. .C.h.a.n.n.e.
                           6C 00 73 00                                       l.s.
             ------ String Descriptor 19 ------
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Playback Output terminal"
Data (HexDump)           : 32 03 50 00 6C 00 61 00 79 00 62 00 61 00 63 00   2.P.l.a.y.b.a.c.
                           6B 00 20 00 4F 00 75 00 74 00 70 00 75 00 74 00   k. .O.u.t.p.u.t.
                           20 00 74 00 65 00 72 00 6D 00 69 00 6E 00 61 00    .t.e.r.m.i.n.a.
                           6C 00                                             l.
             ------ String Descriptor 20 ------
bLength                  : 0x2E (46 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Capture Input terminal"
Data (HexDump)           : 2E 03 43 00 61 00 70 00 74 00 75 00 72 00 65 00   ..C.a.p.t.u.r.e.
                           20 00 49 00 6E 00 70 00 75 00 74 00 20 00 74 00    .I.n.p.u.t. .t.
                           65 00 72 00 6D 00 69 00 6E 00 61 00 6C 00         e.r.m.i.n.a.l.
             ------ String Descriptor 21 ------
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Capture Channels"
Data (HexDump)           : 22 03 43 00 61 00 70 00 74 00 75 00 72 00 65 00   ".C.a.p.t.u.r.e.
                           20 00 43 00 68 00 61 00 6E 00 6E 00 65 00 6C 00    .C.h.a.n.n.e.l.
                           73 00                                             s.
             ------ String Descriptor 22 ------
bLength                  : 0x30 (48 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Capture Output terminal"
Data (HexDump)           : 30 03 43 00 61 00 70 00 74 00 75 00 72 00 65 00   0.C.a.p.t.u.r.e.
                           20 00 4F 00 75 00 74 00 70 00 75 00 74 00 20 00    .O.u.t.p.u.t. .
                           74 00 65 00 72 00 6D 00 69 00 6E 00 61 00 6C 00   t.e.r.m.i.n.a.l.
             ------ String Descriptor 23 ------
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Capture Volume"
Data (HexDump)           : 1E 03 43 00 61 00 70 00 74 00 75 00 72 00 65 00   ..C.a.p.t.u.r.e.
                           20 00 56 00 6F 00 6C 00 75 00 6D 00 65 00          .V.o.l.u.m.e.
             ------ String Descriptor 24 ------
bLength                  : 0x20 (32 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Playback Volume"
Data (HexDump)           : 20 03 50 00 6C 00 61 00 79 00 62 00 61 00 63 00    .P.l.a.y.b.a.c.
                           6B 00 20 00 56 00 6F 00 6C 00 75 00 6D 00 65 00   k. .V.o.l.u.m.e.
             ------ String Descriptor 25 ------
bLength                  : 0x24 (36 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Playback Inactive"
Data (HexDump)           : 24 03 50 00 6C 00 61 00 79 00 62 00 61 00 63 00   $.P.l.a.y.b.a.c.
                           6B 00 20 00 49 00 6E 00 61 00 63 00 74 00 69 00   k. .I.n.a.c.t.i.
                           76 00 65 00                                       v.e.
             ------ String Descriptor 26 ------
bLength                  : 0x20 (32 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Playback Active"
Data (HexDump)           : 20 03 50 00 6C 00 61 00 79 00 62 00 61 00 63 00    .P.l.a.y.b.a.c.
                           6B 00 20 00 41 00 63 00 74 00 69 00 76 00 65 00   k. .A.c.t.i.v.e.
             ------ String Descriptor 27 ------
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Capture Inactive"
Data (HexDump)           : 22 03 43 00 61 00 70 00 74 00 75 00 72 00 65 00   ".C.a.p.t.u.r.e.
                           20 00 49 00 6E 00 61 00 63 00 74 00 69 00 76 00    .I.n.a.c.t.i.v.
                           65 00                                             e.
             ------ String Descriptor 28 ------
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Capture Active"
Data (HexDump)           : 1E 03 43 00 61 00 70 00 74 00 75 00 72 00 65 00   ..C.a.p.t.u.r.e.
                           20 00 41 00 63 00 74 00 69 00 76 00 65 00          .A.c.t.i.v.e.
*/

namespace customer_camera_dual {
const uint8_t dev_desc[] = {
    0x12, 0x01, 0x00, 0x02, 0xEF, 0x02, 0x01, 0x40, 0x07, 0x22, 0x18, 0x00, 0x10, 0x03, 0x01, 0x02,
    0x03, 0x01
};

const uint8_t cfg_desc[] = {
    0x09, 0x02, 0x7A, 0x03, 0x09, 0x01, 0x04, 0x80, 0xFA, 0x08, 0x0B, 0x00, 0x02, 0x0E, 0x03, 0x00,
    0x05, 0x09, 0x04, 0x00, 0x00, 0x01, 0x0E, 0x01, 0x00, 0x05, 0x0D, 0x24, 0x01, 0x00, 0x01, 0x4E,
    0x00, 0x00, 0x6C, 0xDC, 0x02, 0x01, 0x01, 0x12, 0x24, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x00, 0x00, 0x0C, 0x24, 0x05, 0x02, 0x01, 0x00, 0x40,
    0x02, 0x01, 0x00, 0x00, 0x00, 0x09, 0x24, 0x03, 0x03, 0x01, 0x01, 0x00, 0x02, 0x00, 0x1A, 0x24,
    0x06, 0x06, 0xA2, 0x9E, 0x76, 0x41, 0xDE, 0x04, 0x47, 0xE3, 0x8B, 0x2B, 0xF4, 0x34, 0x1A, 0xFF,
    0x00, 0x3B, 0x03, 0x01, 0x02, 0x01, 0x07, 0x00, 0x07, 0x05, 0x81, 0x03, 0x10, 0x00, 0x08, 0x05,
    0x25, 0x03, 0x10, 0x00, 0x09, 0x04, 0x01, 0x00, 0x00, 0x0E, 0x02, 0x00, 0x06, 0x0E, 0x24, 0x01,
    0x01, 0x49, 0x00, 0x82, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0B, 0x24, 0x06, 0x01, 0x01,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x24, 0x07, 0x01, 0x00, 0xD0, 0x02, 0x00, 0x05, 0x00,
    0x40, 0x19, 0x01, 0x00, 0x40, 0x19, 0x01, 0x00, 0x20, 0x1C, 0x00, 0x15, 0x16, 0x05, 0x00, 0x04,
    0x15, 0x16, 0x05, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00,
    0x06, 0x24, 0x0D, 0x01, 0x01, 0x04, 0x09, 0x04, 0x01, 0x01, 0x01, 0x0E, 0x02, 0x00, 0x06, 0x07,
    0x05, 0x82, 0x05, 0x00, 0x0C, 0x01, 0x08, 0x0B, 0x02, 0x02, 0x0E, 0x03, 0x00, 0x08, 0x09, 0x04,
    0x02, 0x00, 0x01, 0x0E, 0x01, 0x00, 0x08, 0x0D, 0x24, 0x01, 0x00, 0x01, 0x4E, 0x00, 0x00, 0x6C,
    0xDC, 0x02, 0x01, 0x03, 0x12, 0x24, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x02, 0x00, 0x00, 0x0C, 0x24, 0x05, 0x02, 0x01, 0x00, 0x40, 0x02, 0x01, 0x00,
    0x00, 0x00, 0x09, 0x24, 0x03, 0x03, 0x01, 0x01, 0x00, 0x02, 0x00, 0x1A, 0x24, 0x06, 0x06, 0xA2,
    0x9E, 0x76, 0x41, 0xDE, 0x04, 0x47, 0xE3, 0x8B, 0x2B, 0xF4, 0x34, 0x1A, 0xFF, 0x00, 0x3B, 0x03,
    0x01, 0x02, 0x01, 0x07, 0x00, 0x07, 0x05, 0x83, 0x03, 0x10, 0x00, 0x08, 0x05, 0x25, 0x03, 0x10,
    0x00, 0x09, 0x04, 0x03, 0x00, 0x00, 0x0E, 0x02, 0x00, 0x09, 0x0E, 0x24, 0x01, 0x01, 0x02, 0x01,
    0x84, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x1C, 0x24, 0x10, 0x01, 0x05, 0x48, 0x32, 0x36,
    0x35, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71, 0x10, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x2A, 0x24, 0x11, 0x01, 0x00, 0x80, 0x02, 0xE0, 0x01, 0x00, 0xE0, 0x2E,
    0x00, 0x00, 0xE0, 0x2E, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x15, 0x16,
    0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x2A, 0x24,
    0x11, 0x02, 0x00, 0x00, 0x05, 0xD0, 0x02, 0x00, 0xA0, 0x8C, 0x00, 0x00, 0xA0, 0x8C, 0x00, 0x2A,
    0x2C, 0x0A, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00,
    0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x2A, 0x24, 0x11, 0x03, 0x00, 0x80, 0x07, 0x38,
    0x04, 0x00, 0x68, 0x3C, 0x01, 0x00, 0x68, 0x3C, 0x01, 0x2A, 0x2C, 0x0A, 0x00, 0x04, 0x00, 0x00,
    0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C,
    0x0A, 0x00, 0x2A, 0x24, 0x11, 0x04, 0x00, 0x00, 0x0A, 0xA0, 0x05, 0x00, 0x80, 0x32, 0x02, 0x00,
    0x80, 0x32, 0x02, 0x2A, 0x2C, 0x0A, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00,
    0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x2A, 0x24, 0x11, 0x05,
    0x00, 0x00, 0x09, 0x10, 0x05, 0x00, 0xA0, 0xC7, 0x01, 0x00, 0xA0, 0xC7, 0x01, 0x2A, 0x2C, 0x0A,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1,
    0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x06, 0x24, 0x0D, 0x01, 0x01, 0x04, 0x09, 0x04, 0x03, 0x01,
    0x01, 0x0E, 0x02, 0x00, 0x09, 0x07, 0x05, 0x84, 0x05, 0x00, 0x0C, 0x01, 0x08, 0x0B, 0x04, 0x02,
    0x02, 0x02, 0x01, 0x0D, 0x09, 0x04, 0x04, 0x00, 0x01, 0x02, 0x02, 0x01, 0x0B, 0x05, 0x24, 0x00,
    0x10, 0x01, 0x05, 0x24, 0x01, 0x00, 0x05, 0x04, 0x24, 0x02, 0x02, 0x05, 0x24, 0x06, 0x04, 0x05,
    0x07, 0x05, 0x86, 0x03, 0x0A, 0x00, 0x09, 0x09, 0x04, 0x05, 0x00, 0x02, 0x0A, 0x00, 0x00, 0x0C,
    0x07, 0x05, 0x85, 0x02, 0x00, 0x02, 0x00, 0x07, 0x05, 0x01, 0x02, 0x00, 0x02, 0x00, 0x08, 0x0B,
    0x06, 0x03, 0x01, 0x02, 0x00, 0x0F, 0x09, 0x04, 0x06, 0x00, 0x01, 0x01, 0x01, 0x00, 0x10, 0x0A,
    0x24, 0x01, 0x00, 0x01, 0x4A, 0x00, 0x02, 0x07, 0x08, 0x0C, 0x24, 0x02, 0x01, 0x01, 0x01, 0x00,
    0x01, 0x01, 0x00, 0x12, 0x11, 0x09, 0x24, 0x03, 0x03, 0x01, 0x03, 0x00, 0x05, 0x13, 0x0B, 0x24,
    0x06, 0x05, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00, 0x18, 0x0C, 0x24, 0x02, 0x02, 0x01, 0x02, 0x00,
    0x01, 0x01, 0x00, 0x15, 0x14, 0x09, 0x24, 0x03, 0x04, 0x01, 0x01, 0x00, 0x06, 0x16, 0x0B, 0x24,
    0x06, 0x06, 0x02, 0x02, 0x03, 0x00, 0x00, 0x00, 0x17, 0x07, 0x05, 0x87, 0x03, 0x02, 0x00, 0x04,
    0x09, 0x04, 0x07, 0x00, 0x00, 0x01, 0x02, 0x00, 0x19, 0x09, 0x04, 0x07, 0x01, 0x01, 0x01, 0x02,
    0x00, 0x1A, 0x07, 0x24, 0x01, 0x01, 0x01, 0x01, 0x00, 0x14, 0x24, 0x02, 0x01, 0x01, 0x02, 0x10,
    0x04, 0x40, 0x1F, 0x00, 0x80, 0x3E, 0x00, 0x44, 0xAC, 0x00, 0x80, 0xBB, 0x00, 0x09, 0x05, 0x02,
    0x09, 0x62, 0x00, 0x04, 0x00, 0x00, 0x07, 0x25, 0x01, 0x01, 0x01, 0x01, 0x00, 0x09, 0x04, 0x08,
    0x00, 0x00, 0x01, 0x02, 0x00, 0x1B, 0x09, 0x04, 0x08, 0x01, 0x01, 0x01, 0x02, 0x00, 0x1C, 0x07,
    0x24, 0x01, 0x04, 0x01, 0x01, 0x00, 0x14, 0x24, 0x02, 0x01, 0x01, 0x02, 0x10, 0x04, 0x40, 0x1F,
    0x00, 0x80, 0x3E, 0x00, 0x44, 0xAC, 0x00, 0x80, 0xBB, 0x00, 0x09, 0x05, 0x88, 0x05, 0x62, 0x00,
    0x04, 0x00, 0x00, 0x07, 0x25, 0x01, 0x01, 0x00, 0x00, 0x00
};
}
