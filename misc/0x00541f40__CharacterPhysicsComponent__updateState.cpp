// FUNC_NAME: CharacterPhysicsComponent::updateState
void __thiscall CharacterPhysicsComponent::updateState(void* thisPtr, void* transformData) {
    undefined4 local_80;
    undefined4 local_7c;
    undefined4 local_78;
    undefined4 local_74;
    undefined1 local_60[16];        // 16 bytes – possibly a quaternion or 4D vector
    undefined1 local_50[76];        // 76 bytes – likely a 4x4 matrix (64) + extra
    undefined1 auStack_b8[8];       // 8 bytes – maybe a float2 or direction
    undefined1 local_b0[40];        // 40 bytes – possibly a bounding box or state buffer
    undefined1 auStack_88[8];       // 8 bytes – another small vector

    // Clear or reset the transform data
    resetTransform(transformData);

    // Extract the embedded object pointer at offset 0x260 in the character component
    // This points to an object that holds an animation/virtual table at +0xD0
    int* internalObj = *(int**)((char*)thisPtr + 0x260);
    if (internalObj != nullptr) {
        // Convert the transform data into matrix form
        transformToMatrix(transformData, local_50);
        // Possibly invert or normalize the matrix
        Math::invertMatrix(local_50);
        // Extract quaternion from matrix
        Math::matrixToQuat(local_50, local_60);

        // Copy position/rotation from transformData (offsets 0x30, 0x34, 0x38)
        local_80 = *(undefined4*)((char*)transformData + 0x30);
        local_7c = *(undefined4*)((char*)transformData + 0x34);
        local_78 = *(undefined4*)((char*)transformData + 0x38);
        // Global time step or constant (e.g., gravity)
        local_74 = DAT_00e2b1a4;

        // Check the current state byte at offset 0xD8 of the internal object
        char stateByte = *(char*)((char*)internalObj + 0xD8);
        if (stateByte == 0x07) {
            // Airborne state – check collision flags
            // Bits 30 and 31 of the flags at +0x2C indicate ground contact?
            uint flags = *(uint*)((char*)internalObj + 0x2C);
            if ((flags & 0xC0000000) == 0xC0000000) {
                // Multiply flags by 4 to get a parameter for unpacking
                int unpackParam = flags * 4;
                if (unpackParam != 0) {
                    // Unpack collision data into local buffer
                    unpackCollisionData(local_b0, unpackParam);
                    // Apply collision response to the matrix
                    applyCollisionResult(local_50);
                }
            }
            // Finalize state after collision handling
            finalizeState(local_b0);
            return;
        } else if (stateByte == 0x06) {
            // Running/active state – maybe do time-based interpolation
            // Global time comparison (e.g., slow motion threshold)
            if (DAT_00e44598 < DAT_012067e8) {
                // Begin global scope for modifying some game state (e.g., physics)
                beginGlobalScope();
                // Call virtual functions at vtable+0x40 and vtable+0x44
                // The vtable is stored at offset +0xD0 of the internal object
                (**(code**)(*(int*)((char*)internalObj + 0xD0) + 0x40))(&DAT_01139820);
                beginGlobalScope();
                (**(code**)(*(int*)((char*)internalObj + 0xD0) + 0x44))(&DAT_01139820);

                // Compute interpolation factor (inverse of global time delta)
                float interpFactor = 1.0f / DAT_012067e8;
                // Convert matrix to another representation
                Math::invertMatrix(auStack_b8);
                // Perform interpolation of the position/rotation with time factor
                interpolateTransform(auStack_88, &local_78, interpFactor, internalObj);
            }
        }
    }
}