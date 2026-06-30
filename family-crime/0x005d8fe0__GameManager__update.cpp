// FUNC_NAME: GameManager::update
void __fastcall GameManager::update(int *this)
{
    FUN_005d8d50(); // updateSoundSystem
    (**(code **)(*this + 0x54))(); // updateAudio
    (**(code **)(*this + 0x44))(); // updatePhysics
    int updateResult = (**(code **)(*this + 0x40))(); // updateGameplay
    FUN_005d87b0(&g_soundManager, updateResult); // updateSoundManager
    /* WARNING: Could not recover jumptable at 0x005d901e. Too many branches */
    /* WARNING: Treating indirect jump as call */
    (**(code **)(this[0x48] + 4))(); // dispatchPendingEvents
    return;
}