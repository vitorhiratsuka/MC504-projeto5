INCLUDES := -I../include -I../../ -I../../../../../usr/include/
CFLAGS := $(CFLAGS) -g -O2 -Wall -D_GNU_SOURCE -pthread $(INCLUDES) $(KHDR_INCLUDES)
LDLIBS := -lpthread -lrt

HEADERS := \
	
TEST_GEN_FILES := \
	weight

TEST_PROGS := run.sh

top_srcdir = ../../../../..
KSFT_KHDR_INSTALL := 1
DEFAULT_INSTALL_HDR_PATH := 1
include ../../lib.mk

$(TEST_GEN_FILES): $(HEADERS)
