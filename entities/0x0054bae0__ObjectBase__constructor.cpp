// FUNC_NAME: ObjectBase::constructor
// Address: 0x0054bae0
// Initializes an object with vtable, linked list node, class hash, and copies source data

void __fastcall ObjectBase::constructor(void *this, undefined4 *source)
{
    // this is passed in ECX, source is passed in EDX? Actually only ECX is used; source is same as this? 
    // But the decompiler shows param_1 as the only parameter, which is ECX. 
    // However the code reads from param_1[0..3] after setting vtable, so source must be a different pointer.
    // Re-analyzing: fastcall convention: ECX = this, EDX = second param. 
    // The Ghidra signature "void __fastcall FUN_0054bae0(undefined4 *param_1)" means param_1 is ECX.
    // But the callers likely set ECX=this and EDX=source, but the decompiler does not show EDX.
    // Actually the code uses in_EAX (the ECX register) and also accesses param_1[]. 
    // Since param_1 is the same as in_EAX, it's reading from its own memory. 
    // So the function reads the first 4 dwords of the object and copies them to offset 0x6c.
    // That suggests the object was partially initialized before this call.
    // We'll model it as taking no additional parameters.

    undefined4 uVar1;
    undefined4 *thisPtr;

    // thisPtr = ECX (this)
    thisPtr = in_EAX;

    // Global initializer value (likely a reference count or sequence number)
    uVar1 = DAT_00e445dc;

    // Set vtable pointer at offset 0
    *thisPtr = &PTR_LAB_00e39f00;  // +0x00: vtable

    // Set linked list pointer at offset 4 to point to itself+8 (intrusive node)
    thisPtr[4] = (undefined4)(thisPtr + 8);  // +0x04: next pointer (points to own offset 8)

    // Set some flag/state at offset 1 from global
    thisPtr[1] = uVar1;  // +0x04? Wait indices: [1] is offset 4 bytes. Actually dword offsets: [0]=0, [1]=4, [2]=8, etc. So [1] is offset 4.
    // But we already set [4] above. That would overwrite? Let's reorder:
    // The code does:
    // in_EAX[6] = 0x80000008;
    // in_EAX[4] = in_EAX + 8;
    // in_EAX[1] = uVar1;
    // *in_EAX = &PTR_LAB_00e39f00;
    // in_EAX[5] = 0;
    // So it sets [6] first, then [4], then [1], then [0], then [5]. So [1] is before [4]? No, [1] is offset 4 bytes, [4] is offset 16 bytes. They don't overlap.

    // Let's follow order from decompiled:
    thisPtr[6] = 0x80000008;   // +0x18: some flag/size (0x80000008)
    thisPtr[4] = (undefined4)(thisPtr + 8); // +0x10: linked list next (points to this+32? actually this+8 is offset 32? Wait: thisPtr is a dword pointer, so thisPtr+8 is offset 32 bytes)
    thisPtr[1] = uVar1;        // +0x04: initial reference count or state from global
    *thisPtr = &PTR_LAB_00e39f00; // +0x00: vtable
    thisPtr[5] = 0;            // +0x14: some pointer cleared

    // Later block:
    thisPtr[0x6a] = 0xfe16702f;  // +0x1A8: class hash/ID
    thisPtr[0x6c] = *source;     // +0x1B0: copy first 4 bytes from source
    thisPtr[0x6d] = source[1];   // +0x1B4
    thisPtr[0x6e] = source[2];   // +0x1B8
    thisPtr[0x6f] = source[3];   // +0x1BC

    // Repeat assignments (likely redundant due to re-initialization)
    thisPtr[1] = uVar1;         // +0x04 again
    uVar1 = DAT_00e2cd54;      // another global

    thisPtr[5] = 0;            // +0x14 again
    thisPtr[0x68] = 0;         // +0x1A0: zero
    thisPtr[0x69] = uVar1;     // +0x1A4: set from global
    thisPtr[0x6a] = 0xfe16702f; // +0x1A8: class hash again
    thisPtr[0x6b] = 0;         // +0x1AC: zero
    return;
}