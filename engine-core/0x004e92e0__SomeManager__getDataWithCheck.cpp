// FUNC_NAME: SomeManager::getDataWithCheck
// Function at 0x004e92e0: checks if a certain resource/hash is valid and returns a pointer from object offset 0x218
int* __fastcall SomeManager::getDataWithCheck(int* this) {
    int outResult; // local_4, unused output from virtual call
    // Virtual function at vtable+0x10 (index 4): takes a hash and a pointer for output, returns bool
    bool success = ((bool (__fastcall*)(int*, int, int*))(*this)[4])(this, 0xAE986323, &outResult);
    if (success) {
        // If validation passed, return the value at offset 0x218 from this object
        return *(int**)(this + 0x218); // +0x218 likely a pointer or integer field
    }
    return nullptr;
}