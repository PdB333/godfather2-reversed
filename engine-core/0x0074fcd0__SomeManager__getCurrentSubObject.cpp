// FUNC_NAME: SomeManager::getCurrentSubObject
void* __fastcall SomeManager::getCurrentSubObject(void* this) {
    // offset 0x110: pointer to a large subsystem (e.g., SimManager, CrimeManager)
    void* subsystem = *(void**)((char*)this + 0x110);
    if (subsystem != 0) {
        // offset 0x24cc: pointer to an embedded structure (e.g., current interaction or active entity)
        void* embedded = *(void**)((char*)subsystem + 0x24cc);
        if (embedded != 0) {
            // The embedded structure is at offset +0x48 within its parent container.
            // Subtract 0x48 to get the containing object.
            return (void*)((char*)embedded - 0x48);
        }
    }
    return 0;
}