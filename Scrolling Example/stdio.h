#define BUFSIZ 512

#ifndef FILE

struct _iobuf
	{
#ifdef pdp11		/* really #ifdef oldunix */
	char *_ptr;
	int _cnt;
#else
	int _cnt;
	char *_ptr;
#endif
	char *_base;
	int _bufsiz;
	short _flag;
	int _file;
	char *_fptr;		/* ANSI void * */
	char _tinybuf;		/* used when _IONBF */
	char *_filename;
	int (*_filbuf)();
	int (*_flsbuf)();
	int (*_readfunc)();
	int (*_writefunc)();
	long (*_seekfunc)();
	int (*_closefunc)();
	int (*_errfunc)();
	struct _iobuf *_next;
	/* spare? */
	};

#define FILE struct _iobuf

#endif

#define EOF (-1)

#define _IOFBF	    0
#define	_IOREAD	   01
#define	_IOWRT	   02
#define	_IONBF	   04
#define	_IOMYBUF  010
#define	_IOEOF	  020
#define	_IOERR	  040
#define	_IOSTRG	 0100
#define	_IOLBF	 0200
#define	_IORW	 0400
#define _IOFPTR	02000	/* I/O functions take _fptr instead of _file */
#define _IOSTFN	04000	/* filename statically allocated (don't free) */

#ifndef NULL
#define NULL 0
#endif

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

#define _NFILE 3	/* not used; only for compatibility */

extern FILE _iob[];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define getc(fp) ((fp)->_cnt-- > 0 ? (*(fp)->_ptr++ & 0377) : \
					_filbuf(fp))

#ifndef PUTCLBUF

#define putc(c, fp) ((fp)->_cnt-- > 0 ? (*(fp)->_ptr++ = (c)) : \
					_flsbuf(c, fp))

#else

#define putc(c, fp) ((fp)->_cnt-- > 0 ? \
		((*(fp)->_ptr = (c)) == '\n' && ((fp)->_flag & _IOLBF) ? \
					_flsbuf(*(fp)->_ptr, fp) : \
					*(fp)->_ptr++) \
		: _flsbuf(c, fp))

#endif

#define getchar() getc(stdin)
#define putchar(c) putc(c, stdout)

#define clearerr(fp) ((fp)->_flag &= ~(_IOEOF | _IOERR))
#define feof(fp) ((fp)->_flag & _IOEOF)
#define ferror(fp) ((fp)->_flag & _IOERR)

#define fileno(fp) ((fp)->_file)
#define _fileptr(fp) ((fp)->_fptr)

#ifndef __STDC__

extern FILE *fdopen();
extern char *fgets();
extern FILE *fopen();
extern FILE *freopen();
extern long int ftell();
extern char *gets();

#ifdef EXTENSIONS

extern char *saprintf();
extern FILE *stropen();
extern FILE *strnopen();
extern char *vsaprintf();

#endif

#else

#include <stdarg.h>		/* for va_list */

extern int fclose(FILE *);
extern FILE *fdopen(int, char *);
extern int fflush(FILE *);
extern int fgetc(FILE *);
extern char *fgets(char *, int, FILE *);
extern FILE *fopen(char *, char *);
extern int fprintf(FILE *, char *, ...);
extern int fputc(char, FILE *);
extern int fputs(char *, FILE *);
extern int fread(char *, unsigned int, int, FILE *);
extern FILE *freopen(char *, char *, FILE *);
extern int fscanf(FILE *, char *, ...);
extern int fseek(FILE *, long int, int);
extern long int ftell(FILE *);
extern int fwrite(char *, unsigned int, int, FILE *);
extern char *gets(char *);
/* getw? */
extern int printf(char *, ...);
extern int puts(char *);
/* putw? */
extern void rewind(FILE *);
extern int scanf(char *, ...);
extern int setbuf(FILE *, char *);
extern int setbuffer(FILE *, char *, int);	/* Berkeley */
extern int setlinebuf(FILE *);			/* Berkeley */
extern int setvbuf(FILE *, char *, int, int);
extern int sprintf(char *, char *, ...);
extern int sscanf(char *, char *, ...);
extern int ungetc(char, FILE *);
extern int vfprintf(FILE *, char *, va_list);
extern int vprintf(char *, va_list);
extern int vsprintf(char *, char *, va_list);

#ifdef EXTENSIONS

extern void fabort(FILE *);
extern int fdclose(FILE *);
extern int flushall(void);
extern int putpad(FILE *, char *, int, int, int);
extern char *saprintf(char *, ...);
extern int scanfiles(int (*)());
extern int seterrfn(FILE *, int (*)());
extern int setfuncs(FILE *, int (*)(), int (*)(), long int (*)(), int (*)());
extern int snprintf(char *, int, char *, ...);
extern FILE *stropen(char *, char *);
extern FILE *strnopen(char *, int, char *);
extern char *vsaprintf(char *, va_list);

#endif

#endif
