savedcmd_/home/ashu/Documents/linuxIPC-and-kernelModule/CustomKernelModule/myModule.mod := printf '%s\n'   myModule.o | awk '!x[$$0]++ { print("/home/ashu/Documents/linuxIPC-and-kernelModule/CustomKernelModule/"$$0) }' > /home/ashu/Documents/linuxIPC-and-kernelModule/CustomKernelModule/myModule.mod
