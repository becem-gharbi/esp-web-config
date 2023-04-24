const FormKitVariants = require("@formkit/themes/tailwindcss");

export default {
  content: [
    "./index.html",
    "./src/**/*.{vue,js,ts,jsx,tsx}",
    "./node_modules/@formkit/themes/dist/tailwindcss/genesis/index.cjs",
  ],
  theme: {
    extend: {},
  },
  plugins: [FormKitVariants],
};
