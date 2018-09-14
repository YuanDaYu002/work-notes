MY_PATH=$(shell pwd)
shangyun_SDK_PATH=$(MY_PATH)/shangyun/Release_PPCS_3.1.0

SRC=$(MY_PATH)/src
LDFLAG =-O2 -g -Wall -DLINUX -lpthread -l${P2P}_API -lstdc++ 
LDFLAG+=-I $(shangyun_SDK_PATH)/Include/PPCS 
LDFLAG+=-I $(MY_PATH)/include
LDFLAG+=-L $(shangyun_SDK_PATH)/Lib/${OS}/${BOARD}/libPPCS_API.a


ifeq ($(BOARD), x64)
LDFLAG+=-m64 
exe=64
else
	ifeq ($(BOARD), x86)
		LDFLAG+=-m32 
		exe=32
	endif
endif

ifeq ($(OS), Linux)
LDFLAG+=-Wl,-rpath=./
dylib=so
endif



all: clean
	$(CXX) $(SRC)/* -o $(MY_PATH)/out/main_$(exe) $(LDFLAG) -s
	#-s: Remove all symbol table and relocation information from the executable.



clean:
	rm -rf $(MY_PATH)/out/*  
	rm -rf $(MY_PATH)/obj/*

