
modctl:src/usr/modctl.c
	cc $< -o $@

SRCS=src/mod/mod.c src/mod/device.c 
KMOD=mod

.include <bsd.kmod.mk>

