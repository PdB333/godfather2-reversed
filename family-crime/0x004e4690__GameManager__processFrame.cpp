// FUNC_NAME: GameManager::processFrame
void __fastcall GameManager::processFrame(void* unusedThis, uint flags)
{
    // Check LSB of flags: 1 = branch A, 0 = branch B
    if (flags & 1)
    {
        // Branch A – likely pause/stop/disable
        FUN_0052cbd0(); // 0x0052cbd0 – unknown function, possibly pauseGame()
        return;
    }
    // Branch B – default active tick
    FUN_0052b770(); // 0x0052b770 – unknown function, possibly tickGame()
    // Accumulate game time: DAT_01125280 (g_gameTime) += DAT_00e2b1a4 (g_frameDelta)
    g_gameTime += g_frameDelta;
}