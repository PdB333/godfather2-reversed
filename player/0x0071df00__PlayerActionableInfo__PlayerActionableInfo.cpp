// FUNC_NAME: PlayerActionableInfo::PlayerActionableInfo
// Address: 0x0071df00
// Role: Constructor for PlayerActionableInfo. Initializes vtable, sets up array of 8 actionable target info structs.
// Each struct consists of 3 float values: a sentinel (from global float DAT_00e44758), 0, 0.
// Two initial ints are set to -1 (likely current/next target indices).

void __fastcall PlayerActionableInfo::PlayerActionableInfo(PlayerActionableInfo* this)
{
    // Vtable at +0x00
    this->vtable = &PlayerActionableInfo_VTable;  // PTR_FUN_00d61e30

    // Two initial ints at +0x04 and +0x08 (maybe currentTargetIndex and previous?)
    this->field_04 = 0;
    this->field_08 = -1;  // 0xffffffff

    // Next two ints at +0x0C and +0x10 (maybe nextTargetIndex and another?)
    this->field_0C = 0;
    this->field_10 = -1;  // 0xffffffff

    // Then 8 copies of a struct: each 3 ints (or floats) at +0x14, +0x18, +0x1C, etc.
    // Pattern: sentinel, 0, 0 repeated 8 times.
    // Global sentinel (likely a float constant like FLT_MAX or -1.0)
    const float sentinel = *(float*)&DAT_00e44758;  // +0x00e44758

    // Helper to set one target info struct
    #define SET_TARGET_INFO(offset) \
        *(float*)(this + offset) = sentinel; \
        *(int*)(this + offset + 4) = 0; \
        *(int*)(this + offset + 8) = 0;

    this->targetInfo[0].field0 = sentinel; this->targetInfo[0].field4 = 0; this->targetInfo[0].field8 = 0;
    this->targetInfo[1].field0 = sentinel; this->targetInfo[1].field4 = 0; this->targetInfo[1].field8 = 0;
    this->targetInfo[2].field0 = sentinel; this->targetInfo[2].field4 = 0; this->targetInfo[2].field8 = 0;
    this->targetInfo[3].field0 = sentinel; this->targetInfo[3].field4 = 0; this->targetInfo[3].field8 = 0;
    this->targetInfo[4].field0 = sentinel; this->targetInfo[4].field4 = 0; this->targetInfo[4].field8 = 0;
    this->targetInfo[5].field0 = sentinel; this->targetInfo[5].field4 = 0; this->targetInfo[5].field8 = 0;
    this->targetInfo[6].field0 = sentinel; this->targetInfo[6].field4 = 0; this->targetInfo[6].field8 = 0;
    this->targetInfo[7].field0 = sentinel; this->targetInfo[7].field4 = 0; this->targetInfo[7].field8 = 0;

    // Remaining zeros up to offset 0x88 (34 * 4 = 136 bytes = 0x88)
    // Already zero-initialized by default, but we set explicitly:
    this->unused0 = 0;
    this->unused1 = 0;
    this->unused2 = 0;
    this->unused3 = 0;
    this->unused4 = 0;
}