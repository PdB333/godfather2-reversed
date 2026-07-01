// FUNC_NAME: PlayerReputationTracker::updateScoreMultiplier

void __thiscall PlayerReputationTracker::updateScoreMultiplier(int thisPtr)
{
    // +0x84: scoreMultiplierActive flag (int)
    *(int *)(thisPtr + 0x84) = 1;

    // Log the multiplier update event
    FUN_005a04a0("UpdateScoreMultiplier", 0, &DAT_00d8b7d4, 0);

    // Global singleton pointer to game manager or reputation manager
    int *globalSingleton = (int *)DAT_0112a838;

    // Call reset/update multiplier function (maybe with multiplier type 0)
    FUN_009848c0(0);

    // +0xCC: byte flag in global singleton (e.g., multiplierActive)
    *(char *)((char *)globalSingleton + 0xCC) = 1;
}