<template>
  <div class="page-center">
    <div class="p-4 w-full sm:max-w-xs">
      <component :is="currentView" />
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref, computed } from 'vue'
import Home from "./components/Home.vue"
import Login from "./components/Login.vue"

const routes: Record<string, any> = {
  '/home': Home,
  '/': Login
}

const loggedIn = ref(false)

const currentPath = ref("")

window.addEventListener('hashchange', () => {
  if (!loggedIn.value) {
    window.location.hash = "#/"
  }
  currentPath.value = window.location.hash
})

window.dispatchEvent(new Event("hashchange"))

const currentView = computed(() => {
  return routes[currentPath.value.slice(1) || '/']
})

</script>