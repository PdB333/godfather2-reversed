// FUNC_NAME: PlayerActionableInfo::reset
void PlayerActionableInfo::reset(PlayerActionableInfo* this) // __thiscall
{
    // Initialize all fields to default values
    this->type = 4;                    // +0x00: action type identifier
    this->targetId = -1;               // +0x04: invalid target entity ID
    this->flags = 0;                   // +0x08: bitfield flags
    this->field_C = 0;                 // +0x0C: reserved
    this->field_10 = 0;                // +0x10: reserved
    this->field_14 = -1;               // +0x14: invalid secondary ID
    this->field_18 = 0;                // +0x18: reserved
    this->field_1C = -1;               // +0x1C: invalid tertiary ID
    this->field_20 = 0;                // +0x20: reserved
    this->field_24 = 0;                // +0x24: reserved
    this->field_28 = 0;                // +0x28: reserved
    this->maxTargets = 0x20;           // +0x2C: maximum number of targets (32)
    this->field_30 = 0;                // +0x30: reserved
    this->field_34 = 0;                // +0x34: reserved
    this->field_38 = 0;                // +0x38: reserved
    this->field_3C = 0;                // +0x3C: reserved
    this->field_40 = 0;                // +0x40: reserved
    this->field_44 = 0;                // +0x44: reserved
    this->field_48 = 0;                // +0x48: reserved
    this->field_4C = 0;                // +0x4C: reserved
}