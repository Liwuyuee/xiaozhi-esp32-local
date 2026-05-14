/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>
/*
    ---------------------- Device Descriptor ----------------------
bLength                  : 0x12 (18 bytes)
bDescriptorType          : 0x01 (Device Descriptor)
bcdUSB                   : 0x200 (USB Version 2.00)
bDeviceClass             : 0xEF (Miscellaneous)
bDeviceSubClass          : 0x02
bDeviceProtocol          : 0x01 (IAD - Interface Association Descriptor)
bMaxPacketSize0          : 0x40 (64 bytes)
idVendor                 : 0x0C45 (Sonix Technology Co., Ltd.)
idProduct                : 0x6340
bcdDevice                : 0x0000
iManufacturer            : 0x02 (String Descriptor 2)
 Language 0x0409         : "Trust Webcam"
iProduct                 : 0x01 (String Descriptor 1)
 Language 0x0409         : "Trust Webcam"
iSerialNumber            : 0x03 (String Descriptor 3)
 Language 0x0409         : "20200907"
bNumConfigurations       : 0x01 (1 Configuration)
Data (HexDump)           : 12 01 00 02 EF 02 01 40 45 0C 40 63 00 00 02 01   .......@E.@c....
                           03 01                                             ..

    ------------------ Configuration Descriptor -------------------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x02 (Configuration Descriptor)
wTotalLength             : 0x02BD (701 bytes)
bNumInterfaces           : 0x04 (4 Interfaces)
bConfigurationValue      : 0x01 (Configuration 1)
iConfiguration           : 0x00 (No String Descriptor)
bmAttributes             : 0x80
 D7: Reserved, set 1     : 0x01
 D6: Self Powered        : 0x00 (no)
 D5: Remote Wakeup       : 0x00 (no)
 D4..0: Reserved, set 0  : 0x00
MaxPower                 : 0xFA (500 mA)
Data (HexDump)           : 09 02 BD 02 04 01 00 80 FA 08 0B 00 02 0E 03 00   ................
                           05 09 04 00 00 01 0E 01 00 05 0D 24 01 00 01 4D   ...........$...M
                           00 C0 E1 E4 00 01 01 09 24 03 02 01 01 00 04 00   ........$.......
                           1A 24 06 04 70 33 F0 28 11 63 2E 4A BA 2C 68 90   .$..p3.(.c.J.,h.
                           EB 33 40 16 08 01 03 01 0F 00 12 24 02 01 01 02   .3@........$....
                           00 00 00 00 00 00 00 00 03 04 00 00 0B 24 05 03   .............$..
                           01 00 00 02 3F 07 00 07 05 83 03 10 00 06 05 25   ....?..........%
                           03 10 00 09 04 01 00 00 0E 02 00 05 0E 24 01 01   .............$..
                           61 01 81 00 02 02 01 01 01 00 1B 24 04 01 06 59   a..........$...Y
                           55 59 32 00 00 10 00 80 00 00 AA 00 38 9B 71 10   UY2.........8.q.
                           01 00 00 00 00 32 24 05 01 00 80 02 E0 01 00 00   .....2$.........
                           77 01 00 00 CA 08 00 60 09 00 15 16 05 00 06 15   w......`........
                           16 05 00 80 1A 06 00 20 A1 07 00 2A 2C 0A 00 40   ....... ...*,..@
                           42 0F 00 80 84 1E 00 32 24 05 02 00 60 01 20 01   B......2$...`. .
                           00 C0 7B 00 00 80 E6 02 00 18 03 00 15 16 05 00   ..{.............
                           06 15 16 05 00 80 1A 06 00 20 A1 07 00 2A 2C 0A   ......... ...*,.
                           00 40 42 0F 00 80 84 1E 00 32 24 05 03 00 40 01   .@B......2$...@.
                           F0 00 00 C0 5D 00 00 80 32 02 00 58 02 00 15 16   ....]...2..X....
                           05 00 06 15 16 05 00 80 1A 06 00 20 A1 07 00 2A   ........... ...*
                           2C 0A 00 40 42 0F 00 80 84 1E 00 32 24 05 04 00   ,..@B......2$...
                           B0 00 90 00 00 F0 1E 00 00 A0 B9 00 00 C6 00 00   ................
                           15 16 05 00 06 15 16 05 00 80 1A 06 00 20 A1 07   ............. ..
                           00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00 1E 24 05   .*,..@B.......$.
                           05 00 00 05 00 04 00 00 40 06 00 00 40 06 00 00   ........@...@...
                           28 00 80 84 1E 00 01 80 84 1E 00 32 24 05 06 00   (..........2$...
                           A0 00 78 00 00 70 17 00 00 A0 8C 00 00 96 00 00   ..x..p..........
                           15 16 05 00 06 15 16 05 00 80 1A 06 00 20 A1 07   ............. ..
                           00 2A 2C 0A 00 40 42 0F 00 80 84 1E 00 1A 24 03   .*,..@B.......$.
                           00 05 80 02 E0 01 60 01 20 01 40 01 F0 00 B0 00   ......`. .@.....
                           90 00 A0 00 78 00 00 06 24 0D 01 01 04 09 04 01   ....x...$.......
                           01 01 0E 02 00 00 07 05 81 05 80 00 01 09 04 01   ................
                           02 01 0E 02 00 00 07 05 81 05 00 01 01 09 04 01   ................
                           03 01 0E 02 00 00 07 05 81 05 20 03 01 09 04 01   .......... .....
                           04 01 0E 02 00 00 07 05 81 05 20 0B 01 09 04 01   .......... .....
                           05 01 0E 02 00 00 07 05 81 05 20 13 01 09 04 01   .......... .....
                           06 01 0E 02 00 00 07 05 81 05 00 14 01 08 0B 02   ................
                           02 01 00 00 04 09 04 02 00 00 01 01 00 04 09 24   ...............$
                           01 00 01 29 00 01 03 0C 24 02 01 01 02 00 01 00   ...)....$.......
                           00 00 00 0B 24 06 02 01 02 01 00 02 00 00 09 24   ....$..........$
                           03 03 01 01 00 02 00 09 04 03 00 00 01 02 00 00   ................
                           09 04 03 01 01 01 02 00 00 07 24 01 03 01 01 00   ..........$.....
                           1D 24 02 01 01 02 10 07 40 1F 00 11 2B 00 80 3E   .$......@...+..>
                           00 22 56 00 C0 5D 00 44 AC 00 80 BB 00 09 05 84   ."V..].D........
                           05 90 01 04 00 00 07 25 01 01 00 00 00            .......%.....

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x00
bInterfaceCount          : 0x02
bFunctionClass           : 0x0E (Video)
bFunctionSubClass        : 0x03 (Video Interface Collection)
bFunctionProtocol        : 0x00 (PC_PROTOCOL_UNDEFINED protocol)
iFunction                : 0x05 (String Descriptor 5)
 Language 0x0409         : "Trust Webcam"
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
 Language 0x0409         : "Trust Webcam"
Data (HexDump)           : 09 04 00 00 01 0E 01 00 05                        .........

        ------- Video Control Interface Header Descriptor -----
bLength                  : 0x0D (13 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x01 (Video Control Header)
bcdUVC                   : 0x0100 (UVC Version 1.00)
wTotalLength             : 0x004D (77 bytes)
dwClockFreq              : 0x00E4E1C0 (15 MHz)
bInCollection            : 0x01 (1 VideoStreaming interface)
baInterfaceNr[1]         : 0x01
Data (HexDump)           : 0D 24 01 00 01 4D 00 C0 E1 E4 00 01 01            .$...M.......

        ------- Video Control Output Terminal Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x03 (Output Terminal)
bTerminalID              : 0x02
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x04
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 02 01 01 00 04 00                        .$.......

        --------- Video Control Extension Unit Descriptor -----
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x06 (Extension Unit)
bUnitID                  : 0x04
guidExtensionCode        : {28F03370-6311-4A2E-BA2C-6890EB334016}
bNumControls             : 0x08
bNrInPins                : 0x01 (1 pins)
baSourceID[1]            : 0x03
bControlSize             : 0x01
bmControls               : 0x0F
 D0                      : 1  yes -  Vendor-Specific (Optional)
 D1                      : 1  yes -  Vendor-Specific (Optional)
 D2                      : 1  yes -  Vendor-Specific (Optional)
 D3                      : 1  yes -  Vendor-Specific (Optional)
 D4                      : 0   no -  Vendor-Specific (Optional)
 D5                      : 0   no -  Vendor-Specific (Optional)
 D6                      : 0   no -  Vendor-Specific (Optional)
 D7                      : 0   no -  Vendor-Specific (Optional)
iExtension               : 0x00
Data (HexDump)           : 1A 24 06 04 70 33 F0 28 11 63 2E 4A BA 2C 68 90   .$..p3.(.c.J.,h.
                           EB 33 40 16 08 01 03 01 0F 00                     .3@.......

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
bmControls               : 0x04, 0x00, 0x00
 D0                      : 0   no -  Scanning Mode
 D1                      : 0   no -  Auto-Exposure Mode
 D2                      : 1  yes -  Auto-Exposure Priority
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
Data (HexDump)           : 12 24 02 01 01 02 00 00 00 00 00 00 00 00 03 04   .$..............
                           00 00                                             ..

        -------- Video Control Processing Unit Descriptor -----
bLength                  : 0x0B (11 bytes)
bDescriptorType          : 0x24 (Video Control Interface)
bDescriptorSubtype       : 0x05 (Processing Unit)
bUnitID                  : 0x03
bSourceID                : 0x01
wMaxMultiplier           : 0x0000
bControlSize             : 0x02
bmControls               : 0x3F, 0x07
 D0                      : 1  yes -  Brightness
 D1                      : 1  yes -  Contrast
 D2                      : 1  yes -  Hue
 D3                      : 1  yes -  Saturation
 D4                      : 1  yes -  Sharpness
 D5                      : 1  yes -  Gamma
 D6                      : 0   no -  White Balance Temperature
 D7                      : 0   no -  White Balance Component
 D8                      : 1  yes -  Backlight Compensation
 D9                      : 1  yes -  Gain
 D10                     : 1  yes -  Power Line Frequency
 D11                     : 0   no -  Hue, Auto
 D12                     : 0   no -  White Balance Temperature, Auto
 D13                     : 0   no -  White Balance Component, Auto
 D14                     : 0   no -  Digital Multiplier
 D15                     : 0   no -  Digital Multiplier Limit
iProcessing              : 0x00
Data (HexDump)           : 0B 24 05 03 01 00 00 02 3F 07 00                  .$......?..

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
iInterface               : 0x05 (String Descriptor 5)
 Language 0x0409         : "Trust Webcam"
Data (HexDump)           : 09 04 01 00 00 0E 02 00 05                        .........

        ---- VC-Specific VS Video Input Header Descriptor -----
bLength                  : 0x0E (14 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x01 (Input Header)
bNumFormats              : 0x01
wTotalLength             : 0x0161 (353 bytes)
bEndpointAddress         : 0x81 (Direction=IN  EndpointID=1)
bmInfo                   : 0x00 (Dynamic Format Change not supported)
bTerminalLink            : 0x02
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
Data (HexDump)           : 0E 24 01 01 61 01 81 00 02 02 01 01 01 00         .$..a.........

        ------- VS Uncompressed Format Type Descriptor --------
bLength                  : 0x1B (27 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x04 (Uncompressed Format Type)
bFormatIndex             : 0x01 (1)
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
Data (HexDump)           : 1B 24 04 01 06 59 55 59 32 00 00 10 00 80 00 00   .$...YUY2.......
                           AA 00 38 9B 71 10 01 00 00 00 00                  ..8.q......

        -------- VS Uncompressed Frame Type Descriptor --------
---> This is the Default (optimum) Frame index
bLength                  : 0x32 (50 bytes)
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
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 05 01 00 80 02 E0 01 00 00 77 01 00 00 CA   2$.........w....
                           08 00 60 09 00 15 16 05 00 06 15 16 05 00 80 1A   ..`.............
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x02
bmCapabilities           : 0x00
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
Data (HexDump)           : 32 24 05 02 00 60 01 20 01 00 C0 7B 00 00 80 E6   2$...`. ...{....
                           02 00 18 03 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x32 (50 bytes)
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
bFrameIntervalType       : 0x06 (6 discrete frame intervals supported)
adwFrameInterval[1]      : 0x00051615 (33.3333 ms -> 30.000 fps)
adwFrameInterval[2]      : 0x00061A80 (40.0000 ms -> 25.000 fps)
adwFrameInterval[3]      : 0x0007A120 (50.0000 ms -> 20.000 fps)
adwFrameInterval[4]      : 0x000A2C2A (66.6666 ms -> 15.000 fps)
adwFrameInterval[5]      : 0x000F4240 (100.0000 ms -> 10.000 fps)
adwFrameInterval[6]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 32 24 05 03 00 40 01 F0 00 00 C0 5D 00 00 80 32   2$...@.....]...2
                           02 00 58 02 00 15 16 05 00 06 15 16 05 00 80 1A   ..X.............
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x04
bmCapabilities           : 0x00
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
Data (HexDump)           : 32 24 05 04 00 B0 00 90 00 00 F0 1E 00 00 A0 B9   2$..............
                           00 00 C6 00 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x1E (30 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x05
bmCapabilities           : 0x00
wWidth                   : 0x0500 (1280)
wHeight                  : 0x0400 (1024)
dwMinBitRate             : 0x06400000 (104857600 bps -> 13.107 MB/s)
dwMaxBitRate             : 0x06400000 (104857600 bps -> 13.107 MB/s)
dwMaxVideoFrameBufferSize: 0x00280000 (2621440 bytes)
dwDefaultFrameInterval   : 0x001E8480 (200.0000 ms -> 5.000 fps)
bFrameIntervalType       : 0x01 (1 discrete frame interval supported)
adwFrameInterval[1]      : 0x001E8480 (200.0000 ms -> 5.000 fps)
Data (HexDump)           : 1E 24 05 05 00 00 05 00 04 00 00 40 06 00 00 40   .$.........@...@
                           06 00 00 28 00 80 84 1E 00 01 80 84 1E 00         ...(..........

        -------- VS Uncompressed Frame Type Descriptor --------
bLength                  : 0x32 (50 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x05 (Uncompressed Frame Type)
bFrameIndex              : 0x06
bmCapabilities           : 0x00
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
Data (HexDump)           : 32 24 05 06 00 A0 00 78 00 00 70 17 00 00 A0 8C   2$.....x..p.....
                           00 00 96 00 00 15 16 05 00 06 15 16 05 00 80 1A   ................
                           06 00 20 A1 07 00 2A 2C 0A 00 40 42 0F 00 80 84   .. ...*,..@B....
                           1E 00                                             ..

        ---------- Still Image Frame Type Descriptor ----------
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x24 (Video Streaming Interface)
bDescriptorSubtype       : 0x03 (Still Image Frame Type)
bEndpointAddress         : 0x00 (no endpoint)
bNumImageSizePatterns    : 0x05 (5 Image Size Patterns)
1: wWidth x wHeight      : 0x0280 x 0x01E0 (640 x 480)
2: wWidth x wHeight      : 0x0160 x 0x0120 (352 x 288)
3: wWidth x wHeight      : 0x0140 x 0x00F0 (320 x 240)
4: wWidth x wHeight      : 0x00B0 x 0x0090 (176 x 144)
5: wWidth x wHeight      : 0x00A0 x 0x0078 (160 x 120)
bNumCompressionPattern   : 0x00
Data (HexDump)           : 1A 24 03 00 05 80 02 E0 01 60 01 20 01 40 01 F0   .$.......`. .@..
                           00 B0 00 90 00 A0 00 78 00 00                     .......x..

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

        ------------------- IAD Descriptor --------------------
bLength                  : 0x08 (8 bytes)
bDescriptorType          : 0x0B
bFirstInterface          : 0x02
bInterfaceCount          : 0x02
bFunctionClass           : 0x01 (Audio)
bFunctionSubClass        : 0x00 (undefined)
bFunctionProtocol        : 0x00
iFunction                : 0x04 (String Descriptor 4)
 Language 0x0409         : "Trust Webcam"
Data (HexDump)           : 08 0B 02 02 01 00 00 04                           ........

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
 Language 0x0409         : "Trust Webcam"
Data (HexDump)           : 09 04 02 00 00 01 01 00 04                        .........

        ------ Audio Control Interface Header Descriptor ------
bLength                  : 0x09 (9 bytes)
bDescriptorType          : 0x24 (Audio Interface Descriptor)
bDescriptorSubtype       : 0x01 (Header)
bcdADC                   : 0x0100
wTotalLength             : 0x0029 (41 bytes)
bInCollection            : 0x01
baInterfaceNr[1]         : 0x03
Data (HexDump)           : 09 24 01 00 01 29 00 01 03                        .$...)...

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
wMaxPacketSize           : 0x0190
 Bits 15..13             : 0x00 (reserved, must be zero)
 Bits 12..11             : 0x00 (0 additional transactions per microframe -> allows 1..1024 bytes per packet)
 Bits 10..0              : 0x190 (400 bytes per packet)
bInterval                : 0x04 (4 ms)
bRefresh                 : 0x00
bSynchAddress            : 0x00
Data (HexDump)           : 09 05 84 05 90 01 04 00 00                        .........

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
                           00 80 8D 5B 00 00 09 24 03 02 01 01 00 03 00 11   ...[...$........
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
 Language 0x0409         : "Trust Webcam"
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
 Language 0x0409         : "Trust Webcam"
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
bTerminalID              : 0x02
wTerminalType            : 0x0101 (TT_STREAMING)
bAssocTerminal           : 0x00 (Not associated with an Input Terminal)
bSourceID                : 0x03
iTerminal                : 0x00
Data (HexDump)           : 09 24 03 02 01 01 00 03 00                        .$.......

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
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Trust Webcam"
Data (HexDump)           : 1A 03 54 00 72 00 75 00 73 00 74 00 20 00 57 00   ..T.r.u.s.t. .W.
                           65 00 62 00 63 00 61 00 6D 00                     e.b.c.a.m.
             ------ String Descriptor 2 ------
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Trust Webcam"
Data (HexDump)           : 1A 03 54 00 72 00 75 00 73 00 74 00 20 00 57 00   ..T.r.u.s.t. .W.
                           65 00 62 00 63 00 61 00 6D 00                     e.b.c.a.m.
             ------ String Descriptor 3 ------
bLength                  : 0x12 (18 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "20200907"
Data (HexDump)           : 12 03 32 00 30 00 32 00 30 00 30 00 39 00 30 00   ..2.0.2.0.0.9.0.
                           37 00                                             7.
             ------ String Descriptor 4 ------
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Trust Webcam"
Data (HexDump)           : 1A 03 54 00 72 00 75 00 73 00 74 00 20 00 57 00   ..T.r.u.s.t. .W.
                           65 00 62 00 63 00 61 00 6D 00                     e.b.c.a.m.
             ------ String Descriptor 5 ------
bLength                  : 0x1A (26 bytes)
bDescriptorType          : 0x03 (String Descriptor)
Language 0x0409          : "Trust Webcam"
Data (HexDump)           : 1A 03 54 00 72 00 75 00 73 00 74 00 20 00 57 00   ..T.r.u.s.t. .W.
                           65 00 62 00 63 00 61 00 6D 00                     e.b.c.a.m.
*/

namespace trust_webcam {
const uint8_t dev_desc[] = {
    0x12, 0x01, 0x00, 0x02, 0xEF, 0x02, 0x01, 0x40, 0x45, 0x0C, 0x40, 0x63, 0x00, 0x00, 0x02, 0x01,
    0x03, 0x01
};

const uint8_t cfg_desc[] = {
    0x09, 0x02, 0xBD, 0x02, 0x04, 0x01, 0x00, 0x80, 0xFA, 0x08, 0x0B, 0x00, 0x02, 0x0E, 0x03, 0x00,
    0x05, 0x09, 0x04, 0x00, 0x00, 0x01, 0x0E, 0x01, 0x00, 0x05, 0x0D, 0x24, 0x01, 0x00, 0x01, 0x4D,
    0x00, 0xC0, 0xE1, 0xE4, 0x00, 0x01, 0x01, 0x09, 0x24, 0x03, 0x02, 0x01, 0x01, 0x00, 0x04, 0x00,
    0x1A, 0x24, 0x06, 0x04, 0x70, 0x33, 0xF0, 0x28, 0x11, 0x63, 0x2E, 0x4A, 0xBA, 0x2C, 0x68, 0x90,
    0xEB, 0x33, 0x40, 0x16, 0x08, 0x01, 0x03, 0x01, 0x0F, 0x00, 0x12, 0x24, 0x02, 0x01, 0x01, 0x02,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x00, 0x00, 0x0B, 0x24, 0x05, 0x03,
    0x01, 0x00, 0x00, 0x02, 0x3F, 0x07, 0x00, 0x07, 0x05, 0x83, 0x03, 0x10, 0x00, 0x06, 0x05, 0x25,
    0x03, 0x10, 0x00, 0x09, 0x04, 0x01, 0x00, 0x00, 0x0E, 0x02, 0x00, 0x05, 0x0E, 0x24, 0x01, 0x01,
    0x61, 0x01, 0x81, 0x00, 0x02, 0x02, 0x01, 0x01, 0x01, 0x00, 0x1B, 0x24, 0x04, 0x01, 0x06, 0x59,
    0x55, 0x59, 0x32, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71, 0x10,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x32, 0x24, 0x05, 0x01, 0x00, 0x80, 0x02, 0xE0, 0x01, 0x00, 0x00,
    0x77, 0x01, 0x00, 0x00, 0xCA, 0x08, 0x00, 0x60, 0x09, 0x00, 0x15, 0x16, 0x05, 0x00, 0x06, 0x15,
    0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40,
    0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x05, 0x02, 0x00, 0x60, 0x01, 0x20, 0x01,
    0x00, 0xC0, 0x7B, 0x00, 0x00, 0x80, 0xE6, 0x02, 0x00, 0x18, 0x03, 0x00, 0x15, 0x16, 0x05, 0x00,
    0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A, 0x2C, 0x0A,
    0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x05, 0x03, 0x00, 0x40, 0x01,
    0xF0, 0x00, 0x00, 0xC0, 0x5D, 0x00, 0x00, 0x80, 0x32, 0x02, 0x00, 0x58, 0x02, 0x00, 0x15, 0x16,
    0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07, 0x00, 0x2A,
    0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x05, 0x04, 0x00,
    0xB0, 0x00, 0x90, 0x00, 0x00, 0xF0, 0x1E, 0x00, 0x00, 0xA0, 0xB9, 0x00, 0x00, 0xC6, 0x00, 0x00,
    0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07,
    0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x1E, 0x24, 0x05,
    0x05, 0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00,
    0x28, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x01, 0x80, 0x84, 0x1E, 0x00, 0x32, 0x24, 0x05, 0x06, 0x00,
    0xA0, 0x00, 0x78, 0x00, 0x00, 0x70, 0x17, 0x00, 0x00, 0xA0, 0x8C, 0x00, 0x00, 0x96, 0x00, 0x00,
    0x15, 0x16, 0x05, 0x00, 0x06, 0x15, 0x16, 0x05, 0x00, 0x80, 0x1A, 0x06, 0x00, 0x20, 0xA1, 0x07,
    0x00, 0x2A, 0x2C, 0x0A, 0x00, 0x40, 0x42, 0x0F, 0x00, 0x80, 0x84, 0x1E, 0x00, 0x1A, 0x24, 0x03,
    0x00, 0x05, 0x80, 0x02, 0xE0, 0x01, 0x60, 0x01, 0x20, 0x01, 0x40, 0x01, 0xF0, 0x00, 0xB0, 0x00,
    0x90, 0x00, 0xA0, 0x00, 0x78, 0x00, 0x00, 0x06, 0x24, 0x0D, 0x01, 0x01, 0x04, 0x09, 0x04, 0x01,
    0x01, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05, 0x81, 0x05, 0x80, 0x00, 0x01, 0x09, 0x04, 0x01,
    0x02, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05, 0x81, 0x05, 0x00, 0x01, 0x01, 0x09, 0x04, 0x01,
    0x03, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05, 0x81, 0x05, 0x20, 0x03, 0x01, 0x09, 0x04, 0x01,
    0x04, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05, 0x81, 0x05, 0x20, 0x0B, 0x01, 0x09, 0x04, 0x01,
    0x05, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05, 0x81, 0x05, 0x20, 0x13, 0x01, 0x09, 0x04, 0x01,
    0x06, 0x01, 0x0E, 0x02, 0x00, 0x00, 0x07, 0x05, 0x81, 0x05, 0x00, 0x14, 0x01, 0x08, 0x0B, 0x02,
    0x02, 0x01, 0x00, 0x00, 0x04, 0x09, 0x04, 0x02, 0x00, 0x00, 0x01, 0x01, 0x00, 0x04, 0x09, 0x24,
    0x01, 0x00, 0x01, 0x29, 0x00, 0x01, 0x03, 0x0C, 0x24, 0x02, 0x01, 0x01, 0x02, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x0B, 0x24, 0x06, 0x02, 0x01, 0x02, 0x01, 0x00, 0x02, 0x00, 0x00, 0x09, 0x24,
    0x03, 0x03, 0x01, 0x01, 0x00, 0x02, 0x00, 0x09, 0x04, 0x03, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00,
    0x09, 0x04, 0x03, 0x01, 0x01, 0x01, 0x02, 0x00, 0x00, 0x07, 0x24, 0x01, 0x03, 0x01, 0x01, 0x00,
    0x1D, 0x24, 0x02, 0x01, 0x01, 0x02, 0x10, 0x07, 0x40, 0x1F, 0x00, 0x11, 0x2B, 0x00, 0x80, 0x3E,
    0x00, 0x22, 0x56, 0x00, 0xC0, 0x5D, 0x00, 0x44, 0xAC, 0x00, 0x80, 0xBB, 0x00, 0x09, 0x05, 0x84,
    0x05, 0x90, 0x01, 0x04, 0x00, 0x00, 0x07, 0x25, 0x01, 0x01, 0x00, 0x00, 0x00
};

}
