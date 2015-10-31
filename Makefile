CONTIKI_PROJECT = ctrl_cell mr_cell admin_cell
all: $(CONTIKI_PROJECT)

#TARGET_LIBFILES += -lpthread -lm
#CFLAGS += -D FUNC_SWITCHER_matrix=false -D FUNC_SWITCHER_message=true -D FUNC_SWITCHER_som=false -D FUNC_SWITCHER_som_kohonenlayer_output=false -D FUNC_SWITCHER_som_train=false -D FUNC_SWITCHER_matrixcvm=false 
#CFLAGS +=-DFRAME_DEBUG
CONTIKI_SOURCEFILES += mysock.c
CONTIKI = ../..
include $(CONTIKI)/Makefile.include
