// FUNC_NAME: EntityManager::CollectActiveTransforms
// Function address: 0x008fcc40
// Role: Iterates over all entities managed by EntityManager, and for each active entity (flag at +0xAD),
// copies its 4-dword transform (at +0x20) into the provided output buffer.

// Note: The transforms are stored as consecutive 4-float blocks (x,y,z,w) in the buffer.
// Global functions GetEntityCount() and GetEntityByIndex() are assumed to exist.
// The entity structure offsets are documented in the code.

void CollectActiveTransforms(void* outBuffer)
{
    uint entityCount = GetEntityCount();
    if (entityCount != 0) {
        float* dest = (float*)outBuffer;
        for (uint i = 0; i < entityCount; i++) {
            // Get pointer to the entity at index i
            Entity* entity = (Entity*)GetEntityByIndex(i);
            // Check if entity is active (byte at +0xAD)
            if (*(char*)((uintptr_t)entity + 0xAD) != 0) {
                // Copy transform data from entity offsets 0x20, 0x24, 0x28, 0x2C
                // These are typically a quaternion (x,y,z,w) or position-like data.
                dest[0] = *(float*)((uintptr_t)entity + 0x20);
                dest[1] = *(float*)((uintptr_t)entity + 0x24);
                dest[2] = *(float*)((uintptr_t)entity + 0x28);
                dest[3] = *(float*)((uintptr_t)entity + 0x2C);
                dest += 4; // Advance by 4 floats (16 bytes) for next active entity
            }
        }
    }
}