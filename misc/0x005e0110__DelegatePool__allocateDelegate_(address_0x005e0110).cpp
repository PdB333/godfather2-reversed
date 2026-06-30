// FUNC_NAME: DelegatePool::allocateDelegate (address 0x005e0110)
// Allocates and initializes a 24-byte delegate/continuation block.
// The object has a vtable pointer at offset +0x4 and a pointer to a previous delegate at offset +0x8.
// The delegate captures the return address, param2, and two values from ESI (likely a two-word data pointer).

void __thiscall DelegatePool::allocateDelegate(int param2) {
    undefined4 *puVar1;
    // unaff_ESI and unaff_retaddr are register values (ESI and return address) at call time
    undefined4 *esiPtr;    // from ESI register
    undefined4 returnAddr; // return address from stack
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;

    puVar1 = (undefined4 *)*(void**)(this + 8); // +0x8: pointer to previous delegate (or null)
    if (*(void**)(this + 8) == 0) {
        // If no previous delegate, use local buffer as fallback
        local_c = 0;
        local_8 = 0;
        local_4 = 0;
        puVar1 = &local_c;
    }
    // Call allocator function from vtable at offset 0 (vtable pointer at +0x4)
    // The allocator takes size (0x18) and a pointer (previous or local buffer)
    puVar1 = (undefined4 *)((*(void**)(*(int*)(this + 4)))(0x18, puVar1));
    if (puVar1 != 0) {
        puVar1[0] = local_4;          // first 4 bytes: from local buffer or zero
        puVar1[1] = returnAddr;       // return address of caller
        puVar1[2] = param2;           // parameter passed to this function
        puVar1[3] = esiPtr[0];        // first word from ESI-register pointer
        puVar1[4] = esiPtr[1];        // second word from ESI-register pointer
        *(char*)(puVar1 + 5) = 0;     // offset 20 (0x14): zero
        *(char*)((int)puVar1 + 0x15) = 0; // offset 21 (0x15): zero
    }
}