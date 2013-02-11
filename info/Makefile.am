# Help the Developers and yourself.  Just use the C locale and settings
# for the compilation. They can still be overriden by make LANG=<whatever>
# but that is general a not very good idea
LANG=C
LC_ALL=C

EXTRA_DIST =
CLEANFILES =

man1_MANS = strerror.1
EXTRA_DIST += $(man1_MANS)
EXTRA_DIST += strerror.ex

strerror.h2m: genh2m.sh $(top_builddir)/src/strerror$(EXEEXT) strerror.ex
	$(AM_V_GEN) $^ > $@
EXTRA_DIST += genh2m.sh
CLEANFILES += strerror.h2m

## Makefile.am ends here
