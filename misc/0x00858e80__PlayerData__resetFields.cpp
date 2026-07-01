// FUNC_NAME: PlayerData::resetFields
void __fastcall PlayerData::resetFields(void)
{
    // Zero out 17 consecutive integer fields starting at offset 0x124
    // This block covers offsets 0x124 through 0x164 (size 0x44 bytes, 17 ints)
    *(int *)(this + 0x128) = 0;
    *(int *)(this + 0x148) = 0;
    *(int *)(this + 0x12C) = 0;
    *(int *)(this + 0x14C) = 0;
    *(int *)(this + 0x130) = 0;
    *(int *)(this + 0x150) = 0;
    *(int *)(this + 0x134) = 0;
    *(int *)(this + 0x154) = 0;
    *(int *)(this + 0x138) = 0;
    *(int *)(this + 0x158) = 0;
    *(int *)(this + 0x13C) = 0;
    *(int *)(this + 0x15C) = 0;
    *(int *)(this + 0x140) = 0;
    *(int *)(this + 0x160) = 0;
    *(int *)(this + 0x144) = 0;
    *(int *)(this + 0x164) = 0;
    *(int *)(this + 0x124) = 0;
    return;
}