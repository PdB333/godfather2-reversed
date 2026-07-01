// FUNC_NAME: SystemManager::updateComponents
void __fastcall SystemManager::updateComponents(SystemManager* this) {
    // Call the first virtual function on each component stored at known offsets
    // The components are stored as pointers to objects with a vtable pointer at offset 0.
    // Offsets: +0x2c, +0x48, +0x64, +0x80, +0x9c, +0xb8
    // Each component's vtable entry 0 is likely an update/think method.

    // Component 1 at offset 0x2c
    if (*(int**)((char*)this + 0x2c) != nullptr) {
        (*(void(__fastcall**)(void*)) * (*(int**)((char*)this + 0x2c))) (*(void**)((char*)this + 0x2c));
    }

    // Component 2 at offset 0x48
    if (*(int**)((char*)this + 0x48) != nullptr) {
        (*(void(__fastcall**)(void*)) * (*(int**)((char*)this + 0x48))) (*(void**)((char*)this + 0x48));
    }

    // Component 3 at offset 0x64
    if (*(int**)((char*)this + 0x64) != nullptr) {
        (*(void(__fastcall**)(void*)) * (*(int**)((char*)this + 0x64))) (*(void**)((char*)this + 0x64));
    }

    // Component 4 at offset 0x80
    if (*(int**)((char*)this + 0x80) != nullptr) {
        (*(void(__fastcall**)(void*)) * (*(int**)((char*)this + 0x80))) (*(void**)((char*)this + 0x80));
    }

    // Component 5 at offset 0x9c
    if (*(int**)((char*)this + 0x9c) != nullptr) {
        (*(void(__fastcall**)(void*)) * (*(int**)((char*)this + 0x9c))) (*(void**)((char*)this + 0x9c));
    }

    // Component 6 at offset 0xb8
    if (*(int**)((char*)this + 0xb8) != nullptr) {
        (*(void(__fastcall**)(void*)) * (*(int**)((char*)this + 0xb8))) (*(void**)((char*)this + 0xb8));
    }

    // Unrecovered jump table at 0x007ef520 – likely dispatches to additional update logic
    // This may be a virtual function call or a switch on an internal state.
    // The exact behavior could not be reconstructed.
    (*(void(__fastcall**)(void*)) * (*(int**)((char*)this + 0xd4))) (*(void**)((char*)this + 0xd4));
}