// FUNC_NAME: PlayerEffectManager::spawnRelativeEffect
// Function address: 0x00715290
// Effect spawn helper that adjusts world position by subtracting the local player/camera transform offset
void __thiscall PlayerEffectManager::spawnRelativeEffect(
    void* this,
    uint32_t unkParam2,
    float* offsetVector,
    uint32_t unkParam4
)
{
    float localPos[3]; // local sound/effect position (x, y, z)

    // Get current listener/camera position (likely world-space)
    getListenerPosition(localPos);

    if (offsetVector != nullptr)
    {
        // Get player transform (camera/character matrix)
        void* playerTransform = getPlayerTransform(); // e.g., pointer to 4x4 matrix at iVar1
        // Adjust the effect position: offsetVector + (listenerPos - playerPosition)
        localPos[0] = offsetVector[0] + (localPos[0] - *(float*)((uintptr_t)playerTransform + 0x30));
        localPos[1] = offsetVector[1] + (localPos[1] - *(float*)((uintptr_t)playerTransform + 0x34));
        localPos[2] = offsetVector[2] + (localPos[2] - *(float*)((uintptr_t)playerTransform + 0x38));
        // Offsets 0x30, 0x34, 0x38 are position x, y, z in the transform matrix.
    }

    // Spawn the effect/sound at the computed position
    // 0x40102 likely an effect type/hash, 7 probably a priority or channel
    spawnEffect(this, localPos, 0x40102, unkParam2, unkParam4, 7);
}