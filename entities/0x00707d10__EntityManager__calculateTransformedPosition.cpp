// FUNC_NAME: EntityManager::calculateTransformedPosition
// Address: 0x00707d10
// This function takes a 3-element float vector (position) and adds offsets from a game object plus a global constant.
// It reads from a structure returned by getGameObject() (FUN_00471610) at offsets 0x20, 0x28, 0x30, 0x38.
// The global _DAT_00d5780c is likely a time delta or constant offset (e.g., gravity or camera height).

#include <cstdint>

// Forward declaration
void* getGameObject(); // FUN_00471610 - returns pointer to some game object (e.g., player, camera, vehicle)

int __thiscall EntityManager::calculateTransformedPosition(float* outPos)
{
    // First call: read velocity/offset part from game object
    int objPtr1 = (int)getGameObject(); // iVar3
    uint64_t velOffsetLow = *(uint64_t*)(objPtr1 + 0x20); // two floats at +0x20 and +0x24
    float velOffsetUp = *(float*)(objPtr1 + 0x28); // third float at +0x28

    // Second call: read base position from same or different game object
    int objPtr2 = (int)getGameObject(); // iVar3 (same pointer likely)
    // Copy 8 bytes (two floats) from +0x30 to outPos[0] and outPos[1]
    *(uint64_t*)outPos = *(uint64_t*)(objPtr2 + 0x30);
    // Set outPos[2] from +0x38
    outPos[2] = *(float*)(objPtr2 + 0x38);

    // Apply additional offsets
    outPos[1] += _DAT_00d5780c; // global constant (e.g., timeStep or fixed offset)
    outPos[0] += (float)(velOffsetLow); // treat low 32 bits of velOffsetLow as float (x component)
    outPos[2] += velOffsetUp; // z component

    // Return a constructed value; likely success flag or handle
    return (int)(((uintptr_t)(objPtr2 + 0x30) >> 8) & 0xFFFFFF00) | 1;
}