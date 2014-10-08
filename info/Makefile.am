include $(top_builddir)/version.mk

# Help the Developers and yourself.  Just use the C locale and settings
# for the compilation. They can still be overriden by make LANG=<whatever>
# but that is general a not very good idea
LANG=C
LC_ALL=C

EXTRA_DIST = $(BUILT_SOURCES)
CLEANFILES =
BUILT_SOURCES =

man1_MANS = strerror.man
EXTRA_DIST += $(man1_MANS)
EXTRA_DIST += strerror.ex
EXTRA_DIST += author.h2m
EXTRA_DIST += genh2m.sh
SUFFIXES =
BUILT_SOURCES += strerror.h2m
CLEANFILES += strerror.h2m

strerror.h2m: genh2m.sh $(top_builddir)/src/strerror$(EXEEXT) strerror.ex
	$(AM_V_GEN) PATH=$(VPATH):$(srcdir):"$${PATH}" $^ > $@

strerror.man: $(top_srcdir)/src/strerror.yuck
	$(AM_V_GEN) PATH="$(top_builddir)/build-aux:$${PATH}" \
	yuck$(EXEEXT) genman \
		--package "$(PACKAGE_NAME)" \
		-i "$(builddir)/strerror.h2m" \
		-i "$(srcdir)/author.h2m" \
		-o $@ --version-file "$(top_builddir)/.version" $<

CLEANFILES += strerror.man

## Makefile.am ends here
