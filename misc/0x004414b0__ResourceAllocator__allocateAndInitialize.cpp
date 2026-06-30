// FUNC_NAME: ResourceAllocator::allocateAndInitialize
// Address: 0x004414b0
// This function allocates a 32-byte object (struct size = 0x20) via a virtual allocator,
// initializes it with a mix of local stack values, a "retaddr" (likely a vtable or ID),
// zeroes the fourth field, and copies 5 fields from the input data pointer.
// The input data pointer (param_4) points to a structure of at least 6 uint32_ts (indices 0,1,3,4,5 used; index 2 skipped).
// If param_4[1] is nonzero, calls an external reference counter (FUN_00408030).

class ResourceAllocator;
struct AllocatedObject {
    uint32_t field0;       // +0x00  - previous list pointer or flag
    uint32_t field1;       // +0x04  - return address / vtable index / type
    uint32_t dataA;        // +0x08  - param_4[0]
    uint32_t dataB;        // +0x0C  - param_4[1]
    uint32_t zeroField;    // +0x10  - always zeroed (two shorts)
    uint32_t dataC;        // +0x14  - param_4[3]
    uint32_t dataD;        // +0x18  - param_4[4]
    uint32_t dataE;        // +0x1C  - param_4[5]
};

// __thiscall: ecx = this (allocator), edx = param_2 (unused), stack: param_3 (unused), param_4 (data input)
AllocatedObject* __thiscall ResourceAllocator::allocateAndInitialize(
    ResourceAllocator* this,
    uint32_t param_2,         // not used
    uint32_t param_3,         // not used
    uint32_t* param_4)        // source data (6+ uint32_ts)
{
    AllocatedObject* obj;
    AllocatedObject stackHint;         // local_c, local_8, local_4 layout as fallback
    AllocatedObject* pObjHint;

    // If the allocator's hint pointer (this[1]) is null, use a temporary zeroed structure on stack
    pObjHint = (AllocatedObject*)this[1];
    if (pObjHint == nullptr) {
        stackHint.field0 = 0;
        stackHint.field1 = 0;
        stackHint.zeroField = 0;   // zeroField covers field0..field4? Actually only field0,field1,zeroField fit in 12 bytes? but compiler will zero all.
        // In reality: local_c=0, local_8=0, local_4=0, then puVar2 = &local_c (which is field0 of stackHint)
        pObjHint = &stackHint;
    }

    // Virtual call to allocate a block of 0x20 (32) bytes, using pObjHint as a placement hint
    // The vtable pointer is at *(void***)this  (first field of this)
    obj = (AllocatedObject*)((this->vtable->allocate)(0x20, pObjHint));

    if (obj != nullptr) {
        obj->field0 = stackHint.field0;   // local_4 (note: if pObjHint not null, stackHint.field0 may be uninitialized? but compiler sets local_4 from actual intended param)
        // In original asm, local_4 came from possibly a register or another stack slot not shown.
        // This likely carries a pointer or flag.
    }

    // The second field is set to the return address (unaff_retaddr) – likely a type ID or vtable pointer
    if (obj + 1 != nullptr) {   // always true unless overflow; safe cast
        obj->field1 = (uint32_t)__return_address();   // unaff_retaddr – substituted for readability
    }

    // Fill fields 2,3,5-7 from input data. Field4 is zeroed.
    if (obj + 2 != nullptr) {   // always true
        obj->dataA = param_4[0];
        int iVar1 = param_4[1];
        obj->dataB = iVar1;
        // Zero out the 4-byte field at offset 0x10 (obj->zeroField) using two 16-bit writes
        *(uint16_t*)&obj->zeroField = 0;
        *(uint16_t*)((uint8_t*)obj + 0x12) = 0;   // overwrites the high half of zeroField
        if (iVar1 != 0) {
            FUN_00408030();   // likely increments reference count or registers this allocation
        }
        obj->dataC = param_4[3];
        obj->dataD = param_4[4];
        obj->dataE = param_4[5];
    }
    return obj;
}