 #../../../dep/vboxSDK/sdk/bindings/c/VBoxCAPIGlue.o: ../../../dep/vboxSDK/sdk/bindings/c/Makefile
#	make -C ../../../dep/vboxSDK/sdk/bindings/c/

libvbox: ../dep/libvbox/CMakeLists.txt
	test -d ../dep/libvbox/build || mkdir ../dep/libvbox/build
	cd ../dep/libvbox/build && cmake -DVirtualBoxSDK_DIR=../../vboxSDK/sdk/ -DVirtualBoxSDK_VERSION=7.0.20 -DVirtualBox_XPCOM_LIB=/usr/local/lib/virtualbox/VBoxXPCOM.so ..

vdservice: ../../../dep/vboxSDK/sdk/bindings/c/VBoxCAPIGlue.o vdservice.c
	cc vdservice.c ../../../dep/vboxSDK/sdk/bindings/c/VBoxCAPIGlue.o -o vdservice -lpthread \
-I../../../dep/vboxSDK/sdk/bindings/c/glue \
-I../../../dep/vboxSDK/sdk/bindings/c/include


