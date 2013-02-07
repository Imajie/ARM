DIRS=src startup include

TARGET=jaguar

OUT_FORMAT=srec

# ARM CPU setup
CPU=cortex-m0
INST_SET=-mthumb

LINK_SCRIPT=scripts/linker.ld
LINK_FLAGS=-nostartfiles -Wl,-Map,$(TARGET).map

ARM_FLAGS=-O0 -Wall 
ARM_DEBUG=-gdwarf-2 -g3

ARM_FLAGS+=-fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"

CROSS=arm-none-eabi-
#
# Don't edit below this line
#

CC=$(CROSS)gcc
OBJCP=$(CROSS)objcopy

#
# Find all sources to build
#
C_SRCS=$(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))

OBJS=$(subst .c,.o,$(C_SRCS))

ARM_FLAGS+=-mcpu=$(CPU) $(INST_SET) -mtune=$(CPU) $(ARM_DEBUG)
CFLAGS=$(foreach dir,$(DIRS),-I$(dir))

CFLAGS+=$(ARM_FLAGS)

#
# Make targets
#
all: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	$(OBJCP) -O $(OUT_FORMAT) $< $@

$(TARGET).elf: $(OBJS)
	$(CC) -o $@ -T $(LINK_SCRIPT) $(LINK_FLAGS) $(CFLAGS) $(OBJS)

.PHONY: clean realclean depend program

clean:
	@-rm $(OBJS)

realclean: clean
	@-rm $(TARGET).elf $(TARGET).hex $(TARGET).map

depend:
	@-makedepend -- $(C_FLAGS) -- $(C_SRCS) 2> /dev/null
	@-rm Makefile.bak

program: all
	../program.sh /dev/sdb $(TARGET).hex

# DO NOT DELETE

src/jaguar.o: /usr/include/stdlib.h /usr/include/features.h
src/jaguar.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
src/jaguar.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/jaguar.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/jaguar.o: /usr/include/endian.h /usr/include/bits/endian.h
src/jaguar.o: /usr/include/bits/byteswap.h /usr/include/bits/types.h
src/jaguar.o: /usr/include/bits/typesizes.h /usr/include/bits/byteswap-16.h
src/jaguar.o: /usr/include/sys/types.h /usr/include/time.h
src/jaguar.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/jaguar.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/jaguar.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
src/jaguar.o: /usr/include/bits/stdlib-float.h
startup/low_level_init.o: /usr/include/stdint.h /usr/include/features.h
startup/low_level_init.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
startup/low_level_init.o: /usr/include/bits/wordsize.h
startup/low_level_init.o: /usr/include/gnu/stubs.h /usr/include/bits/wchar.h
startup/vectors.o: /usr/include/stdint.h /usr/include/features.h
startup/vectors.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
startup/vectors.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
startup/vectors.o: /usr/include/bits/wchar.h
startup/startup.o: /usr/include/stdint.h /usr/include/features.h
startup/startup.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
startup/startup.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
startup/startup.o: /usr/include/bits/wchar.h
