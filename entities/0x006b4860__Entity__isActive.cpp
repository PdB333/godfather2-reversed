// FUNC_NAME: Entity::isActive
// Address: 0x006b4860
// Checks whether this entity is active/valid by examining main flags, a network object pointer,
// and a secondary flag on that object. Returns the cached active state if conditions pass, else true.
bool Entity::isActive() {
    bool cachedActive = *(bool*)((char*)this + 0x16c);       // +0x16c: cached active flag
    uint mainFlags = *(uint*)((char*)this + 0x34);           // +0x34: main state flags

    // Check entity is not dead/hidden (flags 0x120000) and not flagged with bit0
    if ((mainFlags & 0x120000) == 0 && (mainFlags & 0x1) == 0) {
        void* networkObj = *(void**)((char*)this + 0x40);    // +0x40: pointer to network object
        if (networkObj != nullptr) {
            // Get a related object from the network object (e.g., proxy or component)
            void* relatedObj = FUN_008c74d0(networkObj);
            if (relatedObj != nullptr) {
                uint secondaryFlags = *(uint*)((char*)relatedObj + 0x84); // +0x84: secondary flags
                // Proceed only if bit 5 (0x20) is clear (e.g., not removed)
                if ((secondaryFlags & 0x20) == 0) {
                    return cachedActive;
                }
            }
        }
    }
    return true;
}