@echo off
REM Eliminar la ROM anterior para evitar confusiones
DEL *.gb

REM Compilar los archivos .c de la carpeta src/ a archivos .o en la raíz
C:\gbdk\bin\lcc -c -o main.o src\main.c
C:\gbdk\bin\lcc -c -o player.o src\player.c

REM Unir los archivos .o y generar la ROM final
C:\gbdk\bin\lcc -o PoPoPop!.gb main.o player.o

REM Limpiar todos los archivos intermedios generados por el proceso
DEL *.asm
DEL *.lst
DEL *.ihx
DEL *.sym
DEL *.o
DEL *.map
DEL *.noi

echo Compilacion terminada.
