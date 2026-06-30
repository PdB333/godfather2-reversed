// FUNC_NAME: unknown::ensureInitializedAt_00603b20
void ensureInitialized(void) {
    // this pointer likely in ESI (unaff_ESI)
    // Offset 0x4c contains flags; bit 2 (value 4) indicates initialization state.
    if ((*(unsigned int*)((char*)this + 0x4c) & 4) == 0) {
        // Call internal load/init function twice (may be needed for double buffering or two-step init)
        someLoadFunction(this);
        someLoadFunction(this);
        // Mark as initialized (set bit 2)
        *(unsigned int*)((char*)this + 0x4c) |= 4;
    }
}