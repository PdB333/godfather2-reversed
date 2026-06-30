// FUNC_NAME: Entity::addPositionOffset
// Address: 0x0051a0e0
// Adds a 3D translation vector to the entity's position, preserving the w component (likely padding or quaternion w).

void __thiscall Entity::addPositionOffset(float* translation) {
    // Get the global manager from thread-local storage (EA EARS engine pattern)
    // FS:0x2c -> pointer to TLS block -> first dword -> pointer to game manager + 0x8
    int* tlsBase = *(int**)__readfsdword(0x2c);
    int* manager = (int*)*(tlsBase + 2); // offset 0x8 from base

    // The position pool starts at offset 0x80 in the manager.
    // Each entity stores an index into this pool at offset 0x10.
    int poolIndex = *(int*)(this + 0x10);
    float* position = (float*)((int)manager + 0x80 + poolIndex); // +0x80 start of pool

    // Read original 4-component vector (xyz + w)
    float origX = position[0];
    float origY = position[1];
    float origZ = position[2];
    float origW = position[3];

    // Add translation to x,y,z only; w remains unchanged
    position[0] = origX + translation[0];
    position[1] = origY + translation[1];
    position[2] = origZ + translation[2];
    position[3] = origW; // restore original w
}