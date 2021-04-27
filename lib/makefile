# REQUIRES GMAKE!!!!
#
# wgrib2 uses components of varying copyrights and licences.  See wgrib2/LICENSE-wgrib2
#
# makefile for grib2/lib/wgrib2api.lib
# 
SHELL=/bin/sh
# SHELL=/bin/ksh
.SUFFIXES: .x

# list of all libraries
libs:=$(wildcard *.a)

# remove libwgrib2.a
libs:=$(libs:libwgrib2.a=)
# remove libpng.a - duplicated libpng12
libs:=$(libs:libpng.a=)

# .a -> .x
libs:=$(libs:.a=.x)
libsdir:=$(libs:.x=)

ifeq ($(MAKE_SHARED_LIB),gnu_linux)
   shared_lib:=libwgrib2.so
else if ($(MAKE_SHARED_LIB),gnu_mac)
   shared_lib:=libwgrib2.dylib
else
   shared_lib:=
endif


all:	${libs}
	touch libpng.a ; rm libpng.*
	$(AR) cr libwgrib2.a */*.o
ifeq ($(MAKE_SHARED_LIB),gnu_linux)
	${CC} -shared ${CPPFLAGS} -o ${shared_lib} */*.o ${LDFLAGS} 
else ifeq ($(MAKE_SHARED_LIB),gnu_mac)
	${CC} -dynamiclib ${CPPFLAGS} -o ${shared_lib} */*.o ${LDFLAGS} 
endif
	rm */*.o *.x
	rm -r ${libsdir}

clean:
	touch junk.la ; rm *.la
	touch junk.a ; rm *.a
ifneq ($(MAKE_SHARED_LIB),0)
	touch ${shared_lib} ; rm ${shared_lib}
endif
	touch junk.x ; rm  *.x
	touch junk.mod ; rm *.mod
	touch junk.h ; rm *.h
	mkdir -p pkgconfig && rm -r pkgconfig
	touch libjunk ; rm -r lib*

.a.x:   $(*).a
	mkdir -p $(*) && touch $(*)/junk && rm -r $(*)/*
	cd $(*) && $(AR) x ../$(*).a
	touch $*.x
