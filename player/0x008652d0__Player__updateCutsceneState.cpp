// FUNC_NAME: Player::updateCutsceneState
void __fastcall Player::updateCutsceneState(int thisPtr)
{
    char isCutsceneActive;
    
    isCutsceneActive = FUN_008651a0(); // likely Player::isCutscenePlaying()
    if (isCutsceneActive == '\0') {
        FUN_005fe6f0(); // likely some cleanup or state reset function
        // Clear bits 24-27 (0x0f000000) in flags at +0xf28
        *(uint *)(thisPtr + 0xf28) = *(uint *)(thisPtr + 0xf28) & 0xf1ffffff;
    }
    return;
}