// FUNC_NAME: ActionBase::setGoalParameters
void __thiscall ActionBase::setGoalParameters(uint param_2, uint param_3, uint param_4)
{
    // Offset +0x50: first target (e.g., entity handle or position component)
    *(uint *)(this + 0x50) = param_2;
    // Offset +0x70: third target (packed as fourth param in call, stored here)
    *(uint *)(this + 0x70) = param_4;
    // Offset +0x60: second target
    *(uint *)(this + 0x60) = param_3;
    // Offset +0x54: flag/byte associated with first target
    *(byte *)(this + 0x54) = 0;
    // Offset +0x64 (100 decimal): flag/byte associated with second target
    *(byte *)(this + 0x64) = 0;
    // Offset +0x74: flag/byte associated with third target
    *(byte *)(this + 0x74) = 0;
    // Offset +0x4c: clear bit 1 (0x2) – marks goal as invalid or resets state
    *(uint *)(this + 0x4c) &= 0xfffffffdU;
}