import { defineStore } from "pinia";
import { ref } from "vue";
import type { Camera, } from "@/camera";

export const useMainStore = defineStore("main", () => {
  const clientCameras = ref<Camera[]>([]);
  const netRequestError = ref<boolean>(false);

  let updateIntervalId: ReturnType<typeof setInterval> | null = null;

  const updateCameraStatus = async () => {
    if (updateIntervalId) clearInterval(updateIntervalId);
    updateIntervalId = null;

    try {
      const response = await fetch("/api/get_camera_info");
      const data: {cameras: Camera[]} = await response.json();
      clientCameras.value.length = data.cameras.length;

      for (const camNum in data.cameras) {
        const camIndex = Number(camNum);
        clientCameras.value[camIndex] = data.cameras[camIndex];
      }
    } catch (e) {
      console.error(e);
      netRequestError.value = true;
    } finally {
      updateIntervalId = setInterval(updateCameraStatus, 3000);
    }
  }

  return {
    clientCameras,
    netRequestError,
    updateCameraStatus,
  };
});
