SET(picosel_lib_src ../../picosel/picosel.cpp)

ADD_DEFINITIONS(-DOS_UBUNTU -DLITTLE_ENDIAN -DCXLM_NO_ENC -DCODE_CONVERSION_SUPPORT -DWSTRING_CONVERSION_SUPPORT -DREQUIRE_RNR -DBUILD_PICOSELLIB)

ADD_LIBRARY(picosel SHARED ${picosel_lib_src})

#DEFS = -DOS_UBUNTU -DLITTLE_ENDIAN -DCXLM_NO_ENC -DCODE_CONVERSION_SUPPORT -DWSTRING_CONVERSION_SUPPORT -DREQUIRE_RNR -DBUILD_PICOSELLIB
#
#OPTS = -O2 -fpermissive -fPIC -I/usr/lib/jvm/java-6-openjdk/include/
##OPTS = -O2 -fpermissive
#
##LIBS = -licule -licutu -licuio -licuuc -liculx -licudata -licui18n 
#
#OBJS = picosel.o /usr/lib/libboost_thread.so /usr/lib/libicule.so /usr/lib/libicutu.so /usr/lib/libicuio.so /usr/lib/libicuuc.so /usr/lib/libiculx.so /usr/lib/libicudata.so /usr/lib/libicui18n.so 
#
#CC = g++
#
#../../ubuntu32/libpicosellib.so: $(OBJS)
#	$(CC) $(LIBS) -shared -o $@ $(OBJS)
#
#.cpp.o:
#	$(CC) $(DEFS) $(OPTS) -c $< -o $@
#
#picosel.o: ../../picosel/picosel.cpp
#	$(CC) $(DEFS) $(OPTS) -c $< -o $@
#
#clean:
#	@rm -f *.o
#
#.PHONY : clean
#
#
