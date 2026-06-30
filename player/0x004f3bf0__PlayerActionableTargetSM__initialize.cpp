// FUNC_NAME: PlayerActionableTargetSM::initialize
// Address: 0x004f3bf0
// Role: Initializes the target array slots to an invalid sentinel value and zeros the other fields.

void PlayerActionableTargetSM::initialize(void)
{
    // Global constant representing invalid/uninitialized state (likely -1 or 0xFFFFFFFF)
    unsigned int invalidSentinel = DAT_00e2b1a4;

    // Array of 3 target slots, each 20 bytes (5 dwords) with first field being the type/sentinel
    this->targetSlot1.type = invalidSentinel;    // offset +0x00
    this->targetSlot1.field_04 = 0;              // offset +0x04
    this->targetSlot1.field_08 = 0;              // offset +0x08
    this->targetSlot1.field_0C = 0;              // offset +0x0C
    this->targetSlot1.field_10 = 0;              // offset +0x10

    this->targetSlot2.type = invalidSentinel;    // offset +0x14
    this->targetSlot2.field_18 = 0;              // offset +0x18
    this->targetSlot2.field_1C = 0;              // offset +0x1C
    this->targetSlot2.field_20 = 0;              // offset +0x20
    this->targetSlot2.field_24 = 0;              // offset +0x24

    this->targetSlot3.type = invalidSentinel;    // offset +0x28
    this->targetSlot3.field_2C = 0;              // offset +0x2C
    this->targetSlot3.field_30 = 0;              // offset +0x30
    this->targetSlot3.field_34 = 0;              // offset +0x34
    this->targetSlot3.field_38 = 0;              // offset +0x38

    return;
}