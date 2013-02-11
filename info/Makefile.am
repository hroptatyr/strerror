# Help the Developers and yourself.  Just use the C locale and settings
# for the compilation. They can still be overriden by make LANG=<whatever>
# but that is general a not very good idea
LANG=C
LC_ALL=C

EXTRA_DIST =
CLEANFILES =

man1_MANS = strerror.man
EXTRA_DIST += $(man1_MANS)
EXTRA_DIST += strerror.ex
EXTRA_DIST += author.h2m

strerror.h2m: genh2m.sh $(top_builddir)/src/strerror$(EXEEXT) strerror.ex
	$(AM_V_GEN) $^ > $@
EXTRA_DIST += genh2m.sh
CLEANFILES += strerror.h2m

strerror.man: strerror.h2m
	$(AM_V_GEN) $(HELP2MAN) -S "$(PACKAGE_STRING)" -p "($(PACKAGE))$*" \
		-I $< \
		-I "$(srcdir)/author.h2m" \
		-o $@ $(top_builddir)/src/strerror$(EXEEXT)
CLEANFILES += strerror.man

## Makefile.am ends here
