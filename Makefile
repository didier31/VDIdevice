
modctl:src/usr/modctl.c
	cc $< -o $@

SRCS=src/krn/vdevice/vdmc.cpp src/krn/vdevice/kthreadsafe_queue.cpp src/krn/vdevice/vd.cpp
KMOD=mod

.include <bsd.kmod.mk>

