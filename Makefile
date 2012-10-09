default: all

#SUBDIRS = utility/picosellib picosel ccfx/CCFinderXLib  ccfx torq/pyeasytorq 
SUBDIRS = ccfx torq/pyeasytorq ccfx/CCFinderXLib picosel utility/picosellib ubuntu32


all: 
	for dir in $(SUBDIRS); do \
	  [ -d $$dir ] && ( cd $$dir && $(MAKE) ) || exit 1; \
	done

clean:
	for dir in $(SUBDIRS); do \
	  [ -d $$dir ] && ( cd $$dir && $(MAKE) $@ ) || exit 1; \
	done

