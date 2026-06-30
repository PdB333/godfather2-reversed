// FUNC_0043B400: GameObject::~GameObject
void __fastcall GameObject::~GameObject(int *this) {
    // Set vtable to base destructor vtable (indicates partial destruction)
    *this = (int)&PTR_FUN_00e30eec;

    // If the pointer at offset +0x34 (object handle) and +0x38 (maybe string) are non-null,
    // release the resource at +0x34
    if (this[0xd] != 0 && this[0xe] != 0) {
        FUN_00482990(this[0xd]); // free/release object at +0x34
    }

    // Check flag at bit 29 of flags at +0x14. If set, call cleanup on this object
    if (((uint)this[5] >> 0x1d & 1) != 0) {
        FUN_00446560(this); // additional cleanup, e.g., remove from registry
    }

    // Check flag at bit 28 of flags. If set, free a slot in a global bitmask pool
    if (((uint)this[5] >> 0x1c & 1) != 0) {
        // Extract 12-bit index from flags (bits 0-11)
        int idx = this[5] & 0xfff;
        // Clear the corresponding bit in global array DAT_0120e718
        // The shift amount is controlled by global DAT_0120e710 (used as a bit shift divisor)
        int shiftAmount = idx >> ((byte)DAT_0120e710 & 0x1f);
        int bitIndex = idx & 0x1f;
        (&DAT_0120e718)[shiftAmount] &= ~(1 << bitIndex);
        // Clear the index and flags: keep only bits 12-19? Actually 0xeffff000 clears all but bits 12-31, but also clears bit 28.
        this[5] = this[5] & 0xeffff000;
    }
}