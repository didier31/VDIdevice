.SUFFIXES: .c .cpp .o



# This setting must be the same as used when building VBoxXPCOM.so.
# If you get a lot of unresolved symbols, try commenting it out.
VBOX_WITH_XPCOM_NAMESPACE_CLEANUP=1

PATH_XPCOM_IDL=$(PATH_XPCOM)/idl
XPCOM_INCLUDE=/usr/local/include/virtualbox
PATH_XPCOM=/usr/local/share/virtualbox-ose/
PATH_BIN=/usr/local/lib/virtualbox
INCS_XPCOM=-I$(XPCOM_INCLUDE) -I$(XPCOM_INCLUDE)/nsprpub -I$(XPCOM_INCLUDE)/string -I$(XPCOM_INCLUDE)/xpcom -I$(XPCOM_INCLUDE)/ipcd
INCS_PROJECT=-I../../include -Iinclude

.ifdef VBOX_WITH_XPCOM_NAMESPACE_CLEANUP
 DEFS_XPCOM+=VBOX_WITH_XPCOM_NAMESPACE_CLEANUP
.endif

# Adjust this to match your platform, pick from RT_OS_LINUX, RT_OS_WINDOWS,
# RT_OS_DARWIN, RT_OS_SOLARIS...
DEFS_XPCOM+=-DRT_OS_FREEBSD


#
# Link with the public XPCOM libraries
#

SRCS!=ls *.cpp
OBJS=${SRCS:.cpp=.o}

vdservice: $(OBJS)
	c++ -g -o $@ $^ \
$(OBJS) \
$(PATH_BIN)/VBoxXPCOM.so \
-Wl,-rpath $(PATH_BIN)/ \
-ldl -lpthread

.cpp.o:
	c++ -c -g -fshort-wchar $(INCS_PROJECT) $(INCS_XPCOM) -D$(DEFS_XPCOM) -o $@ $<

clean:
	rm -f *.o

