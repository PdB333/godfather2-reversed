// FUNC_NAME: Entity::spawnEffectFromHandle
// Decompiled from 0x0054e9c0
// Extracts a position from the entity's transform and a resource handle from another component,
// then calls a spawn function to create an effect or projectile.

#include <cstdint>

// Forward declaration for the called spawn function
int __fastcall spawnObject(Vector3* position, int param3, int param4, int handleType, int zero, int zero2, int zero3, int zero4, int zero5);

struct Vector3 {
    float x, y, z;
};

// This function takes an entity pointer (param2) and two additional parameters (param3, param4).
// param1 (ecx) appears unused – possibly a leftover or a dummy from calling convention.
void __fastcall Entity::spawnEffect(int unused_ecx, int entity, int param3, int param4)
{
    // Navigate deep pointer chain to get the entity's position
    // entity->transformComponent (? offset 0x14)
    int transformComponent = *(int*)(entity + 0x14);
    // transformComponent->posDataPtr (offset 0x30)
    int posData = *(int*)(transformComponent + 0x30);
    // posData->positionData (offset 0x18)
    int positionData = *(int*)(posData + 0x18);
    // Extract position (Vector3 at offset 0x30 within positionData)
    Vector3 position;
    position.x = *(float*)(positionData + 0x30);
    position.y = *(float*)(positionData + 0x34);
    position.z = *(float*)(positionData + 0x38);

    // Read a handle from another component (e.g., inventory/weapon at entity+0x18)
    int handleComponent = *(int*)(entity + 0x18);
    uint32_t handle = *(uint32_t*)(handleComponent + 0x2c); // handle value

    // Decode the handle type (EA-style tagged pointer):
    // Top 2 bits indicate the type of the handle.
    uint32_t handleType;
    uint32_t tag = handle & 0xC0000000;

    if (tag == 0) {
        // "Inline" small handle: produce a bitmask from bits 5-9
        handleType = 1 << ((handle >> 5) & 0x1F);
    } else if (tag == 0x40000000) {
        // Type 1: pointer into a table at address 8
        handleType = *(int*)(handle * 4 + 8);
    } else if (tag == 0xC0000000) {
        // Type 2: pointer into a table at address 0x54
        handleType = *(int*)(handle * 4 + 0x54);
    } else {
        // Invalid tag
        handleType = -0x80000000; // 0x80000000 as int32
    }

    // Call the spawn function with the position, original params, decoded handle, and six zero placeholders.
    spawnObject(&position, param3, param4, handleType, 0, 0, 0, 0, 0);
}