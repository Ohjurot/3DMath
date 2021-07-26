; Windows
%ifdef WINDOWS
; Define register normal
%define RRETURN RAX
%define RPARAM0 RCX
%define RPARAM1 RDX 
%define RPARAM2 R8
%define RPARAM3 R9
%define R32RETURN EAX
%define R32PARAM0 ECX
%define R32PARAM1 EDX 
%define R32PARAM2 R8D
%define R32PARAM3 R9D
%define R16RETURN AX
%define R16PARAM0 CX
%define R16PARAM1 DX 
%define R16PARAM2 R8W
%define R16PARAM3 R9W
; Float 
%define RFPARAM0 XMM0
%define RFPARAM1 XMM1
%define RFPARAM2 XMM2
%define RFPARAM3 XMM3
%endif

; Linux
%ifdef LINUX
; Define register normal
; %define RRETURN RAX
%define RPARAM0 RDI
%define RPARAM1 RSI 
%define RPARAM2 RDX
%define RPARAM3 RCX
%endif
