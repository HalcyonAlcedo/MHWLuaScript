
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

GetVisualPtr proc
    mov [rcx], rbx
	ret
GetVisualPtr endp

GetWeaponOrnamentsPtr proc
    mov [rcx], rbx
	ret
GetWeaponOrnamentsPtr endp

end