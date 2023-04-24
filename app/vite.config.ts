import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [vue()],
  build: {
    rollupOptions: {
        output: {
            dir: '../data',
            entryFileNames: 'app.js',
            assetFileNames: 'app.css',
            chunkFileNames: "chunk.js",
            manualChunks: undefined,
        }
    }
}
})
