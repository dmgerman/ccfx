SET(easytorq_lib_src ../easytorq/easytorq.cpp ../interpreter.cpp pyeasytorq.cpp ../texttoken.cpp ../torqcommon.cpp ../../common/unportable.cpp ../../common/utf8support.cpp)

ADD_DEFINITIONS(-fPIC -DCXLM_NO_ENC -DCODE_CONVERSION_SUPPORT -DWSTRING_CONVERSION_SUPPORT -DREQUIRE_RNR)


ADD_LIBRARY(easytorq SHARED ${easytorq_lib_src})
TARGET_LINK_LIBRARIES(easytorq ${ICU_LIBRARIES})
TARGET_LINK_LIBRARIES(easytorq ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(easytorq ${PYTHON_LIBRARIES})



#DEFS = -DOS_UBUNTU -DLITTLE_ENDIAN -DCXLM_NO_ENC -DCODE_CONVERSION_SUPPORT -DWSTRING_CONVERSION_SUPPORT -DREQUIRE_RNR
#
##OPTS = -O2 -fpermissive -I/usr/include/python2.6/
#OPTS = -O2 -fpermissive -fPIC -I/usr/include/python2.7/
#
#
##OPTS = -O2 -fpermissive
#
#LIBS = -licule -licutu -licuio -licuuc -liculx -licudata -licui18n -lboost_thread
##LIBS = -licule -licutu -licuio -licuuc -liculx -licudata -licui18n 
#
#OBJS = easytorq.o interpreter.o pyeasytorq.o texttoken.o torqcommon.o unportable.o utf8support.o
##OBJS = easytorq.o interpreter.o pyeasytorq.o texttoken.o torqcommon.o unportable.o utf8support.o /usr/lib/libboost_thread.so.1.46.1
##OBJS = /usr/lib/libboost_thread.so.1.46.1 /usr/lib/libicule.so /usr/lib/libicutu.so /usr/lib/libicuio.so /usr/lib/libicuuc.so /usr/lib/libiculx.so /usr/lib/libicudata.so /usr/lib/libicui18n.so 
#
#CC = g++
#
#../../ubuntu32/scripts/easytorq.so: $(OBJS)
#	$(CC) -shared -o $@ $(OBJS) $(LIBS)  -lpython2.7 -Wl
#
#
#.cpp.o:
#	$(CC) $(DEFS) $(OPTS) -c $< -o $@
#
#easytorq.o: ../easytorq/easytorq.cpp
#	$(CC) $(DEFS) $(OPTS) -c $< -o $@
#
#interpreter.o: ../interpreter.cpp
#	$(CC) $(DEFS) $(OPTS) -c $< -o $@
#
#texttoken.o: ../texttoken.cpp
#	$(CC) $(DEFS) $(OPTS) -c $< -o $@
#
#torqcommon.o: ../torqcommon.cpp
#	$(CC) $(DEFS) $(OPTS) -c $< -o $@
#
#unportable.o: ../../common/unportable.cpp
#	$(CC) $(DEFS) $(OPTS) -c $< -o $@
#
#utf8support.o: ../../common/utf8support.cpp
#	$(CC) $(DEFS) $(OPTS) -c $< -o $@
#
#clean:
#	@rm -f *.o
#
#.PHONY : clean
#
#
