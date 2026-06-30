// FUNC_NAME: UnknownClass::resetOrInitialize
void __fastcall UnknownClass::resetOrInitialize(UnknownClass *this)
{
    // Set vtable pointer to a global vtable (constructor initialization)
    *(uint32_t *)this = PTR_LAB_00d63090;

    // If the member at offset 0x68 (likely a pointer) is not null, destroy it
    // This suggests the memory might have been reused and needs cleanup
    if (*(void **)((uint8_t *)this + 0x68) != nullptr) {
        // Call destructor/release function for the internal object at +0x68
        // FUN_004daf90 is likely an operator delete or a custom free
        FUN_004daf90(this + 0x68);
    }

    // Call a global cleanup/deinitialization function
    // Likely handles engine-level teardown or resource cleanup
    FUN_0080ea60();
}