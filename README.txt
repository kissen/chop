chop
====

Pipe text into chop and all output that would fall outside of your TTY is
skipped. Think of it like

      less --chop-long-lines

except the output is forwarded directly to stdout and not to some pager.

Example Usage
-------------

    chop < chop.c

Installation
------------

You only need a somewhat recent C compiler and GNU Make.

    make install

Caveats
-------

* Right now only single byte characters (i.e. ASCII) is supported because of
  course it is.

* This really should be a shell script.
