// FUNC_NAME: TargetInfo::reset
// Function address: 0x00699180
// Initializes a TargetInfo struct to default state (no target, active flag set).
// Struct size: 0x38 (14 int32 fields)

struct TargetInfo {
    int field_00;      // +0x00
    int field_04;      // +0x04
    int field_08;      // +0x08
    int field_0C;      // +0x0C
    int field_10;      // +0x10
    int field_14;      // +0x14
    int entityId;      // +0x18  // Set to -1 (no entity)
    int field_1C;      // +0x1C
    int isValid;       // +0x20  // Set to 1 (valid/active)
    int field_24;      // +0x24
    int field_28;      // +0x28
    int field_2C;      // +0x2C
    int field_30;      // +0x30
    int field_34;      // +0x34
};

void __fastcall TargetInfo::reset(TargetInfo* thisPtr)
{
    thisPtr->field_00 = 0;
    thisPtr->field_04 = 0;
    thisPtr->field_08 = 0;
    thisPtr->field_0C = 0;
    thisPtr->entityId = -1;
    thisPtr->field_1C = 0;
    thisPtr->isValid = 1;
    thisPtr->field_24 = 0;
    thisPtr->field_28 = 0;
    thisPtr->field_2C = 0;
    thisPtr->field_30 = 0;
    thisPtr->field_34 = 0;
}