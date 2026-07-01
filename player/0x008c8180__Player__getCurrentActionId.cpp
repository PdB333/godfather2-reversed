// FUNC_NAME: Player::getCurrentActionId
uint32 __thiscall Player::getCurrentActionId(Player* this) {
    // +0x10: pointer to current action item (e.g., weapon, tool)
    if (*(int*)((uint8*)this + 0x10) != 0) {
        // +0x58: action ID within the item
        return *(uint32*)(*(int*)((uint8*)this + 0x10) + 0x58);
    }
    // Global difficulty/reputation check (FUN_00791750)
    int iVar1 = getStoryProgress(); // renamed from FUN_00791750
    if (5 < iVar1) {
        // +0x0c: pointer to an action manager or inventory
        // +0x22c: fallback action ID for high progress
        return *(uint32*)(*(int*)((uint8*)this + 0x0c) + 0x22c);
    }
    return 0;
}