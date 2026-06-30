// FUNC_NAME: Player::enableAimAssist
void __fastcall Player::enableAimAssist(Player* this) {
    // Acquire some lock/sync (e.g., thread safety)
    syncLock();

    // Set the aim assist enable flag at offset +0x1f58
    *(uint32_t*)((uint8_t*)this + 0x1f58) |= 0x2000;

    // Notify the global aim assist system (DAT_00d62a14 is likely a static singleton)
    notifyAimAssistSystem(&g_AimAssistManager);
}