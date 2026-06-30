// FUNC_NAME: UnknownClass::~UnknownClass
void __fastcall UnknownClass::~UnknownClass(UnknownClass* this)
{
    // Set vtable pointers for multiple inheritance (base class vtables)
    *this = &PTR_FUN_00d5d768;                   // +0x00: primary vtable
    this->vtable2 = &PTR_LAB_00d5d758;           // +0x3c: second vtable
    this->vtable3 = &PTR_LAB_00d5d754;           // +0x48: third vtable

    // Deallocate global data object
    FUN_004086d0(&DAT_0120e93c);

    // If flag at +0x18 is set, deallocate another global data object
    if (this->byteFlag_0x18 != 0) {
        FUN_004086d0(&DAT_012069c4);
    }

    // Check if any of the four resource pointers at +0x50..0x5c are non-null
    if (this->resourcePtr_0x14 != 0 || this->resourcePtr_0x15 != 0 ||
        this->resourcePtr_0x16 != 0 || this->resourcePtr_0x17 != 0)
    {
        // Compute a hash from four int fields at +0x20,0x24,0x28,0x2c
        // using iterative multiplication by 0x21 (33)
        int hash = this->field_0x20 * 0x21 + this->field_0x24;
        hash = hash * 0x21 + this->field_0x28;
        hash = hash * 0x21 + this->field_0x2c;

        // Release the resource associated with this hash
        FUN_006a64f0(hash);
    }

    // Perform final cleanup (likely operator delete or freeing internal lists)
    FUN_0046c640();
}