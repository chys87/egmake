.PHONY: all install clean test
.SUFFIXES:
.DELETE_ON_ERROR:

all: egmake.so

SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=%.o)

CC := gcc
CFLAGS := -O2 -march=native -flto -std=gnu99 -fPIC \
	-D_GNU_SOURCE -DNDEBUG \
	-fvisibility=hidden \
	-fmerge-all-constants -fno-common \
	-fno-ident \
	-Qn \
	-Wall -Wextra -Wno-shadow -Wwrite-strings -Wabi \
	-Wno-unused-parameter -Wno-missing-field-initializers \
	-Wno-sign-compare -Wno-clobbered \
	-Wformat -Wformat-security -Wmissing-include-dirs -Wfloat-equal \
	-Wlogical-op \
	-Wunused-macros \
	-Wunused-local-typedefs \
	-Werror=address \
	-Werror=endif-labels \
	-Werror=comment \
	-Werror=multichar \
	-Werror=pointer-arith \
	-Werror=char-subscripts \
	-Werror=format \
	-Werror=format-extra-args \
	-Wno-format-zero-length \
	-Werror=return-type \
	-Werror=overflow \
	-Werror=parentheses \
	-Werror=trigraphs \
	-Werror=pragmas -Werror=unknown-pragmas \
	-Werror=parentheses \
	-Werror=strict-aliasing \
	-Werror=trampolines \
	-Werror=switch \
	-Wswitch-enum \
	-Werror=address \
	-Werror=enum-compare \
	-Wdisabled-optimization \
	-Wsuggest-attribute=noreturn \
	-Werror=implicit-int \
	-Werror=implicit-function-declaration \
	-Werror=old-style-declaration -Werror=old-style-definition \
	-Werror=missing-parameter-type \
	-Werror=strict-prototypes \
	-Werror=jump-misses-init \
	-fmax-errors=5

LDFLAGS := -shared -Wl,--gc-section,--as-needed
INSTNAME := ~/bin/egmake.so

-include Makefile-spec

egmake.so: egmake-unstripped.so
	strip -v -o $@ $<

egmake-unstripped.so: $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.so *.o

install: $(INSTNAME)
$(INSTNAME): egmake.so
	install -m755 -C -T -v $< $@

define define_test
.PHONY: test-$(1)
test: test-$(1)
test-$(1):
	./gen_test_makefile.sh $(1) | make --no-print-directory -f -
endef
$(foreach src,$(SRCS),$(eval $(call define_test,$(src))))
