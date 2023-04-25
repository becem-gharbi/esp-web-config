<template>
  <Suspense>
    <div class="page-center p-2">
      <div class="w-full max-w-sm rounded-lg overflow-hidden shadow-md p-4 my-5">
        <Form></Form>
      </div>
    </div>
  </Suspense>
</template>

<script setup lang="ts">
import Form from "./components/Form.vue"
</script>