### Makefile.am
include $(top_builddir)/version.mk

AM_CFLAGS = $(EXTRA_CFLAGS)
AM_CPPFLAGS = -D_POSIX_C_SOURCE=200112L -D_XOPEN_SOURCE=600 -D_BSD_SOURCE
AM_LDFLAGS =

bin_PROGRAMS =
noinst_PROGRAMS =
lib_LTLIBRARIES =
noinst_LTLIBRARIES =
noinst_HEADERS =
dist_built_sources =
nodist_built_sources =
BUILT_SOURCES = $(dist_built_sources) $(nodist_built_sources)
EXTRA_DIST = $(dist_built_sources)
CLEANFILES = $(nodist_built_sources)
SUFFIXES =

CLEANFILES += version.c
EXTRA_DIST += version.c.in

bin_PROGRAMS += strerror
strerror_SOURCES = strerror.c strerror.yuck
strerror_SOURCES += version.c version.h version.c.in
strerror_SOURCES += errno-lit.gperf.in
strerror_SOURCES += strerrno.gperf.in
strerror_CPPFLAGS = $(AM_CPPFLAGS)
strerror_CPPFLAGS += -DHAVE_VERSION_H
dist_built_sources += strerror.yucc
nodist_built_sources += errno-lit.gperf errno-lit.c
nodist_built_sources += strerrno.gperf strerrno.c

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
	$(AM_V_GEN) $(CPPDO) $(CPPFLAGS) -imacros errno.h -x c /dev/null \
		> $@ || rm -f -- $@
CLEANFILES += errno-lit.def

## version rules
version.c: version.c.in $(top_builddir)/.version
	$(AM_V_GEN) PATH="$(top_builddir)/build-aux:$${PATH}" \
		yuck$(EXEEXT) scmver --ignore-noscm --force -o $@ \
			--use-reference --reference $(top_builddir)/.version $<

## yuck rule
SUFFIXES += .yuck
SUFFIXES += .yucc
.yuck.yucc:
	$(AM_V_GEN) PATH=$(top_builddir)/build-aux:"$${PATH}" \
		yuck$(EXEEXT) gen -o $@ $<

## our rule for gperf
SUFFIXES += .gperf
.gperf.c:
	$(AM_V_GEN) $(GPERF) -L ANSI-C $< --output-file $@

# 
# Help the developers get nice post-processed source files

## Create preprocessor output (debugging purposes only)
.c.i:
	$(COMPILE) -E -o $@ $<

## Create assembler output (debugging purposes only)
.c.s:
	$(COMPILE) -S -c $(AM_CFLAGS) $<
