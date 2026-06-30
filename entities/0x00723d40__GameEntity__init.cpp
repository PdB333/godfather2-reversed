// FUNC_NAME: GameEntity::init
void __fastcall GameEntity::init(GameEntity* this) {
    // Clear initial fields
    this->field_4 = 0;
    this->field_8 = 0;
    this->field_C = 0;
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    this->field_1C = 0;

    // Set magic debug signatures (often used to detect uninitialized or overwritten memory)
    this->field_20 = 0xBADBADBA;  // "bad bad ba"
    this->field_24 = 0xBEEFBEEF;  // "beef beef"
    this->field_28 = 0xEAC15A55;  // "EACS??" (EA C? Sa?)
    this->field_2C = 0x91100911;  // "911 0911"?

    // Clear some fields again (possibly resetting after debug)
    this->field_30 = 0;
    this->field_34 = 0;
    this->field_38 = 0;
    this->field_2C = 0;  // Clear the same as before, might be intentional
    this->field_28 = 0;
    this->field_24 = 0;
    this->field_20 = 0;

    // Set virtual function table pointers
    // +0: primary vtable
    this->vtable = (void**)&PTR_FUN_00d620b4;
    // +0x3C (offset 15): secondary vtable or interface pointer
    this->secondaryVtable = (void**)&PTR_LAB_00d620b0;

    // Initialize field_40 to 0
    this->field_40 = 0;

    // Load global constants (likely default values for various properties)
    const int kSomeConstant = DAT_00d5ef84;   // from global
    const int kAnotherConstant = DAT_00d5eee4;
    const int kThirdConstant = _DAT_00d5780c;

    // Initialize multiple members to the same constant (probably an array or list)
    this->field_44 = kSomeConstant;
    this->field_48 = kSomeConstant;
    this->field_4C = kSomeConstant;
    this->field_50 = kSomeConstant;
    this->field_54 = kSomeConstant;
    this->field_58 = kSomeConstant;
    this->field_5C = kSomeConstant;
    this->field_60 = kSomeConstant;
    this->field_74 = kSomeConstant;
    this->field_78 = kSomeConstant;
    this->field_A0 = kSomeConstant;
    this->field_A4 = kSomeConstant;
    this->field_A8 = kSomeConstant;
    this->field_AC = kSomeConstant;
    this->field_B0 = kSomeConstant;
    this->field_B4 = kSomeConstant;
    this->field_B8 = kSomeConstant;
    this->field_BC = kSomeConstant;
    this->field_C0 = kSomeConstant;
    this->field_C4 = kSomeConstant;
    this->field_C8 = kSomeConstant;

    // Other constants
    this->field_CC = DAT_00d5779c;  // another global
    this->field_D0 = DAT_00d5ddec;
    this->field_D4 = DAT_00e445ac;
    this->field_E0 = DAT_00e445ac;
    this->field_E4 = DAT_00e445ac;
    this->field_E8 = DAT_00e445ac;
    this->field_EC = DAT_00e445ac;
    this->field_F0 = DAT_00e445ac;
    this->field_F4 = DAT_00e445ac;
    this->field_F8 = DAT_00e445ac;
    this->field_FC = DAT_00e445ac;

    // Initialize another group to kThirdConstant (0x18 to 0x27 and more)
    this->field_60 = kThirdConstant;
    this->field_64 = kThirdConstant;
    this->field_68 = kThirdConstant;
    this->field_6C = kThirdConstant;
    this->field_70 = kThirdConstant;
    this->field_7C = kThirdConstant;
    this->field_80 = kThirdConstant;
    this->field_84 = kThirdConstant;
    this->field_88 = kThirdConstant;
    this->field_8C = kThirdConstant;
    this->field_90 = kThirdConstant;
    this->field_94 = kThirdConstant;
    this->field_98 = kThirdConstant;
    this->field_9C = kThirdConstant;

    // More fields with kAnotherConstant and kThirdConstant
    this->field_D8 = kAnotherConstant;
    this->field_DC = kThirdConstant;
    this->field_100 = kThirdConstant;
    this->field_104 = 0;
    this->field_108 = 0;
    this->field_10C = kAnotherConstant;
    this->field_110 = kThirdConstant;
    this->field_114 = kThirdConstant;
    this->field_118 = 0;
    this->field_11C = 0;
    this->field_120 = 0;
    this->field_124 = 0;
    this->field_128 = 0;
    this->field_12C = 0;
}