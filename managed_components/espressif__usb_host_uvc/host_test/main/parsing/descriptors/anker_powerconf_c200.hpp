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
Device ID                : USB\VID_291A&PID_3369\ACNV9P0D12366611
Hardware IDs             : USB\VID_291A&PID_3369&REV_0105 USB\VID_291A&PID_3369
Driver KeyName           : {36fc9e60-c465-11cf-8056-444553540000}\0097 (GUID_DEVCLASS_USB)
Driver                   : \SystemRoot\System32\drivers\usbccgp.sys (Version: 10.0.19041.4474  Date: 2024-06-13)
Driver Inf               : C:\Windows\inf\usb.inf
Legacy BusType           : PNPBus
Class                    : USB
Class GUID               : {36fc9e60-c465-11cf-8056-444553540000} (GUID_DEVCLASS_USB)
Service                  : usbccgp
Enumerator               : USB
Location Info            : Port_#0002.Hub_#0012
Location IDs             : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(4)#USB(2), ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(4)#USB(2)
Container ID             : {1311548a-a58a-5e7e-8a3d-947dad1a9988}
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
 Child Device 1          : Anker PowerConf C200 (USB Video Device)
  Device Path 1          : \\?\USB#VID_291A&PID_3369&MI_00#a&1dd8ee0f&0&0000#{6994ad05-93ef-11d0-a3cc-00a0c9223196}\global (AM_KSCATEGORY_VIDEO)
  Device Path 2          : \\?\USB#VID_291A&PID_3369&MI_00#a&1dd8ee0f&0&0000#{6994ad05-93ef-11d0-a3cc-00a0c9223196}\global (AM_KSCATEGORY_VIDEO)
  Kernel Name            : \Device\00000316
  Device ID              : USB\VID_291A&PID_3369&MI_00\A&1DD8EE0F&0&0000
  Class                  : Camera
  Driver KeyName         : {ca3e7ab9-b4c3-4ae6-8251-579ef933890f}\0007 (GUID_DEVCLASS_CAMERA)
  Service                : usbvideo
  Location               : 0005.0000.0004.001.003.004.002.000.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(4)#USB(2)#USBMI(0)  PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(4)#USB(2)#USB(2)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(4)#USB(2)#USBMI(0)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(4)#USB(2)#USB(2)
 Child Device 2          : Anker PowerConf C200 (USB Audio Device)
  Device Path 1          : \\?\USB#VID_291A&PID_3369&MI_02#a&1dd8ee0f&0&0002#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global (AM_KSCATEGORY_CAPTURE)
  Device Path 2          : \\?\USB#VID_291A&PID_3369&MI_02#a&1dd8ee0f&0&0002#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global (AM_KSCATEGORY_CAPTURE)
  Kernel Name            : \Device\00000317
  Device ID              : USB\VID_291A&PID_3369&MI_02\A&1DD8EE0F&0&0002
  Class                  : MEDIA
  Driver KeyName         : {4d36e96c-e325-11ce-bfc1-08002be10318}\0009 (GUID_DEVCLASS_MEDIA)
  Service                : usbaudio
  Location               : 0005.0000.0004.001.003.004.002.000.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(4)#USB(2)#USBMI(2)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(4)#USB(2)#USBMI(2)
   Child Device 1        : Microphone (Anker PowerConf C200) (Audio Endpoint)
    Device ID            : SWD\MMDEVAPI\{0.0.1.00000000}.{998B6389-80E3-4E24-9511-1AFDEA804715}
    Class                : AudioEndpoint
    Driver KeyName       : {c166523c-fe0c-4a94-a586-f1a80cfbbf3e}\0038 (AUDIOENDPOINT_CLASS_UUID)
 Child Device 3          : USB Input Device
  Device ID              : USB\VID_291A&PID_3369&MI_04\A&1DD8EE0F&0&0004
  Class                  : HIDClass
  Driver KeyName         : {745a17a0-74d3-11d0-b6fe-00a0c90f57da}\0042 (GUID_DEVCLASS_HIDCLASS)
  Service                : HidUsb
  Location               : 0005.0000.0004.001.003.004.002.000.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(4)#USB(2)#USBMI(4)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(4)#USB(2)#USBMI(4)
   Child Device 1        : HID-compliant device
    Device Path          : \\?\HID#VID_291A&PID_3369&MI_04#b&20947516&0&0000#{4d1e55b2-f16f-11cf-88cb-001111000030} (GUID_DEVINTERFACE_HID)
    Kernel Name          : \Device\0000031b
    Device ID            : HID\VID_291A&PID_3369&MI_04\B&20947516&0&0000
    Class                : HIDClass
    Driver KeyName       : {745a17a0-74d3-11d0-b6fe-00a0c90f57da}\0043 (GUID_DEVCLASS_HIDCLASS)

        +++++++++++++++++ Registry USB Flags +++++++++++++++++
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\usbflags\291A33690105
 osvc                    : REG_BINARY 00 00

        ---------------- Connection Information ---------------
Connection Index         : 0x02 (Port 2)
Connection Status        : 0x01 (DeviceConnected)
Current Config Value     : 0x01 (Configuration 1)
Device Address           : 0x09 (9)
Is Hub                   : 0x00 (no)
Device Bus Speed         : 0x02 (High-Speed)
Number Of Open Pipes     : 0x03 (3 pipes to data endpoints)
Pipe[0]                  : EndpointID=1  Direction=IN   ScheduleOffset=0  Type=Interrupt
Pipe[1]                  : EndpointID=3  Direction=IN   ScheduleOffset=0  Type=Interrupt
Pipe[2]                  : EndpointID=1  Direction=OUT  ScheduleOffset=0  Type=Interrupt
Data (HexDump)           : 02 00 00 00 12 01 00 02 EF 02 01 40 1A 29 69 33   ...........@.)i3
                           05 01 01 02 03 01 01 02 00 09 00 03 00 00 00 01   ................
                           00 00 00 07 05 81 03 10 00 08 00 00 00 00 07 05   ................
                           83 03 00 04 04 00 00 00 00 07 05 01 03 00 04 04   ................
                           00 00 00 00                                       ....

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
idVendor                 : 0x291A (Anker Innovations Limited)
idProduct                : 0x3369
bcdDevice                : 0x0105
iManufacturer            : 0x01 (String Descriptor 1)
 Language 0x0409         : "Anker PowerConf C200"
iProduct                 : 0x02 (String Descriptor 2)
 Language 0x0409         : "Anker PowerConf C200"
iSerialNumber            : 0x03 (String Descriptor 3)
 Language 0x0409         : "ACNV9P0D12366611"
bNumConfigurations       : 0x01 (1 Configuration)
Data (HexDump)           : 12 01 00 02 EF 02 01 40 1A 29 69 33 05 01 01 02   .......@.)i3....
                           03 01                                             ..

    ------------------ Configuration Descriptor -------------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x02 (Configuration Descriptor)
wTotalLength             : 0x0349 (841 bytes)
bNumInterfaces           : 0x05 (5 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x00 (No String Descriptor)
bmAttributes             : 0xC0
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x01 (yes)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0x64 (200 mA)
Data (HexDump)           : 09 02 49 03 05 01 00 C0 64 08 0B 00 02 0E 03 00   ..I.....d.......
                           04 09 04 00 00 01 0E 01 00 04 0D 24 01 10 01 50   ...........$...P
                           00 00 6C DC 02 01 01 12 24 02 01 01 02 00 00 00   ..l.....$.......
                           00 00 00 00 00 03 2A 8A 02 0C 24 05 02 01 00 40   ......*...$....@
                           02 7F 14 00 00 1C 24 06 06 A2 9E 76 41 DE 04 47   ......$....vA..G
                           E3 8B 2B F4 34 1A FF 00 3B 0F 01 02 03 00 F8 27   ..+.4...;......'
                           00 09 24 03 03 01 01 00 04 00 07 05 81 03 10 00   ..$.............
                           08 05 25 03 10 00 09 04 01 00 00 0E 02 00 00 10   ..%.............
                           24 01 03 2E 02 88 00 03 02 01 01 01 00 04 00 0B   $...............
                           24 06 01 06 00 01 00 00 00 00 1E 24 07 01 00 00   $..........$....
                           0A A0 05 00 00 65 04 00 00 65 04 00 80 70 00 15   .....e...e...p..
                           16 05 00 01 15 16 05 00 1E 24 07 02 00 80 07 38   .........$.....8
                           04 00 D0 78 02 00 D0 78 02 00 48 3F 00 15 16 05   ...x...x..H?....
                           00 01 15 16 05 00 1E 24 07 03 00 00 05 D0 02 00   .......$........
                           40 19 01 00 40 19 01 00 20 1C 00 15 16 05 00 01   @...@... .......
                           15 16 05 00 1E 24 07 04 00 80 02 E0 01 00 C0 5D   .....$.........]
                           00 00 C0 5D 00 00 60 09 00 15 16 05 00 01 15 16   ...]..`.........
                           05 00 1E 24 07 05 00 80 02 68 01 00 50 46 00 00   ...$.....h..PF..
                           50 46 00 00 08 07 00 15 16 05 00 01 15 16 05 00   PF..............
                           1E 24 07 06 00 40 01 F0 00 00 70 17 00 00 70 17   .$...@....p...p.
                           00 00 58 02 00 15 16 05 00 01 15 16 05 00 0A 24   ..X............$
                           03 00 01 80 07 38 04 00 1B 24 04 02 03 59 55 59   .....8...$...YUY
                           32 00 00 10 00 80 00 00 AA 00 38 9B 71 10 01 00   2.........8.q...
                           00 00 00 1E 24 05 01 00 80 02 E0 01 00 C0 5D 00   ....$.........].
                           00 C0 5D 00 00 60 09 00 15 16 05 00 01 15 16 05   ..]..`..........
                           00 1E 24 05 02 00 80 02 68 01 00 50 46 00 00 50   ..$.....h..PF..P
                           46 00 00 08 07 00 15 16 05 00 01 15 16 05 00 1E   F...............
                           24 05 03 00 40 01 F0 00 00 70 17 00 00 70 17 00   $...@....p...p..
                           00 58 02 00 15 16 05 00 01 15 16 05 00 0A 24 03   .X............$.
                           00 01 80 07 38 04 00 1C 24 10 03 06 48 32 36 34   ....8...$...H264
                           00 00 10 00 80 00 00 AA 00 38 9B 71 10 01 00 00   .........8.q....
                           00 00 01 1E 24 11 01 00 00 0A A0 05 00 80 32 02   ....$.........2.
                           00 80 32 02 15 16 05 00 01 00 00 00 00 15 16 05   ..2.............
                           00 1E 24 11 02 00 80 07 38 04 00 68 3C 01 00 68   ..$.....8..h<..h
                           3C 01 15 16 05 00 01 00 00 00 00 15 16 05 00 1E   <...............
                           24 11 03 00 00 05 D0 02 00 A0 8C 00 00 A0 8C 00   $...............
                           15 16 05 00 01 00 00 00 00 15 16 05 00 1E 24 11   ..............$.
                           04 00 80 02 E0 01 00 E0 2E 00 00 E0 2E 00 15 16   ................
                           05 00 01 00 00 00 00 15 16 05 00 1E 24 11 05 00   ............$...
                           80 02 68 01 00 28 23 00 00 28 23 00 15 16 05 00   ..h..(#..(#.....
                           01 00 00 00 00 15 16 05 00 1E 24 11 06 00 40 01   ..........$...@.
                           F0 00 00 B8 0B 00 00 B8 0B 00 15 16 05 00 01 00   ................
                           00 00 00 15 16 05 00 06 24 0D 01 01 04 09 04 01   ........$.......
                           01 01 0E 02 00 00 07 05 88 05 00 0C 01 08 0B 02   ................
                           02 01 00 00 05 09 04 02 00 00 01 01 00 05 09 24   ...............$
                           01 00 01 27 00 01 03 0C 24 02 02 01 02 00 02 03   ...'....$.......
                           00 00 00 09 24 03 04 01 01 00 06 00 09 24 06 06   ....$........$..
                           02 02 03 00 00 09 04 03 00 00 01 02 00 00 09 04   ................
                           03 01 01 01 02 00 00 07 24 01 04 01 01 00 0B 24   ........$......$
                           02 01 02 02 10 01 80 BB 00 09 05 82 0D C0 00 04   ................
                           00 00 07 25 01 01 01 01 00 09 04 04 00 02 03 00   ...%............
                           00 06 09 21 01 01 00 01 22 23 00 07 05 83 03 00   ...!...."#......
                           04 04 07 05 01 03 00 04 04                        .........

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x00
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x04 (String Descriptor 4)
 Language 0x0409         : "Anker PowerConf C200"
Data (HexDump)           : 08 0B 00 02 0E 03 00 04                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x00
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x04 (String Descriptor 4)
 Language 0x0409         : "Anker PowerConf C200"
Data (HexDump)           : 09 04 00 00 01 0E 01 00 04                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0110 (UVC Version 1.10)
wTotalLength             : 0x0050 (80 bytes)
dwClockFreq              : 0x02DC6C00 (48 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x01
Data (HexDump)           : 0D 24 01 10 01 50 00 00 6C DC 02 01 01            .$...P..l....

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
bmControls               : 0x2A, 0x8A, 0x02
 D0                      : 0   no -  Scanning Mode
 D1                      : 1  yes -  Auto-Exposure Mode
 D2                      : 0   no -  Auto-Exposure Priority
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
 D13                     : 0   no -  Roll (Absolute)
 D14                     : 0   no -  Roll (Relative)
 D15                     : 1  yes -  Tilt (Absolute)
 D16                     : 0   no -  Tilt (Relative)
 D17                     : 1  yes -  Focus Auto
 D18                     : 0   no -  Reserved
 D19                     : 0   no -  Reserved
 D20                     : 0   no -  Reserved
 D21                     : 0   no -  Reserved
 D22                     : 0   no -  Reserved
 D23                     : 0   no -  Reserved
Data (HexDump)           : 12 24 02 01 01 02 00 00 00 00 00 00 00 00 03 2A   .$.............*
                           8A 02                                             ..

        -------- Video Control Processing Unit Descriptor -----
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x05 (Processing Unit)
bUnitID                  : 0x02
bSourceID                : 0x01
wMaxMultiplier           : 0x4000 (163.84x Zoom)
bControlSize             : 0x02
bmControls               : 0x7F, 0x14
 D0                      : 1  yes -  Brightness
 D1                      : 1  yes -  Contrast
 D2                      : 1  yes -  Hue
 D3                      : 1  yes -  Saturation
 D4                      : 1  yes -  Sharpness
 D5                      : 1  yes -  Gamma
 D6                      : 1  yes -  White Balance Temperature
 D7                      : 0   no -  White Balance Component
 D8                      : 0   no -  Backlight Compensation
 D9                      : 0   no -  Gain
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
Data (HexDump)           : 0C 24 05 02 01 00 40 02 7F 14 00 00               .$....@.....

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x06
guidExtensionCode        : {41769EA2-04DE-E347-8B2B-F4341AFF003B}
bNumControls             : 0x0F
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x03
bmControls               : 0x00, 0xF8, 0x27
 D0                      : 0   no -  Vendor-Specific (Optional)
 D1                      : 0   no -  Vendor-Specific (Optional)
 D2                      : 0   no -  Vendor-Specific (Optional)
 D3                      : 0   no -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
 D8                      : 0   no -  Vendor-Specific (Optional)
 D9                      : 0   no -  Vendor-Specific (Optional)
 D10                     : 0   no -  Vendor-Specific (Optional)
 D11                     : 1  yes -  Vendor-Specific (Optional)
 D12                     : 1  yes -  Vendor-Specific (Optional)
 D13                     : 1  yes -  Vendor-Specific (Optional)
 D14                     : 1  yes -  Vendor-Specific (Optional)
 D15                     : 1  yes -  Vendor-Specific (Optional)
 D16                     : 1  yes -  Vendor-Specific (Optional)
 D17                     : 1  yes -  Vendor-Specific (Optional)
 D18                     : 1  yes -  Vendor-Specific (Optional)
 D19                     : 0   no -  Vendor-Specific (Optional)
 D20                     : 0   no -  Vendor-Specific (Optional)
 D21                     : 1  yes -  Vendor-Specific (Optional)
 D22                     : 0   no -  Vendor-Specific (Optional)
 D23                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1C 24 06 06 A2 9E 76 41 DE 04 47 E3 8B 2B F4 34   .$....vA..G..+.4
                           1A FF 00 3B 0F 01 02 03 00 F8 27 00               ...;......'.

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x03
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x04
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 03 01 01 00 04 00                        .$.......

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
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 00 00 0E 02 00 00                        .........

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x10 (16 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x03
wTotalLength             : 0x022E (558 bytes)
bEndpointAddress         : 0x88 (Direction=IN  EndpointID=8)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x03
bStillCaptureMethod      : 0x02 (Still Capture Method 2)
nbTriggerSupport         : 0x01 (Hardware Triggering is supported)
bTriggerUsage            : 0x01 (Host will notify client application of button event)
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
Video Payload Format 3   : 0x00
 D0                      : 0   no -  Key Frame Rate
 D1                      : 0   no -  P Frame Rate
 D2                      : 0   no -  Compression Quality
 D3                      : 0   no -  Compression Window Size
 D4                      : 0   no -  Generate Key Frame
 D5                      : 0   no -  Update Frame Segment
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Data (HexDump)           : 10 24 01 03 2E 02 88 00 03 02 01 01 01 00 04 00   .$..............

        ----- Video Streaming MJPEG Format Type Descriptor ----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x06 (Format MJPEG)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x06 (6)
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
*!*ERROR:  no Color Matching Descriptor for this format
Data (HexDump)           : 0B 24 06 01 06 00 01 00 00 00 00                  .$.........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
---> This is the Default (optimum) Frame index
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0A00 (2560)
wHeight                  : 0x05A0 (1440)
dwMinBitRate             : 0x04650000 (73728000 bps -> 9.216 MB/s)
dwMaxBitRate             : 0x04650000 (73728000 bps -> 9.216 MB/s)
dwMaxVideoFrameBufferSize: 0x00708000 (7372800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 07 01 00 00 0A A0 05 00 00 65 04 00 00 65   .$.........e...e
                           04 00 80 70 00 15 16 05 00 01 15 16 05 00         ...p..........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x0278D000 (41472000 bps -> 5.184 MB/s)
dwMaxBitRate             : 0x0278D000 (41472000 bps -> 5.184 MB/s)
dwMaxVideoFrameBufferSize: 0x003F4800 (4147200 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 07 02 00 80 07 38 04 00 D0 78 02 00 D0 78   .$.....8...x...x
                           02 00 48 3F 00 15 16 05 00 01 15 16 05 00         ..H?..........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxVideoFrameBufferSize: 0x001C2000 (1843200 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 07 03 00 00 05 D0 02 00 40 19 01 00 40 19   .$........@...@.
                           01 00 20 1C 00 15 16 05 00 01 15 16 05 00         .. ...........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x005DC000 (6144000 bps -> 768 KB/s)
dwMaxBitRate             : 0x005DC000 (6144000 bps -> 768 KB/s)
dwMaxVideoFrameBufferSize: 0x00096000 (614400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 07 04 00 80 02 E0 01 00 C0 5D 00 00 C0 5D   .$.........]...]
                           00 00 60 09 00 15 16 05 00 01 15 16 05 00         ..`...........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x00465000 (4608000 bps -> 576 KB/s)
dwMaxBitRate             : 0x00465000 (4608000 bps -> 576 KB/s)
dwMaxVideoFrameBufferSize: 0x00070800 (460800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 07 05 00 80 02 68 01 00 50 46 00 00 50 46   .$.....h..PF..PF
                           00 00 08 07 00 15 16 05 00 01 15 16 05 00         ..............

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0140 (320)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x00177000 (1536000 bps -> 192 KB/s)
dwMaxBitRate             : 0x00177000 (1536000 bps -> 192 KB/s)
dwMaxVideoFrameBufferSize: 0x00025800 (153600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 07 06 00 40 01 F0 00 00 70 17 00 00 70 17   .$...@....p...p.
                           00 00 58 02 00 15 16 05 00 01 15 16 05 00         ..X...........

        ---------- Still Image Frame Type Descriptor ----------
bLength                  : 0x0A (10 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x03 (Still Image Frame Type)
bEndpointAddress         : 0x00 (no endpoint)
bNumImageSizePatterns    : 0x01 (1 Image Size Patterns)
1: wWidth x wHeight      : 0x0780 x 0x0438 (1920 x 1080)
bNumCompressionPattern   : 0x00
Data (HexDump)           : 0A 24 03 00 01 80 07 38 04 00                     .$.....8..

        ------- VS Uncompressed Format Type Descriptor --------
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x04 (Uncompressed Format Type)
bFormatIndex             : 0x02 (2)
bNumFrameDescriptors     : 0x03 (3)
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
Data (HexDump)           : 1B 24 04 02 03 59 55 59 32 00 00 10 00 80 00 00   .$...YUY2.......
                           AA 00 38 9B 71 10 01 00 00 00 00                  ..8.q......

        -------- VS Uncompressed Frame Type Descriptor --------
---> This is the Default (optimum) Frame index
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x005DC000 (6144000 bps -> 768 KB/s)
dwMaxBitRate             : 0x005DC000 (6144000 bps -> 768 KB/s)
dwMaxVideoFrameBufferSize: 0x00096000 (614400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 05 01 00 80 02 E0 01 00 C0 5D 00 00 C0 5D   .$.........]...]
                           00 00 60 09 00 15 16 05 00 01 15 16 05 00         ..`...........

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x00465000 (4608000 bps -> 576 KB/s)
dwMaxBitRate             : 0x00465000 (4608000 bps -> 576 KB/s)
dwMaxVideoFrameBufferSize: 0x00070800 (460800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 05 02 00 80 02 68 01 00 50 46 00 00 50 46   .$.....h..PF..PF
                           00 00 08 07 00 15 16 05 00 01 15 16 05 00         ..............

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x0140 (320)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x00177000 (1536000 bps -> 192 KB/s)
dwMaxBitRate             : 0x00177000 (1536000 bps -> 192 KB/s)
dwMaxVideoFrameBufferSize: 0x00025800 (153600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 05 03 00 40 01 F0 00 00 70 17 00 00 70 17   .$...@....p...p.
                           00 00 58 02 00 15 16 05 00 01 15 16 05 00         ..X...........

        ---------- Still Image Frame Type Descriptor ----------
bLength                  : 0x0A (10 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x03 (Still Image Frame Type)
bEndpointAddress         : 0x00 (no endpoint)
bNumImageSizePatterns    : 0x01 (1 Image Size Patterns)
1: wWidth x wHeight      : 0x0780 x 0x0438 (1920 x 1080)
bNumCompressionPattern   : 0x00
Data (HexDump)           : 0A 24 03 00 01 80 07 38 04 00                     .$.....8..

        ---- VS Frame Based Payload Format Type Descriptor ----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x10 (Frame Based Format Type)
bFormatIndex             : 0x03 (3)
bNumFrameDescriptors     : 0x06 (6)
guidFormat               : {34363248-0000-0010-8000-00AA00389B71} (H264)
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
Data (HexDump)           : 1C 24 10 03 06 48 32 36 34 00 00 10 00 80 00 00   .$...H264.......
                           AA 00 38 9B 71 10 01 00 00 00 00 01               ..8.q.......

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0A00 (2560)
wHeight                  : 0x05A0 (1440)
dwMinBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwMaxBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 11 01 00 00 0A A0 05 00 80 32 02 00 80 32   .$.........2...2
                           02 15 16 05 00 01 00 00 00 00 15 16 05 00         ..............

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x013C6800 (20736000 bps -> 2.592 MB/s)
dwMaxBitRate             : 0x013C6800 (20736000 bps -> 2.592 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 11 02 00 80 07 38 04 00 68 3C 01 00 68 3C   .$.....8..h<..h<
                           01 15 16 05 00 01 00 00 00 00 15 16 05 00         ..............

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x008CA000 (9216000 bps -> 1.152 MB/s)
dwMaxBitRate             : 0x008CA000 (9216000 bps -> 1.152 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 11 03 00 00 05 D0 02 00 A0 8C 00 00 A0 8C   .$..............
                           00 15 16 05 00 01 00 00 00 00 15 16 05 00         ..............

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x002EE000 (3072000 bps -> 384 KB/s)
dwMaxBitRate             : 0x002EE000 (3072000 bps -> 384 KB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 11 04 00 80 02 E0 01 00 E0 2E 00 00 E0 2E   .$..............
                           00 15 16 05 00 01 00 00 00 00 15 16 05 00         ..............

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x00232800 (2304000 bps -> 288 KB/s)
dwMaxBitRate             : 0x00232800 (2304000 bps -> 288 KB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 11 05 00 80 02 68 01 00 28 23 00 00 28 23   .$.....h..(#..(#
                           00 15 16 05 00 01 00 00 00 00 15 16 05 00         ..............

        ----- VS Frame Based Payload Frame Type Descriptor ----
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0140 (320)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x000BB800 (768000 bps -> 96 KB/s)
dwMaxBitRate             : 0x000BB800 (768000 bps -> 96 KB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 11 06 00 40 01 F0 00 00 B8 0B 00 00 B8 0B   .$...@..........
                           00 15 16 05 00 01 00 00 00 00 15 16 05 00         ..............

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
bEndpointAddress         : 0x88 (Direction=IN EndpointID=8)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0C00
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x01 (1 additional transactions per microframe -> allows 513..1024 byte per packet)
 Bits 10..0              : 0x400 (1024 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 88 05 00 0C 01                              .......

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x02
bInterfaceCount          : 0x02
bFunctionClass           : 0x01 (Audio)
bFunctionSubClass        : 0x00 (undefined)
bFunctionProtocol        : 0x00
iFunction                : 0x05 (String Descriptor 5)
 Language 0x0409         : "Anker PowerConf C200"
Data (HexDump)           : 08 0B 02 02 01 00 00 05                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x01 (Audio Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x05 (String Descriptor 5)
 Language 0x0409         : "Anker PowerConf C200"
Data (HexDump)           : 09 04 02 00 00 01 01 00 05                        .........

        ------ Audio Control Interface Header Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01 (Header)
bcdADC                   : 0x0100
wTotalLength             : 0x0027 (39 bytes)
bInCollection            : 0x01
baInterfaceNr[1]         : 0x03
Data (HexDump)           : 09 24 01 00 01 27 00 01 03                        .$...'...

        ------- Audio Control Input Terminal Descriptor -------
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Input Terminal)
bTerminalID              : 0x02
wTerminalType            : 0x0201 (Microphone)
bAssocTerminal           : 0x00
bNrChannels              : 0x02 (2 channels)
wChannelConfig           : 0x0003 (L, R)
iChannelNames            : 0x00 (No String Descriptor)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 0C 24 02 02 01 02 00 02 03 00 00 00               .$..........

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x04
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x00 (0)
bSourceID                : 0x06 (6)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 03 04 01 01 00 06 00                        .$.......

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x09 (9 bytes)
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
iFeature                 : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 06 06 02 02 03 00 00                        .$.......

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
bTerminalLink            : 0x04
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 04 01 01 00                              .$.....

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
bEndpointAddress         : 0x82 (Direction=IN EndpointID=2)
bmAttributes             : 0x0D (TransferType=Isochronous  SyncType=Synchronous  EndpointType=Data)
wMaxPacketSize           : 0x00C0
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0xC0 (192 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 82 0D C0 00 04 00 00                        .........

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
bInterfaceNumber         : 0x04
bAlternateSetting        : 0x00
bNumEndpoints            : 0x02 (2 Endpoints)
bInterfaceClass          : 0x03 (HID - Human Interface Device)
bInterfaceSubClass       : 0x00 (None)
bInterfaceProtocol       : 0x00 (None)
iInterface               : 0x06 (String Descriptor 6)
 Language 0x0409         : "HID Interface"
Data (HexDump)           : 09 04 04 00 02 03 00 00 06                        .........

        ------------------- HID Descriptor --------------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x21 (HID Descriptor)
bcdHID                   : 0x0101 (HID Version 1.01)
bCountryCode             : 0x00 (00 = not localized)
bNumDescriptors          : 0x01
Data (HexDump)           : 09 21 01 01 00 01 22 23 00                        .!...."#.
Descriptor 1:
bDescriptorType          : 0x22 (Class=Report)
wDescriptorLength        : 0x0023 (35 bytes)
Error reading descriptor : ERROR_INVALID_PARAMETER (due to a obscure limitation of the Win32 USB API, see UsbTreeView.txt)

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x83 (Direction=IN EndpointID=3)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0400
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x400 (1024 bytes per packet)
bInterval                : 0x04 (4 ms)
Data (HexDump)           : 07 05 83 03 00 04 04                              .......

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x01 (Direction=OUT EndpointID=1)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0400
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x400 (1024 bytes per packet)
bInterval                : 0x04 (4 ms)
Data (HexDump)           : 07 05 01 03 00 04 04                              .......

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
wTotalLength             : 0x01FD (509 bytes)
bNumInterfaces           : 0x05 (5 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x00 (No String Descriptor)
bmAttributes             : 0xC0
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x01 (yes)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0x64 (200 mA)
Data (HexDump)           : 09 07 FD 01 05 01 00 C0 64 08 0B 00 02 0E 03 00   ........d.......
                           04 09 04 00 00 01 0E 01 00 04 0D 24 01 10 01 50   ...........$...P
                           00 00 6C DC 02 01 01 12 24 02 01 01 02 00 00 00   ..l.....$.......
                           00 00 00 00 00 03 2A 8A 02 0C 24 05 02 01 00 40   ......*...$....@
                           02 7F 14 00 00 1C 24 06 06 A2 9E 76 41 DE 04 47   ......$....vA..G
                           E3 8B 2B F4 34 1A FF 00 3B 0F 01 02 03 00 F8 27   ..+.4...;......'
                           00 09 24 03 03 01 01 00 04 00 07 05 81 03 10 00   ..$.............
                           08 05 25 03 10 00 09 04 01 00 00 0E 02 00 00 10   ..%.............
                           24 01 03 E2 00 88 00 03 02 01 01 01 00 04 00 1B   $...............
                           24 04 02 03 59 55 59 32 00 00 10 00 80 00 00 AA   $...YUY2........
                           00 38 9B 71 10 01 00 00 00 00 26 24 05 01 00 80   .8.q......&$....
                           02 68 01 00 40 19 01 00 C0 4B 03 00 08 07 00 80   .h..@....K......
                           1A 06 00 03 80 1A 06 00 2A 2C 0A 00 40 42 0F 00   ........*,..@B..
                           1E 24 05 02 00 20 03 58 02 00 00 C2 01 00 00 C2   .$... .X........
                           01 00 20 1C 00 15 16 05 00 01 15 16 05 00 0B 24   .. ............$
                           06 01 06 00 01 00 00 00 00 22 24 07 04 00 00 05   ........."$.....
                           D0 02 00 00 2F 0D 00 00 5E 1A 00 20 1C 00 15 16   ..../...^.. ....
                           05 00 02 15 16 05 00 2A 2C 0A 00 22 24 07 02 00   .......*,.."$...
                           00 05 C0 03 00 00 B8 0B 00 00 28 23 00 80 25 00   ..........(#..%.
                           15 16 05 00 01 15 16 05 00 2A 2C 0A 00 1E 24 07   .........*,...$.
                           01 00 80 07 38 04 00 80 53 3B 00 80 53 3B 00 48   ....8...S;..S;.H
                           3F 00 15 16 05 00 01 15 16 05 00 06 24 0D 01 01   ?...........$...
                           04 09 04 01 01 01 0E 02 00 00 07 05 88 05 FF 03   ................
                           01 08 0B 02 02 01 00 00 05 09 04 02 00 00 01 01   ................
                           00 05 09 24 01 00 01 27 00 01 03 0C 24 02 02 01   ...$...'....$...
                           02 00 02 03 00 00 00 09 24 03 04 01 01 00 06 00   ........$.......
                           09 24 06 06 02 02 03 00 00 09 04 03 00 00 01 02   .$..............
                           00 00 09 04 03 01 01 01 02 00 00 07 24 01 04 01   ............$...
                           01 00 0B 24 02 01 02 02 10 01 80 BB 00 09 05 82   ...$............
                           0D C0 00 04 00 00 07 25 01 01 01 01 00 09 04 04   .......%........
                           00 02 03 00 00 06 09 21 01 01 00 01 22 23 00 07   .......!...."#..
                           05 83 03 00 04 0A 07 05 01 03 00 04 0A            .............

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x00
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x04 (String Descriptor 4)
 Language 0x0409         : "Anker PowerConf C200"
Data (HexDump)           : 08 0B 00 02 0E 03 00 04                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x00
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x04 (String Descriptor 4)
 Language 0x0409         : "Anker PowerConf C200"
Data (HexDump)           : 09 04 00 00 01 0E 01 00 04                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0110 (UVC Version 1.10)
wTotalLength             : 0x0050 (80 bytes)
dwClockFreq              : 0x02DC6C00 (48 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x01
Data (HexDump)           : 0D 24 01 10 01 50 00 00 6C DC 02 01 01            .$...P..l....

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
bmControls               : 0x2A, 0x8A, 0x02
 D0                      : 0   no -  Scanning Mode
 D1                      : 1  yes -  Auto-Exposure Mode
 D2                      : 0   no -  Auto-Exposure Priority
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
 D13                     : 0   no -  Roll (Absolute)
 D14                     : 0   no -  Roll (Relative)
 D15                     : 1  yes -  Tilt (Absolute)
 D16                     : 0   no -  Tilt (Relative)
 D17                     : 1  yes -  Focus Auto
 D18                     : 0   no -  Reserved
 D19                     : 0   no -  Reserved
 D20                     : 0   no -  Reserved
 D21                     : 0   no -  Reserved
 D22                     : 0   no -  Reserved
 D23                     : 0   no -  Reserved
Data (HexDump)           : 12 24 02 01 01 02 00 00 00 00 00 00 00 00 03 2A   .$.............*
                           8A 02                                             ..

        -------- Video Control Processing Unit Descriptor -----
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x05 (Processing Unit)
bUnitID                  : 0x02
bSourceID                : 0x01
wMaxMultiplier           : 0x4000 (163.84x Zoom)
bControlSize             : 0x02
bmControls               : 0x7F, 0x14
 D0                      : 1  yes -  Brightness
 D1                      : 1  yes -  Contrast
 D2                      : 1  yes -  Hue
 D3                      : 1  yes -  Saturation
 D4                      : 1  yes -  Sharpness
 D5                      : 1  yes -  Gamma
 D6                      : 1  yes -  White Balance Temperature
 D7                      : 0   no -  White Balance Component
 D8                      : 0   no -  Backlight Compensation
 D9                      : 0   no -  Gain
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
Data (HexDump)           : 0C 24 05 02 01 00 40 02 7F 14 00 00               .$....@.....

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x06
guidExtensionCode        : {41769EA2-04DE-E347-8B2B-F4341AFF003B}
bNumControls             : 0x0F
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x03
bmControls               : 0x00, 0xF8, 0x27
 D0                      : 0   no -  Vendor-Specific (Optional)
 D1                      : 0   no -  Vendor-Specific (Optional)
 D2                      : 0   no -  Vendor-Specific (Optional)
 D3                      : 0   no -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
 D8                      : 0   no -  Vendor-Specific (Optional)
 D9                      : 0   no -  Vendor-Specific (Optional)
 D10                     : 0   no -  Vendor-Specific (Optional)
 D11                     : 1  yes -  Vendor-Specific (Optional)
 D12                     : 1  yes -  Vendor-Specific (Optional)
 D13                     : 1  yes -  Vendor-Specific (Optional)
 D14                     : 1  yes -  Vendor-Specific (Optional)
 D15                     : 1  yes -  Vendor-Specific (Optional)
 D16                     : 1  yes -  Vendor-Specific (Optional)
 D17                     : 1  yes -  Vendor-Specific (Optional)
 D18                     : 1  yes -  Vendor-Specific (Optional)
 D19                     : 0   no -  Vendor-Specific (Optional)
 D20                     : 0   no -  Vendor-Specific (Optional)
 D21                     : 1  yes -  Vendor-Specific (Optional)
 D22                     : 0   no -  Vendor-Specific (Optional)
 D23                     : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1C 24 06 06 A2 9E 76 41 DE 04 47 E3 8B 2B F4 34   .$....vA..G..+.4
                           1A FF 00 3B 0F 01 02 03 00 F8 27 00               ...;......'.

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x03
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x04
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 03 01 01 00 04 00                        .$.......

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
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 00 00 0E 02 00 00                        .........

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x10 (16 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x03
wTotalLength             : 0x00E2 (226 bytes)
bEndpointAddress         : 0x88 (Direction=IN  EndpointID=8)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x03
bStillCaptureMethod      : 0x02 (Still Capture Method 2)
nbTriggerSupport         : 0x01 (Hardware Triggering is supported)
bTriggerUsage            : 0x01 (Host will notify client application of button event)
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
Video Payload Format 3   : 0x00
 D0                      : 0   no -  Key Frame Rate
 D1                      : 0   no -  P Frame Rate
 D2                      : 0   no -  Compression Quality
 D3                      : 0   no -  Compression Window Size
 D4                      : 0   no -  Generate Key Frame
 D5                      : 0   no -  Update Frame Segment
 D6                      : 0   no -  Reserved
 D7                      : 0   no -  Reserved
Data (HexDump)           : 10 24 01 03 E2 00 88 00 03 02 01 01 01 00 04 00   .$..............

        ------- VS Uncompressed Format Type Descriptor --------
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x04 (Uncompressed Format Type)
bFormatIndex             : 0x02 (2)
bNumFrameDescriptors     : 0x03 (3)
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
*!*ERROR:  Found 2 frame descriptors (should be 3)
*!*ERROR:  no Color Matching Descriptor for this format
Data (HexDump)           : 1B 24 04 02 03 59 55 59 32 00 00 10 00 80 00 00   .$...YUY2.......
                           AA 00 38 9B 71 10 01 00 00 00 00                  ..8.q......

        -------- VS Uncompressed Frame Type Descriptor --------
---> This is the Default (optimum) Frame index
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxBitRate             : 0x034BC000 (55296000 bps -> 6.912 MB/s)
dwMaxVideoFrameBufferSize: 0x00070800 (460800 bytes)
dwDefaultFrameInterval   : 0x00061A80 (40.0000 ms -> 25.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[2]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[3]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
Data (HexDump)           : 26 24 05 01 00 80 02 68 01 00 40 19 01 00 C0 4B   &$.....h..@....K
                           03 00 08 07 00 80 1A 06 00 03 80 1A 06 00 2A 2C   ..............*,
                           0A 00 40 42 0F 00                                 ..@B..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0320 (800)
wHeight                  : 0x0258 (600)
dwMinBitRate             : 0x01C20000 (29491200 bps -> 3.686 MB/s)
dwMaxBitRate             : 0x01C20000 (29491200 bps -> 3.686 MB/s)
dwMaxVideoFrameBufferSize: 0x001C2000 (1843200 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 05 02 00 20 03 58 02 00 00 C2 01 00 00 C2   .$... .X........
                           01 00 20 1C 00 15 16 05 00 01 15 16 05 00         .. ...........

        ----- Video Streaming MJPEG Format Type Descriptor ----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x06 (Format MJPEG)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x06 (6)
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
*!*ERROR:  Found 3 frame descriptors (should be 6)
Data (HexDump)           : 0B 24 06 01 06 00 01 00 00 00 00                  .$.........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x0D2F0000 (221184000 bps -> 27.648 MB/s)
dwMaxBitRate             : 0x1A5E0000 (442368000 bps -> 55.296 MB/s)
dwMaxVideoFrameBufferSize: 0x001C2000 (1843200 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 22 24 07 04 00 00 05 D0 02 00 00 2F 0D 00 00 5E   "$........./...^
                           1A 00 20 1C 00 15 16 05 00 02 15 16 05 00 2A 2C   .. ...........*,
                           0A 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x03C0 (960)
dwMinBitRate             : 0x0BB80000 (196608000 bps -> 24.576 MB/s)
dwMaxBitRate             : 0x23280000 (589824000 bps -> 73.728 MB/s)
dwMaxVideoFrameBufferSize: 0x00258000 (2457600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
*!*ERROR:  bLength of 34 incorrect, should be 30
*!*WARNING:  if bFrameIntervalType is 1 then dwMinBitRate should equal dwMaxBitRate
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 22 24 07 02 00 00 05 C0 03 00 00 B8 0B 00 00 28   "$.............(
                           23 00 80 25 00 15 16 05 00 01 15 16 05 00 2A 2C   #..%..........*,
                           0A 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
---> This is the Default (optimum) Frame index
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x3B538000 (995328000 bps -> 124.416 MB/s)
dwMaxBitRate             : 0x3B538000 (995328000 bps -> 124.416 MB/s)
dwMaxVideoFrameBufferSize: 0x003F4800 (4147200 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
Data (HexDump)           : 1E 24 07 01 00 80 07 38 04 00 80 53 3B 00 80 53   .$.....8...S;..S
                           3B 00 48 3F 00 15 16 05 00 01 15 16 05 00         ;.H?..........

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
bEndpointAddress         : 0x88 (Direction=IN EndpointID=8)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x03FF
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x3FF (1023 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 88 05 FF 03 01                              .......

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x02
bInterfaceCount          : 0x02
bFunctionClass           : 0x01 (Audio)
bFunctionSubClass        : 0x00 (undefined)
bFunctionProtocol        : 0x00
iFunction                : 0x05 (String Descriptor 5)
 Language 0x0409         : "Anker PowerConf C200"
Data (HexDump)           : 08 0B 02 02 01 00 00 05                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x01 (Audio Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x05 (String Descriptor 5)
 Language 0x0409         : "Anker PowerConf C200"
Data (HexDump)           : 09 04 02 00 00 01 01 00 05                        .........

        ------ Audio Control Interface Header Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01 (Header)
bcdADC                   : 0x0100
wTotalLength             : 0x0027 (39 bytes)
bInCollection            : 0x01
baInterfaceNr[1]         : 0x03
Data (HexDump)           : 09 24 01 00 01 27 00 01 03                        .$...'...

        ------- Audio Control Input Terminal Descriptor -------
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Input Terminal)
bTerminalID              : 0x02
wTerminalType            : 0x0201 (Microphone)
bAssocTerminal           : 0x00
bNrChannels              : 0x02 (2 channels)
wChannelConfig           : 0x0003 (L, R)
iChannelNames            : 0x00 (No String Descriptor)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 0C 24 02 02 01 02 00 02 03 00 00 00               .$..........

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x04
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x00 (0)
bSourceID                : 0x06 (6)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 03 04 01 01 00 06 00                        .$.......

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x09 (9 bytes)
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
iFeature                 : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 06 06 02 02 03 00 00                        .$.......

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
bTerminalLink            : 0x04
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 04 01 01 00                              .$.....

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
bEndpointAddress         : 0x82 (Direction=IN EndpointID=2)
bmAttributes             : 0x0D (TransferType=Isochronous  SyncType=Synchronous  EndpointType=Data)
wMaxPacketSize           : 0x00C0
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0xC0 (192 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 82 0D C0 00 04 00 00                        .........

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
bInterfaceNumber         : 0x04
bAlternateSetting        : 0x00
bNumEndpoints            : 0x02 (2 Endpoints)
bInterfaceClass          : 0x03 (HID - Human Interface Device)
bInterfaceSubClass       : 0x00 (None)
bInterfaceProtocol       : 0x00 (None)
iInterface               : 0x06 (String Descriptor 6)
 Language 0x0409         : "HID Interface"
Data (HexDump)           : 09 04 04 00 02 03 00 00 06                        .........

        ------------------- HID Descriptor --------------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x21 (HID Descriptor)
bcdHID                   : 0x0101 (HID Version 1.01)
bCountryCode             : 0x00 (00 = not localized)
bNumDescriptors          : 0x01
Data (HexDump)           : 09 21 01 01 00 01 22 23 00                        .!...."#.
Descriptor 1:
bDescriptorType          : 0x22 (Class=Report)
wDescriptorLength        : 0x0023 (35 bytes)
Error reading descriptor : ERROR_INVALID_PARAMETER (due to a obscure limitation of the Win32 USB API, see UsbTreeView.txt)

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x83 (Direction=IN EndpointID=3)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0400
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x400 (1024 bytes per packet)
bInterval                : 0x0A (10 ms)
Data (HexDump)           : 07 05 83 03 00 04 0A                              .......

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x01 (Direction=OUT EndpointID=1)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0400
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x400 (1024 bytes per packet)
bInterval                : 0x0A (10 ms)
Data (HexDump)           : 07 05 01 03 00 04 0A                              .......

      -------------------- String Descriptors -------------------
             ------ String Descriptor 0 ------
bLength                  : 0x04 (4 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language ID[0]           : 0x0409 (English - United States)
Data (HexDump)           : 04 03 09 04                                       ....
             ------ String Descriptor 1 ------
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Anker PowerConf C200"
Data (HexDump)           : 2A 03 41 00 6E 00 6B 00 65 00 72 00 20 00 50 00   *.A.n.k.e.r. .P.
                           6F 00 77 00 65 00 72 00 43 00 6F 00 6E 00 66 00   o.w.e.r.C.o.n.f.
                           20 00 43 00 32 00 30 00 30 00                      .C.2.0.0.
             ------ String Descriptor 2 ------
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Anker PowerConf C200"
Data (HexDump)           : 2A 03 41 00 6E 00 6B 00 65 00 72 00 20 00 50 00   *.A.n.k.e.r. .P.
                           6F 00 77 00 65 00 72 00 43 00 6F 00 6E 00 66 00   o.w.e.r.C.o.n.f.
                           20 00 43 00 32 00 30 00 30 00                      .C.2.0.0.
             ------ String Descriptor 3 ------
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "ACNV9P0D12366611"
Data (HexDump)           : 22 03 41 00 43 00 4E 00 56 00 39 00 50 00 30 00   ".A.C.N.V.9.P.0.
                           44 00 31 00 32 00 33 00 36 00 36 00 36 00 31 00   D.1.2.3.6.6.6.1.
                           31 00                                             1.
             ------ String Descriptor 4 ------
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Anker PowerConf C200"
Data (HexDump)           : 2A 03 41 00 6E 00 6B 00 65 00 72 00 20 00 50 00   *.A.n.k.e.r. .P.
                           6F 00 77 00 65 00 72 00 43 00 6F 00 6E 00 66 00   o.w.e.r.C.o.n.f.
                           20 00 43 00 32 00 30 00 30 00                      .C.2.0.0.
             ------ String Descriptor 5 ------
bLength                  : 0x2A (42 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Anker PowerConf C200"
Data (HexDump)           : 2A 03 41 00 6E 00 6B 00 65 00 72 00 20 00 50 00   *.A.n.k.e.r. .P.
                           6F 00 77 00 65 00 72 00 43 00 6F 00 6E 00 66 00   o.w.e.r.C.o.n.f.
                           20 00 43 00 32 00 30 00 30 00                      .C.2.0.0.
             ------ String Descriptor 6 ------
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "HID Interface"
Data (HexDump)           : 1C 03 48 00 49 00 44 00 20 00 49 00 6E 00 74 00   ..H.I.D. .I.n.t.
                           65 00 72 00 66 00 61 00 63 00 65 00               e.r.f.a.c.e.
*/

namespace anker_powerconf_c200 {
const uint8_t dev_desc[] = {
    0x12, 0x01, 0x00, 0x02, 0xEF, 0x02, 0x01, 0x40, 0x1A, 0x29, 0x69, 0x33, 0x05, 0x01, 0x01, 0x02,
    0x03, 0x01
};

const uint8_t cfg_desc[] = {
    0x09, 0x02, 0x49, 0x03, 0x05, 0x01, 0x00, 0xC0, 0x64, 0x08, 0x0B, 0x00, 0x02, 0x0E, 0x03, 0x00,
    0x04, 0x09, 0x04, 0x00, 0x00, 0x01, 0x0E, 0x01, 0x00, 0x04, 0x0D, 0x24, 0x01, 0x10, 0x01, 0x50,
    0x00, 0x00, 0x6C, 0xDC, 0x02, 0x01, 0x01, 0x12, 0x24, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x2A, 0x8A, 0x02, 0x0C, 0x24, 0x05, 0x02, 0x01, 0x00, 0x40,
    0x02, 0x7F, 0x14, 0x00, 0x00, 0x1C, 0x24, 0x06, 0x06, 0xA2, 0x9E, 0x76, 0x41, 0xDE, 0x04, 0x47,
    0xE3, 0x8B, 0x2B, 0xF4, 0x34, 0x1A, 0xFF, 0x00, 0x3B, 0x0F, 0x01, 0x02, 0x03, 0x00, 0xF8, 0x27,
    0x00, 0x09, 0x24, 0x03, 0x03, 0x01, 0x01, 0x00, 0x04, 0x00, 0x07, 0x05, 0x81, 0x03, 0x10, 0x00,
    0x08, 0x05, 0x25, 0x03, 0x10, 0x00, 0x09, 0x04, 0x01, 0x00, 0x00, 0x0E, 0x02, 0x00, 0x00, 0x10,
    0x24, 0x01, 0x03, 0x2E, 0x02, 0x88, 0x00, 0x03, 0x02, 0x01, 0x01, 0x01, 0x00, 0x04, 0x00, 0x0B,
    0x24, 0x06, 0x01, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x24, 0x07, 0x01, 0x00, 0x00,
    0x0A, 0xA0, 0x05, 0x00, 0x00, 0x65, 0x04, 0x00, 0x00, 0x65, 0x04, 0x00, 0x80, 0x70, 0x00, 0x15,
    0x16, 0x05, 0x00, 0x01, 0x15, 0x16, 0x05, 0x00, 0x1E, 0x24, 0x07, 0x02, 0x00, 0x80, 0x07, 0x38,
    0x04, 0x00, 0xD0, 0x78, 0x02, 0x00, 0xD0, 0x78, 0x02, 0x00, 0x48, 0x3F, 0x00, 0x15, 0x16, 0x05,
    0x00, 0x01, 0x15, 0x16, 0x05, 0x00, 0x1E, 0x24, 0x07, 0x03, 0x00, 0x00, 0x05, 0xD0, 0x02, 0x00,
    0x40, 0x19, 0x01, 0x00, 0x40, 0x19, 0x01, 0x00, 0x20, 0x1C, 0x00, 0x15, 0x16, 0x05, 0x00, 0x01,
    0x15, 0x16, 0x05, 0x00, 0x1E, 0x24, 0x07, 0x04, 0x00, 0x80, 0x02, 0xE0, 0x01, 0x00, 0xC0, 0x5D,
    0x00, 0x00, 0xC0, 0x5D, 0x00, 0x00, 0x60, 0x09, 0x00, 0x15, 0x16, 0x05, 0x00, 0x01, 0x15, 0x16,
    0x05, 0x00, 0x1E, 0x24, 0x07, 0x05, 0x00, 0x80, 0x02, 0x68, 0x01, 0x00, 0x50, 0x46, 0x00, 0x00,
    0x50, 0x46, 0x00, 0x00, 0x08, 0x07, 0x00, 0x15, 0x16, 0x05, 0x00, 0x01, 0x15, 0x16, 0x05, 0x00,
    0x1E, 0x24, 0x07, 0x06, 0x00, 0x40, 0x01, 0xF0, 0x00, 0x00, 0x70, 0x17, 0x00, 0x00, 0x70, 0x17,
    0x00, 0x00, 0x58, 0x02, 0x00, 0x15, 0x16, 0x05, 0x00, 0x01, 0x15, 0x16, 0x05, 0x00, 0x0A, 0x24,
    0x03, 0x00, 0x01, 0x80, 0x07, 0x38, 0x04, 0x00, 0x1B, 0x24, 0x04, 0x02, 0x03, 0x59, 0x55, 0x59,
    0x32, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71, 0x10, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x1E, 0x24, 0x05, 0x01, 0x00, 0x80, 0x02, 0xE0, 0x01, 0x00, 0xC0, 0x5D, 0x00,
    0x00, 0xC0, 0x5D, 0x00, 0x00, 0x60, 0x09, 0x00, 0x15, 0x16, 0x05, 0x00, 0x01, 0x15, 0x16, 0x05,
    0x00, 0x1E, 0x24, 0x05, 0x02, 0x00, 0x80, 0x02, 0x68, 0x01, 0x00, 0x50, 0x46, 0x00, 0x00, 0x50,
    0x46, 0x00, 0x00, 0x08, 0x07, 0x00, 0x15, 0x16, 0x05, 0x00, 0x01, 0x15, 0x16, 0x05, 0x00, 0x1E,
    0x24, 0x05, 0x03, 0x00, 0x40, 0x01, 0xF0, 0x00, 0x00, 0x70, 0x17, 0x00, 0x00, 0x70, 0x17, 0x00,
    0x00, 0x58, 0x02, 0x00, 0x15, 0x16, 0x05, 0x00, 0x01, 0x15, 0x16, 0x05, 0x00, 0x0A, 0x24, 0x03,
    0x00, 0x01, 0x80, 0x07, 0x38, 0x04, 0x00, 0x1C, 0x24, 0x10, 0x03, 0x06, 0x48, 0x32, 0x36, 0x34,
    0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71, 0x10, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x1E, 0x24, 0x11, 0x01, 0x00, 0x00, 0x0A, 0xA0, 0x05, 0x00, 0x80, 0x32, 0x02,
    0x00, 0x80, 0x32, 0x02, 0x15, 0x16, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x15, 0x16, 0x05,
    0x00, 0x1E, 0x24, 0x11, 0x02, 0x00, 0x80, 0x07, 0x38, 0x04, 0x00, 0x68, 0x3C, 0x01, 0x00, 0x68,
    0x3C, 0x01, 0x15, 0x16, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x1E,
    0x24, 0x11, 0x03, 0x00, 0x00, 0x05, 0xD0, 0x02, 0x00, 0xA0, 0x8C, 0x00, 0x00, 0xA0, 0x8C, 0x00,
    0x15, 0x16, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x1E, 0x24, 0x11,
    0x04, 0x00, 0x80, 0x02, 0xE0, 0x01, 0x00, 0xE0, 0x2E, 0x00, 0x00, 0xE0, 0x2E, 0x00, 0x15, 0x16,
    0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x1E, 0x24, 0x11, 0x05, 0x00,
    0x80, 0x02, 0x68, 0x01, 0x00, 0x28, 0x23, 0x00, 0x00, 0x28, 0x23, 0x00, 0x15, 0x16, 0x05, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x1E, 0x24, 0x11, 0x06, 0x00, 0x40, 0x01,
    0xF0, 0x00, 0x00, 0xB8, 0x0B, 0x00, 0x00, 0xB8, 0x0B, 0x00, 0x15, 0x16, 0x05, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x24, 0x0D, 0x01, 0x01, 0x04, 0x09, 0x04, 0x01,
    0x01, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05, 0x88, 0x05, 0x00, 0x0C, 0x01, 0x08, 0x0B, 0x02,
    0x02, 0x01, 0x00, 0x00, 0x05, 0x09, 0x04, 0x02, 0x00, 0x00, 0x01, 0x01, 0x00, 0x05, 0x09, 0x24,
    0x01, 0x00, 0x01, 0x27, 0x00, 0x01, 0x03, 0x0C, 0x24, 0x02, 0x02, 0x01, 0x02, 0x00, 0x02, 0x03,
    0x00, 0x00, 0x00, 0x09, 0x24, 0x03, 0x04, 0x01, 0x01, 0x00, 0x06, 0x00, 0x09, 0x24, 0x06, 0x06,
    0x02, 0x02, 0x03, 0x00, 0x00, 0x09, 0x04, 0x03, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x09, 0x04,
    0x03, 0x01, 0x01, 0x01, 0x02, 0x00, 0x00, 0x07, 0x24, 0x01, 0x04, 0x01, 0x01, 0x00, 0x0B, 0x24,
    0x02, 0x01, 0x02, 0x02, 0x10, 0x01, 0x80, 0xBB, 0x00, 0x09, 0x05, 0x82, 0x0D, 0xC0, 0x00, 0x04,
    0x00, 0x00, 0x07, 0x25, 0x01, 0x01, 0x01, 0x01, 0x00, 0x09, 0x04, 0x04, 0x00, 0x02, 0x03, 0x00,
    0x00, 0x06, 0x09, 0x21, 0x01, 0x01, 0x00, 0x01, 0x22, 0x23, 0x00, 0x07, 0x05, 0x83, 0x03, 0x00,
    0x04, 0x04, 0x07, 0x05, 0x01, 0x03, 0x00, 0x04, 0x04
};
}
