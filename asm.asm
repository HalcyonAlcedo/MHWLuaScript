
.data

.const

.code

Navigation proc
	fld dword ptr [rbp+000002D0h]
	fstp dword ptr [rcx]
	fld dword ptr [rbp+000002D4h]
	fstp dword ptr [rdx]
	fld dword ptr [rbp+000002D8h]
	fstp dword ptr [r8]
	ret
Navigation endp

GetRAXPtr proc
    mov [rcx], rax
	ret
GetRAXPtr endp

GetRBXPtr proc
    mov [rcx], rbx
	ret
GetRBXPtr endp

GetRDIPtr proc
    mov [rcx], rdi
	ret
GetRDIPtr endp

GetHitPtr proc
    mov rax, [rdi+24]
	mov [rcx], rax
	ret
GetHitPtr endp

SetEDX proc
    mov edx, [rcx]
	ret
SetEDX endp

end