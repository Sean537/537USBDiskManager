/* Code generated by cmd/cgo; DO NOT EDIT. */

/* package command-line-arguments */


#line 1 "cgo-builtin-export-prolog"

#include <stddef.h>

#ifndef GO_CGO_EXPORT_PROLOGUE_H
#define GO_CGO_EXPORT_PROLOGUE_H

#ifndef GO_CGO_GOSTRING_TYPEDEF
typedef struct { const char *p; ptrdiff_t n; } _GoString_;
#endif

#endif

/* Start of preamble from import "C" comments.  */




/* End of preamble from import "C" comments.  */


/* Start of boilerplate cgo prologue.  */
#line 1 "cgo-gcc-export-header-prolog"

#ifndef GO_CGO_PROLOGUE_H
#define GO_CGO_PROLOGUE_H

typedef signed char GoInt8;
typedef unsigned char GoUint8;
typedef short GoInt16;
typedef unsigned short GoUint16;
typedef int GoInt32;
typedef unsigned int GoUint32;
typedef long long GoInt64;
typedef unsigned long long GoUint64;
typedef GoInt64 GoInt;
typedef GoUint64 GoUint;
typedef size_t GoUintptr;
typedef float GoFloat32;
typedef double GoFloat64;
#ifdef _MSC_VER
#include <complex.h>
typedef _Fcomplex GoComplex64;
typedef _Dcomplex GoComplex128;
#else
typedef float _Complex GoComplex64;
typedef double _Complex GoComplex128;
#endif

/*
  static assertion to make sure the file is being used on architecture
  at least with matching size of GoInt.
*/
typedef char _check_for_64_bit_pointer_matching_GoInt[sizeof(void*)==64/8 ? 1:-1];

#ifndef GO_CGO_GOSTRING_TYPEDEF
typedef _GoString_ GoString;
#endif
typedef void *GoMap;
typedef void *GoChan;
typedef struct { void *t; void *v; } GoInterface;
typedef struct { void *data; GoInt len; GoInt cap; } GoSlice;

#endif

/* End of boilerplate cgo prologue.  */

#ifdef __cplusplus
extern "C" {
#endif

extern __declspec(dllexport) GoInt NewHttpServe();
extern __declspec(dllexport) GoInt ListenHttp(GoString path, GoInt sock);
extern __declspec(dllexport) GoInt GetHttpConn(GoInt queue_id);
extern __declspec(dllexport) void WriteToHttpConn(GoInt sock, GoString data);
extern __declspec(dllexport) void ReadFromHttpConn(GoInt sock, GoString* buf);
extern __declspec(dllexport) GoUint8 HasConn(GoInt sock);
extern __declspec(dllexport) GoInt StartHttpServe(GoString addr, GoInt sock);
extern __declspec(dllexport) void NonBlocking(GoInt sock_id, GoInt ms);
extern __declspec(dllexport) GoInt Listen(GoString protocol, GoString ip);
extern __declspec(dllexport) GoInt Accept(GoInt listener);
extern __declspec(dllexport) GoInt Connect(GoString protocol, GoString ip);
extern __declspec(dllexport) GoInt Write(GoString data, GoInt sock_);
extern __declspec(dllexport) GoInt WriteToPacket(GoString data, GoInt sock_, GoInt to);
extern __declspec(dllexport) GoInt Read(GoString* data, GoInt sock_);
extern __declspec(dllexport) void GetError(GoInt ecode, GoString* buf);
extern __declspec(dllexport) void PrintError(GoInt ecode);
extern __declspec(dllexport) GoInt CloseSock(GoInt sock_);

#ifdef __cplusplus
}
#endif
