// FUNC_NAME: SimNpc::initCollisionShape
// Function address: 0x0066ef50
// Called from: likely SimNpc constructor or setup
// Purpose: Allocate and initialize a character collision shape (size 0x48), store pointer at this+0xa1c

void SimNpc::initCollisionShape() {
    // Attempt to allocate a 72-byte collision shape structure
    void* pShape = FUN_009c8e50(0x48); // Custom allocator, possibly g_pMemoryManager->allocate(0x48)
    if (pShape != nullptr) {
        // Zero out a local Vector3 (center position) – shape starts at origin
        Vector3 center = { 0.0f, 0.0f, 0.0f };
        // Call shape initializer (creates Havok capsule or sphere shape)
        // FUN_004b4d10 likely takes pointer to a struct containing center and size, returns a handle/id
        // Store result at this+0xa1c (field: m_pCollisionShape or m_collisionShapeId)
        *(int*)((uint8_t*)this + 0xa1c) = FUN_004b4d10(&center);
    } else {
        // Allocation failed, clear pointer
        *(int*)((uint8_t*)this + 0xa1c) = 0;
    }
}