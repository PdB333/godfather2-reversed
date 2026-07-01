// FUNC_NAME: Player::checkRespawnTimer
void __fastcall Player::checkRespawnTimer(int this) {
    GameManager* mgr = getGameManager(); // FUN_007ab710 - singleton getter
    if (mgr != nullptr) {
        // Notify manager of player state (arg1 = true, arg2 = this->field_0x58)
        mgr->vtableMethod0x288(true, *(int*)(this + 0x58));
        
        float timer = mgr->vtableMethod0xc0(); // Get some timer value
        if (timer <= 0.0f) {
            // Clear byte flag at mgr+0x782
            *(byte*)(mgr + 0x782) = 0;
            // Set bit 0x40 in dword at mgr+0x1b94 (piVar2[0x6e5])
            *(int*)(mgr + 0x1b94) |= 0x40;
            
            int result = 0; // uStack_10
            // Trigger event with hash 0x369ac561, passing result pointer
            bool eventTriggered = mgr->vtableMethod0x10(0x369ac561, &result);
            if (eventTriggered && this != nullptr) {
                // Set bit 0x80 in this->field_0x2188
                *(uint*)(this + 0x2188) |= 0x80;
            }
        }
    }
}