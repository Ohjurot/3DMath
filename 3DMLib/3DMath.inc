; Windows
%ifdef WINDOWS
; Define register normal
%define RRETURN RAX
%define RPARAM0 RCX
%define RPARAM1 RDX 
%define RPARAM2 R8
%define RPARAM3 R9
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
