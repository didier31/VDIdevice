 ../../../dep/vboxSDK/sdk/bindings/c/VBoxCAPIGlue.o: ../../../dep/vboxSDK/sdk/bindings/c/Makefile
	make -C ../../../dep/vboxSDK/sdk/bindings/c/

vdservice: ../../../dep/vboxSDK/sdk/bindings/c/VBoxCAPIGlue.o vdservice.c
	cc vdservice.c ../../../dep/vboxSDK/sdk/bindings/c/VBoxCAPIGlue.o -o vdservice -lpthread -I../../../dep/vboxSDK/sdk/bindings/c/glue -I../../../dep/vboxSDK/sdk/bindings/c/include
