CC_PTHREAD_FLAGS     = -lpthread
CC_FLAGS             = -c
CC_OUTPUT_FLAGS      = -o
CC_MATH              = -lm
CC                   = gcc
RM                   = rm
RM_FLAGS             = -f

TARGET               = test
OBJS                 = linktable.o menu.o test.o

all:	$(OBJS)
	$(CC) $(CC_OUTPUT_FLAGS) $(TARGET) $(OBJS) $(CC_MATH)
 
.c.o:
	$(CC) $(CC_FLAGS) $<
     
clean:
	$(RM) $(RM_FLAGS) $(OBJS) $(TARGET) *.bak