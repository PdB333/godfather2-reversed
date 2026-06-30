// FUNC_NAME: SomeClass::reinitialize
void __thiscall SomeClass::reinitialize(void *this) {
    // set vtable pointer to base class vtable (0x00d64d18)
    *(int *)this = &PTR_LAB_00d64d18;

    // check flag at offset +0x20 (byte) – if zero, allocate sub-object of size 0x48
    if (*(char *)((char *)this + 0x20) == '\0') {
        customAlloc(0x48);  // allocation result is not stored (likely a side-effect or different initialization)
    }

    // if pointer at offset +0x64 exists, release it
    if (*(void **)((char *)this + 0x64) != 0) {
        customDelete((void *)(*(int *)((char *)this + 0x64))); // actually call on the pointer value (maybe cast)
    }

    // global cleanup / registration function
    globalCleanup();
}