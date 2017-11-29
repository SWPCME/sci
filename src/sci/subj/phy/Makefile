# Makefile
# For core.

#
# Options.
#
# Directory.
SRC_DIR = ../../..
OBJ_DIR = $(TMP_DIR)/sci
# Search.
INCLUDE_DIR = -I$(HUB_H_DIR) -I$(SCI_DIR)

# Include.
OPT_LIST = $(SRC_DIR)/opt.lst
include $(OPT_LIST)

default: target_dir_default create_obj

clean: target_dir_clean clean_obj

install: target_dir_install
