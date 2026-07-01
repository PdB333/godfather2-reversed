// FUNC_NAME: SomeClass::copyFrom (0x00856510)
// Role: Copies fields from source object to this, after calling base copy at FUN_00856110.
// Offsets: +0x0c, +0x10, +0x14, +0x1c, +0x20, +0x28, +0x2c, +0x34, +0x38, +0x40

int __thiscall SomeClass::copyFrom(int thisPtr, int sourcePtr)
{
    // Call base class copy/init (likely copies fields at offsets 0x00-0x0b)
    FUN_00856110(sourcePtr);

    // Copy fields from source to this
    *(int*)(thisPtr + 0x0c) = *(int*)(sourcePtr + 0x0c);       // +0x0c: field1 (4 bytes)
    *(int*)(thisPtr + 0x10) = *(int*)(sourcePtr + 0x10);       // +0x10: field2 (4 bytes)
    *(long long*)(thisPtr + 0x14) = *(long long*)(sourcePtr + 0x14); // +0x14: field3 (8 bytes)
    *(int*)(thisPtr + 0x1c) = *(int*)(sourcePtr + 0x1c);       // +0x1c: field4 (4 bytes)
    *(long long*)(thisPtr + 0x20) = *(long long*)(sourcePtr + 0x20); // +0x20: field5 (8 bytes)
    *(int*)(thisPtr + 0x28) = *(int*)(sourcePtr + 0x28);       // +0x28: field6 (4 bytes)
    *(long long*)(thisPtr + 0x2c) = *(long long*)(sourcePtr + 0x2c); // +0x2c: field7 (8 bytes)
    *(int*)(thisPtr + 0x34) = *(int*)(sourcePtr + 0x34);       // +0x34: field8 (4 bytes)
    *(long long*)(thisPtr + 0x38) = *(long long*)(sourcePtr + 0x38); // +0x38: field9 (8 bytes)
    *(int*)(thisPtr + 0x40) = *(int*)(sourcePtr + 0x40);       // +0x40: field10 (4 bytes)

    return thisPtr;
}