### Makefile.am

AM_CPPFLAGS = -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600 -D_BSD_SOURCE
AM_LDFLAGS =

bin_PROGRAMS =
noinst_PROGRAMS =
lib_LTLIBRARIES =
noinst_LTLIBRARIES =
noinst_HEADERS =
BUILT_SOURCES =
EXTRA_DIST =
CLEANFILES = $(BUILT_SOURCES)


bin_PROGRAMS += strerror
strerror_SOURCES = strerror.c
strerror_SOURCES += strerror-clo.ggo
strerror_SOURCES += errno-lit.gperf.in
BUILT_SOURCES += strerror-clo.c strerror-clo.h
BUILT_SOURCES += errno-lit.gperf errno-lit.c
BUILT_SOURCES += strerrno.gperf strerrno.c

errno-lit.gperf: errno-lit.gperf.in errno-lit.def
	$(AM_V_GEN) $(AWK) '\
/^#define[ \t]+/ { \
  if (!sub(/^#define[ \t]+E/, "E")) { \
    next; \
  } \
  gsub(/[ \t]+/, ", "); \
} { \
  print; \
}' $? > $@

strerrno.gperf: strerrno.gperf.in errno-lit.def
	$(AM_V_GEN) $(AWK) '\
/^#define[ \t]+/ { \
  if (!sub(/^#define[ \t]+E/, "E")) { \
    next; \
  } else if (!(x = match($$0, /[ \t]+[0-9]+/))) { \
    next; \
  } \
  len = length($$0); \
  y = x + match(substr($$0, x, len + 1 - x), /[0-9]+/) - 1; \
  eno = substr($$0, y, len + 1 - y); \
  str = substr($$0, 1, x - 1); \
  $$0 = eno ", \"" str "\""; \
} { \
  print; \
}' $? > $@

errno-lit.def:
	$(AM_V_GEN) $(CPPDO) $(CPPFLAGS) -imacros errno.h /dev/null \
		> $@ || rm -f -- $@

## our rule for gengetopt
%.c %.h: %.ggo
	$(AM_V_GEN) $(GENGETOPT) -l -i $< -F $*

## our rule for gperf
%.c: %.gperf
	$(AM_V_GEN) $(GPERF) -L ANSI-C $< --output-file $@

# 
# Help the developers get nice post-processed source files

## Create preprocessor output (debugging purposes only)
.c.i:
	$(COMPILE) -E -o $@ $<

## Create assembler output (debugging purposes only)
.c.s:
	$(COMPILE) -S -c $(AM_CFLAGS) $<
