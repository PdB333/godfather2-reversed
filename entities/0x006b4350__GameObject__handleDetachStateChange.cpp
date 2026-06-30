// FUNC_NAME: GameObject::handleDetachStateChange
void __fastcall GameObject::handleDetachStateChange(GameObject* this) {
    int typeId;
    int detachState;

    // Check if there is an attachment object at offset 0xFC
    if (*(int*)(this + 0xFC) != 0) {
        detachState = getDetachState(); // Returns current state (e.g., 0,1,2)
        if (detachState != 0) {
            // Use appropriate type ID based on state
            if (detachState == 2) {
                typeId = *(int*)(this + 0x40); // +0x40: secondary type field
            } else {
                typeId = *(int*)(this + 0x3C); // +0x3C: primary type field
            }
            // Check for a specific type/magic value (maybe e.g., "Player" type hash)
            if (typeId == 0x637B907) {
                globalStructClear(0x112A59C, 0); // Clear some global data
            }
            // Perform detachment operations on children
            detachChild1(this, detachState);
            detachChild2(this, detachState);
            // If attachment object exists, call its virtual method at vtable+0x18 (e.g., release)
            if (*(int*)(this + 0xFC) != nullptr) {
                (*(void(__thiscall**)(int))(**(int**)(this + 0xFC) + 0x18))(1);
            }
            // Clear attachment pointer
            *(int*)(this + 0xFC) = 0;
            // Copy some value from global manager into offset 0x100
            if (*(int*)(DAT_0112A668 + 0x18) != 0) {
                *(int*)(this + 0x100) = *(int*)(*(int*)(DAT_0112A668 + 0x18) + 0xBC);
            }
            // Run post-detach cleanup
            postDetachCleanup();
        }
    }
}