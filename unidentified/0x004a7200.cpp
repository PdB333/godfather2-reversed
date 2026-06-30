// FUN_004a7200: EARSObject::~EARSObject

// EARS engine destructor – sets vtable to a destruction-specific table before cleanup
// and then resets to the original base vtable after the sub-object cleanup.
void __thiscall EARSObject::~EARSObject(void* this) {
    // +0x00: vtable pointer
    *(void**)this = (void*)0x00e35468; // Temporary vtable for destruction

    // +0x90 (offset 0x24 in dwords) – if non‑zero, clean up sub‑object at +0x10
    if (*(int*)((char*)this + 0x90) != 0) {
        // +0x10: sub‑object (e.g., a resource handle, pointer, or embedded structure)
        FUN_00610100((void*)((char*)this + 0x10));
    }

    // +0x00: restore the original base vtable (often used after chaining to base destructor)
    *(void**)this = (void*)0x00e2f638;
}