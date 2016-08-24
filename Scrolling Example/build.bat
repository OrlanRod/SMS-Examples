@echo off 
set PATH="Location to wherever you have SDCC's Bin";%PATH%
echo Build assets.c and assets.h from assets folder
folder2c assets assets
sdcc -c -mz80 assets.c
if %errorlevel% NEQ 0 goto :EOF
echo Build Main
sdcc -c -mz80 main.c
if %errorlevel% NEQ 0 goto :EOF
echo Linking 
sdcc -o game.ihx -mz80 --data-loc 0xC000 --no-std-crt0 crt0_sms.rel main.rel SMSlib.lib PSGlib.rel assets.rel
if %errorlevel% NEQ 0 goto :EOF
ihx2sms game.ihx game.sms 