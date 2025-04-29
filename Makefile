
vdmcctl:src/usr/modctl.c
	cc $< -o $@

SRCS=src/krn/vdevice/vdmc.cpp  src/krn/vdevice/vd.cpp src/krn/vdevice/io_queue.cpp src/krn/vdevice/mod.c
KMOD=vdmc
CXXFLAGS += -ffreestanding -fno-exceptions -fno-rtti -fvisibility=hidden
CXXFLAGS += -nostdlib -fno-threadsafe-statics -fno-use-cxa-atexit

.include <bsd.kmod.mk>

