// FUNC_NAME: PlayerActionableInfo::constructor
void __thiscall PlayerActionableInfo::constructor(void *this)
{
    int in_EAX;
    undefined4 *puVar1;
    int *piVar2;
    undefined1 uVar3;
    int extraout_EDX;
    int iVar4;
    undefined4 uVar5;
    undefined4 uVar6;
    undefined4 uVar7;
    undefined4 uVar8;
    
    uVar6 = DAT_00e2b1a4;
    uVar8 = DAT_00e2b050;
    uVar7 = DAT_00e2b04c;
    uVar5 = 0;
    
    // Initialize member variables
    *(undefined4 *)(in_EAX + 0xc) = 0;   // +0x0C: some flag
    *(undefined4 *)(in_EAX + 0x10) = 0;  // +0x10: some flag
    *(undefined4 *)(in_EAX + 0x14) = 0xffffffff; // +0x14: -1 (invalid index)
    *(undefined4 *)(in_EAX + 0x68) = 0;  // +0x68: some pointer/flag
    *(undefined4 *)(in_EAX + 0x6c) = 0;  // +0x6C: some pointer/flag
    *(undefined1 *)(in_EAX + 0x70) = 0;  // +0x70: byte flag
    *(undefined4 *)(in_EAX + 100) = 1;   // +0x64: some count (set to 1)
    *(undefined4 *)(in_EAX + 0x74) = 1;  // +0x74: some count (set to 1)
    *(undefined4 *)(in_EAX + 0x78) = 0;  // +0x78: some flag
    *(undefined4 *)(in_EAX + 0x7c) = 0;  // +0x7C: some flag
    *(undefined1 *)(in_EAX + 0x80) = 0;  // +0x80: byte flag
    *(undefined4 *)(in_EAX + 0x98) = 0;  // +0x98: some pointer/flag
    *(undefined1 *)(in_EAX + 0x84) = 0;  // +0x84: byte flag
    *(undefined4 *)(in_EAX + 0x88) = uVar6; // +0x88: some global value
    *(undefined1 *)(in_EAX + 0x85) = 0;  // +0x85: byte flag
    *(undefined4 *)(in_EAX + 0x8c) = uVar7; // +0x8C: some global value
    *(undefined4 *)(in_EAX + 0x90) = uVar8; // +0x90: some global value
    *(undefined4 *)(in_EAX + 0x94) = 0;  // +0x94: some pointer/flag
    *(undefined4 *)(in_EAX + 0x9c) = 0;  // +0x9C: some pointer/flag
    *(undefined4 *)(in_EAX + 0xa0) = 0;  // +0xA0: some pointer/flag
    
    FUN_005e3130(); // Initialize some sub-component
    
    piVar2 = (int *)(in_EAX + 0xe0); // +0xE0: start of an array
    iVar4 = extraout_EDX + 3;        // Array size (4 elements)
    puVar1 = (undefined4 *)(in_EAX + 0xf0); // +0xF0: start of another array
    
    do {
        // Initialize each element of the array (size 0x78 = 120 bytes per element)
        puVar1[3] = 1;               // +0x0C: some flag
        puVar1[4] = uVar5;           // +0x10: zero
        puVar1[5] = uVar5;           // +0x14: zero
        uVar3 = (undefined1)extraout_EDX;
        *(undefined1 *)(puVar1 + 6) = uVar3; // +0x18: byte
        puVar1[0x12] = 100;          // +0x48: some value (100)
        *piVar2 = extraout_EDX;      // +0x00: some value
        puVar1[0x18] = extraout_EDX; // +0x60: some value
        puVar1[0x19] = extraout_EDX; // +0x64: some value
        puVar1[-3] = extraout_EDX;   // -0x0C: some value
        *(undefined1 *)(puVar1 + -2) = uVar3; // -0x08: byte
        *(undefined1 *)((int)puVar1 + -7) = uVar3; // -0x07: byte
        puVar1[0x14] = extraout_EDX; // +0x50: some value
        puVar1[0x15] = extraout_EDX; // +0x54: some value
        puVar1[0x16] = 0xffffffff;   // +0x58: -1 (invalid index)
        puVar1[-1] = 1;              // -0x04: some flag (1)
        *puVar1 = uVar5;             // +0x00: zero
        puVar1[1] = uVar5;           // +0x04: zero
        *(undefined1 *)(puVar1 + 2) = uVar3; // +0x08: byte
        puVar1[0xc] = extraout_EDX;  // +0x30: some value
        *(undefined1 *)(puVar1 + 7) = uVar3; // +0x1C: byte
        puVar1[8] = uVar6;           // +0x20: some global value
        *(undefined1 *)((int)puVar1 + 0x1d) = uVar3; // +0x1D: byte
        puVar1[9] = uVar7;           // +0x24: some global value
        puVar1[10] = uVar8;          // +0x28: some global value
        puVar1[0xb] = extraout_EDX;  // +0x2C: some value
        puVar1[0xd] = extraout_EDX;  // +0x34: some value
        puVar1[0xe] = extraout_EDX;  // +0x38: some value
        puVar1[0xf] = uVar6;         // +0x3C: some global value
        puVar1[0x10] = uVar6;        // +0x40: some global value
        puVar1[0x11] = uVar6;        // +0x44: some global value
        puVar1[0x12] = 100;          // +0x48: some value (100)
        puVar1[0x13] = extraout_EDX; // +0x4C: some value
        puVar1[0x17] = extraout_EDX; // +0x5C: some value
        
        piVar2 = piVar2 + 0x1e;      // Advance by 30 ints (120 bytes)
        puVar1 = puVar1 + 0x1e;      // Advance by 30 ints (120 bytes)
        iVar4 = iVar4 + -1;
    } while (-1 < iVar4);
    
    FUN_005e7ee0(); // Finalize initialization
    return;
}