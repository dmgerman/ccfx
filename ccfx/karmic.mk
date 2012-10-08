DEFS = -DOS_UBUNTU -DLITTLE_ENDIAN -DCXLM_NO_ENC -DCODE_CONVERSION_SUPPORT -DWSTRING_CONVERSION_SUPPORT -DREQUIRE_RNR

#OPTS = -O2 -I/usr/include/python2.5/
OPTS = -O2 -fpermissive

LIBS = -licule -licutu -licuio -licuuc -liculx -licudata -licui18n -lboost_thread-mt

OBJS = base64encoder.o bitvector.o ccfx.o ccfxcommon.o prettyprintermain.o rawclonepairdata.o unportable.o utf8support.o ccfxconstants.o

CC = g++

.cpp.o:
	$(CC) $(DEFS) $(OPTS) -c $< -o $@

../ubuntu32/ccfx: $(OBJS)
	$(CC) $(LIBS) -o $@ $(OBJS)

base64encoder.o: ../common/base64encoder.cpp
	$(CC) $(DEFS) $(OPTS) -c $< -o $@

bitvector.o: ../common/bitvector.cpp
	$(CC) $(DEFS) $(OPTS) -c $< -o $@

ccfx.o: ccfx.cpp

ccfxcommon.o: ccfxcommon.cpp

prettyprintermain.o: prettyprintermain.cpp

rawclonepairdata.o: rawclonepairdata.cpp

unportable.o: ../common/unportable.cpp
	$(CC) $(DEFS) $(OPTS) -c $< -o $@

utf8support.o: ../common/utf8support.cpp
	$(CC) $(DEFS) $(OPTS) -c $< -o $@

clean:
	@rm -f *.o

.PHONY: clean
