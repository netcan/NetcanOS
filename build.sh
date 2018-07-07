#########################################################################
# File Name: build.sh
# Author: Netcan
# Blog: http://www.netcan666.com
# Mail: 1469709759@qq.com
# Created Time: 2018-07-06 Fri 18:55:13 CST
#########################################################################
#!/bin/bash

cd src
nasm -f bin -o bootloader.bin bootloader.asm || exit
cd ..
