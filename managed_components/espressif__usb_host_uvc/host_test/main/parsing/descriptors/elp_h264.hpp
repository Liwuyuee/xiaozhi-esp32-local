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
Device ID                : USB\VID_32E4&PID_9422\2020032801
Hardware IDs             : USB\VID_32E4&PID_9422&REV_0100 USB\VID_32E4&PID_9422
Driver KeyName           : {36fc9e60-c465-11cf-8056-444553540000}\0082 (GUID_DEVCLASS_USB)
Driver                   : \SystemRoot\System32\drivers\usbccgp.sys (Version: 10.0.19041.4474  Date: 2024-06-13)
Driver Inf               : C:\Windows\inf\usb.inf
Legacy BusType           : PNPBus
Class                    : USB
Class GUID               : {36fc9e60-c465-11cf-8056-444553540000} (GUID_DEVCLASS_USB)
Service                  : usbccgp
Enumerator               : USB
Location Info            : Port_#0006.Hub_#0013
Location IDs             : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(1)#USB(3)#USB(6), ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(1)#USB(3)#USB(6)
Container ID             : {068caf32-6f04-5def-b70f-1dfab2acdd8e}
Manufacturer Info        : (Standard USB Host Controller)
Capabilities             : 0x94 (Removable, UniqueID, SurpriseRemovalOK)
Status                   : 0x0180600A (DN_DRIVER_LOADED, DN_STARTED, DN_DISABLEABLE, DN_REMOVABLE, DN_NT_ENUMERATOR, DN_NT_DRIVER)
Problem Code             : 0
Address                  : 6
HcDisableSelectiveSuspend: 0
EnableSelectiveSuspend   : 0
SelectiveSuspendEnabled  : 0
EnhancedPowerMgmtEnabled : 0
IdleInWorkingState       : 0
WakeFromSleepState       : 0
Power State              : D0 (supported: D0, D3, wake from D0)
 Child Device 1          : USB Camera (USB Video Device)
  Device Path            : \\?\USB#VID_32E4&PID_9422&MI_00#b&149655b1&0&0000#{6994ad05-93ef-11d0-a3cc-00a0c9223196}\global (AM_KSCATEGORY_VIDEO)
  Kernel Name            : \Device\00000365
  Device ID              : USB\VID_32E4&PID_9422&MI_00\B&149655B1&0&0000
  Class                  : Camera
  Driver KeyName         : {ca3e7ab9-b4c3-4ae6-8251-579ef933890f}\0005 (GUID_DEVCLASS_CAMERA)
  Service                : usbvideo
  Location               : 0005.0000.0004.001.003.001.003.006.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(1)#USB(3)#USB(6)#USBMI(0)  PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(1)#USB(3)#USB(6)#USB(6)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(1)#USB(3)#USB(6)#USBMI(0)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(1)#USB(3)#USB(6)#USB(6)
 Child Device 2          : H264 USB Camera (USB Audio Device)
  Device Path            : \\?\USB#VID_32E4&PID_9422&MI_03#b&149655b1&0&0003#{6994ad04-93ef-11d0-a3cc-00a0c9223196}\global (AM_KSCATEGORY_AUDIO)
  Kernel Name            : \Device\00000366
  Device ID              : USB\VID_32E4&PID_9422&MI_03\B&149655B1&0&0003
  Class                  : MEDIA
  Driver KeyName         : {4d36e96c-e325-11ce-bfc1-08002be10318}\0008 (GUID_DEVCLASS_MEDIA)
  Service                : usbaudio
  Location               : 0005.0000.0004.001.003.001.003.006.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(1)#USB(3)#USB(6)#USBMI(3)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(1)#USB(3)#USB(6)#USBMI(3)
   Child Device 1        : Microphone (H264 USB Camera) (Audio Endpoint)
    Device ID            : SWD\MMDEVAPI\{0.0.1.00000000}.{BBBA02A7-B137-4252-B0CF-EF0F84C1D0B7}
    Class                : AudioEndpoint
    Driver KeyName       : {c166523c-fe0c-4a94-a586-f1a80cfbbf3e}\0037 (AUDIOENDPOINT_CLASS_UUID)

        +++++++++++++++++ Registry USB Flags +++++++++++++++++
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\usbflags\32E494220100
 osvc                    : REG_BINARY 00 00
 NewInterfaceUsage       : REG_DWORD 00000000 (0)

        ---------------- Connection Information ---------------
Connection Index         : 0x06 (Port 6)
Connection Status        : 0x01 (DeviceConnected)
Current Config Value     : 0x01 (Configuration 1)
Device Address           : 0x0F (15)
Is Hub                   : 0x00 (no)
Device Bus Speed         : 0x02 (High-Speed)
Number Of Open Pipes     : 0x01 (1 pipe to data endpoints)
Pipe[0]                  : EndpointID=3  Direction=IN   ScheduleOffset=0  Type=Interrupt
Data (HexDump)           : 06 00 00 00 12 01 00 02 EF 02 01 40 E4 32 22 94   ...........@.2".
                           00 01 02 01 03 01 01 02 00 0F 00 01 00 00 00 01   ................
                           00 00 00 07 05 83 03 10 00 06 00 00 00 00         ..............

        --------------- Connection Information V2 -------------
Connection Index         : 0x06 (6)
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
Data (HexDump)           : 06 00 00 00 10 00 00 00 03 00 00 00 00 00 00 00   ................

    ---------------------- Device Descriptor ----------------------
bLength                  : 0x12 (18 bytes)
bDescriptorType          : 0x01 (Device Descriptor)
bcdUSB                   : 0x200 (USB Version 2.00)
bDeviceClass             : 0xEF (Miscellaneous)
bDeviceSubClass          : 0x02
bDeviceProtocol          : 0x01 (IAD - Interface Association Descriptor)
bMaxPacketSize0          : 0x40 (64 bytes)
idVendor                 : 0x32E4 (Ailipu Technology Co., Ltd.)
idProduct                : 0x9422
bcdDevice                : 0x0100
iManufacturer            : 0x02 (String Descriptor 2)
 Language 0x0409         : "H264 USB Camera"
iProduct                 : 0x01 (String Descriptor 1)
 Language 0x0409         : "H264 USB Camera"
iSerialNumber            : 0x03 (String Descriptor 3)
 Language 0x0409         : "2020032801"
bNumConfigurations       : 0x01 (1 Configuration)
Data (HexDump)           : 12 01 00 02 EF 02 01 40 E4 32 22 94 00 01 02 01   .......@.2".....
                           03 01                                             ..

    ------------------ Configuration Descriptor -------------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x02 (Configuration Descriptor)
wTotalLength             : 0x0592 (1426 bytes)
bNumInterfaces           : 0x05 (5 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x00 (No String Descriptor)
bmAttributes             : 0x80
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x00 (no)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0xFA (500 mA)
Data (HexDump)           : 09 02 92 05 05 01 00 80 FA 08 0B 00 03 0E 03 00   ................
                           05 09 04 00 00 01 0E 01 00 05 0E 24 01 00 01 73   ...........$...s
                           00 C0 E1 E4 00 02 01 02 09 24 03 05 01 01 00 04   .........$......
                           00 1C 24 06 03 70 33 F0 28 11 63 2E 4A BA 2C 68   ..$..p3.(.c.J.,h
                           90 EB 33 40 16 18 01 02 03 FF FF FF 00 1A 24 06   ..3@..........$.
                           04 94 73 DF DD 3E 97 27 47 BE D9 04 ED 64 26 DC   ..s..>.'G....d&.
                           67 08 01 03 01 FF 00 12 24 02 01 01 02 00 00 00   g.......$.......
                           00 00 00 00 00 03 0E 20 00 0B 24 05 02 01 00 00   ....... ..$.....
                           02 7F 17 00 09 24 03 06 01 01 00 04 00 07 05 83   .....$..........
                           03 10 00 06 05 25 03 40 00 09 04 01 00 00 0E 02   .....%.@........
                           00 00 0F 24 01 02 47 02 81 00 05 00 00 00 01 00   ...$..G.........
                           00 0B 24 06 01 08 00 01 00 00 00 00 26 24 07 01   ..$.........&$..
                           00 80 07 38 04 00 C0 A9 1D 00 80 53 3B 4D 4A 3F   ...8.......S;MJ?
                           00 15 16 05 00 03 15 16 05 00 80 1A 06 00 2A 2C   ..............*,
                           0A 00 26 24 07 02 00 00 05 D0 02 00 00 2F 0D 00   ..&$........./..
                           00 5E 1A 4D 22 1C 00 15 16 05 00 03 15 16 05 00   .^.M"...........
                           80 1A 06 00 2A 2C 0A 00 26 24 07 03 00 20 03 58   ....*,..&$... .X
                           02 00 D0 DD 06 00 A0 BB 0D 4D A8 0E 00 15 16 05   .........M......
                           00 03 15 16 05 00 80 1A 06 00 2A 2C 0A 00 26 24   ..........*,..&$
                           07 04 00 80 02 E0 01 00 00 65 04 00 00 CA 08 4D   .........e.....M
                           62 09 00 15 16 05 00 03 15 16 05 00 80 1A 06 00   b...............
                           2A 2C 0A 00 26 24 07 05 00 80 02 68 01 00 C0 4B   *,..&$.....h...K
                           03 00 80 97 06 4D 0A 07 00 15 16 05 00 03 15 16   .....M..........
                           05 00 80 1A 06 00 2A 2C 0A 00 26 24 07 06 00 60   ......*,..&$...`
                           01 20 01 00 40 73 01 00 80 E6 02 4D 1A 03 00 15   . ..@s.....M....
                           16 05 00 03 15 16 05 00 80 1A 06 00 2A 2C 0A 00   ............*,..
                           26 24 07 07 00 40 01 F0 00 00 40 19 01 00 80 32   &$...@....@....2
                           02 4D 5A 02 00 15 16 05 00 03 15 16 05 00 80 1A   .MZ.............
                           06 00 2A 2C 0A 00 26 24 07 08 00 80 07 38 04 00   ..*,..&$.....8..
                           C0 A9 1D 00 80 53 3B 4D 4A 3F 00 15 16 05 00 03   .....S;MJ?......
                           15 16 05 00 80 1A 06 00 2A 2C 0A 00 1B 24 04 02   ........*,...$..
                           06 59 55 59 32 00 00 10 00 80 00 00 AA 00 38 9B   .YUY2.........8.
                           71 10 01 00 00 00 00 26 24 05 01 00 80 02 E0 01   q......&$.......
                           00 00 65 04 00 00 CA 08 00 60 09 00 15 16 05 00   ..e......`......
                           03 15 16 05 00 80 1A 06 00 2A 2C 0A 00 1E 24 05   .........*,...$.
                           02 00 20 03 58 02 00 D0 DD 06 00 D0 DD 06 00 A6   .. .X...........
                           0E 00 2A 2C 0A 00 01 2A 2C 0A 00 26 24 05 03 00   ..*,...*,..&$...
                           80 02 68 01 00 C0 4B 03 00 80 97 06 00 08 07 00   ..h...K.........
                           15 16 05 00 03 15 16 05 00 80 1A 06 00 2A 2C 0A   .............*,.
                           00 26 24 05 04 00 60 01 20 01 00 40 73 01 00 80   .&$...`. ..@s...
                           E6 02 00 18 03 00 15 16 05 00 03 15 16 05 00 80   ................
                           1A 06 00 2A 2C 0A 00 26 24 05 05 00 40 01 F0 00   ...*,..&$...@...
                           00 40 19 01 00 80 32 02 00 58 02 00 15 16 05 00   .@....2..X......
                           03 15 16 05 00 80 1A 06 00 2A 2C 0A 00 26 24 05   .........*,..&$.
                           06 00 80 02 E0 01 00 00 65 04 00 00 CA 08 00 60   ........e......`
                           09 00 15 16 05 00 03 15 16 05 00 80 1A 06 00 2A   ...............*
                           2C 0A 00 06 24 0D 01 01 04 09 04 01 01 01 0E 02   ,...$...........
                           00 00 07 05 81 05 80 00 01 09 04 01 02 01 0E 02   ................
                           00 00 07 05 81 05 00 01 01 09 04 01 03 01 0E 02   ................
                           00 00 07 05 81 05 20 03 01 09 04 01 04 01 0E 02   ...... .........
                           00 00 07 05 81 05 20 0B 01 09 04 01 05 01 0E 02   ...... .........
                           00 00 07 05 81 05 20 13 01 09 04 01 06 01 0E 02   ...... .........
                           00 00 07 05 81 05 00 14 01 09 04 02 00 00 0E 02   ................
                           00 00 0E 24 01 01 60 01 82 00 06 00 00 00 01 00   ...$..`.........
                           1C 24 10 01 08 48 32 36 34 00 00 10 00 80 00 00   .$...H264.......
                           AA 00 38 9B 71 10 01 00 00 00 00 01 26 24 11 01   ..8.q.......&$..
                           00 80 07 38 04 00 40 E3 09 00 80 C6 13 15 16 05   ...8..@.........
                           00 03 00 00 00 00 15 16 05 00 80 1A 06 00 2A 2C   ..............*,
                           0A 00 26 24 11 02 00 00 05 D0 02 00 00 65 04 00   ..&$.........e..
                           00 CA 08 15 16 05 00 03 00 00 00 00 15 16 05 00   ................
                           80 1A 06 00 2A 2C 0A 00 26 24 11 03 00 20 03 58   ....*,..&$... .X
                           02 00 F0 49 02 00 E0 93 04 15 16 05 00 03 00 00   ...I............
                           00 00 15 16 05 00 80 1A 06 00 2A 2C 0A 00 26 24   ..........*,..&$
                           11 04 00 80 02 E0 01 00 00 77 01 00 00 EE 02 15   .........w......
                           16 05 00 03 00 00 00 00 15 16 05 00 80 1A 06 00   ................
                           2A 2C 0A 00 26 24 11 05 00 80 02 68 01 00 40 19   *,..&$.....h..@.
                           01 00 80 32 02 15 16 05 00 03 00 00 00 00 15 16   ...2............
                           05 00 80 1A 06 00 2A 2C 0A 00 26 24 11 06 00 60   ......*,..&$...`
                           01 20 01 00 C0 7B 00 00 80 F7 00 15 16 05 00 03   . ...{..........
                           00 00 00 00 15 16 05 00 80 1A 06 00 2A 2C 0A 00   ............*,..
                           26 24 11 07 00 40 01 F0 00 00 C0 5D 00 00 80 BB   &$...@.....]....
                           00 15 16 05 00 03 00 00 00 00 15 16 05 00 80 1A   ................
                           06 00 2A 2C 0A 00 26 24 11 08 00 80 07 38 04 00   ..*,..&$.....8..
                           40 E3 09 00 80 C6 13 15 16 05 00 03 00 00 00 00   @...............
                           15 16 05 00 80 1A 06 00 2A 2C 0A 00 06 24 0D 01   ........*,...$..
                           01 04 09 04 02 01 01 0E 02 00 00 07 05 82 05 80   ................
                           00 01 09 04 02 02 01 0E 02 00 00 07 05 82 05 00   ................
                           01 01 09 04 02 03 01 0E 02 00 00 07 05 82 05 20   ...............
                           03 01 09 04 02 04 01 0E 02 00 00 07 05 82 05 20   ...............
                           0B 01 09 04 02 05 01 0E 02 00 00 07 05 82 05 20   ...............
                           13 01 09 04 02 06 01 0E 02 00 00 07 05 82 05 00   ................
                           14 01 08 0B 03 02 01 00 00 00 09 04 03 00 00 01   ................
                           01 00 00 09 24 01 00 01 29 00 01 04 0C 24 02 01   ....$...)....$..
                           01 02 00 01 00 00 00 00 0B 24 06 02 01 02 01 00   .........$......
                           02 00 00 09 24 03 03 01 01 00 02 00 09 04 04 00   ....$...........
                           00 01 02 00 00 09 04 04 01 01 01 02 00 00 07 24   ...............$
                           01 03 01 01 00 1D 24 02 01 01 02 10 07 40 1F 00   ......$......@..
                           11 2B 00 80 3E 00 22 56 00 C0 5D 00 44 AC 00 80   .+..>."V..].D...
                           BB 00 09 05 84 05 92 01 04 00 00 07 25 01 01 00   ............%...
                           92 01                                             ..

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x00
bInterfaceCount          : 0x03
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x05 (String Descriptor 5)
 Language 0x0409         : "USB Camera"
Data (HexDump)           : 08 0B 00 03 0E 03 00 05                           ........

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
 Language 0x0409         : "USB Camera"
Data (HexDump)           : 09 04 00 00 01 0E 01 00 05                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0E (14 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0100 (UVC Version 1.00)
wTotalLength             : 0x0073 (115 bytes)
dwClockFreq              : 0x00E4E1C0 (15 MHz)
bInCollection            : 0x02 (2 VideoStreaming interfaces)
baInterfaceNr[1]         : 0x01
baInterfaceNr[2]         : 0x02
Data (HexDump)           : 0E 24 01 00 01 73 00 C0 E1 E4 00 02 01 02         .$...s........

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

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x03
guidExtensionCode        : {28F03370-6311-4A2E-BA2C-6890EB334016}
bNumControls             : 0x18
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x02
bControlSize             : 0x03
bmControls               : 0xFF, 0xFF, 0xFF
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
 D18                     : 1  yes -  Vendor-Specific (Optional)
 D19                     : 1  yes -  Vendor-Specific (Optional)
 D20                     : 1  yes -  Vendor-Specific (Optional)
 D21                     : 1  yes -  Vendor-Specific (Optional)
 D22                     : 1  yes -  Vendor-Specific (Optional)
 D23                     : 1  yes -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1C 24 06 03 70 33 F0 28 11 63 2E 4A BA 2C 68 90   .$..p3.(.c.J.,h.
                           EB 33 40 16 18 01 02 03 FF FF FF 00               .3@.........

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x04
guidExtensionCode        : {DDDF7394-973E-4727-BED9-04ED6426DC67}
bNumControls             : 0x08
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x03
bControlSize             : 0x01
bmControls               : 0xFF
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 1  yes -  Vendor-Specific (Optional)
 D3                      : 1  yes -  Vendor-Specific (Optional)
 D4                      : 1  yes -  Vendor-Specific (Optional)
 D5                      : 1  yes -  Vendor-Specific (Optional)
 D6                      : 1  yes -  Vendor-Specific (Optional)
 D7                      : 1  yes -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1A 24 06 04 94 73 DF DD 3E 97 27 47 BE D9 04 ED   .$...s..>.'G....
                           64 26 DC 67 08 01 03 01 FF 00                     d&.g......

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
bmControls               : 0x0E, 0x20, 0x00
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
                           20 00                                              .

        -------- Video Control Processing Unit Descriptor -----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x05 (Processing Unit)
bUnitID                  : 0x02
bSourceID                : 0x01
wMaxMultiplier           : 0x0000
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
Data (HexDump)           : 0B 24 05 02 01 00 00 02 7F 17 00                  .$.........

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x06
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x04
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 06 01 01 00 04 00                        .$.......

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x83 (Direction=IN EndpointID=3)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x0010
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x10 (16 bytes per packet)
bInterval                : 0x06 (6 ms)
Data (HexDump)           : 07 05 83 03 10 00 06                              .......

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
wTotalLength             : 0x0247 (583 bytes)
bEndpointAddress         : 0x81 (Direction=IN  EndpointID=1)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x05
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
Data (HexDump)           : 0F 24 01 02 47 02 81 00 05 00 00 00 01 00 00      .$..G..........

        ----- Video Streaming MJPEG Format Type Descriptor ----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x06 (Format MJPEG)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x08 (8)
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
Data (HexDump)           : 0B 24 06 01 08 00 01 00 00 00 00                  .$.........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
---> This is the Default (optimum) Frame index
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x1DA9C000 (497664000 bps -> 62.208 MB/s)
dwMaxBitRate             : 0x3B538000 (995328000 bps -> 124.416 MB/s)
dwMaxVideoFrameBufferSize: 0x003F4A4D (4147789 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 01 00 80 07 38 04 00 C0 A9 1D 00 80 53   &$.....8.......S
                           3B 4D 4A 3F 00 15 16 05 00 03 15 16 05 00 80 1A   ;MJ?............
                           06 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x0D2F0000 (221184000 bps -> 27.648 MB/s)
dwMaxBitRate             : 0x1A5E0000 (442368000 bps -> 55.296 MB/s)
dwMaxVideoFrameBufferSize: 0x001C224D (1843789 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 02 00 00 05 D0 02 00 00 2F 0D 00 00 5E   &$........./...^
                           1A 4D 22 1C 00 15 16 05 00 03 15 16 05 00 80 1A   .M".............
                           06 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x0320 (800)
wHeight                  : 0x0258 (600)
dwMinBitRate             : 0x06DDD000 (115200000 bps -> 14.400 MB/s)
dwMaxBitRate             : 0x0DBBA000 (230400000 bps -> 28.800 MB/s)
dwMaxVideoFrameBufferSize: 0x000EA84D (960589 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 03 00 20 03 58 02 00 D0 DD 06 00 A0 BB   &$... .X........
                           0D 4D A8 0E 00 15 16 05 00 03 15 16 05 00 80 1A   .M..............
                           06 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x04650000 (73728000 bps -> 9.216 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x0009624D (614989 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 04 00 80 02 E0 01 00 00 65 04 00 00 CA   &$.........e....
                           08 4D 62 09 00 15 16 05 00 03 15 16 05 00 80 1A   .Mb.............
                           06 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x034BC000 (55296000 bps -> 6.912 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxVideoFrameBufferSize: 0x00070A4D (461389 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 05 00 80 02 68 01 00 C0 4B 03 00 80 97   &$.....h...K....
                           06 4D 0A 07 00 15 16 05 00 03 15 16 05 00 80 1A   .M..............
                           06 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0160 (352)
wHeight                  : 0x0120 (288)
dwMinBitRate             : 0x01734000 (24330240 bps -> 3.41 MB/s)
dwMaxBitRate             : 0x02E68000 (48660480 bps -> 6.82 MB/s)
dwMaxVideoFrameBufferSize: 0x00031A4D (203341 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 06 00 60 01 20 01 00 40 73 01 00 80 E6   &$...`. ..@s....
                           02 4D 1A 03 00 15 16 05 00 03 15 16 05 00 80 1A   .M..............
                           06 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x07
bmCapabilities           : 0x00
wWidth                   : 0x0140 (320)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwMaxVideoFrameBufferSize: 0x00025A4D (154189 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 07 00 40 01 F0 00 00 40 19 01 00 80 32   &$...@....@....2
                           02 4D 5A 02 00 15 16 05 00 03 15 16 05 00 80 1A   .MZ.............
                           06 00 2A 2C 0A 00                                 ..*,..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x08
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x1DA9C000 (497664000 bps -> 62.208 MB/s)
dwMaxBitRate             : 0x3B538000 (995328000 bps -> 124.416 MB/s)
dwMaxVideoFrameBufferSize: 0x003F4A4D (4147789 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 07 08 00 80 07 38 04 00 C0 A9 1D 00 80 53   &$.....8.......S
                           3B 4D 4A 3F 00 15 16 05 00 03 15 16 05 00 80 1A   ;MJ?............
                           06 00 2A 2C 0A 00                                 ..*,..

        ------- VS Uncompressed Format Type Descriptor --------
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x04 (Uncompressed Format Type)
bFormatIndex             : 0x02 (2)
bNumFrameDescriptors     : 0x06 (6)
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
Data (HexDump)           : 1B 24 04 02 06 59 55 59 32 00 00 10 00 80 00 00   .$...YUY2.......
                           AA 00 38 9B 71 10 01 00 00 00 00                  ..8.q......

        -------- VS Uncompressed Frame Type Descriptor --------
---> This is the Default (optimum) Frame index
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x04650000 (73728000 bps -> 9.216 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x00096000 (614400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 05 01 00 80 02 E0 01 00 00 65 04 00 00 CA   &$.........e....
                           08 00 60 09 00 15 16 05 00 03 15 16 05 00 80 1A   ..`.............
                           06 00 2A 2C 0A 00                                 ..*,..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0320 (800)
wHeight                  : 0x0258 (600)
dwMinBitRate             : 0x06DDD000 (115200000 bps -> 14.400 MB/s)
dwMaxBitRate             : 0x06DDD000 (115200000 bps -> 14.400 MB/s)
dwMaxVideoFrameBufferSize: 0x000EA600 (960000 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 1E 24 05 02 00 20 03 58 02 00 D0 DD 06 00 D0 DD   .$... .X........
                           06 00 A6 0E 00 2A 2C 0A 00 01 2A 2C 0A 00         .....*,...*,..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x034BC000 (55296000 bps -> 6.912 MB/s)
dwMaxBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxVideoFrameBufferSize: 0x00070800 (460800 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 05 03 00 80 02 68 01 00 C0 4B 03 00 80 97   &$.....h...K....
                           06 00 08 07 00 15 16 05 00 03 15 16 05 00 80 1A   ................
                           06 00 2A 2C 0A 00                                 ..*,..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0160 (352)
wHeight                  : 0x0120 (288)
dwMinBitRate             : 0x01734000 (24330240 bps -> 3.41 MB/s)
dwMaxBitRate             : 0x02E68000 (48660480 bps -> 6.82 MB/s)
dwMaxVideoFrameBufferSize: 0x00031800 (202752 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 05 04 00 60 01 20 01 00 40 73 01 00 80 E6   &$...`. ..@s....
                           02 00 18 03 00 15 16 05 00 03 15 16 05 00 80 1A   ................
                           06 00 2A 2C 0A 00                                 ..*,..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0140 (320)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwMaxVideoFrameBufferSize: 0x00025800 (153600 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 05 05 00 40 01 F0 00 00 40 19 01 00 80 32   &$...@....@....2
                           02 00 58 02 00 15 16 05 00 03 15 16 05 00 80 1A   ..X.............
                           06 00 2A 2C 0A 00                                 ..*,..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x04650000 (73728000 bps -> 9.216 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwMaxVideoFrameBufferSize: 0x00096000 (614400 bytes)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 05 06 00 80 02 E0 01 00 00 65 04 00 00 CA   &$.........e....
                           08 00 60 09 00 15 16 05 00 03 15 16 05 00 80 1A   ..`.............
                           06 00 2A 2C 0A 00                                 ..*,..

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
wMaxPacketSize           : 0x0080
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x80 (128 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 80 00 01                              .......

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
wMaxPacketSize           : 0x0100
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x100 (256 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 00 01 01                              .......

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
wMaxPacketSize           : 0x1320
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x02 (2 additional transactions per microframe -> allows 683..1024 bytes per packet)
 Bits 10..0              : 0x320 (800 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 20 13 01                              .... ..

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
wMaxPacketSize           : 0x1400
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x02 (2 additional transactions per microframe -> allows 683..1024 bytes per packet)
 Bits 10..0              : 0x400 (1024 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 81 05 00 14 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 02 00 00 0E 02 00 00                        .........

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x0E (14 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x01
wTotalLength             : 0x0160 (352 bytes)
bEndpointAddress         : 0x82 (Direction=IN  EndpointID=2)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x06
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
Data (HexDump)           : 0E 24 01 01 60 01 82 00 06 00 00 00 01 00         .$..`.........

        ---- VS Frame Based Payload Format Type Descriptor ----
*!*ERROR: This format is NOT ALLOWED for UVC 1.0 devices
bLength                  : 0x1C (28 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x10 (Frame Based Format Type)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x08 (8)
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
Data (HexDump)           : 1C 24 10 01 08 48 32 36 34 00 00 10 00 80 00 00   .$...H264.......
                           AA 00 38 9B 71 10 01 00 00 00 00 01               ..8.q.......

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x09E34000 (165888000 bps -> 20.736 MB/s)
dwMaxBitRate             : 0x13C68000 (331776000 bps -> 41.472 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 01 00 80 07 38 04 00 40 E3 09 00 80 C6   &$.....8..@.....
                           13 15 16 05 00 03 00 00 00 00 15 16 05 00 80 1A   ................
                           06 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x04650000 (73728000 bps -> 9.216 MB/s)
dwMaxBitRate             : 0x08CA0000 (147456000 bps -> 18.432 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 02 00 00 05 D0 02 00 00 65 04 00 00 CA   &$.........e....
                           08 15 16 05 00 03 00 00 00 00 15 16 05 00 80 1A   ................
                           06 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x00
wWidth                   : 0x0320 (800)
wHeight                  : 0x0258 (600)
dwMinBitRate             : 0x0249F000 (38400000 bps -> 4.800 MB/s)
dwMaxBitRate             : 0x0493E000 (76800000 bps -> 9.600 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 03 00 20 03 58 02 00 F0 49 02 00 E0 93   &$... .X...I....
                           04 15 16 05 00 03 00 00 00 00 15 16 05 00 80 1A   ................
                           06 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x01770000 (24576000 bps -> 3.72 MB/s)
dwMaxBitRate             : 0x02EE0000 (49152000 bps -> 6.144 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 04 00 80 02 E0 01 00 00 77 01 00 00 EE   &$.........w....
                           02 15 16 05 00 03 00 00 00 00 15 16 05 00 80 1A   ................
                           06 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0280 (640)
wHeight                  : 0x0168 (360)
dwMinBitRate             : 0x01194000 (18432000 bps -> 2.304 MB/s)
dwMaxBitRate             : 0x02328000 (36864000 bps -> 4.608 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 05 00 80 02 68 01 00 40 19 01 00 80 32   &$.....h..@....2
                           02 15 16 05 00 03 00 00 00 00 15 16 05 00 80 1A   ................
                           06 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
wWidth                   : 0x0160 (352)
wHeight                  : 0x0120 (288)
dwMinBitRate             : 0x007BC000 (8110080 bps -> 1.13 MB/s)
dwMaxBitRate             : 0x00F78000 (16220160 bps -> 2.27 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 06 00 60 01 20 01 00 C0 7B 00 00 80 F7   &$...`. ...{....
                           00 15 16 05 00 03 00 00 00 00 15 16 05 00 80 1A   ................
                           06 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x07
bmCapabilities           : 0x00
wWidth                   : 0x0140 (320)
wHeight                  : 0x00F0 (240)
dwMinBitRate             : 0x005DC000 (6144000 bps -> 768 KB/s)
dwMaxBitRate             : 0x00BB8000 (12288000 bps -> 1.536 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 07 00 40 01 F0 00 00 C0 5D 00 00 80 BB   &$...@.....]....
                           00 15 16 05 00 03 00 00 00 00 15 16 05 00 80 1A   ................
                           06 00 2A 2C 0A 00                                 ..*,..

        ----- VS Frame Based Payload Frame Type Descriptor ----
*!*ERROR  bDescriptorSubtype did not exist in UVC 1.0
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x11 (Frame Based Payload Frame Type)
bFrameIndex              : 0x08
bmCapabilities           : 0x00
wWidth                   : 0x0780 (1920)
wHeight                  : 0x0438 (1080)
dwMinBitRate             : 0x09E34000 (165888000 bps -> 20.736 MB/s)
dwMaxBitRate             : 0x13C68000 (331776000 bps -> 41.472 MB/s)
dwDefaultFrameInterval   : 0x00051615 (33.3333 ms -> 30.000 fps)
bFrameIntervalType       : 0x03 (3 discrete frame intervals supported)
dwBytesPerLine           : 0x00 (0 bytes)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 26 24 11 08 00 80 07 38 04 00 40 E3 09 00 80 C6   &$.....8..@.....
                           13 15 16 05 00 03 00 00 00 00 15 16 05 00 80 1A   ................
                           06 00 2A 2C 0A 00                                 ..*,..

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
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x01
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 02 01 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x82 (Direction=IN EndpointID=2)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0080
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x80 (128 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 82 05 80 00 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x02
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 02 02 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x82 (Direction=IN EndpointID=2)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0100
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x100 (256 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 82 05 00 01 01                              .......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x03
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 02 03 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x82 (Direction=IN EndpointID=2)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0320
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x320 (800 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 82 05 20 03 01                              .... ..

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x04
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 02 04 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x82 (Direction=IN EndpointID=2)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0B20
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x01 (1 additional transactions per microframe -> allows 513..1024 byte per packet)
 Bits 10..0              : 0x320 (800 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 82 05 20 0B 01                              .... ..

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x05
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 02 05 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x82 (Direction=IN EndpointID=2)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x1320
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x02 (2 additional transactions per microframe -> allows 683..1024 bytes per packet)
 Bits 10..0              : 0x320 (800 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 82 05 20 13 01                              .... ..

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x06
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 02 06 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x82 (Direction=IN EndpointID=2)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x1400
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x02 (2 additional transactions per microframe -> allows 683..1024 bytes per packet)
 Bits 10..0              : 0x400 (1024 bytes per packet)
bInterval                : 0x01 (1 ms)
Data (HexDump)           : 07 05 82 05 00 14 01                              .......

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x03
bInterfaceCount          : 0x02
bFunctionClass           : 0x01 (Audio)
bFunctionSubClass        : 0x00 (undefined)
bFunctionProtocol        : 0x00
iFunction                : 0x00 (No String Descriptor)
Data (HexDump)           : 08 0B 03 02 01 00 00 00                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x01 (Audio Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 03 00 00 01 01 00 00                        .........

        ------ Audio Control Interface Header Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01 (Header)
bcdADC                   : 0x0100
wTotalLength             : 0x0029 (41 bytes)
bInCollection            : 0x01
baInterfaceNr[1]         : 0x04
Data (HexDump)           : 09 24 01 00 01 29 00 01 04                        .$...)...

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

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x06 (Feature Unit)
bUnitID                  : 0x02 (2)
bSourceID                : 0x01 (1)
bControlSize             : 0x02 (2 bytes per control)
bmaControls[0]           : 0x01, 0x00
 D0: Mute                : 1
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
bmaControls[1]           : 0x02, 0x00
 D0: Mute                : 0
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
Data (HexDump)           : 0B 24 06 02 01 02 01 00 02 00 00                  .$.........

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x03
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x00 (0)
bSourceID                : 0x02 (2)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 03 03 01 01 00 02 00                        .$.......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x04
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 04 00 00 01 02 00 00                        .........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x04
bAlternateSetting        : 0x01
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x02 (Audio Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 04 01 01 01 02 00 00                        .........

        -------- Audio Streaming Interface Descriptor ---------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01
bTerminalLink            : 0x03
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 03 01 01 00                              .$.....

        ------- Audio Streaming Format Type Descriptor --------
bLength                  : 0x1D (29 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Format Type)
bFormatType              : 0x01 (FORMAT_TYPE_I)
bNrChannels              : 0x01 (1 channel)
bSubframeSize            : 0x02 (2 bytes per subframe)
bBitResolution           : 0x10 (16 bits per sample)
bSamFreqType             : 0x07 (supports 7 sample frequencies)
tSamFreq[1]              : 0x01F40 (8000 Hz)
tSamFreq[2]              : 0x02B11 (11025 Hz)
tSamFreq[3]              : 0x03E80 (16000 Hz)
tSamFreq[4]              : 0x05622 (22050 Hz)
tSamFreq[5]              : 0x05DC0 (24000 Hz)
tSamFreq[6]              : 0x0AC44 (44100 Hz)
tSamFreq[7]              : 0x0BB80 (48000 Hz)
Data (HexDump)           : 1D 24 02 01 01 02 10 07 40 1F 00 11 2B 00 80 3E   .$......@...+..>
                           00 22 56 00 C0 5D 00 44 AC 00 80 BB 00            ."V..].D.....

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x84 (Direction=IN EndpointID=4)
bmAttributes             : 0x05 (TransferType=Isochronous  SyncType=Asynchronous  EndpointType=Data)
wMaxPacketSize           : 0x0192
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x192 (402 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 84 05 92 01 04 00 00                        .........

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
wLockDelay               : 0x0192
Data (HexDump)           : 07 25 01 01 00 92 01                              .%.....

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
wTotalLength             : 0x0040 (64 bytes)
bNumInterfaces           : 0x01 (1 Interface)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x00 (No String Descriptor)
bmAttributes             : 0x80
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x00 (no)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0xFA (500 mA)
Data (HexDump)           : 09 07 40 00 01 01 00 80 FA 08 0B 00 01 0E 03 00   ..@.............
                           01 09 04 00 00 00 0E 01 00 01 0C 24 01 00 01 26   ...........$...&
                           00 80 8D 5B 00 00 09 24 03 05 01 01 00 02 00 11   ...[...$........
                           24 02 01 01 02 00 00 00 00 00 00 00 00 02 00 00   $...............

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x00
bInterfaceCount          : 0x01
*!*ERROR  bInterfaceCount must be greater than 1
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x01 (String Descriptor 1)
 Language 0x0409         : "H264 USB Camera"
Data (HexDump)           : 08 0B 00 01 0E 03 00 01                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x00
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x01 (String Descriptor 1)
 Language 0x0409         : "H264 USB Camera"
Data (HexDump)           : 09 04 00 00 00 0E 01 00 01                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0100 (UVC Version 1.00)
wTotalLength             : 0x0026 (38 bytes)
dwClockFreq              : 0x005B8D80 (6 MHz)
bInCollection            : 0x00 (0 VideoStreaming interface)
Data (HexDump)           : 0C 24 01 00 01 26 00 80 8D 5B 00 00               .$...&...[..

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x05
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x02
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 05 01 01 00 02 00                        .$.......

        -------- Video Control Input Terminal Descriptor ------
bLength                  : 0x11 (17 bytes)
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
bControlSize             : 0x02
bmControls               : 0x00, 0x00
 D0                      : 0   no -  Scanning Mode
 D1                      : 0   no -  Auto-Exposure Mode
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
Data (HexDump)           : 11 24 02 01 01 02 00 00 00 00 00 00 00 00 02 00   .$..............
                           00                                                .

      -------------------- String Descriptors -------------------
             ------ String Descriptor 0 ------
bLength                  : 0x04 (4 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language ID[0]           : 0x0409 (English - United States)
Data (HexDump)           : 04 03 09 04                                       ....
             ------ String Descriptor 1 ------
bLength                  : 0x20 (32 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "H264 USB Camera"
Data (HexDump)           : 20 03 48 00 32 00 36 00 34 00 20 00 55 00 53 00    .H.2.6.4. .U.S.
                           42 00 20 00 43 00 61 00 6D 00 65 00 72 00 61 00   B. .C.a.m.e.r.a.
             ------ String Descriptor 2 ------
bLength                  : 0x20 (32 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "H264 USB Camera"
Data (HexDump)           : 20 03 48 00 32 00 36 00 34 00 20 00 55 00 53 00    .H.2.6.4. .U.S.
                           42 00 20 00 43 00 61 00 6D 00 65 00 72 00 61 00   B. .C.a.m.e.r.a.
             ------ String Descriptor 3 ------
bLength                  : 0x16 (22 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "2020032801"
Data (HexDump)           : 16 03 32 00 30 00 32 00 30 00 30 00 33 00 32 00   ..2.0.2.0.0.3.2.
                           38 00 30 00 31 00                                 8.0.1.
             ------ String Descriptor 5 ------
bLength                  : 0x16 (22 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "USB Camera"
Data (HexDump)           : 16 03 55 00 53 00 42 00 20 00 43 00 61 00 6D 00   ..U.S.B. .C.a.m.
                           65 00 72 00 61 00                                 e.r.a.
*/

namespace elp_h264 {
const uint8_t dev_desc[] = {
    0x12, 0x01, 0x00, 0x02, 0xEF, 0x02, 0x01, 0x40, 0xE4, 0x32, 0x22, 0x94, 0x00, 0x01, 0x02, 0x01,
    0x03, 0x01
};
const uint8_t cfg_desc[] = {
    0x09, 0x02, 0x92, 0x05, 0x05, 0x01, 0x00, 0x80, 0xFA, 0x08, 0x0B, 0x00, 0x03, 0x0E, 0x03, 0x00,
    0x05, 0x09, 0x04, 0x00, 0x00, 0x01, 0x0E, 0x01, 0x00, 0x05, 0x0E, 0x24, 0x01, 0x00, 0x01, 0x73,
    0x00, 0xC0, 0xE1, 0xE4, 0x00, 0x02, 0x01, 0x02, 0x09, 0x24, 0x03, 0x05, 0x01, 0x01, 0x00, 0x04,
    0x00, 0x1C, 0x24, 0x06, 0x03, 0x70, 0x33, 0xF0, 0x28, 0x11, 0x63, 0x2E, 0x4A, 0xBA, 0x2C, 0x68,
    0x90, 0xEB, 0x33, 0x40, 0x16, 0x18, 0x01, 0x02, 0x03, 0xFF, 0xFF, 0xFF, 0x00, 0x1A, 0x24, 0x06,
    0x04, 0x94, 0x73, 0xDF, 0xDD, 0x3E, 0x97, 0x27, 0x47, 0xBE, 0xD9, 0x04, 0xED, 0x64, 0x26, 0xDC,
    0x67, 0x08, 0x01, 0x03, 0x01, 0xFF, 0x00, 0x12, 0x24, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0E, 0x20, 0x00, 0x0B, 0x24, 0x05, 0x02, 0x01, 0x00, 0x00,
    0x02, 0x7F, 0x17, 0x00, 0x09, 0x24, 0x03, 0x06, 0x01, 0x01, 0x00, 0x04, 0x00, 0x07, 0x05, 0x83,
    0x03, 0x10, 0x00, 0x06, 0x05, 0x25, 0x03, 0x40, 0x00, 0x09, 0x04, 0x01, 0x00, 0x00, 0x0E, 0x02,
    0x00, 0x00, 0x0F, 0x24, 0x01, 0x02, 0x47, 0x02, 0x81, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x0B, 0x24, 0x06, 0x01, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x26, 0x24, 0x07, 0x01,
    0x00, 0x80, 0x07, 0x38, 0x04, 0x00, 0xC0, 0xA9, 0x1D, 0x00, 0x80, 0x53, 0x3B, 0x4D, 0x4A, 0x3F,
    0x00, 0x15, 0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C,
    0x0A, 0x00, 0x26, 0x24, 0x07, 0x02, 0x00, 0x00, 0x05, 0xD0, 0x02, 0x00, 0x00, 0x2F, 0x0D, 0x00,
    0x00, 0x5E, 0x1A, 0x4D, 0x22, 0x1C, 0x00, 0x15, 0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00,
    0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x07, 0x03, 0x00, 0x20, 0x03, 0x58,
    0x02, 0x00, 0xD0, 0xDD, 0x06, 0x00, 0xA0, 0xBB, 0x0D, 0x4D, 0xA8, 0x0E, 0x00, 0x15, 0x16, 0x05,
    0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24,
    0x07, 0x04, 0x00, 0x80, 0x02, 0xE0, 0x01, 0x00, 0x00, 0x65, 0x04, 0x00, 0x00, 0xCA, 0x08, 0x4D,
    0x62, 0x09, 0x00, 0x15, 0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00,
    0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x07, 0x05, 0x00, 0x80, 0x02, 0x68, 0x01, 0x00, 0xC0, 0x4B,
    0x03, 0x00, 0x80, 0x97, 0x06, 0x4D, 0x0A, 0x07, 0x00, 0x15, 0x16, 0x05, 0x00, 0x03, 0x15, 0x16,
    0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x07, 0x06, 0x00, 0x60,
    0x01, 0x20, 0x01, 0x00, 0x40, 0x73, 0x01, 0x00, 0x80, 0xE6, 0x02, 0x4D, 0x1A, 0x03, 0x00, 0x15,
    0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00,
    0x26, 0x24, 0x07, 0x07, 0x00, 0x40, 0x01, 0xF0, 0x00, 0x00, 0x40, 0x19, 0x01, 0x00, 0x80, 0x32,
    0x02, 0x4D, 0x5A, 0x02, 0x00, 0x15, 0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A,
    0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x07, 0x08, 0x00, 0x80, 0x07, 0x38, 0x04, 0x00,
    0xC0, 0xA9, 0x1D, 0x00, 0x80, 0x53, 0x3B, 0x4D, 0x4A, 0x3F, 0x00, 0x15, 0x16, 0x05, 0x00, 0x03,
    0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x1B, 0x24, 0x04, 0x02,
    0x06, 0x59, 0x55, 0x59, 0x32, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B,
    0x71, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x26, 0x24, 0x05, 0x01, 0x00, 0x80, 0x02, 0xE0, 0x01,
    0x00, 0x00, 0x65, 0x04, 0x00, 0x00, 0xCA, 0x08, 0x00, 0x60, 0x09, 0x00, 0x15, 0x16, 0x05, 0x00,
    0x03, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x1E, 0x24, 0x05,
    0x02, 0x00, 0x20, 0x03, 0x58, 0x02, 0x00, 0xD0, 0xDD, 0x06, 0x00, 0xD0, 0xDD, 0x06, 0x00, 0xA6,
    0x0E, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x01, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x05, 0x03, 0x00,
    0x80, 0x02, 0x68, 0x01, 0x00, 0xC0, 0x4B, 0x03, 0x00, 0x80, 0x97, 0x06, 0x00, 0x08, 0x07, 0x00,
    0x15, 0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A,
    0x00, 0x26, 0x24, 0x05, 0x04, 0x00, 0x60, 0x01, 0x20, 0x01, 0x00, 0x40, 0x73, 0x01, 0x00, 0x80,
    0xE6, 0x02, 0x00, 0x18, 0x03, 0x00, 0x15, 0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x80,
    0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x05, 0x05, 0x00, 0x40, 0x01, 0xF0, 0x00,
    0x00, 0x40, 0x19, 0x01, 0x00, 0x80, 0x32, 0x02, 0x00, 0x58, 0x02, 0x00, 0x15, 0x16, 0x05, 0x00,
    0x03, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x05,
    0x06, 0x00, 0x80, 0x02, 0xE0, 0x01, 0x00, 0x00, 0x65, 0x04, 0x00, 0x00, 0xCA, 0x08, 0x00, 0x60,
    0x09, 0x00, 0x15, 0x16, 0x05, 0x00, 0x03, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x2A,
    0x2C, 0x0A, 0x00, 0x06, 0x24, 0x0D, 0x01, 0x01, 0x04, 0x09, 0x04, 0x01, 0x01, 0x01, 0x0E, 0x02,
    0x00, 0x00, 0x07, 0x05, 0x81, 0x05, 0x80, 0x00, 0x01, 0x09, 0x04, 0x01, 0x02, 0x01, 0x0E, 0x02,
    0x00, 0x00, 0x07, 0x05, 0x81, 0x05, 0x00, 0x01, 0x01, 0x09, 0x04, 0x01, 0x03, 0x01, 0x0E, 0x02,
    0x00, 0x00, 0x07, 0x05, 0x81, 0x05, 0x20, 0x03, 0x01, 0x09, 0x04, 0x01, 0x04, 0x01, 0x0E, 0x02,
    0x00, 0x00, 0x07, 0x05, 0x81, 0x05, 0x20, 0x0B, 0x01, 0x09, 0x04, 0x01, 0x05, 0x01, 0x0E, 0x02,
    0x00, 0x00, 0x07, 0x05, 0x81, 0x05, 0x20, 0x13, 0x01, 0x09, 0x04, 0x01, 0x06, 0x01, 0x0E, 0x02,
    0x00, 0x00, 0x07, 0x05, 0x81, 0x05, 0x00, 0x14, 0x01, 0x09, 0x04, 0x02, 0x00, 0x00, 0x0E, 0x02,
    0x00, 0x00, 0x0E, 0x24, 0x01, 0x01, 0x60, 0x01, 0x82, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x1C, 0x24, 0x10, 0x01, 0x08, 0x48, 0x32, 0x36, 0x34, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00,
    0xAA, 0x00, 0x38, 0x9B, 0x71, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x26, 0x24, 0x11, 0x01,
    0x00, 0x80, 0x07, 0x38, 0x04, 0x00, 0x40, 0xE3, 0x09, 0x00, 0x80, 0xC6, 0x13, 0x15, 0x16, 0x05,
    0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C,
    0x0A, 0x00, 0x26, 0x24, 0x11, 0x02, 0x00, 0x00, 0x05, 0xD0, 0x02, 0x00, 0x00, 0x65, 0x04, 0x00,
    0x00, 0xCA, 0x08, 0x15, 0x16, 0x05, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00,
    0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11, 0x03, 0x00, 0x20, 0x03, 0x58,
    0x02, 0x00, 0xF0, 0x49, 0x02, 0x00, 0xE0, 0x93, 0x04, 0x15, 0x16, 0x05, 0x00, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24,
    0x11, 0x04, 0x00, 0x80, 0x02, 0xE0, 0x01, 0x00, 0x00, 0x77, 0x01, 0x00, 0x00, 0xEE, 0x02, 0x15,
    0x16, 0x05, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00,
    0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11, 0x05, 0x00, 0x80, 0x02, 0x68, 0x01, 0x00, 0x40, 0x19,
    0x01, 0x00, 0x80, 0x32, 0x02, 0x15, 0x16, 0x05, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x15, 0x16,
    0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11, 0x06, 0x00, 0x60,
    0x01, 0x20, 0x01, 0x00, 0xC0, 0x7B, 0x00, 0x00, 0x80, 0xF7, 0x00, 0x15, 0x16, 0x05, 0x00, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00,
    0x26, 0x24, 0x11, 0x07, 0x00, 0x40, 0x01, 0xF0, 0x00, 0x00, 0xC0, 0x5D, 0x00, 0x00, 0x80, 0xBB,
    0x00, 0x15, 0x16, 0x05, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A,
    0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x26, 0x24, 0x11, 0x08, 0x00, 0x80, 0x07, 0x38, 0x04, 0x00,
    0x40, 0xE3, 0x09, 0x00, 0x80, 0xC6, 0x13, 0x15, 0x16, 0x05, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x06, 0x24, 0x0D, 0x01,
    0x01, 0x04, 0x09, 0x04, 0x02, 0x01, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05, 0x82, 0x05, 0x80,
    0x00, 0x01, 0x09, 0x04, 0x02, 0x02, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05, 0x82, 0x05, 0x00,
    0x01, 0x01, 0x09, 0x04, 0x02, 0x03, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05, 0x82, 0x05, 0x20,
    0x03, 0x01, 0x09, 0x04, 0x02, 0x04, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05, 0x82, 0x05, 0x20,
    0x0B, 0x01, 0x09, 0x04, 0x02, 0x05, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05, 0x82, 0x05, 0x20,
    0x13, 0x01, 0x09, 0x04, 0x02, 0x06, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05, 0x82, 0x05, 0x00,
    0x14, 0x01, 0x08, 0x0B, 0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x09, 0x04, 0x03, 0x00, 0x00, 0x01,
    0x01, 0x00, 0x00, 0x09, 0x24, 0x01, 0x00, 0x01, 0x29, 0x00, 0x01, 0x04, 0x0C, 0x24, 0x02, 0x01,
    0x01, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x24, 0x06, 0x02, 0x01, 0x02, 0x01, 0x00,
    0x02, 0x00, 0x00, 0x09, 0x24, 0x03, 0x03, 0x01, 0x01, 0x00, 0x02, 0x00, 0x09, 0x04, 0x04, 0x00,
    0x00, 0x01, 0x02, 0x00, 0x00, 0x09, 0x04, 0x04, 0x01, 0x01, 0x01, 0x02, 0x00, 0x00, 0x07, 0x24,
    0x01, 0x03, 0x01, 0x01, 0x00, 0x1D, 0x24, 0x02, 0x01, 0x01, 0x02, 0x10, 0x07, 0x40, 0x1F, 0x00,
    0x11, 0x2B, 0x00, 0x80, 0x3E, 0x00, 0x22, 0x56, 0x00, 0xC0, 0x5D, 0x00, 0x44, 0xAC, 0x00, 0x80,
    0xBB, 0x00, 0x09, 0x05, 0x84, 0x05, 0x92, 0x01, 0x04, 0x00, 0x00, 0x07, 0x25, 0x01, 0x01, 0x00,
    0x92, 0x01
};
}
