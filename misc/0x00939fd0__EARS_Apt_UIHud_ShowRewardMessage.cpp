// Xbox PDB: EARS_Apt_UIHud_ShowRewardMessage
// FUNC_NAME: RewardManager::showRewardMessage
// Function address: 0x00939fd0
// Sets a flag after triggering the "ShowRewardMessage" callback.

void __thiscall RewardManager::showRewardMessage(uint32_t rewardId)
{
    // Fire the named event with given reward ID.
    // FUN_005a04a0 is likely EventManager::fireEvent(const char*, int, void*, int, uint32_t)
    EventManager::fireEvent("ShowRewardMessage", 0, (void*)0x00d8a64c, 1, rewardId);

    // Set bit 22 (0x400000) on the flag at offset 0x5c to indicate reward message was shown.
    *(uint32_t*)((uint8_t*)this + 0x5c) |= 0x400000;
}