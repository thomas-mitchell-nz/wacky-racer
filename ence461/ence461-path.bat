@ECHO OFF
cls

set GCC_EXEC_PREFIX=
set DEV_PATH=%~dp0tool-chain\

SET PATH=%DEV_PATH%msys64\usr\bin;%DEV_PATH%gcc-arm-none-eabi-9-2019-q4\bin;%DEV_PATH%msys64;%DEV_PATH%OpenOCD-0.10.0\bin;%PATH%

ECHO PATH SET FOR ARM EMBEDDED DEVELOPMENT.
ECHO SEE %DEV_PATH% FOR THE FILES.
ECHO **************************************************
ls %DEV_PATH%gcc-arm-none-eabi-9-2019-q4\bin
