// FUNC_NAME: Player::updateCooldownTimer
bool __fastcall Player::updateCooldownTimer(Player* this) {
    // Decrement cooldown counter at +0x138, clamp to 0
    int* cooldownPtr = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x138);
    *cooldownPtr = *cooldownPtr - 1;
    if (*cooldownPtr < 0) {
        *cooldownPtr = 0;
    }

    // Check global flag: bit 10 of g_gameState+0x60 (likely pause/menu flag)
    if ((*(reinterpret_cast<uint32_t*>(DAT_0112af70 + 0x60) >> 10) & 1) == 0) {
        int currentTime = FUN_00849ff0(); // getTickCount() or similar
        *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x13c) = currentTime; // m_lastUpdateTime
        *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x140) = currentTime; // m_currentTime

        // If time is zero and a global manager is active, override m_currentTime
        if ((currentTime == 0) && (*(reinterpret_cast<int*>(DAT_0112a66c + 0x14) != 0))) {
            *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x140) =
                *reinterpret_cast<int*>(**(reinterpret_cast<int**>(DAT_0112a66c + 0x10)) + 0x50);
        }
    }

    // Reset some flag at +0x14c
    *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x14c) = 0;
    return true;
}