// FUNC_NAME: GhostObject::writeStateChangeFlag
// Address: 0x004aab40
// Role: Writes a boolean flag (whether sum of three floats <= threshold) onto a global stream/stack for packet serialization.
// The 'this' pointer is assumed to be in ESI (__thiscall).
// Structure offsets:
//   this+0x18: pointer to physics component (e.g., RigidBody*)
//   RigidBody+0x40, +0x44, +0x48: three float values (velocity X, Y, Z?).
// Global DAT_01206880+0x14: stream pointer (growable buffer) used for building packets.
// Global DAT_00e2e210: threshold constant.

void GhostObject::writeStateChangeFlag(void)
{
    int iPhysicsPtr;
    int *pPhysics;
    bool bSumBelowThreshold;
    uint *puStreamPtr;
    int *piAlignedPtr;
    int unaff_ESI; // 'this' pointer
    int unaff_FS_OFFSET; // TLS offset (unused in this function but referenced)

    // Get the physics component pointer from this->physicsComponent (offset 0x18)
    // Also fetch a TLS value (likely thread-local data, but not used further)
    iPhysicsPtr = *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8);
    pPhysics = *(int *)(unaff_ESI + 0x18);

    // Sum three floats from physics component at offsets 0x40, 0x44, 0x48
    // Compare against a global threshold
    bSumBelowThreshold = *(float *)(pPhysics + 0x48 + iPhysicsPtr) + 
                         *(float *)(pPhysics + 0x44 + iPhysicsPtr) +
                         *(float *)(pPhysics + 0x40 + iPhysicsPtr) <= DAT_00e2e210;

    // Access global stream buffer: point to the current write location
    puStreamPtr = (uint *)(DAT_01206880 + 0x14);
    // Write a vtable pointer (type identifier for the serialized object)
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_011244b0;
    // Advance stream pointer by 4 bytes
    *puStreamPtr = *puStreamPtr + 4;
    // Align to 4-byte boundary
    piAlignedPtr = (int *)(*puStreamPtr + 3 & 0xfffffffc);
    *puStreamPtr = (uint)piAlignedPtr;
    // Write 'this' pointer (the object being serialized)
    *piAlignedPtr = unaff_ESI;
    // Advance by 4 more bytes
    *puStreamPtr = *puStreamPtr + 4;
    // Write the boolean flag (0 or 1)
    *(bool *)*puStreamPtr = bSumBelowThreshold;
    // Final alignment for next write
    *puStreamPtr = *puStreamPtr + 4 & 0xfffffffc;
    return;
}