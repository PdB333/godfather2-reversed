// FUNC_NAME: Entity::initializeUUIDRegistration
void __thiscall Entity::initializeUUIDRegistration(void) {
    char networkFlag; // from FUN_0071fa00
    int handle; // entity handle
    UUID uuid; // buffer for UUID
    int* local_8; // pointer to some UUID structure (size 8? but defined as int[2])
    
    // Retrieve primary handle (likely a game object handle)
    handle = *(int*)((int)this + 0x264);
    
    // If the game is in a network mode and a flag is set, use secondary handle
    if (*(int*)(*(int*)((int)this + 0x180) + 0xd8) != 0) {
        networkFlag = FUN_0071fa00(); // likely returns non-zero if network game
        if (networkFlag != '\0') {
            handle = *(int*)((int)this + 0x268);
        }
    }
    
    if (handle != 0) {
        // Clear some global state (perhaps a network packet buffer)
        FUN_00892af0(0);
        // Set flags on this object (e.g., mark as network-replicated)
        FUN_00892a90((int)this, 1);
        // Extract UUID from the entity handle
        FUN_00894c40(handle, (byte*)&uuid);
        // If a second UUID structure is present, process it
        if (local_8 != 0) {
            FUN_004daf90(local_8);
        }
    }
    
    // Check if this object's type hash matches a known constant (e.g., "Player")
    if (*(int*)(*(int*)((int)this + 0x180) + 0x40) == 0x637b907) {
        // Build a UUID from a stored value at offset 0x254
        unsigned int guidPart1 = *(unsigned int*)((int)this + 0x254);
        unsigned int guidPart2 = 0;
        unsigned char guidPart3 = 0;
        // Note: this local stack layout may form a 12-byte GUID (4+4+4)
        unsigned int* guidBuffer = &guidPart1;
        // Register this UUID in the game's global object table
        FUN_00408a00(guidBuffer, 0);
    }
}