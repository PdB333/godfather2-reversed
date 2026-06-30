// FUNC_NAME: Player::updateAttachedEffects
void __thiscall Player::updateAttachedEffects(void)
{
    // Enable the effect system for this player (0 = disabled, 1 = active)
    // FUN_00653230 might be setActive(bool) on a sub-object at a fixed offset
    FUN_00653230(this, 1); // likely this->effectSystem.setActive(true)

    // Check if an attached visual effect object exists at +0x1b0
    if (*(int *)(this + 0x1b0) != 0) {
        // Update the effect's position/rotation from player's transform data
        // +0x90 and +0x98 are probably components of a vector (e.g., forward or right)
        // FUN_0065a6c0 may be something like setEffectTransform(void* effect, float param, float param, bool enabled)
        FUN_0065a6c0(*(int *)(this + 0x1b0),      // effect pointer
                     *(undefined4 *)(this + 0x98), // some float (e.g., X)
                     *(undefined4 *)(this + 0x90), // some float (e.g., Y)
                     1);                          // enable/trigger flag

        // Trigger additional effect behavior with parameter 3 (e.g., play, loop, release)
        // FUN_0064c980 might be playEffect(int type, void* effect)
        FUN_0064c980(3, *(undefined4 *)(this + 0x1b0));
    }

    // Update global engine subsystems (audio, physics, etc.)
    FUN_00653df0(); // likely updateAudioSystem()
    FUN_0064b440(); // likely updatePhysicsSystem()
}