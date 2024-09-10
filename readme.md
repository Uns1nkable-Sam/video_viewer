# Description

Тестовое задание

# Prerequisites

## OpenFrameworks

Скачать [отсюда](https://openframeworks.cc/download/), установить как сказано [здесь](https://openframeworks.cc/setup/linux-install/)

## CEF

Скачать [отсюда](https://cef-builds.spotifycdn.com/index.html#linux64), установить через CMake

## Crow

Скачать [отсюда] (https://github.com/CrowCpp/Crow), достаточно просто скачать и положить. Честно.

# Build and run

В директории с этим файлом выполнить

```
QBS=/home/raistlin/Qt/Tools/QtCreator/bin/qbs OF_ROOT=/home/raistlin/software/of_v0.12.0_linux64gcc6_release CEF_ROOT=/home/raistlin/software/cef_binary_128.4.9+g9840ad9+chromium-128.0.6613.120_linux64 CROW_ROOT=/home/raistlin/software/Crow/ make run
```

Переменные окружения нужные для сборки:

`QBS` - путь к исполняемому файлу qbs
`OF_ROOT` - путь к OpenFrameworks
`CEF_ROOT` - путь к CEF
`CROW_ROOT` - путь к репозиторию с Crow
