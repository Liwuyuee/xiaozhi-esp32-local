export type QualityRange = {
  min: number;
  max: number;
  step?: number;
  default?: number;
};

export type ImageFormat = {
  id: string | number;
  description: string;
  quality?: QualityRange;
};

export type Resolution = {
  width: number;
  height: number;
};

export type Camera = {
  index: string | number;
  name?: string;
  src: string;
  currentFrameRate: number;
  currentImageFormat: number | string;
  currentImageFormatDescription?: string;
  currentQuality?: number;
  currentResolution: Resolution;
  imageFormats: ImageFormat[];
};
