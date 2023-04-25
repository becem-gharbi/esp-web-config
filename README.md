# ESP Web Config

A Platform IO library to configure ESP32 devices over a web interface.

## ❓ How it works

- Sets WiFi to Access point.
- Runs a web server of a static web app from SPIFFS.
- Uses web basic authentication (username/password).
- Accepts configuration data via a personalized form.
- Saves configuration to Non-volatile Storage.

## Web application

The served web app is located under `app` folder.
It's built with [Vue.js 3](https://vuejs.org/). Uses [Tailwindcss](https://tailwindcss.com/) for styling and [FormKit](https://formkit.com/) for dynamic form generation. No need to be concerned about the tech stack, we just need the bundle located under `data` folder.

## Form generation

The form definition is decoupled from the web application. It's defined by `schema.json` located under `data` folder. The schema is a JSON object interpreted by [Formkit](https://formkit.com/essentials/schema). It supports styling, validation, conditional rendering and more.

## Default configuration

- host: 192.168.4.1:80
- ssid: device's MAC address
- passphrase: 123456789
- username: admin
- password: 1234

## Setup

- Download data folder from [link](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/becem-gharbi/esp-web-config/tree/main/data) and place it in your project root.
- Edit `schema.json` file depending on your use case.
- Build Filesystem image.
- Upload Filesystem image.

## Usage

The library exposes `WebConfig` class which has the following methods:

| Method | Description                                      |
| ------ | ------------------------------------------------ |
| read   | Get a configuration field                        |
| write  | Set a configuration field                        |
| begin  | Start the web server                             |
| end    | Stop the web server and restart the software     |
| reset  | Clear the configuration                          |
| init   | Initialize storage and set default configuration |

## License

[MIT License](./LICENSE)
