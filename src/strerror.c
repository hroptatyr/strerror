/*** strerror.c -- like strerror(3) but for the command line
 *
 * Copyright (C) 2013-2014 Sebastian Freundt
 *
 * Author:  Sebastian Freundt <devel@fresse.org>
 *
 * This file is part of strerror.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the author nor the names of any contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ***/
#if defined HAVE_CONFIG_H
# include "config.h"
#endif	/* HAVE_CONFIG_H */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if !defined HAVE_STRERROR
# error bad bad luck, mate; contrary to intuition this tool is based on strerror(3)
#endif	/* !HAVE_STRERROR */


/* errno -> errno literal converter */
#if !defined HAVE_STRERRNO
# include "strerrno.c"

static const char*
strerrno(const char *eno)
{
	const struct strerrno_s *tmp;

	if ((tmp = __strerrno(eno, strlen(eno))) == NULL) {
		return NULL;
	}
	return tmp->str;
}
#endif	/* HAVE_STRERRNO */


/* errno literal -> errno converter */
#include "errno-lit.c"

static int
errnostr(const char lit[static 1])
{
	const struct errno_lit_s *tmp;

	if ((tmp = errno_lit(lit, strlen(lit))) == NULL) {
		return -1;
	}
	return tmp->eno;
}


#include "strerror.yucc"

int
main(int argc, char *argv[])
{
	/* args */
	yuck_t argi[1U];
	/* business logic */
	int res = 0;

	/* parse the command line */
	if (yuck_parse(argi, argc, argv)) {
		res = 1;
		goto out;
	} else if (argi->nargs < 1U) {
		yuck_auto_help(argi);
		res = 1;
		goto out;
	}

	for (size_t i = 0U; i < argi->nargs; i++) {
		const char *inp = argi->args[i];
		const char *rnostr;
		const char *rorstr;
		long int x;

		if ((x = atol(inp)) > 0) {
			/* reuse inp as stringified number */
			if (argi->verbose_flag) {
				rnostr = strerrno(inp);
			}
		} else if ((x = errnostr(inp)) > 0) {
			if (argi->verbose_flag) {
				rnostr = inp;
			}
		}

		if (x <= 0 || (rorstr = strerror(x)) == NULL) {
			fprintf(stderr, "\
no error string associated with errno %ld (%s)\n", x, inp);
			continue;
		}

		if (!argi->verbose_flag) {
			puts(rorstr);
		} else {
			printf("%ld\t%s\t%s\n", x, rnostr, rorstr);
		}
	}

out:
	yuck_free(argi);
	return res;
}

/* strerror.c ends here */
