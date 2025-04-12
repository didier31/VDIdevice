
modctl:src/usr/modctl.c
	cc $< -o $@

SRCS=src/krn/vdevice/vdmc.c src/krn/vdevice/vd.c 
KMOD=mod

.include <bsd.kmod.mk>

