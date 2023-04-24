//@ts-ignore
import App from "./App.vue";
import { createApp } from "vue";
import { plugin, defaultConfig } from "@formkit/vue";
import { generateClasses } from "@formkit/themes";
import theme from "./assets/formKitTheme";
import "./style.css";

createApp(App)
  .use(
    plugin,
    defaultConfig({
      config: {
        classes: generateClasses(theme),
      },
    })
  )
  .mount("#app");
