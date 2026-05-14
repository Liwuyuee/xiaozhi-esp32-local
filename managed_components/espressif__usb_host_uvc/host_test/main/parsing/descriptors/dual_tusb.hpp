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
Device Path              : \\?\USB#VID_303A&PID_8000#12345678#{a5dcbf10-6530-11d2-901f-00c04fb951ed} (GUID_DEVINTERFACE_USB_DEVICE)
Kernel Name              : \Device\USBPDO-19
Device ID                : USB\VID_303A&PID_8000\12345678
Hardware IDs             : USB\VID_303A&PID_8000&REV_0100 USB\VID_303A&PID_8000
Driver KeyName           : {36fc9e60-c465-11cf-8056-444553540000}\0067 (GUID_DEVCLASS_USB)
Driver                   : \SystemRoot\System32\drivers\usbccgp.sys (Version: 10.0.19041.4355  Date: 2024-05-01)
Driver Inf               : C:\Windows\inf\usb.inf
Legacy BusType           : PNPBus
Class                    : USB
Class GUID               : {36fc9e60-c465-11cf-8056-444553540000} (GUID_DEVCLASS_USB)
Service                  : usbccgp
Enumerator               : USB
Location Info            : Port_#0003.Hub_#0010
Location IDs             : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(3), ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(3)
Container ID             : {ddab37e9-bf1d-5d60-87aa-5cdee04ae009}
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
 Child Device 1          : UVC CAM1 (USB Video Device)
  Device Path 1          : \\?\USB#VID_303A&PID_8000&MI_00#b&cf21808&0&0000#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global (AM_KSCATEGORY_CAPTURE)
  Device Path 2          : \\?\USB#VID_303A&PID_8000&MI_00#b&cf21808&0&0000#{e5323777-f976-4f5b-9b55-b94699c46e44}\global (STATIC_KSCATEGORY_VIDEO_CAMERA)
  Device Path 3          : \\?\USB#VID_303A&PID_8000&MI_00#b&cf21808&0&0000#{6994ad05-93ef-11d0-a3cc-00a0c9223196}\global (AM_KSCATEGORY_VIDEO)
  Kernel Name            : \Device\000001c2
  Device ID              : USB\VID_303A&PID_8000&MI_00\B&CF21808&0&0000
  Class                  : Camera
  Driver KeyName         : {ca3e7ab9-b4c3-4ae6-8251-579ef933890f}\0005 (GUID_DEVCLASS_CAMERA)
  Service                : usbvideo
  Location               : 0005.0000.0004.001.003.003.000.000.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(3)#USBMI(0)  PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(3)#USB(3)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(3)#USBMI(0)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(3)#USB(3)
 Child Device 2          : UVC CAM2 (USB Video Device)
  Device Path 1          : \\?\USB#VID_303A&PID_8000&MI_02#b&cf21808&0&0002#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global (AM_KSCATEGORY_CAPTURE)
  Device Path 2          : \\?\USB#VID_303A&PID_8000&MI_02#b&cf21808&0&0002#{e5323777-f976-4f5b-9b55-b94699c46e44}\global (STATIC_KSCATEGORY_VIDEO_CAMERA)
  Device Path 3          : \\?\USB#VID_303A&PID_8000&MI_02#b&cf21808&0&0002#{6994ad05-93ef-11d0-a3cc-00a0c9223196}\global (AM_KSCATEGORY_VIDEO)
  Kernel Name            : \Device\000001c3
  Device ID              : USB\VID_303A&PID_8000&MI_02\B&CF21808&0&0002
  Class                  : Camera
  Driver KeyName         : {ca3e7ab9-b4c3-4ae6-8251-579ef933890f}\0006 (GUID_DEVCLASS_CAMERA)
  Service                : usbvideo
  Location               : 0005.0000.0004.001.003.003.000.000.000
  LocationPaths          : PCIROOT(0)#PCI(0803)#PCI(0004)#USBROOT(0)#USB(1)#USB(3)#USB(3)#USBMI(2)  ACPI(_SB_)#ACPI(PCI0)#ACPI(GP19)#ACPI(XHC4)#ACPI(RHUB)#ACPI(PRT1)#USB(3)#USB(3)#USBMI(2)

        +++++++++++++++++ Registry USB Flags +++++++++++++++++
HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\usbflags\303A80000100
 osvc                    : REG_BINARY 00 00

        ---------------- Connection Information ---------------
Connection Index         : 0x03 (Port 3)
Connection Status        : 0x01 (DeviceConnected)
Current Config Value     : 0x01 (Configuration 1)
Device Address           : 0x09 (9)
Is Hub                   : 0x00 (no)
Device Bus Speed         : 0x02 (High-Speed)
Number Of Open Pipes     : 0x02 (2 pipes to data endpoints)
Pipe[0]                  : EndpointID=1  Direction=IN   ScheduleOffset=0  Type=Bulk
Pipe[1]                  : EndpointID=2  Direction=IN   ScheduleOffset=0  Type=Bulk
Data (HexDump)           : 03 00 00 00 12 01 00 02 EF 02 01 40 3A 30 00 80   ...........@:0..
                           00 01 01 02 03 01 01 02 00 09 00 02 00 00 00 01   ................
                           00 00 00 07 05 81 02 00 02 01 00 00 00 00 07 05   ................
                           82 02 00 02 01 00 00 00 00                        .........

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
idVendor                 : 0x303A (Espressif Incorporated)
idProduct                : 0x8000
bcdDevice                : 0x0100
iManufacturer            : 0x01 (String Descriptor 1)
 *!*ERROR  String descriptor not found
iProduct                 : 0x02 (String Descriptor 2)
 *!*ERROR  String descriptor not found
iSerialNumber            : 0x03 (String Descriptor 3)
 *!*ERROR  String descriptor not found
bNumConfigurations       : 0x01 (1 Configuration)
Data (HexDump)           : 12 01 00 02 EF 02 01 40 3A 30 00 80 00 01 01 02   .......@:0......
                           03 01                                             ..

    ------------------ Configuration Descriptor -------------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x02 (Configuration Descriptor)
wTotalLength             : 0x0125 (293 bytes)
bNumInterfaces           : 0x04 (4 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x00 (No String Descriptor)
bmAttributes             : 0x80
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x00 (no)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0xFA (500 mA)
Data (HexDump)           : 09 02 25 01 04 01 00 80 FA 08 0B 00 02 0E 03 00   ..%.............
                           04 09 04 00 00 00 0E 01 01 04 0D 24 01 50 01 28   ...........$.P.(
                           00 C0 FC 9B 01 01 01 12 24 02 01 01 02 00 00 00   ........$.......
                           00 00 00 00 00 03 00 00 00 09 24 03 02 01 01 00   ..........$.....
                           01 00 09 04 01 00 01 0E 02 01 04 0E 24 01 01 45   ............$..E
                           00 81 00 02 00 00 00 01 00 0B 24 06 01 01 00 01   ..........$.....
                           00 00 00 00 26 24 07 01 00 E0 01 0E 01 00 A4 1F   ....&$..........
                           00 00 D0 78 02 80 F4 03 00 20 A1 07 00 00 20 A1   ...x..... .... .
                           07 00 20 A1 07 00 20 A1 07 00 06 24 0D 01 01 04   .. ... ....$....
                           07 05 81 02 00 02 01 08 0B 02 02 0E 03 00 05 09   ................
                           04 02 00 00 0E 01 01 05 0D 24 01 50 01 28 00 C0   .........$.P.(..
                           FC 9B 01 01 03 12 24 02 01 01 02 00 00 00 00 00   ......$.........
                           00 00 00 03 00 00 00 09 24 03 02 01 01 00 01 00   ........$.......
                           09 04 03 00 01 0E 02 01 05 0E 24 01 01 45 00 82   ..........$..E..
                           00 02 00 00 00 01 00 0B 24 06 01 01 00 01 00 00   ........$.......
                           00 00 26 24 07 01 00 00 05 D0 02 00 00 E1 00 00   ..&$............
                           00 2F 0D 00 20 1C 00 2A 2C 0A 00 00 2A 2C 0A 00   ./.. ..*,...*,..
                           2A 2C 0A 00 2A 2C 0A 00 06 24 0D 01 01 04 07 05   *,..*,...$......
                           82 02 00 02 01                                    .....

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x00
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x04 (String Descriptor 4)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 08 0B 00 02 0E 03 00 04                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x00
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x01  *!*ERROR  must be 0 for this class
iInterface               : 0x04 (String Descriptor 4)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 09 04 00 00 00 0E 01 01 04                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0150 (UVC Version 1.50)
wTotalLength             : 0x0028 (40 bytes)
dwClockFreq              : 0x019BFCC0 (27 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x01
Data (HexDump)           : 0D 24 01 50 01 28 00 C0 FC 9B 01 01 01            .$.P.(.......

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

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x02
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x01
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 02 01 01 00 01 00                        .$.......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x01
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x01  *!*ERROR  must be 0 for this class
iInterface               : 0x04 (String Descriptor 4)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 09 04 01 00 01 0E 02 01 04                        .........

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x0E (14 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x01
wTotalLength             : 0x0045 (69 bytes)
bEndpointAddress         : 0x81 (Direction=IN  EndpointID=1)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x02
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
Data (HexDump)           : 0E 24 01 01 45 00 81 00 02 00 00 00 01 00         .$..E.........

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
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x01E0 (480)
wHeight                  : 0x010E (270)
dwMinBitRate             : 0x001FA400 (2073600 bps -> 259.125 KB/s)
dwMaxBitRate             : 0x0278D000 (41472000 bps -> 5.184 MB/s)
dwMaxVideoFrameBufferSize: 0x0003F480 (259200 bytes)
dwDefaultFrameInterval   : 0x0007A120 (50.0000 ms -> 20.000 fps)
bFrameIntervalType       : 0x00 (0 discrete frame intervals supported)
dwMinFrameInterval       : 0x0007A120 (50.0000 ms -> 20.000 fps)
dwMaxFrameInterval       : 0x0007A120 (50.0000 ms -> 20.000 fps)
dwFrameIntervalStep      : 0x0007A120
*!*WARNING:  dwMinFrameInterval + dwFrameIntervalStep is greater than dwMaxFrameInterval, this could cause problems
Data (HexDump)           : 26 24 07 01 00 E0 01 0E 01 00 A4 1F 00 00 D0 78   &$.............x
                           02 80 F4 03 00 20 A1 07 00 00 20 A1 07 00 20 A1   ..... .... ... .
                           07 00 20 A1 07 00                                 .. ...

        ------- VS Color Matching Descriptor Descriptor -------
bLength                  : 0x06 (6 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x0D (Color Matching)
bColorPrimaries          : 0x01 (BT.709, sRGB)
bTransferCharacteristics : 0x01 (BT.709)
bMatrixCoefficients      : 0x04 (SMPTE 170M)
Data (HexDump)           : 06 24 0D 01 01 04                                 .$....

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x81 (Direction=IN EndpointID=1)
bmAttributes             : 0x02 (TransferType=Bulk)
wMaxPacketSize           : 0x0200 (max 512 bytes)
bInterval                : 0x01 (at most 1 NAK each 1 microframes)
Data (HexDump)           : 07 05 81 02 00 02 01                              .......

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x02
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x05 (String Descriptor 5)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 08 0B 02 02 0E 03 00 05                           ........

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x02
bAlternateSetting        : 0x00
bNumEndpoints            : 0x00 (Default Control Pipe only)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x01 (Video Control)
bInterfaceProtocol       : 0x01  *!*ERROR  must be 0 for this class
iInterface               : 0x05 (String Descriptor 5)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 09 04 02 00 00 0E 01 01 05                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0150 (UVC Version 1.50)
wTotalLength             : 0x0028 (40 bytes)
dwClockFreq              : 0x019BFCC0 (27 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x03
Data (HexDump)           : 0D 24 01 50 01 28 00 C0 FC 9B 01 01 03            .$.P.(.......

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

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x02
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x01
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 02 01 01 00 01 00                        .$.......

        ---------------- Interface Descriptor -----------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x04 (Interface Descriptor)
bInterfaceNumber         : 0x03
bAlternateSetting        : 0x00
bNumEndpoints            : 0x01 (1 Endpoint)
bInterfaceClass          : 0x0E (Video)
bInterfaceSubClass       : 0x02 (Video Streaming)
bInterfaceProtocol       : 0x01  *!*ERROR  must be 0 for this class
iInterface               : 0x05 (String Descriptor 5)
 *!*ERROR  String descriptor not found
Data (HexDump)           : 09 04 03 00 01 0E 02 01 05                        .........

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x0E (14 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x01
wTotalLength             : 0x0045 (69 bytes)
bEndpointAddress         : 0x82 (Direction=IN  EndpointID=2)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x02
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
Data (HexDump)           : 0E 24 01 01 45 00 82 00 02 00 00 00 01 00         .$..E.........

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
bLength                  : 0x26 (38 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x07 (MJPEG Frame Type)
bFrameIndex              : 0x01
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x02D0 (720)
dwMinBitRate             : 0x00E10000 (14745600 bps -> 1.843 MB/s)
dwMaxBitRate             : 0x0D2F0000 (221184000 bps -> 27.648 MB/s)
dwMaxVideoFrameBufferSize: 0x001C2000 (1843200 bytes)
dwDefaultFrameInterval   : 0x000A2C2A (66.6666 ms -> 15.000 fps)
bFrameIntervalType       : 0x00 (0 discrete frame intervals supported)
dwMinFrameInterval       : 0x000A2C2A (66.6666 ms -> 15.000 fps)
dwMaxFrameInterval       : 0x000A2C2A (66.6666 ms -> 15.000 fps)
dwFrameIntervalStep      : 0x000A2C2A
*!*WARNING:  dwMinFrameInterval + dwFrameIntervalStep is greater than dwMaxFrameInterval, this could cause problems
Data (HexDump)           : 26 24 07 01 00 00 05 D0 02 00 00 E1 00 00 00 2F   &$............./
                           0D 00 20 1C 00 2A 2C 0A 00 00 2A 2C 0A 00 2A 2C   .. ..*,...*,..*,
                           0A 00 2A 2C 0A 00                                 ..*,..

        ------- VS Color Matching Descriptor Descriptor -------
bLength                  : 0x06 (6 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x0D (Color Matching)
bColorPrimaries          : 0x01 (BT.709, sRGB)
bTransferCharacteristics : 0x01 (BT.709)
bMatrixCoefficients      : 0x04 (SMPTE 170M)
Data (HexDump)           : 06 24 0D 01 01 04                                 .$....

        ----------------- Endpoint Descriptor -----------------
bLength                  : 0x07 (7 bytes)
bDescriptorType          : 0x05 (Endpoint Descriptor)
bEndpointAddress         : 0x82 (Direction=IN EndpointID=2)
bmAttributes             : 0x02 (TransferType=Bulk)
wMaxPacketSize           : 0x0200 (max 512 bytes)
bInterval                : 0x01 (at most 1 NAK each 1 microframes)
Data (HexDump)           : 07 05 82 02 00 02 01                              .......

    ----------------- Device Qualifier Descriptor -----------------
Error                    : ERROR_GEN_FAILURE

      -------------------- String Descriptors -------------------
none
*/

namespace dual_tusb {
const uint8_t dev_desc[] = {
    0x12, 0x01, 0x00, 0x02, 0xEF, 0x02, 0x01, 0x40, 0x3A, 0x30, 0x00, 0x80, 0x00, 0x01, 0x01, 0x02,
    0x03, 0x01
};

const uint8_t cfg_desc[] = {
    0x09, 0x02, 0x25, 0x01, 0x04, 0x01, 0x00, 0x80, 0xFA, 0x08, 0x0B, 0x00, 0x02, 0x0E, 0x03, 0x00,
    0x04, 0x09, 0x04, 0x00, 0x00, 0x00, 0x0E, 0x01, 0x01, 0x04, 0x0D, 0x24, 0x01, 0x50, 0x01, 0x28,
    0x00, 0xC0, 0xFC, 0x9B, 0x01, 0x01, 0x01, 0x12, 0x24, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x09, 0x24, 0x03, 0x02, 0x01, 0x01, 0x00,
    0x01, 0x00, 0x09, 0x04, 0x01, 0x00, 0x01, 0x0E, 0x02, 0x01, 0x04, 0x0E, 0x24, 0x01, 0x01, 0x45,
    0x00, 0x81, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0B, 0x24, 0x06, 0x01, 0x01, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x26, 0x24, 0x07, 0x01, 0x00, 0xE0, 0x01, 0x0E, 0x01, 0x00, 0xA4, 0x1F,
    0x00, 0x00, 0xD0, 0x78, 0x02, 0x80, 0xF4, 0x03, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x00, 0x20, 0xA1,
    0x07, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x06, 0x24, 0x0D, 0x01, 0x01, 0x04,
    0x07, 0x05, 0x81, 0x02, 0x00, 0x02, 0x01, 0x08, 0x0B, 0x02, 0x02, 0x0E, 0x03, 0x00, 0x05, 0x09,
    0x04, 0x02, 0x00, 0x00, 0x0E, 0x01, 0x01, 0x05, 0x0D, 0x24, 0x01, 0x50, 0x01, 0x28, 0x00, 0xC0,
    0xFC, 0x9B, 0x01, 0x01, 0x03, 0x12, 0x24, 0x02, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x09, 0x24, 0x03, 0x02, 0x01, 0x01, 0x00, 0x01, 0x00,
    0x09, 0x04, 0x03, 0x00, 0x01, 0x0E, 0x02, 0x01, 0x05, 0x0E, 0x24, 0x01, 0x01, 0x45, 0x00, 0x82,
    0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0B, 0x24, 0x06, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x26, 0x24, 0x07, 0x01, 0x00, 0x00, 0x05, 0xD0, 0x02, 0x00, 0x00, 0xE1, 0x00, 0x00,
    0x00, 0x2F, 0x0D, 0x00, 0x20, 0x1C, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x00, 0x2A, 0x2C, 0x0A, 0x00,
    0x2A, 0x2C, 0x0A, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x06, 0x24, 0x0D, 0x01, 0x01, 0x04, 0x07, 0x05,
    0x82, 0x02, 0x00, 0x02, 0x01
};
}
