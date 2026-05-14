import type { MockHandler } from "vite-plugin-mock-server";
import type { Camera } from "../src/camera";

const mockCameras: Camera[] = [
  {
    index: 0,
    name: "Front Camera",
    src: "https://picsum.photos/640/480",
    currentFrameRate: 30,
    currentImageFormat: 1,
    currentImageFormatDescription: "RGB 5-6-5 640x480",
    currentQuality: 85,
    currentResolution: {
      width: 640,
      height: 480,
    },
    imageFormats: [
      {
        id: 1,
        description: "RGB 5-6-5 640x480",
        quality: {
          min: 50,
          max: 100,
          step: 5,
          default: 85,
        },
      },
      {
        id: 2,
        description: "RGB 8-8-8 640x480",
        quality: {
          min: 80,
          max: 100,
          step: 1,
          default: 95,
        },
      },
    ],
  },
  {
    index: 1,
    name: "Back Camera",
    src: "https://picsum.photos/1920/1080",
    currentFrameRate: 25,
    currentImageFormat: 1,
    currentImageFormatDescription: "RGB 5-6-5 1920x1080",
    currentQuality: 90,
    currentResolution: {
      width: 1920,
      height: 1080,
    },
    imageFormats: [
      {
        id: 1,
        description: "RGB 5-6-5 1920x1080",
        quality: {
          min: 50,
          max: 100,
          step: 5,
          default: 90,
        },
      },
      {
        id: 2,
        description: "RGB 8-8-8 1920x1080",
        quality: {
          min: 80,
          max: 100,
          step: 1,
          default: 95,
        },
      },
      {
        id: 3,
        description: "RGB 8-8-8 1080x720",
        quality: {
          min: 60,
          max: 100,
          step: 10,
          default: 80,
        },
      },
    ],
  },
  {
    index: 2,
    name: "Side Camera",
    src: "https://picsum.photos/800/600",
    currentFrameRate: 15,
    currentImageFormat: 2,
    currentImageFormatDescription: "RGB 8-8-8 800x600",
    currentQuality: 95,
    currentResolution: {
      width: 800,
      height: 600,
    },
    imageFormats: [
      {
        id: 1,
        description: "RGB 8-8-8 800x600",
        quality: {
          min: 50,
          max: 100,
          step: 5,
          default: 85,
        },
      },
      {
        id: 2,
        description: "YUV 4-2-2 800x600",
        quality: {
          min: 80,
          max: 100,
          step: 1,
          default: 95,
        },
      },
    ],
  },
];

const updateCameraSrc = (camera: Camera) => {
  const { width, height } = camera.currentResolution;
  camera.src = `https://picsum.photos/${width}/${height}`;
};

export default (): MockHandler[] => [
  {
    pattern: "/api/get_camera_info",
    method: "GET",
    handle: (req, res) => {
      res.setHeader("Content-Type", "application/json");
      res.end(
        JSON.stringify({
          cameras: mockCameras,
        })
      );
    },
  },

  {
    pattern: "/api/capture_image",
    method: "GET",
    handle: (req, res) => {
      const url = new URL(req.url!, `http://${req.headers.host}`);
      const source = url.searchParams.get("source");

      if (!source) {
        res.statusCode = 400;
        res.end("Missing source parameter");
        return;
      }

      const camera = mockCameras.find((cam) => cam.index.toString() === source);
      if (!camera) {
        res.statusCode = 404;
        res.end("Camera not found");
        return;
      }

      res.statusCode = 302;
      res.setHeader(
        "Location",
        `https://picsum.photos/${camera.currentResolution.width}/${camera.currentResolution.height}`
      );
      res.end();
    },
  },

  {
    pattern: "/api/capture_binary",
    method: "GET",
    handle: (req, res) => {
      const url = new URL(req.url!, `http://${req.headers.host}`);
      const source = url.searchParams.get("source");

      if (!source) {
        res.statusCode = 400;
        res.end("Missing source parameter");
        return;
      }

      const camera = mockCameras.find((cam) => cam.index.toString() === source);
      if (!camera) {
        res.statusCode = 404;
        res.end("Camera not found");
        return;
      }

      const mockBinaryData = Buffer.from(
        `Mock binary data for camera ${source}`,
        "utf-8"
      );
      res.setHeader("Content-Type", "application/octet-stream");
      res.setHeader(
        "Content-Disposition",
        `attachment; filename="camera_${source}_raw.bin"`
      );
      res.end(mockBinaryData);
    },
  },

  {
    pattern: "/api/set_camera_config",
    method: "POST",
    handle: (req, res) => {
      let body = "";
      req.on("data", (chunk) => {
        body += chunk.toString();
      });

      req.on("end", () => {
        try {
          const config = JSON.parse(body);
          const { index, image_format, jpeg_quality } = config;

          const camera = mockCameras.find(
            (cam) => cam.index.toString() === index.toString()
          );
          if (!camera) {
            res.statusCode = 404;
            res.setHeader("Content-Type", "application/json");
            res.end(JSON.stringify({ error: "Camera not found" }));
            return;
          }

          if (image_format !== undefined) {
            camera.currentImageFormat = image_format;
            const format = camera.imageFormats.find(
              (f) => f.id === image_format
            );
            if (format) {
              camera.currentImageFormatDescription = format.description;
            }
          }

          if (jpeg_quality !== undefined) {
            camera.currentQuality = jpeg_quality;
          }

          updateCameraSrc(camera);

          res.setHeader("Content-Type", "application/json");
          res.end(
            JSON.stringify({
              success: true,
              message: "Camera configuration updated successfully",
            })
          );
        } catch (error) {
          console.error(error);
          res.statusCode = 400;
          res.setHeader("Content-Type", "application/json");
          res.end(JSON.stringify({ error: "Invalid JSON in request body" }));
        }
      });
    },
  },
];
