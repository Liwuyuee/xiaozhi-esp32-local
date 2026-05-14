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
Device ID                : USB\VID_349C&PID_3307\20210901000000
Hardware IDs             : USB\VID_349C&PID_3307&REV_0301 USB\VID_349C&PID_3307
Driver KeyName           : {36fc9e60-c465-11cf-8056-444553540000}\0047 (GUID_DEVCLASS_USB)
Driver                   : \SystemRoot\System32\drivers\usbccgp.sys (Version: 10.0.19041.4474  Date: 2024-06-13)
Driver Inf               : C:\Windows\inf\usb.inf
Legacy BusType           : PNPBus
Class                    : USB
Class GUID               : {36fc9e60-c465-11cf-8056-444553540000} (GUID_DEVCLASS_USB)
Service                  : usbccgp
Enumerator               : USB
Location Info            : Port_#0006.Hub_#0013
Location IDs             : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(1)#USB(3)#USB(6), ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(1)#USB(3)#USB(6)
Container ID             : {6120a654-188f-5ceb-accc-eaff9ba0b47c}
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
 Child Device 1          : HD video (USB Video Device)
  Device Path            : \\?\USB#VID_349C&PID_3307&MI_00#b&26a56595&0&0000#{6994ad05-93ef-11d0-a3cc-00a0c9223196}\global (AM_KSCATEGORY_VIDEO)
  Kernel Name            : \Device\0000035e
  Device ID              : USB\VID_349C&PID_3307&MI_00\B&26A56595&0&0000
  Class                  : Camera
  Driver KeyName         : {ca3e7ab9-b4c3-4ae6-8251-579ef933890f}\0004 (GUID_DEVCLASS_CAMERA)
  Service                : usbvideo
  Location               : 0005.0000.0004.001.003.001.003.006.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(1)#USB(3)#USB(6)#USBMI(0)  PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(1)#USB(3)#USB(6)#USB(6)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(1)#USB(3)#USB(6)#USBMI(0)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(1)#USB(3)#USB(6)#USB(6)
 Child Device 2          : HD audio (USB Audio Device)
  Device Path            : \\?\USB#VID_349C&PID_3307&MI_02#b&26a56595&0&0002#{6994ad04-93ef-11d0-a3cc-00a0c9223196}\global (AM_KSCATEGORY_AUDIO)
  Kernel Name            : \Device\0000035f
  Device ID              : USB\VID_349C&PID_3307&MI_02\B&26A56595&0&0002
  Class                  : MEDIA
  Driver KeyName         : {4d36e96c-e325-11ce-bfc1-08002be10318}\0006 (GUID_DEVCLASS_MEDIA)
  Service                : usbaudio
  Location               : 0005.0000.0004.001.003.001.003.006.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(1)#USB(3)#USB(6)#USBMI(2)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(1)#USB(3)#USB(6)#USBMI(2)
   Child Device 1        : Speakers (HD audio  ) (Audio Endpoint)
    Device ID            : SWD\MMDEVAPI\{0.0.0.00000000}.{1F0BF8E7-7F03-4A2C-9183-9B9B0979B4DF}
    Class                : AudioEndpoint
    Driver KeyName       : {c166523c-fe0c-4a94-a586-f1a80cfbbf3e}\0030 (AUDIOENDPOINT_CLASS_UUID)
   Child Device 2        : Microphone (HD audio  ) (Audio Endpoint)
    Device ID            : SWD\MMDEVAPI\{0.0.1.00000000}.{3EBDEB23-D5D6-4B4D-8EED-94904D2B527B}
    Class                : AudioEndpoint
    Driver KeyName       : {c166523c-fe0c-4a94-a586-f1a80cfbbf3e}\0036 (AUDIOENDPOINT_CLASS_UUID)

        +++++++++++++++++ Registry USB Flags +++++++++++++++++
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\usbflags\349C33070301
 osvc                    : REG_BINARY 00 00

        ---------------- Connection Information ---------------
Connection Index         : 0x06 (Port 6)
Connection Status        : 0x01 (DeviceConnected)
Current Config Value     : 0x01 (Configuration 1)
Device Address           : 0x0F (15)
Is Hub                   : 0x00 (no)
Device Bus Speed         : 0x01 (Full-Speed)
Number Of Open Pipes     : 0x02 (2 pipes to data endpoints)
Pipe[0]                  : EndpointID=4  Direction=IN   ScheduleOffset=0  Type=Interrupt
Pipe[1]                  : EndpointID=1  Direction=IN   ScheduleOffset=0  Type=Bulk
Data (HexDump)           : 06 00 00 00 12 01 00 02 EF 02 01 40 9C 34 07 33   ...........@.4.3
                           01 03 01 02 03 01 01 01 00 0F 00 02 00 00 00 01   ................
                           00 00 00 07 05 84 03 0A 00 05 00 00 00 00 07 05   ................
                           81 02 40 00 00 00 00 00 00                        ..@......

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
idVendor                 : 0x349C
idProduct                : 0x3307
bcdDevice                : 0x0301
iManufacturer            : 0x01 (String Descriptor 1)
 Language 0x0409         : "Generic"
iProduct                 : 0x02 (String Descriptor 2)
 Language 0x0409         : "HD video  "
iSerialNumber            : 0x03 (String Descriptor 3)
 Language 0x0409         : "20210901000000"
bNumConfigurations       : 0x01 (1 Configuration)
Data (HexDump)           : 12 01 00 02 EF 02 01 40 9C 34 07 33 01 03 01 02   .......@.4.3....
                           03 01                                             ..

    ------------------ Configuration Descriptor -------------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x02 (Configuration Descriptor)
wTotalLength             : 0x01E4 (484 bytes)
bNumInterfaces           : 0x05 (5 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x00 (No String Descriptor)
bmAttributes             : 0x80
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x00 (no)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0x80 (256 mA)
Data (HexDump)           : 09 02 E4 01 05 01 00 80 80 08 0B 00 02 0E 03 00   ................
                           02 09 04 00 00 01 0E 01 00 02 0D 24 01 00 01 33   ...........$...3
                           00 00 36 6E 01 01 01 12 24 02 01 01 02 00 00 00   ..6n....$.......
                           00 00 00 00 00 03 00 00 00 0B 24 05 02 01 00 00   ..........$.....
                           02 7F 17 00 09 24 03 03 01 01 00 02 00 07 05 84   .....$..........
                           03 0A 00 05 05 25 03 40 00 09 04 01 00 01 0E 02   .....%.@........
                           00 00 07 05 81 02 40 00 00 0E 24 01 01 BD 00 81   ......@...$.....
                           00 03 02 01 00 01 00 0B 24 06 01 04 01 01 00 00   ........$.......
                           00 00 22 24 07 01 01 00 05 D0 02 00 80 97 06 00   .."$............
                           00 2F 0D 00 20 1C 00 2A 2C 0A 00 02 2A 2C 0A 00   ./.. ..*,...*,..
                           40 42 0F 00 22 24 07 02 01 20 03 E0 01 00 80 A9   @B.."$... ......
                           03 00 00 53 07 00 B8 0B 00 20 A1 07 00 02 20 A1   ...S..... .... .
                           07 00 2A 2C 0A 00 22 24 07 03 01 80 02 E0 01 00   ..*,.."$........
                           80 A9 03 00 00 53 07 00 60 09 00 80 1A 06 00 02   .....S..`.......
                           80 1A 06 00 2A 2C 0A 00 22 24 07 04 01 E0 01 40   ....*,.."$.....@
                           01 00 C0 D4 01 00 80 A9 03 00 B0 04 00 80 1A 06   ................
                           00 02 80 1A 06 00 2A 2C 0A 00 16 24 03 00 04 00   ......*,...$....
                           05 D0 02 20 03 E0 01 80 02 E0 01 E0 01 40 01 00   ... .........@..
                           06 24 0D 01 01 04 08 0B 02 03 01 00 00 04 09 04   .$..............
                           02 00 00 01 01 00 04 0A 24 01 00 01 45 00 02 03   ........$...E...
                           04 0C 24 02 04 01 02 00 01 01 00 00 00 08 24 06   ..$...........$.
                           05 04 01 03 00 09 24 03 06 01 01 00 05 00 0C 24   ......$........$
                           02 07 01 01 00 01 01 00 00 00 09 24 06 08 07 01   ...........$....
                           01 02 00 09 24 03 09 01 03 07 08 00 09 04 03 00   ....$...........
                           00 01 02 00 00 09 04 03 01 01 01 02 00 00 07 24   ...............$
                           01 06 01 01 00 0B 24 02 01 01 02 10 01 80 3E 00   ......$.......>.
                           09 05 82 0D 64 00 01 00 00 07 25 01 01 00 00 00   ....d.....%.....
                           09 04 04 00 00 01 02 00 00 09 04 04 01 01 01 02   ................
                           00 00 07 24 01 07 01 01 00 0B 24 02 01 01 02 10   ...$......$.....
                           01 80 3E 00 09 05 03 09 64 00 01 00 00 07 25 01   ..>.....d.....%.
                           01 01 01 00                                       ....

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x00
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x02 (String Descriptor 2)
 Language 0x0409         : "HD video  "
Data (HexDump)           : 08 0B 00 02 0E 03 00 02                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x00
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x02 (String Descriptor 2)
 Language 0x0409         : "HD video  "
Data (HexDump)           : 09 04 00 00 01 0E 01 00 02                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0100 (UVC Version 1.00)
wTotalLength             : 0x0033 (51 bytes)
dwClockFreq              : 0x016E3600 (24 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x01
Data (HexDump)           : 0D 24 01 00 01 33 00 00 36 6E 01 01 01            .$...3..6n...

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
bmControls               : 0x00, 0x00, 0x00
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
 D16                     : 0   no -  Tilt (Relative)
 D17                     : 0   no -  Focus Auto
 D18                     : 0   no -  Reserved
 D19                     : 0   no -  Reserved
 D20                     : 0   no -  Reserved
 D21                     : 0   no -  Reserved
 D22                     : 0   no -  Reserved
 D23                     : 0   no -  Reserved
Data (HexDump)           : 12 24 02 01 01 02 00 00 00 00 00 00 00 00 03 00   .$..............
                           00 00                                             ..

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
bTerminalID              : 0x03
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x02
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 03 01 01 00 02 00                        .$.......

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x84 (Direction=IN EndpointID=4)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x000A (10 bytes)
bInterval                : 0x05 (5 ms)
Data (HexDump)           : 07 05 84 03 0A 00 05                              .......

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
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 00 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x02 (TransferType=Bulk)
wMaxPacketSize           : 0x0040 (64 bytes)
bInterval                : 0x00 (ignored)
Data (HexDump)           : 07 05 81 02 40 00 00                              ....@..

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x0E (14 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x01
wTotalLength             : 0x00BD (189 bytes)
bEndpointAddress         : 0x81 (Direction=IN  EndpointID=1)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x03
bStillCaptureMethod      : 0x02 (Still Capture Method 2)
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
Data (HexDump)           : 0E 24 01 01 BD 00 81 00 03 02 01 00 01 00         .$............

        ----- Video Streaming MJPEG Format Type Descriptor ----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x06 (Format MJPEG)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x04 (4)
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
Data (HexDump)           : 0B 24 06 01 04 01 01 00 00 00 00                  .$.........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
---> This is the Default (optimum) Frame index
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x01
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxBitRate             : 0x0D2F0000 (221184000 bps -> 27.648 MB/s)
dwMaxVideoFrameBufferSize: 0x001C2000 (1843200 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[2]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
Data (HexDump)           : 22 24 07 01 01 00 05 D0 02 00 80 97 06 00 00 2F   "$............./
                           0D 00 20 1C 00 2A 2C 0A 00 02 2A 2C 0A 00 40 42   .. ..*,...*,..@B
                           0F 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x01
wWidth                   : 0x0320 (800)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x03A98000 (61440000 bps -> 7.680 MB/s)
dwMaxBitRate             : 0x07530000 (122880000 bps -> 15.360 MB/s)
dwMaxVideoFrameBufferSize: 0x000BB800 (768000 bytes)
dwDefaultFrameInterval   : 0x0007A120 (50.0000 ms -> 20.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[2]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 22 24 07 02 01 20 03 E0 01 00 80 A9 03 00 00 53   "$... .........S
                           07 00 B8 0B 00 20 A1 07 00 02 20 A1 07 00 2A 2C   ..... .... ...*,
                           0A 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x01
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x03A98000 (61440000 bps -> 7.680 MB/s)
dwMaxBitRate             : 0x07530000 (122880000 bps -> 15.360 MB/s)
dwMaxVideoFrameBufferSize: 0x00096000 (614400 bytes)
dwDefaultFrameInterval   : 0x00061A80 (40.0000 ms -> 25.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[2]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 22 24 07 03 01 80 02 E0 01 00 80 A9 03 00 00 53   "$.............S
                           07 00 60 09 00 80 1A 06 00 02 80 1A 06 00 2A 2C   ..`...........*,
                           0A 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x01
wWidth                   : 0x01E0 (480)
wHeight                  : 0x0140 (320)
dwMinBitRate             : 0x01D4C000 (30720000 bps -> 3.840 MB/s)
dwMaxBitRate             : 0x03A98000 (61440000 bps -> 7.680 MB/s)
dwMaxVideoFrameBufferSize: 0x0004B000 (307200 bytes)
dwDefaultFrameInterval   : 0x00061A80 (40.0000 ms -> 25.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[2]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 22 24 07 04 01 E0 01 40 01 00 C0 D4 01 00 80 A9   "$.....@........
                           03 00 B0 04 00 80 1A 06 00 02 80 1A 06 00 2A 2C   ..............*,
                           0A 00                                             ..

        ---------- Still Image Frame Type Descriptor ----------
bLength                  : 0x16 (22 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x03 (Still Image Frame Type)
bEndpointAddress         : 0x00 (no endpoint)
bNumImageSizePatterns    : 0x04 (4 Image Size Patterns)
1: wWidth x wHeight      : 0x0500 x 0x02D0 (1280 x 720)
2: wWidth x wHeight      : 0x0320 x 0x01E0 (800 x 480)
3: wWidth x wHeight      : 0x0280 x 0x01E0 (640 x 480)
4: wWidth x wHeight      : 0x01E0 x 0x0140 (480 x 320)
bNumCompressionPattern   : 0x00
Data (HexDump)           : 16 24 03 00 04 00 05 D0 02 20 03 E0 01 80 02 E0   .$....... ......
                           01 E0 01 40 01 00                                 ...@..

        ------- VS Color Matching Descriptor Descriptor -------
bLength                  : 0x06 (6 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x0D (Color Matching)
bColorPrimaries          : 0x01 (BT.709, sRGB)
bTransferCharacteristics : 0x01 (BT.709)
bMatrixCoefficients      : 0x04 (SMPTE 170M)
Data (HexDump)           : 06 24 0D 01 01 04                                 .$....

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x02
bInterfaceCount          : 0x03
bFunctionClass           : 0x01 (Audio)
bFunctionSubClass        : 0x00 (undefined)
bFunctionProtocol        : 0x00
iFunction                : 0x04 (String Descriptor 4)
 Language 0x0409         : "HD audio  "
Data (HexDump)           : 08 0B 02 03 01 00 00 04                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x01 (Audio Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x04 (String Descriptor 4)
 Language 0x0409         : "HD audio  "
Data (HexDump)           : 09 04 02 00 00 01 01 00 04                        .........

        ------ Audio Control Interface Header Descriptor ------
bLength                  : 0x0A (10 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01 (Header)
bcdADC                   : 0x0100
wTotalLength             : 0x0045 (69 bytes)
bInCollection            : 0x02
baInterfaceNr[1]         : 0x03
baInterfaceNr[2]         : 0x04
Data (HexDump)           : 0A 24 01 00 01 45 00 02 03 04                     .$...E....

        ------- Audio Control Input Terminal Descriptor -------
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Input Terminal)
bTerminalID              : 0x04
wTerminalType            : 0x0201 (Microphone)
bAssocTerminal           : 0x00
bNrChannels              : 0x01 (1 channel)
wChannelConfig           : 0x0001 (L)
iChannelNames            : 0x00 (No String Descriptor)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 0C 24 02 04 01 02 00 01 01 00 00 00               .$..........

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x06 (Feature Unit)
bUnitID                  : 0x05 (5)
bSourceID                : 0x04 (4)
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
Data (HexDump)           : 08 24 06 05 04 01 03 00                           .$......

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x06
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x00 (0)
bSourceID                : 0x05 (5)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 03 06 01 01 00 05 00                        .$.......

        ------- Audio Control Input Terminal Descriptor -------
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Input Terminal)
bTerminalID              : 0x07
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x00
bNrChannels              : 0x01 (1 channel)
wChannelConfig           : 0x0001 (L)
iChannelNames            : 0x00 (No String Descriptor)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 0C 24 02 07 01 01 00 01 01 00 00 00               .$..........

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x06 (Feature Unit)
bUnitID                  : 0x08 (8)
bSourceID                : 0x07 (7)
bControlSize             : 0x01 (1 byte per control)
bmaControls[0]           : 0x01
 D0: Mute                : 1
 D1: Volume              : 0
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
bmaControls[1]           : 0x02
 D0: Mute                : 0
 D1: Volume              : 1
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
iFeature                 : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 06 08 07 01 01 02 00                        .$.......

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x09
wTerminalType            : 0x0301 (Speaker)
bAssocTerminal           : 0x07 (7)
bSourceID                : 0x08 (8)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 03 09 01 03 07 08 00                        .$.......

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
bTerminalLink            : 0x06
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 06 01 01 00                              .$.....

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
bEndpointAddress         : 0x82 (Direction=IN EndpointID=2)
bmAttributes             : 0x0D (TransferType=Isochronous  SyncType=Synchronous  EndpointType=Data)
wMaxPacketSize           : 0x0064 (100 bytes)
bInterval                : 0x01 (1 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 82 0D 64 00 01 00 00                        ....d....

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
bTerminalLink            : 0x07
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 07 01 01 00                              .$.....

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
bEndpointAddress         : 0x03 (Direction=OUT EndpointID=3)
bmAttributes             : 0x09 (TransferType=Isochronous  SyncType=Adaptive  EndpointType=Data)
wMaxPacketSize           : 0x0064 (100 bytes)
bInterval                : 0x01 (1 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 03 09 64 00 01 00 00                        ....d....

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

    ----------------- Device Qualifier Descriptor -----------------
bLength                  : 0x0A (10 bytes)
bDescriptorType          : 0x06 (Device_qualifier Descriptor)
bcdUSB                   : 0x200 (USB Version 2.00)
bDeviceClass             : 0x00 (defined by the interface descriptors)
bDeviceSubClass          : 0x00
bDeviceProtocol          : 0x00
bMaxPacketSize0          : 0x40 (64 Bytes)
bNumConfigurations       : 0x01 (1 other-speed configuration)
bReserved                : 0x00
Data (HexDump)           : 0A 06 00 02 00 00 00 40 01 00                     .......@..

    ------------ Other Speed Configuration Descriptor -------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x07 (Other_speed_configuration Descriptor)
wTotalLength             : 0x01E4 (484 bytes)
bNumInterfaces           : 0x05 (5 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x00 (No String Descriptor)
bmAttributes             : 0x80
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x00 (no)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0x80 (256 mA)
Data (HexDump)           : 09 07 E4 01 05 01 00 80 80 08 0B 00 02 0E 03 00   ................
                           02 09 04 00 00 01 0E 01 00 02 0D 24 01 00 01 33   ...........$...3
                           00 00 36 6E 01 01 01 12 24 02 01 01 02 00 00 00   ..6n....$.......
                           00 00 00 00 00 03 00 00 00 0B 24 05 02 01 00 00   ..........$.....
                           02 7F 17 00 09 24 03 03 01 01 00 02 00 07 05 84   .....$..........
                           03 0A 00 05 05 25 03 40 00 09 04 01 00 01 0E 02   .....%.@........
                           00 00 07 05 81 02 40 00 00 0E 24 01 01 BD 00 81   ......@...$.....
                           00 03 02 01 00 01 00 0B 24 06 01 04 01 01 00 00   ........$.......
                           00 00 22 24 07 01 01 00 05 D0 02 00 80 97 06 00   .."$............
                           00 2F 0D 00 20 1C 00 2A 2C 0A 00 02 2A 2C 0A 00   ./.. ..*,...*,..
                           40 42 0F 00 22 24 07 02 01 20 03 E0 01 00 80 A9   @B.."$... ......
                           03 00 00 53 07 00 B8 0B 00 20 A1 07 00 02 20 A1   ...S..... .... .
                           07 00 2A 2C 0A 00 22 24 07 03 01 80 02 E0 01 00   ..*,.."$........
                           80 A9 03 00 00 53 07 00 60 09 00 80 1A 06 00 02   .....S..`.......
                           80 1A 06 00 2A 2C 0A 00 22 24 07 04 01 E0 01 40   ....*,.."$.....@
                           01 00 C0 D4 01 00 80 A9 03 00 B0 04 00 80 1A 06   ................
                           00 02 80 1A 06 00 2A 2C 0A 00 16 24 03 00 04 00   ......*,...$....
                           05 D0 02 20 03 E0 01 80 02 E0 01 E0 01 40 01 00   ... .........@..
                           06 24 0D 01 01 04 08 0B 02 03 01 00 00 04 09 04   .$..............
                           02 00 00 01 01 00 04 0A 24 01 00 01 45 00 02 03   ........$...E...
                           04 0C 24 02 04 01 02 00 01 01 00 00 00 08 24 06   ..$...........$.
                           05 04 01 03 00 09 24 03 06 01 01 00 05 00 0C 24   ......$........$
                           02 07 01 01 00 01 01 00 00 00 09 24 06 08 07 01   ...........$....
                           01 02 00 09 24 03 09 01 03 07 08 00 09 04 03 00   ....$...........
                           00 01 02 00 00 09 04 03 01 01 01 02 00 00 07 24   ...............$
                           01 06 01 01 00 0B 24 02 01 01 02 10 01 80 3E 00   ......$.......>.
                           09 05 82 0D 64 00 01 00 00 07 25 01 01 00 00 00   ....d.....%.....
                           09 04 04 00 00 01 02 00 00 09 04 04 01 01 01 02   ................
                           00 00 07 24 01 07 01 01 00 0B 24 02 01 01 02 10   ...$......$.....
                           01 80 3E 00 09 05 03 09 64 00 01 00 00 07 25 01   ..>.....d.....%.
                           01 01 01 00                                       ....

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x00
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x02 (String Descriptor 2)
 Language 0x0409         : "HD video  "
Data (HexDump)           : 08 0B 00 02 0E 03 00 02                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x00
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x02 (String Descriptor 2)
 Language 0x0409         : "HD video  "
Data (HexDump)           : 09 04 00 00 01 0E 01 00 02                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0100 (UVC Version 1.00)
wTotalLength             : 0x0033 (51 bytes)
dwClockFreq              : 0x016E3600 (24 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x01
Data (HexDump)           : 0D 24 01 00 01 33 00 00 36 6E 01 01 01            .$...3..6n...

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
bmControls               : 0x00, 0x00, 0x00
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
 D16                     : 0   no -  Tilt (Relative)
 D17                     : 0   no -  Focus Auto
 D18                     : 0   no -  Reserved
 D19                     : 0   no -  Reserved
 D20                     : 0   no -  Reserved
 D21                     : 0   no -  Reserved
 D22                     : 0   no -  Reserved
 D23                     : 0   no -  Reserved
Data (HexDump)           : 12 24 02 01 01 02 00 00 00 00 00 00 00 00 03 00   .$..............
                           00 00                                             ..

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
bTerminalID              : 0x03
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x02
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 03 01 01 00 02 00                        .$.......

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x84 (Direction=IN EndpointID=4)
bmAttributes             : 0x03 (TransferType=Interrupt)
wMaxPacketSize           : 0x000A (10 bytes)
bInterval                : 0x05 (5 ms)
Data (HexDump)           : 07 05 84 03 0A 00 05                              .......

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
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x00
iInterface               : 0x00 (No String Descriptor)
Data (HexDump)           : 09 04 01 00 01 0E 02 00 00                        .........

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x02 (TransferType=Bulk)
wMaxPacketSize           : 0x0040 (64 bytes)
bInterval                : 0x00 (ignored)
Data (HexDump)           : 07 05 81 02 40 00 00                              ....@..

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x0E (14 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x01
wTotalLength             : 0x00BD (189 bytes)
bEndpointAddress         : 0x81 (Direction=IN  EndpointID=1)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x03
bStillCaptureMethod      : 0x02 (Still Capture Method 2)
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
Data (HexDump)           : 0E 24 01 01 BD 00 81 00 03 02 01 00 01 00         .$............

        ----- Video Streaming MJPEG Format Type Descriptor ----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x06 (Format MJPEG)
bFormatIndex             : 0x01 (1)
bNumFrameDescriptors     : 0x04 (4)
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
Data (HexDump)           : 0B 24 06 01 04 01 01 00 00 00 00                  .$.........

        ----- Video Streaming MJPEG Frame Type Descriptor -----
---> This is the Default (optimum) Frame index
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x01
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x06978000 (110592000 bps -> 13.824 MB/s)
dwMaxBitRate             : 0x0D2F0000 (221184000 bps -> 27.648 MB/s)
dwMaxVideoFrameBufferSize: 0x001C2000 (1843200 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[2]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
Data (HexDump)           : 22 24 07 01 01 00 05 D0 02 00 80 97 06 00 00 2F   "$............./
                           0D 00 20 1C 00 2A 2C 0A 00 02 2A 2C 0A 00 40 42   .. ..*,...*,..@B
                           0F 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x01
wWidth                   : 0x0320 (800)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x03A98000 (61440000 bps -> 7.680 MB/s)
dwMaxBitRate             : 0x07530000 (122880000 bps -> 15.360 MB/s)
dwMaxVideoFrameBufferSize: 0x000BB800 (768000 bytes)
dwDefaultFrameInterval   : 0x0007A120 (50.0000 ms -> 20.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[2]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 22 24 07 02 01 20 03 E0 01 00 80 A9 03 00 00 53   "$... .........S
                           07 00 B8 0B 00 20 A1 07 00 02 20 A1 07 00 2A 2C   ..... .... ...*,
                           0A 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x03
bmCapabilities           : 0x01
wWidth                   : 0x0280 (640)
wHeight                  : 0x01E0 (480)
dwMinBitRate             : 0x03A98000 (61440000 bps -> 7.680 MB/s)
dwMaxBitRate             : 0x07530000 (122880000 bps -> 15.360 MB/s)
dwMaxVideoFrameBufferSize: 0x00096000 (614400 bytes)
dwDefaultFrameInterval   : 0x00061A80 (40.0000 ms -> 25.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[2]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 22 24 07 03 01 80 02 E0 01 00 80 A9 03 00 00 53   "$.............S
                           07 00 60 09 00 80 1A 06 00 02 80 1A 06 00 2A 2C   ..`...........*,
                           0A 00                                             ..

        ----- Video Streaming MJPEG Frame Type Descriptor -----
bLength                  : 0x22 (34 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x01
wWidth                   : 0x01E0 (480)
wHeight                  : 0x0140 (320)
dwMinBitRate             : 0x01D4C000 (30720000 bps -> 3.840 MB/s)
dwMaxBitRate             : 0x03A98000 (61440000 bps -> 7.680 MB/s)
dwMaxVideoFrameBufferSize: 0x0004B000 (307200 bytes)
dwDefaultFrameInterval   : 0x00061A80 (40.0000 ms -> 25.000 fps)
bFrameIntervalType       : 0x02 (2 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[2]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
Data (HexDump)           : 22 24 07 04 01 E0 01 40 01 00 C0 D4 01 00 80 A9   "$.....@........
                           03 00 B0 04 00 80 1A 06 00 02 80 1A 06 00 2A 2C   ..............*,
                           0A 00                                             ..

        ---------- Still Image Frame Type Descriptor ----------
bLength                  : 0x16 (22 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x03 (Still Image Frame Type)
bEndpointAddress         : 0x00 (no endpoint)
bNumImageSizePatterns    : 0x04 (4 Image Size Patterns)
1: wWidth x wHeight      : 0x0500 x 0x02D0 (1280 x 720)
2: wWidth x wHeight      : 0x0320 x 0x01E0 (800 x 480)
3: wWidth x wHeight      : 0x0280 x 0x01E0 (640 x 480)
4: wWidth x wHeight      : 0x01E0 x 0x0140 (480 x 320)
bNumCompressionPattern   : 0x00
Data (HexDump)           : 16 24 03 00 04 00 05 D0 02 20 03 E0 01 80 02 E0   .$....... ......
                           01 E0 01 40 01 00                                 ...@..

        ------- VS Color Matching Descriptor Descriptor -------
bLength                  : 0x06 (6 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x0D (Color Matching)
bColorPrimaries          : 0x01 (BT.709, sRGB)
bTransferCharacteristics : 0x01 (BT.709)
bMatrixCoefficients      : 0x04 (SMPTE 170M)
Data (HexDump)           : 06 24 0D 01 01 04                                 .$....

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x02
bInterfaceCount          : 0x03
bFunctionClass           : 0x01 (Audio)
bFunctionSubClass        : 0x00 (undefined)
bFunctionProtocol        : 0x00
iFunction                : 0x04 (String Descriptor 4)
 Language 0x0409         : "HD audio  "
Data (HexDump)           : 08 0B 02 03 01 00 00 04                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x01 (Audio)
bInterfaceSubClass       : 0x01 (Audio Control)
bInterfaceProtocol       : 0x00
iInterface               : 0x04 (String Descriptor 4)
 Language 0x0409         : "HD audio  "
Data (HexDump)           : 09 04 02 00 00 01 01 00 04                        .........

        ------ Audio Control Interface Header Descriptor ------
bLength                  : 0x0A (10 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01 (Header)
bcdADC                   : 0x0100
wTotalLength             : 0x0045 (69 bytes)
bInCollection            : 0x02
baInterfaceNr[1]         : 0x03
baInterfaceNr[2]         : 0x04
Data (HexDump)           : 0A 24 01 00 01 45 00 02 03 04                     .$...E....

        ------- Audio Control Input Terminal Descriptor -------
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Input Terminal)
bTerminalID              : 0x04
wTerminalType            : 0x0201 (Microphone)
bAssocTerminal           : 0x00
bNrChannels              : 0x01 (1 channel)
wChannelConfig           : 0x0001 (L)
iChannelNames            : 0x00 (No String Descriptor)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 0C 24 02 04 01 02 00 01 01 00 00 00               .$..........

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x06 (Feature Unit)
bUnitID                  : 0x05 (5)
bSourceID                : 0x04 (4)
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
Data (HexDump)           : 08 24 06 05 04 01 03 00                           .$......

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x06
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x00 (0)
bSourceID                : 0x05 (5)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 03 06 01 01 00 05 00                        .$.......

        ------- Audio Control Input Terminal Descriptor -------
bLength                  : 0x0C (12 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x02 (Input Terminal)
bTerminalID              : 0x07
wTerminalType            : 0x0101 (USB streaming)
bAssocTerminal           : 0x00
bNrChannels              : 0x01 (1 channel)
wChannelConfig           : 0x0001 (L)
iChannelNames            : 0x00 (No String Descriptor)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 0C 24 02 07 01 01 00 01 01 00 00 00               .$..........

        -------- Audio Control Feature Unit Descriptor --------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x06 (Feature Unit)
bUnitID                  : 0x08 (8)
bSourceID                : 0x07 (7)
bControlSize             : 0x01 (1 byte per control)
bmaControls[0]           : 0x01
 D0: Mute                : 1
 D1: Volume              : 0
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
bmaControls[1]           : 0x02
 D0: Mute                : 0
 D1: Volume              : 1
 D2: Bass                : 0
 D3: Mid                 : 0
 D4: Treble              : 0
 D5: Graphic Equalizer   : 0
 D6: Automatic Gain      : 0
 D7: Delay               : 0
iFeature                 : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 06 08 07 01 01 02 00                        .$.......

        ------- Audio Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x09
wTerminalType            : 0x0301 (Speaker)
bAssocTerminal           : 0x07 (7)
bSourceID                : 0x08 (8)
iTerminal                : 0x00 (No String Descriptor)
Data (HexDump)           : 09 24 03 09 01 03 07 08 00                        .$.......

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
bTerminalLink            : 0x06
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 06 01 01 00                              .$.....

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
bEndpointAddress         : 0x82 (Direction=IN EndpointID=2)
bmAttributes             : 0x0D (TransferType=Isochronous  SyncType=Synchronous  EndpointType=Data)
wMaxPacketSize           : 0x0064 (100 bytes)
bInterval                : 0x01 (1 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 82 0D 64 00 01 00 00                        ....d....

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
bTerminalLink            : 0x07
bDelay                   : 0x01
wFormatTag               : 0x0001 (PCM)
Data (HexDump)           : 07 24 01 07 01 01 00                              .$.....

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
bEndpointAddress         : 0x03 (Direction=OUT EndpointID=3)
bmAttributes             : 0x09 (TransferType=Isochronous  SyncType=Adaptive  EndpointType=Data)
wMaxPacketSize           : 0x0064 (100 bytes)
bInterval                : 0x01 (1 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 03 09 64 00 01 00 00                        ....d....

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

      -------------------- String Descriptors -------------------
             ------ String Descriptor 0 ------
bLength                  : 0x04 (4 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language ID[0]           : 0x0409 (English - United States)
Data (HexDump)           : 04 03 09 04                                       ....
             ------ String Descriptor 1 ------
bLength                  : 0x10 (16 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Generic"
Data (HexDump)           : 10 03 47 00 65 00 6E 00 65 00 72 00 69 00 63 00   ..G.e.n.e.r.i.c.
             ------ String Descriptor 2 ------
bLength                  : 0x16 (22 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "HD video  "  *!*CAUTION  trailing space characters
Data (HexDump)           : 16 03 48 00 44 00 20 00 76 00 69 00 64 00 65 00   ..H.D. .v.i.d.e.
                           6F 00 20 00 20 00                                 o. . .
             ------ String Descriptor 3 ------
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "20210901000000"
Data (HexDump)           : 1E 03 32 00 30 00 32 00 31 00 30 00 39 00 30 00   ..2.0.2.1.0.9.0.
                           31 00 30 00 30 00 30 00 30 00 30 00 30 00         1.0.0.0.0.0.0.
             ------ String Descriptor 4 ------
bLength                  : 0x16 (22 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "HD audio  "  *!*CAUTION  trailing space characters
Data (HexDump)           : 16 03 48 00 44 00 20 00 61 00 75 00 64 00 69 00   ..H.D. .a.u.d.i.
                           6F 00 20 00 20 00                                 o. . .

*/

namespace customer_camera {
const uint8_t dev_desc[] = {
    0x12, 0x01, 0x00, 0x02, 0xEF, 0x02, 0x01, 0x40, 0x9C, 0x34, 0x07, 0x33, 0x01, 0x03, 0x01, 0x02,
    0x03, 0x01
};

const uint8_t cfg_desc[] = {
    0x09, 0x02, 0xE4, 0x01, 0x05, 0x01, 0x00, 0x80, 0x80, 0x08, 0x0B, 0x00, 0x02, 0x0E, 0x03, 0x00,
    0x02, 0x09, 0x04, 0x00, 0x00, 0x01, 0x0E, 0x01, 0x00, 0x02, 0x0D, 0x24, 0x01, 0x00, 0x01, 0x33,
    0x00, 0x00, 0x36, 0x6E, 0x01, 0x01, 0x01, 0x12, 0x24, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0B, 0x24, 0x05, 0x02, 0x01, 0x00, 0x00,
    0x02, 0x7F, 0x17, 0x00, 0x09, 0x24, 0x03, 0x03, 0x01, 0x01, 0x00, 0x02, 0x00, 0x07, 0x05, 0x84,
    0x03, 0x0A, 0x00, 0x05, 0x05, 0x25, 0x03, 0x40, 0x00, 0x09, 0x04, 0x01, 0x00, 0x01, 0x0E, 0x02,
    0x00, 0x00, 0x07, 0x05, 0x81, 0x02, 0x40, 0x00, 0x00, 0x0E, 0x24, 0x01, 0x01, 0xBD, 0x00, 0x81,
    0x00, 0x03, 0x02, 0x01, 0x00, 0x01, 0x00, 0x0B, 0x24, 0x06, 0x01, 0x04, 0x01, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x22, 0x24, 0x07, 0x01, 0x01, 0x00, 0x05, 0xD0, 0x02, 0x00, 0x80, 0x97, 0x06, 0x00,
    0x00, 0x2F, 0x0D, 0x00, 0x20, 0x1C, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x02, 0x2A, 0x2C, 0x0A, 0x00,
    0x40, 0x42, 0x0F, 0x00, 0x22, 0x24, 0x07, 0x02, 0x01, 0x20, 0x03, 0xE0, 0x01, 0x00, 0x80, 0xA9,
    0x03, 0x00, 0x00, 0x53, 0x07, 0x00, 0xB8, 0x0B, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x02, 0x20, 0xA1,
    0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x22, 0x24, 0x07, 0x03, 0x01, 0x80, 0x02, 0xE0, 0x01, 0x00,
    0x80, 0xA9, 0x03, 0x00, 0x00, 0x53, 0x07, 0x00, 0x60, 0x09, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x02,
    0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x22, 0x24, 0x07, 0x04, 0x01, 0xE0, 0x01, 0x40,
    0x01, 0x00, 0xC0, 0xD4, 0x01, 0x00, 0x80, 0xA9, 0x03, 0x00, 0xB0, 0x04, 0x00, 0x80, 0x1A, 0x06,
    0x00, 0x02, 0x80, 0x1A, 0x06, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x16, 0x24, 0x03, 0x00, 0x04, 0x00,
    0x05, 0xD0, 0x02, 0x20, 0x03, 0xE0, 0x01, 0x80, 0x02, 0xE0, 0x01, 0xE0, 0x01, 0x40, 0x01, 0x00,
    0x06, 0x24, 0x0D, 0x01, 0x01, 0x04, 0x08, 0x0B, 0x02, 0x03, 0x01, 0x00, 0x00, 0x04, 0x09, 0x04,
    0x02, 0x00, 0x00, 0x01, 0x01, 0x00, 0x04, 0x0A, 0x24, 0x01, 0x00, 0x01, 0x45, 0x00, 0x02, 0x03,
    0x04, 0x0C, 0x24, 0x02, 0x04, 0x01, 0x02, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x08, 0x24, 0x06,
    0x05, 0x04, 0x01, 0x03, 0x00, 0x09, 0x24, 0x03, 0x06, 0x01, 0x01, 0x00, 0x05, 0x00, 0x0C, 0x24,
    0x02, 0x07, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x09, 0x24, 0x06, 0x08, 0x07, 0x01,
    0x01, 0x02, 0x00, 0x09, 0x24, 0x03, 0x09, 0x01, 0x03, 0x07, 0x08, 0x00, 0x09, 0x04, 0x03, 0x00,
    0x00, 0x01, 0x02, 0x00, 0x00, 0x09, 0x04, 0x03, 0x01, 0x01, 0x01, 0x02, 0x00, 0x00, 0x07, 0x24,
    0x01, 0x06, 0x01, 0x01, 0x00, 0x0B, 0x24, 0x02, 0x01, 0x01, 0x02, 0x10, 0x01, 0x80, 0x3E, 0x00,
    0x09, 0x05, 0x82, 0x0D, 0x64, 0x00, 0x01, 0x00, 0x00, 0x07, 0x25, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x09, 0x04, 0x04, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x09, 0x04, 0x04, 0x01, 0x01, 0x01, 0x02,
    0x00, 0x00, 0x07, 0x24, 0x01, 0x07, 0x01, 0x01, 0x00, 0x0B, 0x24, 0x02, 0x01, 0x01, 0x02, 0x10,
    0x01, 0x80, 0x3E, 0x00, 0x09, 0x05, 0x03, 0x09, 0x64, 0x00, 0x01, 0x00, 0x00, 0x07, 0x25, 0x01,
    0x01, 0x01, 0x00
};
}
