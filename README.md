# ESP Web Config

A Platform IO library to configure ESP32 devices over a web interface.

## ❓ How it works

- Sets WiFi to Access point.
- Runs a web server from a static web app via SPIFFS.
- Uses web basic authentication (username/password).
- Accepts configuration data via a personalized form.
- Saves configuration to Non-volatile Storage.

## Web application

The served web app is located under `app` folder.
It's built with [Vue.js 3](https://vuejs.org/). Uses [Tailwindcss](https://tailwindcss.com/) for styling and [FormKit](https://formkit.com/) for dynamic form generation. No need to be concerned about the tech stack, we just need the bundle located under `data` folder.

## Form generation

The form definition is decoupled from the web application. It's defined by `schema.json` located under `data` folder. The schema is a JSON object interpreted by [Formkit](https://formkit.com/essentials/schema). It supports styling, validation, conditional rendering and more.

## Default configuration

- ssid: device's MAC address
- passphrase: 123456789
- username: admin
- password: 1234

## Usage

- Make sure `data` folder is located on your project root.
- Edit `schema.json` file depending on your use case.
- Build Filesystem image.
- Upload Filesystem image.
- Add `WebConfig` library to your project.

