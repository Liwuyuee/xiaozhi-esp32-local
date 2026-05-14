## Frame buffer size

<details>
<summary>Q1: My camera reports a `dwMaxVideoFrameSize` that is unnecessarily large during format negotiation, causing excessive RAM usage. How can I reduce this?</summary>

You can limit RAM usage during UVC stream opening by configuring the frame buffer size in the `uvc_host_stream_config_t.advanced.frame_size` parameter of the uvc_host_stream_open call. The table below provides frame sizes for typical video resolutions and standard MJPEG compression ratios, which can help you choose an appropriate size.

> **Note**: If you configure the frame buffer size smaller than the reported `dwMaxVideoFrameSize`, you might occasionally encounter the `UVC_HOST_FRAME_BUFFER_OVERFLOW` event. This indicates that the actual received frame exceeded the allocated buffer size.


| Resolution         | Width (px) | Height (px) | Uncompressed Size (kB) | Compressed Size (10:1) (kB) | Compressed Size (15:1) (kB) | Compressed Size (20:1) (kB) |
|--------------------|------------|-------------|------------------------|----------------------------|-----------------------------|-----------------------------|
| QQVGA              | 160        | 120         | 56.25                  | 5.63                       | 3.75                        | 2.81                        |
| HQVGA              | 240        | 160         | 112.50                 | 11.25                      | 7.50                        | 5.63                        |
| QVGA               | 320        | 240         | 225.00                 | 22.50                      | 15.00                       | 11.25                       |
| VGA                | 640        | 480         | 900.00                 | 90.00                      | 60.00                       | 45.00                       |
| SVGA               | 800        | 600         | 1406.25                | 140.63                     | 93.75                       | 70.31                       |
| XGA                | 1,024      | 768         | 2304.00                | 230.40                     | 153.60                      | 115.20                      |
| HD                 | 1,280      | 720         | 2700.00                | 270.00                     | 180.00                      | 135.00                      |
| WXGA               | 1,280      | 800         | 3000.00                | 300.00                     | 200.00                      | 150.00                      |
| SXGA               | 1,280      | 1,024       | 3840.00                | 384.00                     | 256.00                      | 192.00                      |
| UXGA               | 1,600      | 1,200       | 5625.00                | 562.50                     | 375.00                      | 281.25                      |
| Full HD (1080p)    | 1,920      | 1,080       | 6075.00                | 607.50                     | 405.00                      | 303.75                      |
| WUXGA              | 1,920      | 1,200       | 6750.00                | 675.00                     | 450.00                      | 337.50                      |
| QHD (1440p)        | 2,560      | 1,440       | 10800.00               | 1080.00                    | 720.00                      | 540.00                      |
| 4K UHD             | 3,840      | 2,160       | 24300.00               | 2430.00                    | 1620.00                     | 1215.00                     |
| 5K                 | 5,120      | 2,880       | 43200.00               | 4320.00                    | 2880.00                     | 2160.00                     |
| 8K UHD             | 7,680      | 4,320       | 97200.00               | 9720.00                    | 6480.00                     | 4860.00                     |

</details>

## FAQ H265 encoding

<details>
<summary>Q1: I have two input frames inputI.hevc, which is full Intra-coded frame and a second inputP.hevc which is Predicted frame. How do I decode the second frame to png?</summary>

### Decoding a P-frame Using an I-frame in HEVC

To decode a P-frame using the corresponding I-frame, you need to combine both frames into a single stream since a P-frame requires the reference frame (I-frame) to be properly decoded. Here’s how you can do it using FFmpeg:

#### Step 1: Combine the I-frame and P-frame into a Single Stream

1. **Concatenate the frames**: Create a text file with the paths to the input HEVC files in the order they should be decoded.

   Create a file `inputs.txt` with the following content:
   ```plaintext
   file 'inputI.hevc'
   file 'inputP.hevc'
   ```

2. **Concatenate the HEVC files using FFmpeg**:
   ```sh
   ffmpeg -f concat -safe 0 -i inputs.txt -c copy combined.hevc
   ```

#### Step 2: Extract and Decode the Second Frame

1. **Decode the combined HEVC stream and extract the second frame**:
   ```sh
   ffmpeg -i combined.hevc -vf "select=eq(n\,1)" -vsync vfr second_frame.png
   ```

#### Explanation

- The `-f concat -safe 0 -i inputs.txt -c copy combined.hevc` command concatenates the I-frame and P-frame into a single HEVC file.
- The `-vf "select=eq(n\,1)" -vsync vfr second_frame.png` command extracts and decodes the second frame (P-frame) from the combined stream.

#### Complete Command Sequence

1. **Create `inputs.txt`**:
   ```plaintext
   file 'inputI.hevc'
   file 'inputP.hevc'
   ```

2. **Combine the HEVC files**:
   ```sh
   ffmpeg -f concat -safe 0 -i inputs.txt -c copy combined.hevc
   ```

3. **Extract and decode the second frame**:
   ```sh
   ffmpeg -i combined.hevc -vf "select=eq(n\,1)" -vsync vfr second_frame.png
   ```

By following these steps, you should be able to decode the second frame (P-frame) using the initial I-frame and convert it to PNG.

</details>
