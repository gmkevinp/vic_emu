CC = clang-9
prg = vic_emu
src = $(wildcard src/*.c) \
      $(wildcard src/instructions/src/*.c)
obj = $(src:.c=.o)
dep = $(obj:.o=.d)
inc = -Isrc/inc -Isrc/instructions/inc

CFLAGS = -g $(inc)
LDFLAGS = -lGL -lglut

$(prg): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

-include $(dep)

%.d: %.c
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.c.o:
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean: cleandep
	rm -f $(obj) $(prg)

.PHONY:
cleandep:
	rm -f $(dep)
