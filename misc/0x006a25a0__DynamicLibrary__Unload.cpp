// FUNC_NAME: DynamicLibrary::Unload
// Address: 0x006a25a0
// Role: Releases the loaded library handle and zeroes out associated fields.
// Offsets: +0x90 = HMODULE handle, +0x94..+0xA4 = additional pointers/handles.

void __thiscall DynamicLibrary::Unload(int this)
{
    // Free the loaded library
    FreeLibrary(*(HMODULE *)(this + 0x90));
    
    // Clear all module tracking fields
    *(int *)(this + 0x90) = 0;  // HMODULE
    *(int *)(this + 0x94) = 0;  // Unknown field 1
    *(int *)(this + 0x98) = 0;  // Unknown field 2
    *(int *)(this + 0x9c) = 0;  // Unknown field 3
    *(int *)(this + 0xa0) = 0;  // Unknown field 4
    *(int *)(this + 0xa4) = 0;  // Unknown field 5
}