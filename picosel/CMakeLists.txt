SET(picosel_src picosel.cpp ../common/unportable.cpp)

ADD_DEFINITIONS(-fPIC -DCXLM_NO_ENC -DCODE_CONVERSION_SUPPORT -DWSTRING_CONVERSION_SUPPORT -DREQUIRE_RNR)

ADD_EXECUTABLE(main ${picosel_src})

SET_TARGET_PROPERTIES(main 
                      PROPERTIES OUTPUT_NAME picosel)


#DEFS = -DOS_UBUNTU -DLITTLE_ENDIAN -DCXLM_NO_ENC -DCODE_CONVERSION_SUPPORT -DWSTRING_CONVERSION_SUPPORT -DREQUIRE_RNR
#
##OPTS = -O2 -I/usr/include/python2.5/
#OPTS = -O2 -fpermissive
#
##LIBS = -licule -licutu -licuio -licuuc -liculx -licudata -licui18n -lboost_thread-mt
#LIBS =
#
#OBJS = picosel.o unportable.o
#
#CC = g++
#
#.cpp.o:
#	$(CC) $(DEFS) $(OPTS) -c $< -o $@
#
#../ubuntu32/picosel: $(OBJS)
#	$(CC) $(LIBS) -o $@ $(OBJS)
#
#unportable.o: ../common/unportable.cpp
#	$(CC) $(DEFS) $(OPTS) -c $< -o $@
#
#clean:
#	@rm -f *.o
#
#.PHONY : clean
#
#


