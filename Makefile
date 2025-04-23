
modctl:src/usr/modctl.c
	cc $< -o $@

SRCS=src/krn/vdevice/vdmc.cpp src/krn/vdevice/vd.c 
KMOD=mod

.include <bsd.kmod.mk>

