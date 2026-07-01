// FUNC_NAME: Sentient::~Sentient
void __fastcall Sentient::~Sentient(Sentient* this)
{
    int* piVar1;

    // Store pointer to a child component at offset 0x5c
    piVar1 = (int*)this->field_0x5c;
    // Set vtable to the derived class vtable (PTR_LAB_00d6821c)
    this->vtable = &g_vtable_SentientDerived;
    // Call some initialization/reset with value 1.0f (e.g., set speed, volume, or max health)
    FUN_00460300(1.0f);
    // If pointer at offset 0x70 is non-null and not equal to 0x48, release it
    if ((this->field_0x70 != 0) && (this->field_0_0x70 != (int*)0x48)) {
        FUN_007768b0();
    }
    // Virtual call on the component at offset 0x5c (via its vtable at offset 0x260)
    (**(code**)(*piVar1 + 0x260))();
    // Check bit 10 of the flags at offset 0xAC
    if (((uint)this->field_0xAC >> 10 & 1) != 0) {
        // Retrieve the global input manager or similar system
        piVar1 = (int*)FUN_00716420();
        // Disable two features on that manager (functions at vtable offsets 0x24 and 0x28)
        (**(code**)(*piVar1 + 0x24))(0);
        (**(code**)(*piVar1 + 0x28))(0);
    }
    // Deallocate memory of size 0x5a (90 bytes) – possibly a pool allocation
    FUN_007f6420(0x5a);
    // If the subobject at offset 0x70 exists, call its destructor
    if (this->field_0x70 != 0) {
        FUN_004daf90((int*)this + 0x1c);
    }
    // Switch vtable to the base class (PTR_LAB_00d63090)
    this->vtable = &g_vtable_SentientBase;
    // If the subobject at offset 0x68 exists, call its destructor
    if (this->field_0x68 != 0) {
        FUN_004daf90((int*)this + 0x1a);
    }
    // Perform global cleanup (e.g., decrement a reference counter, finalize stats)
    FUN_0080ea60();
}