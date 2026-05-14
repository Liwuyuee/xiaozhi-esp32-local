<template>
  <v-container max-width="600">
    <CameraCard v-for="(item, index) of mainStore.clientCameras" :key="index" :cam-num="index" />
  </v-container>

  <v-dialog v-model="webRequestErr" persistent>
    <div class="mx-auto my-auto text-center font-large">
      Web Request Error <br>
      Please Refresh This Page
    </div>
  </v-dialog>
</template>

<script lang="ts" setup>
import { ref } from 'vue';

import { useMainStore } from '@/store/mainstore';
import CameraCard from '@/components/CameraCard.vue';

const mainStore = useMainStore()

const webRequestErr = ref<boolean>(false)

onBeforeMount(() => {
  mainStore.updateCameraStatus();
})
</script>

<style lang="css" scoped>
.text-center {
  text-align: center;
}

.font-large {
  font-size: large;
}
</style>