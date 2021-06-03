#pragma once
#include <Psapi.h>

namespace AobAddress {
    typedef unsigned char byte;

    /* Player_BasePtr OK
    * A0 81 F3 3F 00 00 00 00 20
    "MonsterHunterWorld.exe"+5073E68: 20 F7                       -  and bh,dh
    "MonsterHunterWorld.exe"+5073E6A: FF 44 01 00                 -  inc [rcx+rax+00]
    "MonsterHunterWorld.exe"+5073E6E: 00 00                       -  add [rax],al
    "MonsterHunterWorld.exe"+5073E70: 58                          -  pop rax
    "MonsterHunterWorld.exe"+5073E71: 4D 07                       -  pop es
    "MonsterHunterWorld.exe"+5073E73: 45 01 00                    -  add [r8],r8d
    "MonsterHunterWorld.exe"+5073E76: 00 00                       -  add [rax],al
    "MonsterHunterWorld.exe"+5073E78: 12 00                       -  adc al,byte ptr [rax]
    "MonsterHunterWorld.exe"+5073E7A: 80                          - db 80  // SHORTENED TO HIT INJECTION FROM:  add byte ptr [1B6BF0BE0],-60
    "MonsterHunterWorld.exe"+5073E7B: 05 5F CD B7 71              -  add eax,71B7CD5F
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+5073E80: A0 81 F3 3F 00 00 00 00 20  -  mov al,[20000000003FF381]
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+5073E89: D7                          -  xlatb 
    "MonsterHunterWorld.exe"+5073E8A: 45 43                       -  inc r11d
    "MonsterHunterWorld.exe"+5073E8C: 01 00                       -  add [rax],eax
    "MonsterHunterWorld.exe"+5073E8E: 00 00                       -  add [rax],al
    "MonsterHunterWorld.exe"+5073E90: E8 D2 45 43 01              -  call MonsterHunterWorld.exe+64A8467
    "MonsterHunterWorld.exe"+5073E95: 00 00                       -  add [rax],al
    "MonsterHunterWorld.exe"+5073E97: 00 88 7D FE 44 01           -  add [rax+0144FE7D],cl
    "MonsterHunterWorld.exe"+5073E9D: 00 00                       -  add [rax],al
    "MonsterHunterWorld.exe"+5073E9F: 00 00                       -  add [rax],al
    "MonsterHunterWorld.exe"+5073EA1: 00 00                       -  add [rax],al
    */
    struct vector<byte> Player_BasePtr = { 0xA0, 0x81, 0x1B, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x20 };

    /* Player_PlayerBasePlot OK
    * 60 D5 05 41 00 00
    "MonsterHunterWorld.exe"+5073EB8: B6 83                 -  mov dh,-7D
    "MonsterHunterWorld.exe"+5073EBA: 80 05 52 8D 30 67 00  -  add byte ptr [1AC37CC13],00
    "MonsterHunterWorld.exe"+5073EC1: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073EC3: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073EC5: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073EC7: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073EC9: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073ECB: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073ECD: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073ECF: 00 60                 - db 00 60  // SHORTENED TO HIT INJECTION FROM:  add [rax-2B],ah
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+5073ED1: D5 05                 -  aad 05
    "MonsterHunterWorld.exe"+5073ED3: 41 00 00              -  add [r8],al
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+5073ED6: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073ED8: 10 DA                 -  adc dl,bl
    "MonsterHunterWorld.exe"+5073EDA: 45 43                 -  inc r11d
    "MonsterHunterWorld.exe"+5073EDC: 01 00                 -  add [rax],eax
    "MonsterHunterWorld.exe"+5073EDE: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073EE0: A8 E2                 -  test al,-1E
    "MonsterHunterWorld.exe"+5073EE2: 45 43                 -  inc r11d
    "MonsterHunterWorld.exe"+5073EE4: 01 00                 -  add [rax],eax
    "MonsterHunterWorld.exe"+5073EE6: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073EE8: 00 A7 22 45 01 00     -  add [rdi+00014522],ah
    */
    struct vector<byte> Player_PlayerBasePlot = { 0x60, 0xD5, 0xB7, 0x3B, 0x00 };

    /* Player_ActionTrigger OK
    * 46 89 4C D1 1C
    "MonsterHunterWorld.exe"+226E903: 41 8D 42 01           -  lea eax,[r10+01]
    "MonsterHunterWorld.exe"+226E907: F3 0F 10 4C 24 38     -  movss xmm1,[rsp+38]
    "MonsterHunterWorld.exe"+226E90D: 4F 8D 14 92           -  lea r10,[r10+r10*4]
    "MonsterHunterWorld.exe"+226E911: 89 81 08 05 00 00     -  mov [rcx+00000508],eax
    "MonsterHunterWorld.exe"+226E917: 8B 44 24 28           -  mov eax,[rsp+28]
    "MonsterHunterWorld.exe"+226E91B: 42 89 44 D1 20        -  mov [rcx+r10*8+20],eax
    "MonsterHunterWorld.exe"+226E920: F3 42 0F 11 44 D1 24  -  movss [rcx+r10*8+24],xmm0
    "MonsterHunterWorld.exe"+226E927: F3 42 0F 11 4C D1 28  -  movss [rcx+r10*8+28],xmm1
    "MonsterHunterWorld.exe"+226E92E: 46 89 44 D1 18        -  mov [rcx+r10*8+18],r8d
    "MonsterHunterWorld.exe"+226E933: 4A 89 54 D1 10        -  mov [rcx+r10*8+10],rdx
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+226E938: 46 89 4C D1 1C        -  mov [rcx+r10*8+1C],r9d
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+226E93D: C3                    -  ret 
    "MonsterHunterWorld.exe"+226E93E: CC                    -  int 3 
    "MonsterHunterWorld.exe"+226E93F: CC                    -  int 3 
    "MonsterHunterWorld.exe"+226E940: 83 FA 04              -  cmp edx,04
    "MonsterHunterWorld.exe"+226E943: 0F 83 9C 0D 00 00     -  jae MonsterHunterWorld.exe+226F6E5
    "MonsterHunterWorld.exe"+226E949: 89 54 24 10           -  mov [rsp+10],edx
    "MonsterHunterWorld.exe"+226E94D: 4C 8B DC              -  mov r11,rsp
    "MonsterHunterWorld.exe"+226E950: 41 57                 -  push r15
    "MonsterHunterWorld.exe"+226E952: 48 83 EC 60           -  sub rsp,60
    "MonsterHunterWorld.exe"+226E956: 8B C2                 -  mov eax,edx
    */
    struct vector<byte> Player_ActionTrigger = { 0x46, 0x89, 0x4C, 0xD1, 0x1C };

    /* Player_Effects OK
    * E9 FB C8 FF FF
    "MonsterHunterWorld.exe"+AE3A85: 48 8B 5C 24 30        -  mov rbx,[rsp+30]
    "MonsterHunterWorld.exe"+AE3A8A: 48 83 C4 20           -  add rsp,20
    "MonsterHunterWorld.exe"+AE3A8E: 5F                    -  pop rdi
    "MonsterHunterWorld.exe"+AE3A8F: C3                    -  ret 
    "MonsterHunterWorld.exe"+AE3A90: 45 33 C0              -  xor r8d,r8d
    "MonsterHunterWorld.exe"+AE3A93: BA D3 07 00 00        -  mov edx,000007D3
    "MonsterHunterWorld.exe"+AE3A98: E9 03 C9 FF FF        -  jmp MonsterHunterWorld.exe+AE03A0
    "MonsterHunterWorld.exe"+AE3A9D: CC                    -  int 3 
    "MonsterHunterWorld.exe"+AE3A9E: CC                    -  int 3 
    "MonsterHunterWorld.exe"+AE3A9F: CC                    -  int 3 
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+AE3AA0: E9 FB C8 FF FF        -  jmp MonsterHunterWorld.exe+AE03A0
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+AE3AA5: CC                    -  int 3 
    "MonsterHunterWorld.exe"+AE3AA6: CC                    -  int 3 
    "MonsterHunterWorld.exe"+AE3AA7: CC                    -  int 3 
    "MonsterHunterWorld.exe"+AE3AA8: CC                    -  int 3 
    "MonsterHunterWorld.exe"+AE3AA9: CC                    -  int 3 
    "MonsterHunterWorld.exe"+AE3AAA: CC                    -  int 3 
    "MonsterHunterWorld.exe"+AE3AAB: CC                    -  int 3 
    "MonsterHunterWorld.exe"+AE3AAC: CC                    -  int 3 
    "MonsterHunterWorld.exe"+AE3AAD: CC                    -  int 3 
    "MonsterHunterWorld.exe"+AE3AAE: CC                    -  int 3 

    to -> E3 5F C3 CC CC CC CC CC CC CC CC CC 48 89 5C 24 08 48 89 74 24 10 57 48 81 EC 30
    "MonsterHunterWorld.exe"+AE0396: C3                                   -  ret
    "MonsterHunterWorld.exe"+AE0397: CC                                   -  int 3
    "MonsterHunterWorld.exe"+AE0398: CC                                   -  int 3
    "MonsterHunterWorld.exe"+AE0399: CC                                   -  int 3
    "MonsterHunterWorld.exe"+AE039A: CC                                   -  int 3
    "MonsterHunterWorld.exe"+AE039B: CC                                   -  int 3
    "MonsterHunterWorld.exe"+AE039C: CC                                   -  int 3
    "MonsterHunterWorld.exe"+AE039D: CC                                   -  int 3
    "MonsterHunterWorld.exe"+AE039E: CC                                   -  int 3
    "MonsterHunterWorld.exe"+AE039F: CC                                   -  int 3
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+AE03A0: 48 89 5C 24 08                       -  mov [rsp+08],rbx
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+AE03A5: 48 89 74 24 10                       -  mov [rsp+10],rsi
    "MonsterHunterWorld.exe"+AE03AA: 57                                   -  push rdi
    "MonsterHunterWorld.exe"+AE03AB: 48 81 EC 30 01 00 00                 -  sub rsp,00000130
    "MonsterHunterWorld.exe"+AE03B2: 48 8B F1                             -  mov rsi,rcx
    "MonsterHunterWorld.exe"+AE03B5: 41 8B D8                             -  mov ebx,r8d
    "MonsterHunterWorld.exe"+AE03B8: 48 8D 4C 24 40                       -  lea rcx,[rsp+40]
    "MonsterHunterWorld.exe"+AE03BD: 8B FA                                -  mov edi,edx
    "MonsterHunterWorld.exe"+AE03BF: E8 2C 76 86 01                       -  call MonsterHunterWorld.exe+23479F0
    "MonsterHunterWorld.exe"+AE03C4: F3 0F 10 05 B4 7A 3C 02              -  movss xmm0,[MonsterHunterWorld.exe+2EA7E80]
    "MonsterHunterWorld.exe"+AE03CC: 48 8D 05 3D 06 49 02                 -  lea rax,[MonsterHunterWorld.exe+2F70A10]
    */
    struct vector<byte> Player_Effects = { 0xE9, 0xFB, 0xC8, 0xFF, 0xFF };

    /* Player_Visual OK
    * 11 4B 08 48 8B 5C 24 60
    "MonsterHunterWorld.exe"+1FBB707: F3 0F 11 33              -  movss [rbx],xmm6
    "MonsterHunterWorld.exe"+1FBB70B: F3 0F 10 40 04           -  movss xmm0,[rax+04]
    "MonsterHunterWorld.exe"+1FBB710: F3 0F 58 43 04           -  addss xmm0,[rbx+04]
    "MonsterHunterWorld.exe"+1FBB715: F3 0F 11 43 04           -  movss [rbx+04],xmm0
    "MonsterHunterWorld.exe"+1FBB71A: F3 0F 10 48 08           -  movss xmm1,[rax+08]
    "MonsterHunterWorld.exe"+1FBB71F: F3 0F 58 4B 08           -  addss xmm1,[rbx+08]
    "MonsterHunterWorld.exe"+1FBB724: 48 8B 74 24 68           -  mov rsi,[rsp+68]
    "MonsterHunterWorld.exe"+1FBB729: 48 8B C3                 -  mov rax,rbx
    "MonsterHunterWorld.exe"+1FBB72C: 0F 28 74 24 40           -  movaps xmm6,[rsp+40]
    "MonsterHunterWorld.exe"+1FBB731: F3 0F 11 4B 08           -  movss [rbx+08],xmm1
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+1FBB736: 48 8B 5C 24 60           -  mov rbx,[rsp+60]
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+1FBB73B: 48 83 C4 50              -  add rsp,50
    "MonsterHunterWorld.exe"+1FBB73F: 5F                       -  pop rdi
    "MonsterHunterWorld.exe"+1FBB740: C3                       -  ret 
    "MonsterHunterWorld.exe"+1FBB741: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1FBB742: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1FBB743: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1FBB744: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1FBB745: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1FBB746: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1FBB747: CC                       -  int 3 
    */
    struct vector<byte> Player_Visual = { 0x11, 0x4B, 0x08, 0x48, 0x8B, 0x5C, 0x24, 0x60 };

    /* Player_PlayerDataPlot OK
    * F0 D9 F8 40 00 00
    "MonsterHunterWorld.exe"+522538E: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5225390: F0 C9                 - lock  leave 
    "MonsterHunterWorld.exe"+5225392: 09 45 01              -  or [rbp+01],eax
    "MonsterHunterWorld.exe"+5225395: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5225397: 00 98 8E 22 45 01     -  add [rax+0145228E],bl
    "MonsterHunterWorld.exe"+522539D: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+522539F: 00 AA 00 80 05 17     -  add [rdx+17058000],ch
    "MonsterHunterWorld.exe"+52253A5: FE                    -  db -02
    "MonsterHunterWorld.exe"+52253A6: 91                    -  xchg eax,ecx
    "MonsterHunterWorld.exe"+52253A7: 12                    - db 12  // SHORTENED TO HIT INJECTION FROM:  adc dh,al
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+52253A8: F0 D9 F8              - lock  fprem 
    "MonsterHunterWorld.exe"+52253AB: 40 00 00              -  add [rax],al
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+52253AE: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+52253B0: E0 8A                 -  loopne MonsterHunterWorld.exe+522533C
    "MonsterHunterWorld.exe"+52253B2: 56                    -  push rsi
    "MonsterHunterWorld.exe"+52253B3: 43 01 00              -  add [r8],eax
    "MonsterHunterWorld.exe"+52253B6: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+52253B8: 00 8B 56 43 01 00     -  add [rbx+00014356],cl
    "MonsterHunterWorld.exe"+52253BE: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+52253C0: B8 58 22 45 01        -  mov eax,01452258
    "MonsterHunterWorld.exe"+52253C5: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+52253C7: 00 30                 -  add [rax],dh
    */
    struct vector<byte> Player_PlayerDataPlot = { 0xF0, 0xD9, 0xF8, 0x40, 0x00, 0x00 };
    
    /* Player_PlayerDataHandlePlot OK
    * 70 2A ED 3F 00 00
    "MonsterHunterWorld.exe"+522C837: 00 D0                          -  add al,dl
    "MonsterHunterWorld.exe"+522C839: CA 22 45                       -  ret 4522
    "MonsterHunterWorld.exe"+522C83C: 01 00                          -  add [rax],eax
    "MonsterHunterWorld.exe"+522C83E: 00 00                          -  add [rax],al
    "MonsterHunterWorld.exe"+522C840: 06                             -  push es
    "MonsterHunterWorld.exe"+522C841: 00 80 05 60 4D 45              -  add [rax+454D6005],al
    "MonsterHunterWorld.exe"+522C847: 6C                             -  insb 
    "MonsterHunterWorld.exe"+522C848: E8 03 00 00 52                 -  call 19722C850
    "MonsterHunterWorld.exe"+522C84D: 2B 01                          -  sub eax,[rcx]
    "MonsterHunterWorld.exe"+522C84F: 00 70                          - db 00 70  // SHORTENED TO HIT INJECTION FROM:  add [rax+2A],dh
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+522C851: 2A ED                          -  sub ch,ch
    "MonsterHunterWorld.exe"+522C853: 3F                             -  db 3F
    "MonsterHunterWorld.exe"+522C854: 00 00                          -  add [rax],al
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+522C856: 00 00                          -  add [rax],al
    "MonsterHunterWorld.exe"+522C858: D0 2E                          -  shr byte ptr [rsi],1
    "MonsterHunterWorld.exe"+522C85A: 59                             -  pop rcx
    "MonsterHunterWorld.exe"+522C85B: 43 01 00                       -  add [r8],eax
    "MonsterHunterWorld.exe"+522C85E: 00 00                          -  add [rax],al
    "MonsterHunterWorld.exe"+522C860: 28 2F                          -  sub [rdi],ch
    "MonsterHunterWorld.exe"+522C862: 59                             -  pop rcx
    "MonsterHunterWorld.exe"+522C863: 43 01 00                       -  add [r8],eax
    "MonsterHunterWorld.exe"+522C866: 00 00                          -  add [rax],al
    "MonsterHunterWorld.exe"+522C868: D8 49 22                       -  fmul dword ptr [rcx+22]
    */
    struct vector<byte> Player_PlayerDataHandlePlot = { 0x70, 0x2A, 0xED, 0x3F, 0x00, 0x00 };

    /* EnvironmentalBiological_ctor OK
    * 48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 60 8B DA
    "MonsterHunterWorld.exe"+1D442A1: 48 8B 5C 24 30           -  mov rbx,[rsp+30]
    "MonsterHunterWorld.exe"+1D442A6: 48 8D 05 9B 2D 22 01     -  lea rax,[MonsterHunterWorld.exe+2F67048]
    "MonsterHunterWorld.exe"+1D442AD: 48 89 87 38 01 00 00     -  mov [rdi+00000138],rax
    "MonsterHunterWorld.exe"+1D442B4: 48 8B C7                 -  mov rax,rdi
    "MonsterHunterWorld.exe"+1D442B7: 48 83 C4 20              -  add rsp,20
    "MonsterHunterWorld.exe"+1D442BB: 5F                       -  pop rdi
    "MonsterHunterWorld.exe"+1D442BC: C3                       -  ret 
    "MonsterHunterWorld.exe"+1D442BD: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1D442BE: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1D442BF: CC                       -  int 3 
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+1D442C0: 48 89 5C 24 08           -  mov [rsp+08],rbx
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+1D442C5: 48 89 74 24 10           -  mov [rsp+10],rsi
    "MonsterHunterWorld.exe"+1D442CA: 57                       -  push rdi
    "MonsterHunterWorld.exe"+1D442CB: 48 83 EC 60              -  sub rsp,60
    "MonsterHunterWorld.exe"+1D442CF: 8B DA                    -  mov ebx,edx
    "MonsterHunterWorld.exe"+1D442D1: 48 8B F9                 -  mov rdi,rcx
    "MonsterHunterWorld.exe"+1D442D4: E8 57 D0 FB FF           -  call MonsterHunterWorld.exe+1D01330
    "MonsterHunterWorld.exe"+1D442D9: 48 8D 05 30 2E 77 01     -  lea rax,[MonsterHunterWorld.exe+34B7110]
    "MonsterHunterWorld.exe"+1D442E0: 33 F6                    -  xor esi,esi
    "MonsterHunterWorld.exe"+1D442E2: 48 8D 8F 28 0C 00 00     -  lea rcx,[rdi+00000C28]
    "MonsterHunterWorld.exe"+1D442E9: 48 89 07                 -  mov [rdi],rax
    */
    struct vector<byte> EnvironmentalBiological_ctor = { 0x48, 0x89, 0x5C, 0x24, 0x08, 0x48, 0x89, 0x74, 0x24, 0x10, 0x57, 0x48, 0x83, 0xEC, 0x60, 0x8B, 0xDA };

    /* World_WaypointZLocal OK
    * F3 0F 10 85 D8 02 00 00
    "MonsterHunterWorld.exe"+1DBF521: 48 8B 01                 -  mov rax,[rcx]
    "MonsterHunterWorld.exe"+1DBF524: FF 50 78                 -  call qword ptr [rax+78]
    "MonsterHunterWorld.exe"+1DBF527: F3 0F 10 B0 90 01 00 00  -  movss xmm6,[rax+00000190]
    "MonsterHunterWorld.exe"+1DBF52F: 80 BD E0 02 00 00 00     -  cmp byte ptr [rbp+000002E0],00
    "MonsterHunterWorld.exe"+1DBF536: 0F 84 C2 00 00 00        -  je MonsterHunterWorld.exe+1DBF5FE
    "MonsterHunterWorld.exe"+1DBF53C: F3 0F 10 8D D0 02 00 00  -  movss xmm1,[rbp+000002D0]
    "MonsterHunterWorld.exe"+1DBF544: 0F 57 FF                 -  xorps xmm7,xmm7
    "MonsterHunterWorld.exe"+1DBF547: F3 0F 10 95 D4 02 00 00  -  movss xmm2,[rbp+000002D4]
    "MonsterHunterWorld.exe"+1DBF54F: F3 0F 5C 95 64 01 00 00  -  subss xmm2,[rbp+00000164]
    "MonsterHunterWorld.exe"+1DBF557: F3 0F 5C 8D 60 01 00 00  -  subss xmm1,[rbp+00000160]
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+1DBF55F: F3 0F 10 85 D8 02 00 00  -  movss xmm0,[rbp+000002D8]
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+1DBF567: F3 0F 5C 85 68 01 00 00  -  subss xmm0,[rbp+00000168]
    "MonsterHunterWorld.exe"+1DBF56F: 48 8B 0D 8A 2F 2B 03     -  mov rcx,[MonsterHunterWorld.exe+5072500]
    "MonsterHunterWorld.exe"+1DBF576: F3 0F 59 D2              -  mulss xmm2,xmm2
    "MonsterHunterWorld.exe"+1DBF57A: F3 0F 59 C9              -  mulss xmm1,xmm1
    "MonsterHunterWorld.exe"+1DBF57E: 48 8B 01                 -  mov rax,[rcx]
    "MonsterHunterWorld.exe"+1DBF581: F3 0F 59 C0              -  mulss xmm0,xmm0
    "MonsterHunterWorld.exe"+1DBF585: F3 0F 58 D1              -  addss xmm2,xmm1
    "MonsterHunterWorld.exe"+1DBF589: F3 0F 58 D0              -  addss xmm2,xmm0
    "MonsterHunterWorld.exe"+1DBF58D: F3 0F 51 FA              -  sqrtss xmm7,xmm2
    "MonsterHunterWorld.exe"+1DBF591: FF 50 78                 -  call qword ptr [rax+78]
    */
    struct vector<byte> World_WaypointZLocal = { 0xF3, 0x0F, 0x10, 0x85, 0xD8, 0x02, 0x00, 0x00 };

    /* World_MapClockLocal OK
    * 48 89 5C 24 08 57 48 83 EC 50 48 8B D9 0F 29 7C
    "MonsterHunterWorld.exe"+AE9E90: 48 8D 05 21 DA 48 04     -  lea rax,[MonsterHunterWorld.exe+4F778B8]
    "MonsterHunterWorld.exe"+AE9E97: C3                       -  ret 
    "MonsterHunterWorld.exe"+AE9E98: CC                       -  int 3 
    "MonsterHunterWorld.exe"+AE9E99: CC                       -  int 3 
    "MonsterHunterWorld.exe"+AE9E9A: CC                       -  int 3 
    "MonsterHunterWorld.exe"+AE9E9B: CC                       -  int 3 
    "MonsterHunterWorld.exe"+AE9E9C: CC                       -  int 3 
    "MonsterHunterWorld.exe"+AE9E9D: CC                       -  int 3 
    "MonsterHunterWorld.exe"+AE9E9E: CC                       -  int 3 
    "MonsterHunterWorld.exe"+AE9E9F: CC                       -  int 3 
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+AE9EA0: 48 89 5C 24 08           -  mov [rsp+08],rbx
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+AE9EA5: 57                       -  push rdi
    "MonsterHunterWorld.exe"+AE9EA6: 48 83 EC 50              -  sub rsp,50
    "MonsterHunterWorld.exe"+AE9EAA: 48 8B D9                 -  mov rbx,rcx
    "MonsterHunterWorld.exe"+AE9EAD: 0F 29 7C 24 30           -  movaps [rsp+30],xmm7
    "MonsterHunterWorld.exe"+AE9EB2: 48 8B 49 08              -  mov rcx,[rcx+08]
    "MonsterHunterWorld.exe"+AE9EB6: 44 0F 29 44 24 20        -  movaps [rsp+20],xmm8
    "MonsterHunterWorld.exe"+AE9EBC: 44 0F 28 C1              -  movaps xmm8,xmm1
    "MonsterHunterWorld.exe"+AE9EC0: E8 FB 51 49 01           -  call MonsterHunterWorld.exe+1F7F0C0
    "MonsterHunterWorld.exe"+AE9EC5: 48 8B 4B 08              -  mov rcx,[rbx+08]
    "MonsterHunterWorld.exe"+AE9EC9: 0F 57 FF                 -  xorps xmm7,xmm7
    */
    struct vector<byte> World_MapClockLocal = { 0x48, 0x89, 0x5C, 0x24, 0x08, 0x57, 0x48, 0x83, 0xEC, 0x50, 0x48, 0x8B, 0xD9, 0x0F, 0x29, 0x7C };

    /* World_GameClock OK
    * D0 58 FA 3F 00 00
    "MonsterHunterWorld.exe"+5073D4D: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073D4F: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073D51: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073D53: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073D55: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073D57: 00 D0                 -  add al,dl
    "MonsterHunterWorld.exe"+5073D59: 07                    -  pop es
    "MonsterHunterWorld.exe"+5073D5A: 00 02                 -  add [rdx],al
    "MonsterHunterWorld.exe"+5073D5C: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073D5E: 00 00                 -  add [rax],al
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+5073D60: D0 58 FA              -  rcr byte ptr [rax-06],1
    "MonsterHunterWorld.exe"+5073D63: 3F                    -  db 3F
    "MonsterHunterWorld.exe"+5073D64: 00 00                 -  add [rax],al
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+5073D66: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073D68: C8 CC 45 43           -  enter 45CC,43
    "MonsterHunterWorld.exe"+5073D6C: 01 00                 -  add [rax],eax
    "MonsterHunterWorld.exe"+5073D6E: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073D70: B4 CC                 -  mov ah,-34
    "MonsterHunterWorld.exe"+5073D72: 45 43                 -  inc r11d
    "MonsterHunterWorld.exe"+5073D74: 01 00                 -  add [rax],eax
    "MonsterHunterWorld.exe"+5073D76: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5073D78: F8                    -  clc 
    "MonsterHunterWorld.exe"+5073D79: 3D 07 45 01 00        -  cmp eax,00014507
    */
    struct vector<byte> World_GameClock = { 0xD0, 0x58, 0x22, 0x3B, 0x00 };

    /* World_GameClockControl OK
    * F3 0F 11 41 38 8B
    "MonsterHunterWorld.exe"+1B9EB0C: 0F 28 C2                 -  movaps xmm0,xmm2
    "MonsterHunterWorld.exe"+1B9EB0F: F3 0F 5E 41 4C           -  divss xmm0,[rcx+4C]
    "MonsterHunterWorld.exe"+1B9EB14: F3 0F 11 41 44           -  movss [rcx+44],xmm0
    "MonsterHunterWorld.exe"+1B9EB19: F3 0F 59 C5              -  mulss xmm0,xmm5
    "MonsterHunterWorld.exe"+1B9EB1D: F3 0F 59 05 AF E3 8B 01  -  mulss xmm0,[MonsterHunterWorld.exe+345CED4]
    "MonsterHunterWorld.exe"+1B9EB25: F3 0F 58 C1              -  addss xmm0,xmm1
    "MonsterHunterWorld.exe"+1B9EB29: 0F 2F C4                 -  comiss xmm0,xmm4
    "MonsterHunterWorld.exe"+1B9EB2C: 72 04                    -  jb MonsterHunterWorld.exe+1B9EB32
    "MonsterHunterWorld.exe"+1B9EB2E: F3 0F 5C C4              -  subss xmm0,xmm4
    "MonsterHunterWorld.exe"+1B9EB32: BF 01 00 00 00           -  mov edi,00000001
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+1B9EB37: F3 0F 11 41 38           -  movss [rcx+38],xmm0
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+1B9EB3C: 8B D7                    -  mov edx,edi
    "MonsterHunterWorld.exe"+1B9EB3E: 48 8D 46 5C              -  lea rax,[rsi+5C]
    "MonsterHunterWorld.exe"+1B9EB42: 8B CF                    -  mov ecx,edi
    "MonsterHunterWorld.exe"+1B9EB44: 0F 2F 00                 -  comiss xmm0,[rax]
    "MonsterHunterWorld.exe"+1B9EB47: 72 3B                    -  jb MonsterHunterWorld.exe+1B9EB84
    "MonsterHunterWorld.exe"+1B9EB49: FF C2                    -  inc edx
    "MonsterHunterWorld.exe"+1B9EB4B: 48 FF C1                 -  inc rcx
    "MonsterHunterWorld.exe"+1B9EB4E: 48 83 C0 04              -  add rax,04
    "MonsterHunterWorld.exe"+1B9EB52: 48 83 F9 05              -  cmp rcx,05
    "MonsterHunterWorld.exe"+1B9EB56: 7C EC                    -  jl MonsterHunterWorld.exe+1B9EB44
    */
    struct vector<byte> World_GameClockControl = { 0xF3, 0x0F, 0x11, 0x41, 0x38, 0x8B };

    /* Shlp_GetShlp OK
    * 3B 91 B0 00 00 00 72 03 33 C0 C3 8B C2 48 C1 E0 04
    "MonsterHunterWorld.exe"+F86080: 48 8D 05 71 FB 05 04     -  lea rax,[MonsterHunterWorld.exe+4FE5BF8]
    "MonsterHunterWorld.exe"+F86087: C3                       -  ret 
    "MonsterHunterWorld.exe"+F86088: CC                       -  int 3 
    "MonsterHunterWorld.exe"+F86089: CC                       -  int 3 
    "MonsterHunterWorld.exe"+F8608A: CC                       -  int 3 
    "MonsterHunterWorld.exe"+F8608B: CC                       -  int 3 
    "MonsterHunterWorld.exe"+F8608C: CC                       -  int 3 
    "MonsterHunterWorld.exe"+F8608D: CC                       -  int 3 
    "MonsterHunterWorld.exe"+F8608E: CC                       -  int 3 
    "MonsterHunterWorld.exe"+F8608F: CC                       -  int 3 
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+F86090: 3B 91 B0 00 00 00        -  cmp edx,[rcx+000000B0]
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+F86096: 72 03                    -  jb MonsterHunterWorld.exe+F8609B
    "MonsterHunterWorld.exe"+F86098: 33 C0                    -  xor eax,eax
    "MonsterHunterWorld.exe"+F8609A: C3                       -  ret 
    "MonsterHunterWorld.exe"+F8609B: 8B C2                    -  mov eax,edx
    "MonsterHunterWorld.exe"+F8609D: 48 C1 E0 04              -  shl rax,04
    "MonsterHunterWorld.exe"+F860A1: 48 03 81 A8 00 00 00     -  add rax,[rcx+000000A8]
    "MonsterHunterWorld.exe"+F860A8: C3                       -  ret 
    "MonsterHunterWorld.exe"+F860A9: CC                       -  int 3 
    "MonsterHunterWorld.exe"+F860AA: CC                       -  int 3 
    "MonsterHunterWorld.exe"+F860AB: CC                       -  int 3 
    */
    struct vector<byte> Shlp_GetShlp = { 0x3B, 0x91, 0xB0, 0x00, 0x00, 0x00, 0x72, 0x03, 0x33, 0xC0, 0xC3, 0x8B, 0xC2, 0x48, 0xC1, 0xE0, 0x04 };

    /* Shlp_CallShlp OK
    * 48 8B C4 57 48 81 EC 90 01 00 00
    "MonsterHunterWorld.exe"+1ABA8FE: 48 81 C4 70 01 00 00           -  add rsp,00000170
    "MonsterHunterWorld.exe"+1ABA905: 41 5E                          -  pop r14
    "MonsterHunterWorld.exe"+1ABA907: 41 5C                          -  pop r12
    "MonsterHunterWorld.exe"+1ABA909: 5F                             -  pop rdi
    "MonsterHunterWorld.exe"+1ABA90A: 5E                             -  pop rsi
    "MonsterHunterWorld.exe"+1ABA90B: 5D                             -  pop rbp
    "MonsterHunterWorld.exe"+1ABA90C: C3                             -  ret 
    "MonsterHunterWorld.exe"+1ABA90D: CC                             -  int 3 
    "MonsterHunterWorld.exe"+1ABA90E: CC                             -  int 3 
    "MonsterHunterWorld.exe"+1ABA90F: CC                             -  int 3 
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+1ABA910: 48 8B C4                       -  mov rax,rsp
    "MonsterHunterWorld.exe"+1ABA913: 57                             -  push rdi
    "MonsterHunterWorld.exe"+1ABA914: 48 81 EC 90 01 00 00           -  sub rsp,00000190
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+1ABA91B: 48 89 58 08                    -  mov [rax+08],rbx
    "MonsterHunterWorld.exe"+1ABA91F: 49 8B F8                       -  mov rdi,r8
    "MonsterHunterWorld.exe"+1ABA922: 48 89 68 10                    -  mov [rax+10],rbp
    "MonsterHunterWorld.exe"+1ABA926: 48 8B D9                       -  mov rbx,rcx
    "MonsterHunterWorld.exe"+1ABA929: 4C 89 70 F0                    -  mov [rax-10],r14
    "MonsterHunterWorld.exe"+1ABA92D: 48 8D 4C 24 50                 -  lea rcx,[rsp+50]
    "MonsterHunterWorld.exe"+1ABA932: 41 BE FF FF FF FF              -  mov r14d,FFFFFFFF
    "MonsterHunterWorld.exe"+1ABA938: 4C 89 78 E8                    -  mov [rax-18],r15
    "MonsterHunterWorld.exe"+1ABA93C: 4C 8B FA                       -  mov r15,rdx
    "MonsterHunterWorld.exe"+1ABA93F: 44 89 74 24 40                 -  mov [rsp+40],r14d
    */
    struct vector<byte> Shlp_CallShlp = { 0x48, 0x8B, 0xC4, 0x57, 0x48, 0x81, 0xEC, 0x90, 0x01, 0x00, 0x00 };

    /* Monster_dtor OK
    * 03 48 8B 5C 24 30 48 83 C4 20 5F C3 CC CC CC CC CC CC 48 89 5C 24 08 48 89 6C
    "MonsterHunterWorld.exe"+1CBFF6F: 48 8B 5C 24 30           -  mov rbx,[rsp+30]
    "MonsterHunterWorld.exe"+1CBFF74: 48 83 C4 20              -  add rsp,20
    "MonsterHunterWorld.exe"+1CBFF78: 5F                       -  pop rdi
    "MonsterHunterWorld.exe"+1CBFF79: C3                       -  ret 
    "MonsterHunterWorld.exe"+1CBFF7A: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1CBFF7B: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1CBFF7C: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1CBFF7D: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1CBFF7E: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1CBFF7F: CC                       -  int 3 
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+1CBFF80: 48 89 5C 24 08           -  mov [rsp+08],rbx
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+1CBFF85: 48 89 6C 24 10           -  mov [rsp+10],rbp
    "MonsterHunterWorld.exe"+1CBFF8A: 48 89 74 24 18           -  mov [rsp+18],rsi
    "MonsterHunterWorld.exe"+1CBFF8F: 57                       -  push rdi
    "MonsterHunterWorld.exe"+1CBFF90: 41 56                    -  push r14
    "MonsterHunterWorld.exe"+1CBFF92: 41 57                    -  push r15
    "MonsterHunterWorld.exe"+1CBFF94: 48 83 EC 20              -  sub rsp,20
    "MonsterHunterWorld.exe"+1CBFF98: 48 8B B9 A0 09 00 00     -  mov rdi,[rcx+000009A0]
    "MonsterHunterWorld.exe"+1CBFF9F: 48 8D 05 7A 7A 7E 01     -  lea rax,[MonsterHunterWorld.exe+34A7A20]
    "MonsterHunterWorld.exe"+1CBFFA6: 33 ED                    -  xor ebp,ebp
    "MonsterHunterWorld.exe"+1CBFFA8: 48 89 01                 -  mov [rcx],rax
    */
    struct vector<byte> Monster_dtor = { 0x03, 0x48, 0x8B, 0x5C, 0x24, 0x30, 0x48, 0x83, 0xC4, 0x20, 0x5F, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x48, 0x89, 0x5C, 0x24, 0x08, 0x48, 0x89, 0x6C };

    /* Monster_ctor OK
    * C3 CC CC CC CC CC CC CC CC 44 89 44 24 18 89
    "MonsterHunterWorld.exe"+1CBD696: 5F                                -  pop rdi
    "MonsterHunterWorld.exe"+1CBD697: C3                                -  ret 
    "MonsterHunterWorld.exe"+1CBD698: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1CBD699: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1CBD69A: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1CBD69B: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1CBD69C: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1CBD69D: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1CBD69E: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1CBD69F: CC                                -  int 3 
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+1CBD6A0: 44 89 44 24 18                    -  mov [rsp+18],r8d
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+1CBD6A5: 89 54 24 10                       -  mov [rsp+10],edx
    "MonsterHunterWorld.exe"+1CBD6A9: 48 89 4C 24 08                    -  mov [rsp+08],rcx
    "MonsterHunterWorld.exe"+1CBD6AE: 55                                -  push rbp
    "MonsterHunterWorld.exe"+1CBD6AF: 53                                -  push rbx
    "MonsterHunterWorld.exe"+1CBD6B0: 56                                -  push rsi
    "MonsterHunterWorld.exe"+1CBD6B1: 57                                -  push rdi
    "MonsterHunterWorld.exe"+1CBD6B2: 41 54                             -  push r12
    "MonsterHunterWorld.exe"+1CBD6B4: 41 55                             -  push r13
    "MonsterHunterWorld.exe"+1CBD6B6: 41 56                             -  push r14
    "MonsterHunterWorld.exe"+1CBD6B8: 41 57                             -  push r15
    */
    struct vector<byte> Monster_ctor = { 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x44, 0x89, 0x44, 0x24, 0x18, 0x89 };

    /* Weapon_ChangeWeapon OK
    * 48 8B C4 55 41 54 48 81
    "MonsterHunterWorld.exe"+1F76CC9: 48 8B 52 20                    -  mov rdx,[rdx+20]
    "MonsterHunterWorld.exe"+1F76CCD: 48 83 C4 20                    -  add rsp,20
    "MonsterHunterWorld.exe"+1F76CD1: 5B                             -  pop rbx
    "MonsterHunterWorld.exe"+1F76CD2: E9 89 14 2E 00                 -  jmp MonsterHunterWorld.exe+2258160
    "MonsterHunterWorld.exe"+1F76CD7: 48 83 C4 20                    -  add rsp,20
    "MonsterHunterWorld.exe"+1F76CDB: 5B                             -  pop rbx
    "MonsterHunterWorld.exe"+1F76CDC: C3                             -  ret 
    "MonsterHunterWorld.exe"+1F76CDD: CC                             -  int 3 
    "MonsterHunterWorld.exe"+1F76CDE: CC                             -  int 3 
    "MonsterHunterWorld.exe"+1F76CDF: CC                             -  int 3 
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+1F76CE0: 48 8B C4                       -  mov rax,rsp
    "MonsterHunterWorld.exe"+1F76CE3: 55                             -  push rbp
    "MonsterHunterWorld.exe"+1F76CE4: 41 54                          -  push r12
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+1F76CE6: 48 81 EC 38 01 00 00           -  sub rsp,00000138
    "MonsterHunterWorld.exe"+1F76CED: 48 89 70 E8                    -  mov [rax-18],rsi
    "MonsterHunterWorld.exe"+1F76CF1: 45 8B E0                       -  mov r12d,r8d
    "MonsterHunterWorld.exe"+1F76CF4: 48 89 78 E0                    -  mov [rax-20],rdi
    "MonsterHunterWorld.exe"+1F76CF8: 48 8D B1 B0 76 00 00           -  lea rsi,[rcx+000076B0]
    "MonsterHunterWorld.exe"+1F76CFF: 4C 89 68 D8                    -  mov [rax-28],r13
    "MonsterHunterWorld.exe"+1F76D03: 45 33 C0                       -  xor r8d,r8d
    "MonsterHunterWorld.exe"+1F76D06: 4C 89 70 D0                    -  mov [rax-30],r14
    "MonsterHunterWorld.exe"+1F76D0A: 8B EA                          -  mov ebp,edx
    "MonsterHunterWorld.exe"+1F76D0C: 4C 89 78 C8                    -  mov [rax-38],r15
    */
    struct vector<byte> Weapon_ChangeWeapon = { 0x48, 0x8B, 0xC4, 0x55, 0x41, 0x54, 0x48, 0x81 };

    /* Weapon_WeaponOrnaments OK
    * 48 81 C4 50 01 00 00 5F C3 CC CC CC CC CC CC 48 8B
    "MonsterHunterWorld.exe"+21300B9: E8 92 B3 1E FF           -  call MonsterHunterWorld.exe+131B450
    "MonsterHunterWorld.exe"+21300BE: 48 8D 15 33 9D 3F 01     -  lea rdx,[MonsterHunterWorld.exe+3529DF8]
    "MonsterHunterWorld.exe"+21300C5: 4C 8D 44 24 40           -  lea r8,[rsp+40]
    "MonsterHunterWorld.exe"+21300CA: 48 8B C8                 -  mov rcx,rax
    "MonsterHunterWorld.exe"+21300CD: E8 6E D1 1E 00           -  call MonsterHunterWorld.exe+231D240
    "MonsterHunterWorld.exe"+21300D2: C6 87 48 22 00 00 00     -  mov byte ptr [rdi+00002248],00
    "MonsterHunterWorld.exe"+21300D9: 48 8B CF                 -  mov rcx,rdi
    "MonsterHunterWorld.exe"+21300DC: E8 7F 0B 00 00           -  call MonsterHunterWorld.exe+2130C60
    "MonsterHunterWorld.exe"+21300E1: 0F 28 B4 24 40 01 00 00  -  movaps xmm6,[rsp+00000140]
    "MonsterHunterWorld.exe"+21300E9: 48 8B 9C 24 60 01 00 00  -  mov rbx,[rsp+00000160]
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+21300F1: 48 81 C4 50 01 00 00     -  add rsp,00000150
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+21300F8: 5F                       -  pop rdi
    "MonsterHunterWorld.exe"+21300F9: C3                       -  ret 
    "MonsterHunterWorld.exe"+21300FA: CC                       -  int 3 
    "MonsterHunterWorld.exe"+21300FB: CC                       -  int 3 
    "MonsterHunterWorld.exe"+21300FC: CC                       -  int 3 
    "MonsterHunterWorld.exe"+21300FD: CC                       -  int 3 
    "MonsterHunterWorld.exe"+21300FE: CC                       -  int 3 
    "MonsterHunterWorld.exe"+21300FF: CC                       -  int 3 
    "MonsterHunterWorld.exe"+2130100: 48 8B C4                 -  mov rax,rsp
    "MonsterHunterWorld.exe"+2130103: 48 89 70 18              -  mov [rax+18],rsi
    */
    struct vector<byte> Weapon_WeaponOrnaments = { 0x48, 0x81, 0xC4, 0x50, 0x01, 0x00, 0x00, 0x5F, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x48, 0x8B };

    /* Weapon_MainWeaponPtr OK
    * 48 83 C4 50 5B C3 CC 48 89 5C 24 10 55
    "MonsterHunterWorld.exe"+2135AE3: F3 0F 10 44 24 28        -  movss xmm0,[rsp+28]
    "MonsterHunterWorld.exe"+2135AE9: F3 0F 11 83 68 01 00 00  -  movss [rbx+00000168],xmm0
    "MonsterHunterWorld.exe"+2135AF1: 0F 28 44 24 40           -  movaps xmm0,[rsp+40]
    "MonsterHunterWorld.exe"+2135AF6: F3 0F 11 8B 64 01 00 00  -  movss [rbx+00000164],xmm1
    "MonsterHunterWorld.exe"+2135AFE: 89 83 6C 01 00 00        -  mov [rbx+0000016C],eax
    "MonsterHunterWorld.exe"+2135B04: 0F 11 83 70 01 00 00     -  movups [rbx+00000170],xmm0
    "MonsterHunterWorld.exe"+2135B0B: 89 83 8C 01 00 00        -  mov [rbx+0000018C],eax
    "MonsterHunterWorld.exe"+2135B11: F3 0F 11 93 80 01 00 00  -  movss [rbx+00000180],xmm2
    "MonsterHunterWorld.exe"+2135B19: F3 0F 11 9B 84 01 00 00  -  movss [rbx+00000184],xmm3
    "MonsterHunterWorld.exe"+2135B21: F3 0F 11 A3 88 01 00 00  -  movss [rbx+00000188],xmm4
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+2135B29: 48 83 C4 50              -  add rsp,50
    "MonsterHunterWorld.exe"+2135B2D: 5B                       -  pop rbx
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+2135B2E: C3                       -  ret 
    "MonsterHunterWorld.exe"+2135B2F: CC                       -  int 3 
    "MonsterHunterWorld.exe"+2135B30: 48 89 5C 24 10           -  mov [rsp+10],rbx
    "MonsterHunterWorld.exe"+2135B35: 55                       -  push rbp
    "MonsterHunterWorld.exe"+2135B36: 48 8D 6C 24 D0           -  lea rbp,[rsp-30]
    "MonsterHunterWorld.exe"+2135B3B: 48 81 EC 30 01 00 00     -  sub rsp,00000130
    "MonsterHunterWorld.exe"+2135B42: 48 8B D9                 -  mov rbx,rcx
    "MonsterHunterWorld.exe"+2135B45: E8 E6 87 FF FF           -  call MonsterHunterWorld.exe+212E330
    "MonsterHunterWorld.exe"+2135B4A: 48 8B 83 00 21 00 00     -  mov rax,[rbx+00002100]
    "MonsterHunterWorld.exe"+2135B51: 48 85 C0                 -  test rax,rax
    */
    struct vector<byte> Weapon_MainWeaponPtr = { 0x48, 0x83, 0xC4, 0x50, 0x5B, 0xC3, 0xCC, 0x48, 0x89, 0x5C, 0x24, 0x10, 0x55 };
    
    /* HookCoordinateChange2 OK
    * 48 8B 05 E8 7D 17 04
    "MonsterHunterWorld.exe"+EFA663: 0F 84 E5 00 00 00        -  je MonsterHunterWorld.exe+EFA74E
    "MonsterHunterWorld.exe"+EFA669: 8B 81 60 01 00 00        -  mov eax,[rcx+00000160]
    "MonsterHunterWorld.exe"+EFA66F: 48 8B 53 10              -  mov rdx,[rbx+10]
    "MonsterHunterWorld.exe"+EFA673: 89 82 30 E5 00 00        -  mov [rdx+0000E530],eax
    "MonsterHunterWorld.exe"+EFA679: 8B 81 64 01 00 00        -  mov eax,[rcx+00000164]
    "MonsterHunterWorld.exe"+EFA67F: 89 82 34 E5 00 00        -  mov [rdx+0000E534],eax
    "MonsterHunterWorld.exe"+EFA685: 8B 81 68 01 00 00        -  mov eax,[rcx+00000168]
    "MonsterHunterWorld.exe"+EFA68B: 33 C9                    -  xor ecx,ecx
    "MonsterHunterWorld.exe"+EFA68D: 89 8A 3C E5 00 00        -  mov [rdx+0000E53C],ecx
    "MonsterHunterWorld.exe"+EFA693: 89 82 38 E5 00 00        -  mov [rdx+0000E538],eax
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+EFA699: 48 8B 05 E8 7D 17 04     -  mov rax,[MonsterHunterWorld.exe+5072488]
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+EFA6A0: F3 0F 10 05 08 40 14 03  -  movss xmm0,[MonsterHunterWorld.exe+403E6B0]
    "MonsterHunterWorld.exe"+EFA6A8: F3 0F 10 0D 04 40 14 03  -  movss xmm1,[MonsterHunterWorld.exe+403E6B4]
    "MonsterHunterWorld.exe"+EFA6B0: F3 0F 10 98 94 19 00 00  -  movss xmm3,[rax+00001994]
    "MonsterHunterWorld.exe"+EFA6B8: 48 8B 83 B0 00 00 00     -  mov rax,[rbx+000000B0]
    "MonsterHunterWorld.exe"+EFA6BF: F3 0F 59 C3              -  mulss xmm0,xmm3
    "MonsterHunterWorld.exe"+EFA6C3: F3 0F 59 CB              -  mulss xmm1,xmm3
    "MonsterHunterWorld.exe"+EFA6C7: F3 0F 10 A0 60 01 00 00  -  movss xmm4,[rax+00000160]
    "MonsterHunterWorld.exe"+EFA6CF: F3 0F 10 90 64 01 00 00  -  movss xmm2,[rax+00000164]
    "MonsterHunterWorld.exe"+EFA6D7: F3 0F 5C E0              -  subss xmm4,xmm0
    "MonsterHunterWorld.exe"+EFA6DB: F3 0F 10 05 D5 3F 14 03  -  movss xmm0,[MonsterHunterWorld.exe+403E6B8]
    */
    struct vector<byte> Player_HookCoordinateChange2 = { 0x48, 0x8B, 0x05, 0xE8, 0x7D, 0x17, 0x04 };

    /* Player_HookCoordinateChange OK
    * 45 89 BE 3C E5 00 00
    "MonsterHunterWorld.exe"+1F80A7A: 49 8B CF                    -  mov rcx,r15
    "MonsterHunterWorld.exe"+1F80A7D: 48 8B 01                    -  mov rax,[rcx]
    "MonsterHunterWorld.exe"+1F80A80: 33 D2                       -  xor edx,edx
    "MonsterHunterWorld.exe"+1F80A82: FF 90 20 01 00 00           -  call qword ptr [rax+00000120]
    "MonsterHunterWorld.exe"+1F80A88: F3 0F 10 68 30              -  movss xmm5,[rax+30]
    "MonsterHunterWorld.exe"+1F80A8D: F3 0F 10 60 34              -  movss xmm4,[rax+34]
    "MonsterHunterWorld.exe"+1F80A92: F3 0F 10 58 38              -  movss xmm3,[rax+38]
    "MonsterHunterWorld.exe"+1F80A97: F3 41 0F 11 AE 30 E5 00 00  -  movss [r14+0000E530],xmm5
    "MonsterHunterWorld.exe"+1F80AA0: F3 41 0F 11 A6 34 E5 00 00  -  movss [r14+0000E534],xmm4
    "MonsterHunterWorld.exe"+1F80AA9: F3 41 0F 11 9E 38 E5 00 00  -  movss [r14+0000E538],xmm3
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+1F80AB2: 45 89 BE 3C E5 00 00        -  mov [r14+0000E53C],r15d
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+1F80AB9: 48 8B 05 C8 19 0F 03        -  mov rax,[MonsterHunterWorld.exe+5072488]
    "MonsterHunterWorld.exe"+1F80AC0: F3 0F 10 90 94 19 00 00     -  movss xmm2,[rax+00001994]
    "MonsterHunterWorld.exe"+1F80AC8: 0F 28 C2                    -  movaps xmm0,xmm2
    "MonsterHunterWorld.exe"+1F80ACB: 0F 28 CA                    -  movaps xmm1,xmm2
    "MonsterHunterWorld.exe"+1F80ACE: F3 0F 59 05 DA DB 0B 02     -  mulss xmm0,[MonsterHunterWorld.exe+403E6B0]
    "MonsterHunterWorld.exe"+1F80AD6: F3 0F 59 0D D6 DB 0B 02     -  mulss xmm1,[MonsterHunterWorld.exe+403E6B4]
    "MonsterHunterWorld.exe"+1F80ADE: F3 0F 59 15 D2 DB 0B 02     -  mulss xmm2,[MonsterHunterWorld.exe+403E6B8]
    "MonsterHunterWorld.exe"+1F80AE6: F3 0F 5C E8                 -  subss xmm5,xmm0
    "MonsterHunterWorld.exe"+1F80AEA: 45 89 BE 4C E5 00 00        -  mov [r14+0000E54C],r15d
    "MonsterHunterWorld.exe"+1F80AF1: F3 0F 5C E1                 -  subss xmm4,xmm1
    */
    struct vector<byte> Player_HookCoordinateChange = { 0x45, 0x89, 0xBE, 0x3C, 0xE5, 0x00, 0x00 };

    /* ActionFrameSpeed OK
    * 89 57 6C 48 8B 05 26 E8 F3 02
    "MonsterHunterWorld.exe"+224559A: 48 8B F9                 -  mov rdi,rcx
    "MonsterHunterWorld.exe"+224559D: 48 8D 05 CC 66 31 01     -  lea rax,[MonsterHunterWorld.exe+355BC70]
    "MonsterHunterWorld.exe"+22455A4: 48 8D 4C 24 20           -  lea rcx,[rsp+20]
    "MonsterHunterWorld.exe"+22455A9: 48 89 44 24 20           -  mov [rsp+20],rax
    "MonsterHunterWorld.exe"+22455AE: E8 3D 91 A8 00           -  call MonsterHunterWorld.exe+2CCE6F0
    "MonsterHunterWorld.exe"+22455B3: 48 63 47 10              -  movsxd  rax,dword ptr [rdi+10]
    "MonsterHunterWorld.exe"+22455B7: 48 8B CF                 -  mov rcx,rdi
    "MonsterHunterWorld.exe"+22455BA: 4C 69 C0 F8 00 00 00     -  imul r8,rax,000000F8
    "MonsterHunterWorld.exe"+22455C1: 48 8B 05 38 E8 F3 02     -  mov rax,[MonsterHunterWorld.exe+5183E00]
    "MonsterHunterWorld.exe"+22455C8: 41 8B 94 00 A0 00 00 00  -  mov edx,[r8+rax+000000A0]
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+22455D0: 89 57 6C                 -  mov [rdi+6C],edx
    "MonsterHunterWorld.exe"+22455D3: 48 8B 05 26 E8 F3 02     -  mov rax,[MonsterHunterWorld.exe+5183E00]
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+22455DA: 41 8B 94 00 A4 00 00 00  -  mov edx,[r8+rax+000000A4]
    "MonsterHunterWorld.exe"+22455E2: 48 8B 07                 -  mov rax,[rdi]
    "MonsterHunterWorld.exe"+22455E5: 89 57 68                 -  mov [rdi+68],edx
    "MonsterHunterWorld.exe"+22455E8: FF 90 E8 00 00 00        -  call qword ptr [rax+000000E8]
    "MonsterHunterWorld.exe"+22455EE: 83 7F 0C 08              -  cmp dword ptr [rdi+0C],08
    "MonsterHunterWorld.exe"+22455F2: 75 26                    -  jne MonsterHunterWorld.exe+224561A
    "MonsterHunterWorld.exe"+22455F4: F6 47 14 01              -  test byte ptr [rdi+14],01
    "MonsterHunterWorld.exe"+22455F8: 74 20                    -  je MonsterHunterWorld.exe+224561A
    "MonsterHunterWorld.exe"+22455FA: 48 8B 05 FF E7 F3 02     -  mov rax,[MonsterHunterWorld.exe+5183E00]
    "MonsterHunterWorld.exe"+2245601: 48 8B 88 48 4A 00 00     -  mov rcx,[rax+00004A48]
    */
    struct vector<byte> Player_ActionFrameSpeed = { 0x89, 0x57, 0x6C, 0x48, 0x8B, 0x05, 0x26, 0xE8, 0xF3, 0x02 };

    /* CallLmt OK
    * 48 83 EC 48 F3 0F 10 15 BC B2 28 01
    "MonsterHunterWorld.exe"+1C1CBC2: 5F                       -  pop rdi
    "MonsterHunterWorld.exe"+1C1CBC3: C3                       -  ret 
    "MonsterHunterWorld.exe"+1C1CBC4: E8 33 86 B7 00           -  call MonsterHunterWorld.exe+27951FC
    "MonsterHunterWorld.exe"+1C1CBC9: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1C1CBCA: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1C1CBCB: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1C1CBCC: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1C1CBCD: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1C1CBCE: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1C1CBCF: CC                       -  int 3 
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+1C1CBD0: 48 83 EC 48              -  sub rsp,48
    "MonsterHunterWorld.exe"+1C1CBD4: F3 0F 10 15 BC B2 28 01  -  movss xmm2,[MonsterHunterWorld.exe+2EA7E98]
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+1C1CBDC: 45 8B C8                 -  mov r9d,r8d
    "MonsterHunterWorld.exe"+1C1CBDF: 48 8B 01                 -  mov rax,[rcx]
    "MonsterHunterWorld.exe"+1C1CBE2: C7 44 24 30 FF FF FF FF  -  mov [rsp+30],FFFFFFFF
    "MonsterHunterWorld.exe"+1C1CBEA: F3 0F 11 54 24 28        -  movss [rsp+28],xmm2
    "MonsterHunterWorld.exe"+1C1CBF0: C7 44 24 20 FF FF 00 00  -  mov [rsp+20],0000FFFF
    "MonsterHunterWorld.exe"+1C1CBF8: FF 90 98 02 00 00        -  call qword ptr [rax+00000298]
    "MonsterHunterWorld.exe"+1C1CBFE: 48 83 C4 48              -  add rsp,48
    "MonsterHunterWorld.exe"+1C1CC02: C3                       -  ret 
    "MonsterHunterWorld.exe"+1C1CC03: CC                       -  int 3 
    "MonsterHunterWorld.exe"+1C1CC04: CC                       -  int 3 
    */
    struct vector<byte> Player_CallLmt = { 0x48, 0x83, 0xEC, 0x48, 0xF3, 0x0F, 0x10, 0x15, 0xBC, 0xB2, 0x28, 0x01 };

    /* World_ActionFrameSpeed OK
    * 48 89 5C 24 08
    "MonsterHunterWorld.exe"+224557D: 48 85 51 40              -  test [rcx+40],rdx
    "MonsterHunterWorld.exe"+2245581: 75 07                    -  jne MonsterHunterWorld.exe+224558A
    "MonsterHunterWorld.exe"+2245583: 48 8B 01                 -  mov rax,[rcx]
    "MonsterHunterWorld.exe"+2245586: 48 FF 60 50              -  jmp qword ptr [rax+50]
    "MonsterHunterWorld.exe"+224558A: C3                       -  ret 
    "MonsterHunterWorld.exe"+224558B: CC                       -  int 3 
    "MonsterHunterWorld.exe"+224558C: CC                       -  int 3 
    "MonsterHunterWorld.exe"+224558D: CC                       -  int 3 
    "MonsterHunterWorld.exe"+224558E: CC                       -  int 3 
    "MonsterHunterWorld.exe"+224558F: CC                       -  int 3 
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+2245590: 48 89 5C 24 08           -  mov [rsp+08],rbx
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+2245595: 57                       -  push rdi
    "MonsterHunterWorld.exe"+2245596: 48 83 EC 50              -  sub rsp,50
    "MonsterHunterWorld.exe"+224559A: 48 8B F9                 -  mov rdi,rcx
    "MonsterHunterWorld.exe"+224559D: 48 8D 05 CC 66 31 01     -  lea rax,[MonsterHunterWorld.exe+355BC70]
    "MonsterHunterWorld.exe"+22455A4: 48 8D 4C 24 20           -  lea rcx,[rsp+20]
    "MonsterHunterWorld.exe"+22455A9: 48 89 44 24 20           -  mov [rsp+20],rax
    "MonsterHunterWorld.exe"+22455AE: E8 3D 91 A8 00           -  call MonsterHunterWorld.exe+2CCE6F0
    "MonsterHunterWorld.exe"+22455B3: 48 63 47 10              -  movsxd  rax,dword ptr [rdi+10]
    "MonsterHunterWorld.exe"+22455B7: 48 8B CF                 -  mov rcx,rdi
    "MonsterHunterWorld.exe"+22455BA: 4C 69 C0 F8 00 00 00     -  imul r8,rax,000000F8
    */
    struct vector<byte> World_ActionFrameSpeed = { 0x48, 0x89, 0x5C, 0x24, 0x08 };
    
    /* World_Message OK
    * B0 6D D0 40 00 00 00 00 70
    "MonsterHunterWorld.exe"+4D18268: 4C 4B                 -  dec rbx
    "MonsterHunterWorld.exe"+4D1826A: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+4D1826C: 5D                    -  pop rbp
    "MonsterHunterWorld.exe"+4D1826D: 7A 25                 -  jp MonsterHunterWorld.exe+4D18294
    "MonsterHunterWorld.exe"+4D1826F: 2F                    -  das 
    "MonsterHunterWorld.exe"+4D18270: 2F                    -  das 
    "MonsterHunterWorld.exe"+4D18271: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+4D18273: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+4D18275: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+4D18277: 00 B0 6D D0 40        - db 00 B0 6D D0 40  // SHORTENED TO HIT INJECTION FROM:  add [rax+0040D06D],dh
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+4D1827C: 00 00                 -  add [rax],al
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+4D1827E: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+4D18280: 70 ED                 -  jo MonsterHunterWorld.exe+4D1826F
    "MonsterHunterWorld.exe"+4D18282: FD                    -  std 
    "MonsterHunterWorld.exe"+4D18283: 42 01 00              -  add [rax],eax
    "MonsterHunterWorld.exe"+4D18286: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+4D18288: 90                    -  nop 
    "MonsterHunterWorld.exe"+4D18289: ED                    -  in eax,dx
    "MonsterHunterWorld.exe"+4D1828A: FD                    -  std 
    "MonsterHunterWorld.exe"+4D1828B: 42 01 00              -  add [rax],eax
    "MonsterHunterWorld.exe"+4D1828E: 00 00                 -  add [rax],al
    */
    struct vector<byte> World_Message = { 0xB0, 0x6D, 0xD0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x70 };

    /* Weapon_BehaviorControl OK
    * C3 CC CC 89 54 24 10 53
    "MonsterHunterWorld.exe"+1CE0A32: 74 0F                 -  je MonsterHunterWorld.exe+1CE0A43
    "MonsterHunterWorld.exe"+1CE0A34: 8B 83 8C D1 01 00     -  mov eax,[rbx+0001D18C]
    "MonsterHunterWorld.exe"+1CE0A3A: 0F AB F8              -  bts eax,edi
    "MonsterHunterWorld.exe"+1CE0A3D: 89 83 8C D1 01 00     -  mov [rbx+0001D18C],eax
    "MonsterHunterWorld.exe"+1CE0A43: 48 8B 5C 24 30        -  mov rbx,[rsp+30]
    "MonsterHunterWorld.exe"+1CE0A48: 48 83 C4 20           -  add rsp,20
    "MonsterHunterWorld.exe"+1CE0A4C: 5F                    -  pop rdi
    "MonsterHunterWorld.exe"+1CE0A4D: C3                    -  ret 
    "MonsterHunterWorld.exe"+1CE0A4E: CC                    -  int 3 
    "MonsterHunterWorld.exe"+1CE0A4F: CC                    -  int 3 
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+1CE0A50: 89 54 24 10           -  mov [rsp+10],edx
    "MonsterHunterWorld.exe"+1CE0A54: 53                    -  push rbx
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+1CE0A55: 48 83 EC 20           -  sub rsp,20
    "MonsterHunterWorld.exe"+1CE0A59: 48 8B D9              -  mov rbx,rcx
    "MonsterHunterWorld.exe"+1CE0A5C: 48 8B 0D 95 3D 54 03  -  mov rcx,[MonsterHunterWorld.exe+52247F8]
    "MonsterHunterWorld.exe"+1CE0A63: E8 C8 37 DF FF        -  call MonsterHunterWorld.exe+1AD4230
    "MonsterHunterWorld.exe"+1CE0A68: 84 C0                 -  test al,al
    "MonsterHunterWorld.exe"+1CE0A6A: 74 1E                 -  je MonsterHunterWorld.exe+1CE0A8A
    "MonsterHunterWorld.exe"+1CE0A6C: 48 8B 8B E0 89 00 00  -  mov rcx,[rbx+000089E0]
    "MonsterHunterWorld.exe"+1CE0A73: 48 8D 54 24 38        -  lea rdx,[rsp+38]
    "MonsterHunterWorld.exe"+1CE0A78: 41 B8 01 00 00 00     -  mov r8d,00000001
    "MonsterHunterWorld.exe"+1CE0A7E: 48 8B 89 30 01 00 00  -  mov rcx,[rcx+00000130]
    */
    struct vector<byte> Monster_BehaviorControl = { 0xC3, 0xCC, 0xCC, 0x89, 0x54, 0x24, 0x10, 0x53 };

    /* Weapon_CompleteChangeWeapon OK
    * F2 00 00 00 48 83 C4 20 5B C3 CC CC CC CC CC CC CC 48 89 5C 24 08
    "MonsterHunterWorld.exe"+205E043: 48 83 C4 20                       -  add rsp,20
    "MonsterHunterWorld.exe"+205E047: 5B                                -  pop rbx
    "MonsterHunterWorld.exe"+205E048: C3                                -  ret 
    "MonsterHunterWorld.exe"+205E049: CC                                -  int 3 
    "MonsterHunterWorld.exe"+205E04A: CC                                -  int 3 
    "MonsterHunterWorld.exe"+205E04B: CC                                -  int 3 
    "MonsterHunterWorld.exe"+205E04C: CC                                -  int 3 
    "MonsterHunterWorld.exe"+205E04D: CC                                -  int 3 
    "MonsterHunterWorld.exe"+205E04E: CC                                -  int 3 
    "MonsterHunterWorld.exe"+205E04F: CC                                -  int 3 
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+205E050: 48 89 5C 24 08                    -  mov [rsp+08],rbx
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+205E055: 48 89 6C 24 10                    -  mov [rsp+10],rbp
    "MonsterHunterWorld.exe"+205E05A: 48 89 74 24 18                    -  mov [rsp+18],rsi
    "MonsterHunterWorld.exe"+205E05F: 48 89 7C 24 20                    -  mov [rsp+20],rdi
    "MonsterHunterWorld.exe"+205E064: 41 56                             -  push r14
    "MonsterHunterWorld.exe"+205E066: 48 83 EC 20                       -  sub rsp,20
    "MonsterHunterWorld.exe"+205E06A: 8B 81 1C 26 01 00                 -  mov eax,[rcx+0001261C]
    "MonsterHunterWorld.exe"+205E070: 8B EA                             -  mov ebp,edx
    "MonsterHunterWorld.exe"+205E072: 0F BA E8 01                       -  bts eax,01
    "MonsterHunterWorld.exe"+205E076: 48 8B F9                          -  mov rdi,rcx
    "MonsterHunterWorld.exe"+205E079: 89 81 1C 26 01 00                 -  mov [rcx+0001261C],eax
    */
    struct vector<byte> Weapon_CompleteChangeWeapon = { 0xF2, 0x00, 0x00, 0x00, 0x48, 0x83, 0xC4, 0x20, 0x5B, 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x48, 0x89, 0x5C, 0x24, 0x08 };

    /* Weapon_Hit OK
    * 48 8B 57 18 48 8B 72 08
    "MonsterHunterWorld.exe"+1F8E36C: 48 8B 57 18              -  mov rdx,[rdi+18]
    "MonsterHunterWorld.exe"+1F8E370: 48 8B 8B 20 7D 00 00     -  mov rcx,[rbx+00007D20]
    "MonsterHunterWorld.exe"+1F8E377: 8B 42 70                 -  mov eax,[rdx+70]
    "MonsterHunterWorld.exe"+1F8E37A: 48 8B 74 24 70           -  mov rsi,[rsp+70]
    "MonsterHunterWorld.exe"+1F8E37F: 4C 8B 64 24 40           -  mov r12,[rsp+40]
    "MonsterHunterWorld.exe"+1F8E384: 89 81 08 0A 00 00        -  mov [rcx+00000A08],eax
    "MonsterHunterWorld.exe"+1F8E38A: 48 83 C4 48              -  add rsp,48
    "MonsterHunterWorld.exe"+1F8E38E: 5F                       -  pop rdi
    "MonsterHunterWorld.exe"+1F8E38F: 5B                       -  pop rbx
    "MonsterHunterWorld.exe"+1F8E390: C3                       -  ret 
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+1F8E391: 48 8B 57 18              -  mov rdx,[rdi+18]
    "MonsterHunterWorld.exe"+1F8E395: 48 8B 72 08              -  mov rsi,[rdx+08]
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+1F8E399: 8B 46 60                 -  mov eax,[rsi+60]
    "MonsterHunterWorld.exe"+1F8E39C: 48 C1 E8 0A              -  shr rax,0A
    "MonsterHunterWorld.exe"+1F8E3A0: A8 01                    -  test al,01
    "MonsterHunterWorld.exe"+1F8E3A2: 0F 84 D5 00 00 00        -  je MonsterHunterWorld.exe+1F8E47D
    "MonsterHunterWorld.exe"+1F8E3A8: 48 85 F6                 -  test rsi,rsi
    "MonsterHunterWorld.exe"+1F8E3AB: 74 06                    -  je MonsterHunterWorld.exe+1F8E3B3
    "MonsterHunterWorld.exe"+1F8E3AD: F6 46 0C 0E              -  test byte ptr [rsi+0C],0E
    "MonsterHunterWorld.exe"+1F8E3B1: 75 02                    -  jne MonsterHunterWorld.exe+1F8E3B5
    "MonsterHunterWorld.exe"+1F8E3B3: 33 F6                    -  xor esi,esi
    "MonsterHunterWorld.exe"+1F8E3B5: 48 8B 86 88 02 00 00     -  mov rax,[rsi+00000288]
    */
    struct vector<byte> Weapon_Hit = { 0x48, 0x8B, 0x57, 0x18, 0x48, 0x8B, 0x72, 0x08 };

    /* Weapon_SecondaryWeaponPtr OK
    * 1E 00 00 49 8B 5B 38 49 8B E3 41 5F 41 5E 41 5D
    "MonsterHunterWorld.exe"+216ECC5: 89 83 88 01 00 00        -  mov [rbx+00000188],eax
    "MonsterHunterWorld.exe"+216ECCB: 44 89 AB 8C 01 00 00     -  mov [rbx+0000018C],r13d
    "MonsterHunterWorld.exe"+216ECD2: 40 88 B3 98 1D 00 00     -  mov [rbx+00001D98],sil
    "MonsterHunterWorld.exe"+216ECD9: 49 8B 73 40              -  mov rsi,[r11+40]
    "MonsterHunterWorld.exe"+216ECDD: 40 88 BB C0 1D 00 00     -  mov [rbx+00001DC0],dil
    "MonsterHunterWorld.exe"+216ECE4: 49 8B 7B 48              -  mov rdi,[r11+48]
    "MonsterHunterWorld.exe"+216ECE8: 44 88 B3 F0 1D 00 00     -  mov [rbx+00001DF0],r14l
    "MonsterHunterWorld.exe"+216ECEF: 44 88 A3 24 1E 00 00     -  mov [rbx+00001E24],r12l
    "MonsterHunterWorld.exe"+216ECF6: 49 8B 5B 38              -  mov rbx,[r11+38]
    "MonsterHunterWorld.exe"+216ECFA: 49 8B E3                 -  mov rsp,r11
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+216ECFD: 41 5F                    -  pop r15
    "MonsterHunterWorld.exe"+216ECFF: 41 5E                    -  pop r14
    "MonsterHunterWorld.exe"+216ED01: 41 5D                    -  pop r13
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+216ED03: 41 5C                    -  pop r12
    "MonsterHunterWorld.exe"+216ED05: 5D                       -  pop rbp
    "MonsterHunterWorld.exe"+216ED06: C3                       -  ret 
    "MonsterHunterWorld.exe"+216ED07: CC                       -  int 3 
    "MonsterHunterWorld.exe"+216ED08: CC                       -  int 3 
    "MonsterHunterWorld.exe"+216ED09: CC                       -  int 3 
    "MonsterHunterWorld.exe"+216ED0A: CC                       -  int 3 
    "MonsterHunterWorld.exe"+216ED0B: CC                       -  int 3 
    "MonsterHunterWorld.exe"+216ED0C: CC                       -  int 3 
    "MonsterHunterWorld.exe"+216ED0D: CC                       -  int 3 
    */
    struct vector<byte> Weapon_SecondaryWeaponPtr = { 0x1E, 0x00, 0x00, 0x49, 0x8B, 0x5B, 0x38, 0x49, 0x8B, 0xE3, 0x41, 0x5F, 0x41, 0x5E, 0x41, 0x5D };

    /* Chat_ShowGameMessage OK
    * 48 89 5C 24 08 48 89 74 24 10 57 48 81 EC C0 01 00 00 80
    "MonsterHunterWorld.exe"+1A671E6: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1A671E7: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1A671E8: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1A671E9: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1A671EA: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1A671EB: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1A671EC: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1A671ED: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1A671EE: CC                                -  int 3 
    "MonsterHunterWorld.exe"+1A671EF: CC                                -  int 3 
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+1A671F0: 48 89 5C 24 08                    -  mov [rsp+08],rbx
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+1A671F5: 48 89 74 24 10                    -  mov [rsp+10],rsi
    "MonsterHunterWorld.exe"+1A671FA: 57                                -  push rdi
    "MonsterHunterWorld.exe"+1A671FB: 48 81 EC C0 01 00 00              -  sub rsp,000001C0
    "MonsterHunterWorld.exe"+1A67202: 80 79 30 00                       -  cmp byte ptr [rcx+30],00
    "MonsterHunterWorld.exe"+1A67206: 41 8B F1                          -  mov esi,r9d
    "MonsterHunterWorld.exe"+1A67209: 0F 29 B4 24 B0 01 00 00           -  movaps [rsp+000001B0],xmm6
    "MonsterHunterWorld.exe"+1A67211: 48 8B DA                          -  mov rbx,rdx
    "MonsterHunterWorld.exe"+1A67214: 0F 28 F2                          -  movaps xmm6,xmm2
    "MonsterHunterWorld.exe"+1A67217: 48 8B F9                          -  mov rdi,rcx
    "MonsterHunterWorld.exe"+1A6721A: 75 09                             -  jne MonsterHunterWorld.exe+1A67225
    */
    struct vector<byte> Chat_ShowGameMessage = { 0x48, 0x89, 0x5C, 0x24, 0x08, 0x48, 0x89, 0x74, 0x24, 0x10, 0x57, 0x48, 0x81, 0xEC, 0xC0, 0x01, 0x00, 0x00, 0x80 };

    /* Chat_MainPtr OK
    * 20 F7 FB 40 00 00
    "MonsterHunterWorld.exe"+506D32D: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+506D32F: 00 2F                 -  add [rdi],ch
    "MonsterHunterWorld.exe"+506D331: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+506D333: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+506D335: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+506D337: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+506D339: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+506D33B: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+506D33D: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+506D33F: 00                    - db 00  // SHORTENED TO HIT INJECTION FROM:  add [rax],ah
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+506D340: 20 F7                 -  and bh,dh
    "MonsterHunterWorld.exe"+506D342: FB                    -  sti 
    "MonsterHunterWorld.exe"+506D343: 40 00 00              -  add [rax],al
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+506D346: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+506D348: 2F                    -  das 
    "MonsterHunterWorld.exe"+506D349: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+506D34B: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+506D34D: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+506D34F: 00 38                 -  add [rax],bh
    "MonsterHunterWorld.exe"+506D351: 8A 44 43 01           -  mov al,[rbx+rax*2+01]
    "MonsterHunterWorld.exe"+506D355: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+506D357: 00 2C 8A              -  add [rdx+rcx*4],ch
    "MonsterHunterWorld.exe"+506D35A: 44 43                 -  inc ebx
    */
    struct vector<byte> Chat_MainPtr = { 0x20, 0xF7, 0xB7, 0x3B, 0x00, 0x00 };
    
    /* XboxPadPtr OK
    * 20 8C * 40 00 00 00
    "MonsterHunterWorld.exe"+5224A87: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5224A89: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5224A8B: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5224A8D: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5224A8F: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5224A91: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5224A93: 00                    - db 00  // SHORTENED TO HIT INJECTION FROM:  add [165A24A99],al
    "MonsterHunterWorld.exe"+5224A94: 05                    - db 05  // SHORTENED TO HIT INJECTION FROM:  add eax,20800000
    "MonsterHunterWorld.exe"+5224A95: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5224A97: 80 20                 - db 80 20  // SHORTENED TO HIT INJECTION FROM:  and byte ptr [rax],-74
    // ---------- INJECTING HERE ----------
    "MonsterHunterWorld.exe"+5224A99: 8C CF                 -  mov di,cs
    "MonsterHunterWorld.exe"+5224A9B: 40 00 00              -  add [rax],al
    "MonsterHunterWorld.exe"+5224A9E: 00 00                 -  add [rax],al
    // ---------- DONE INJECTING  ----------
    "MonsterHunterWorld.exe"+5224AA0: 98                    -  cwde
    "MonsterHunterWorld.exe"+5224AA1: 5D                    -  pop rbp
    "MonsterHunterWorld.exe"+5224AA2: 56                    -  push rsi
    "MonsterHunterWorld.exe"+5224AA3: 43 01 00              -  add [r8],eax
    "MonsterHunterWorld.exe"+5224AA6: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5224AA8: 80 5D 56 43           -  sbb byte ptr [rbp+56],43
    "MonsterHunterWorld.exe"+5224AAC: 01 00                 -  add [rax],eax
    "MonsterHunterWorld.exe"+5224AAE: 00 00                 -  add [rax],al
    "MonsterHunterWorld.exe"+5224AB0: D8 4A 22              -  fmul dword ptr [rdx+22]
    "MonsterHunterWorld.exe"+5224AB3: 45 01 00              -  add [r8],r8d
    */
    struct vector<byte> XboxPadPtr = { 0x20, 0x8c, 0xcf, 0x40, 0x00, 0x00 };


    static vector<byte*> scanmem(const vector<byte>& bytes)
    {
        vector<byte*> results;
        auto module = GetModuleHandle("MonsterHunterWorld.exe");
        if (module == nullptr) return results;

        MODULEINFO moduleInfo;
        if (!GetModuleInformation(GetCurrentProcess(), module, &moduleInfo, sizeof(moduleInfo)))
            return results;

        byte* startAddr = (byte*)module;
        byte* endAddr = startAddr + moduleInfo.SizeOfImage;
        byte* addr = startAddr;

        while (addr < endAddr)
        {
            MEMORY_BASIC_INFORMATION memInfo;
            if (!VirtualQuery(addr, &memInfo, sizeof(memInfo)) || memInfo.State != MEM_COMMIT || (memInfo.Protect & PAGE_GUARD))
                continue;
            byte* begin = (byte*)memInfo.BaseAddress;
            byte* end = begin + memInfo.RegionSize;


            byte* found = search(begin, end, bytes.begin(), bytes.end());
            while (found != end) {
                results.push_back(found);
                found = search(found + 1, end, bytes.begin(), bytes.end());
            }

            addr = end;
            memInfo = {};
        }

        return results;
    }

    static long long AobScanmem(vector<byte> AobData) {
        auto ScanmemData = scanmem(AobData);
        if (ScanmemData.size() == 1) {
            return (long long)ScanmemData[0];
        }
        else {
            return 0x0;
        }
    }

    static void InitAobAddress() {
        map<string, long long> AobScanmems;
        AobScanmems["Player_BasePtr"] = AobScanmem(Player_BasePtr);

        for (auto [name, address] : AobScanmems) {
            if (name == "Player_BasePtr" and address != 0x0)
                MH::Player::BasePtr = (void*)address;
        }
    }
}

