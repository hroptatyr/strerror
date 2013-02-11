strerror
========

[![Build Status](https://secure.travis-ci.org/hroptatyr/strerror.png?branch=master)](http://travis-ci.org/hroptatyr/strerror)

Just a nifty variant of `strerror(3)` for occasional usage.

  Documentation by example:

    strerror 11
    =>
      11	EAGAIN	Resource temporarily unavailable

    strerror ERANGE
    =>
      34	ERANGE	Numerical result out of range

  multiple arguments are possible:

    strerror 15 EBUSY
    =>
      15	ENOTBLK	Block device required
      16	EBUSY	Device or resource busy

That's pretty much all `strerror` will ever be able to do.
