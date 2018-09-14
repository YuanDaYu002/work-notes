.PHONY: all clean

SUBDIRS=libencoder libamazon libstream main
	
all:
	$(foreach D, $(SUBDIRS), make -C $(D) all;)
	
clean:
	$(foreach D, $(SUBDIRS), make -C $(D) clean;)
	