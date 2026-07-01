// FUNC_NAME: EARSObject::destroy
void __fastcall EARSObject::destroy(void* this) {
    // Check if child object pointer at +0x64 is non-null
    if (*(void***)((char*)this + 0x64) != nullptr) {
        // Call virtual function at vtable offset 0x14 (likely a destructor/release)
        (*(void(__thiscall**)(void*))(**(void***)((char*)this + 0x64) + 0x14))(
            *(void**)((char*)this + 0x64));
    }
    // Set destroyed flag at +0x60 to true
    *(uint8_t*)((char*)this + 0x60) = 1;
}