// FUNC_NAME: CBasePooledObject::~CBasePooledObject
void __fastcall CBasePooledObject::destructor(CBasePooledObject* this) {
    int iVar1;
    int* piVar2;

    // Set vtable to first (derived) vtable
    this->vtable = (uint32_t*)&PTR_FUN_00e380f8;

    iVar1 = this->field_0x68;   // +0x68: pointer to sub-object or resource
    if (iVar1 != 0) {
        if (*(int*)(iVar1 + 8) != 0) {
            FUN_009e7530(iVar1);  // likely sub-object destructor / release
        }
        FUN_009f01a0();          // static cleanup routine
    }

    if (this->field_0x6c != 0) {  // +0x6c: second sub-object
        FUN_009c8eb0(this->field_0x6c);
    }

    // State check (byte at +0x5b == 6) and flag check in another object (+0x24)
    if ((*(char*)((int)this + 0x5b) == 0x06) &&
        ((*(uint32_t*)(this->field_0x24 + 0x104) & 0x400) != 0)) {
        this->field_0x64 = 0;     // +0x64: flag or pointer cleared
    }

    FUN_0050bef0();               // base class destructor chain / common cleanup

    // Set vtable for base class (second vtable)
    this->vtable = (uint32_t*)&PTR_FUN_00e37110;

    // If this object was allocated from a pool, return the node to free list
    if (this->field_0x10 != 0) {   // +0x10: pointer to pool node (linked list)
        piVar2 = (int*)(DAT_01206880 + 0x14);  // global pool manager + offset for freelist head
        **(uint32_t**)(DAT_01206880 + 0x14) = &PTR_LAB_01123be8; // sentinel value
        *piVar2 = *piVar2 + 4;                    // increment freelist pointer
        *(int*)*piVar2 = this->field_0x10;        // store node address into free list
        *piVar2 = *piVar2 + 4;                    // advance freelist pointer
        this->field_0x10 = 0;                     // clear node pointer
        this->field_0x14 = 0;
    }
}