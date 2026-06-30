// FUNC_NAME: JobReward::setRewardData
void __thiscall JobReward::setRewardData(void* this, uint32_t unused1, uint32_t money, uint32_t unused2, uint32_t respect, uint32_t heat)
{
    // Base class initialization (likely sets vtable or other base fields)
    baseInitialize(); // FUN_0059b5e0

    // Set type flag to 0 (e.g., reward type id)
    *(uint8_t*)((uint8_t*)this + 0x70) = 0;

    // Store reward components
    *(uint32_t*)((uint8_t*)this + 0x74) = money;   // +0x74: money reward
    *(uint32_t*)((uint8_t*)this + 0x78) = respect; // +0x78: respect reward
    *(uint32_t*)((uint8_t*)this + 0x7C) = heat;    // +0x7C: heat (notoriety) reward
}