// FUNC_NAME: Entity::updateWorldTransformFromSource
void __thiscall Entity::updateWorldTransformFromSource(void *this, undefined4 param2)
{
    // +0x24: int m_transformType (0 = physics, 1 = animation, else = fallback)
    // +0x30: Transform* m_pTransformSource (pointer to current transform provider)
    // +0x80-0xac: float m_worldTransform[3][4] (3 rows of 4 floats, row-major affine matrix)

    int transformType = *(int *)((uint)this + 0x24);
    int transformProvider; // return value from helper functions

    // Local buffers (stack allocated) for receiving transform data from source
    // Sizes differ based on type (physics: 140 bytes, animation: 128 bytes, fallback: 128 bytes)
    if (transformType == 0) {
        // Physics transform (Havok rigid body or similar)
        uint8_t physicsBuffer[140]; // local_90
        transformProvider = getPhysicsWorldTransform(physicsBuffer, param2); // FUN_0082f450
    } else if (transformType == 1) {
        // Animation transform (skeleton root or bone)
        uint8_t animBuffer0[128]; // local_190
        transformProvider = getAnimationWorldTransform(animBuffer0, param2, 0); // FUN_0082f160
    } else {
        // Fallback transform (e.g., static object)
        uint8_t animBuffer1[128]; // local_110
        transformProvider = getAnimationWorldTransform(animBuffer1, param2, 0); // FUN_0082f160
    }

    // Only update if the transform source provider changed
    if ((void *)((uint)this + 0x30) != (void *)transformProvider) {
        // Release/assign reference to new transform provider (e.g., addref/release)
        setTransformSource(transformProvider); // FUN_00820830

        // Copy 12 floats (3x4 matrix) from provider to this object's world transform cache
        // Source offsets: 0x50-0x5c -> row0
        *(int *)((uint)this + 0x80) = *(int *)(transformProvider + 0x50);
        *(int *)((uint)this + 0x84) = *(int *)(transformProvider + 0x54);
        *(int *)((uint)this + 0x88) = *(int *)(transformProvider + 0x58);
        *(int *)((uint)this + 0x8c) = *(int *)(transformProvider + 0x5c);
        // Source offsets: 0x60-0x6c -> row1
        *(int *)((uint)this + 0x90) = *(int *)(transformProvider + 0x60);
        *(int *)((uint)this + 0x94) = *(int *)(transformProvider + 0x64);
        *(int *)((uint)this + 0x98) = *(int *)(transformProvider + 0x68);
        *(int *)((uint)this + 0x9c) = *(int *)(transformProvider + 0x6c);
        // Source offsets: 0x70-0x7c -> row2
        *(int *)((uint)this + 0xa0) = *(int *)(transformProvider + 0x70);
        *(int *)((uint)this + 0xa4) = *(int *)(transformProvider + 0x74);
        *(int *)((uint)this + 0xa8) = *(int *)(transformProvider + 0x78);
        *(int *)((uint)this + 0xac) = *(int *)(transformProvider + 0x7c);
    }
}