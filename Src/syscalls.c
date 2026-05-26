
/*
========================================================
TEAM CTRLBRAIN
Members: Iyasere, Bautista, and Miura
Course Term: Spring 2026

syscall.c
STM32L476RG Newlib System Call Stubs

Purpose:
Provides minimal system call implementations
for embedded bare-metal environment (no OS).
========================================================
*/

#include <sys/stat.h>
#include <errno.h>

/*======================================================
  SYSTEM CALL: _close
======================================================*/
int _close(int file)
{
    /*
    Not used in embedded systems (no file system)
    */

    return -1;

    /*
    Returns error code because file handling
    is not supported [1]
    */
}

/*======================================================
  SYSTEM CALL: _fstat
======================================================*/
int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;

    /*
    S_IFCHR = Character device [1]

    This tells the system:
    - standard input/output is treated as device
    */

    return 0;
}

/*======================================================
  SYSTEM CALL: _isatty
======================================================*/
int _isatty(int file)
{
    return 1;

    /*
    Always returns TRUE (1)

    Meaning:
    - system assumes terminal-like I/O device [2]
    */
}

/*======================================================
  SYSTEM CALL: _lseek
======================================================*/
int _lseek(int file, int ptr, int dir)
{
    return 0;

    /*
    No file positioning supported [1]

    Embedded systems usually do not use file offsets
    */
}

/*======================================================
  SYSTEM CALL: _read
======================================================*/
int _read(int file, char *ptr, int len)
{
    return 0;

    /*
    No input stream implemented

    Could be replaced with:
    - UART receive
    - sensor input
    */
}
