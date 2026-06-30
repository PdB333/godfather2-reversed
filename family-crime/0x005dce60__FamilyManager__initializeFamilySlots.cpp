// FUNC_NAME: FamilyManager::initializeFamilySlots

void FamilyManager::initializeFamilySlots()
{
    // Call base initialization
    FUN_005dd030(); // Likely FamilyManager::initBase or similar

    // Global constants - likely default state values
    uint32 defaultVal1 = DAT_00e2b1a4; // e.g., 0x00000000 or some sentinel
    uint32 defaultVal2 = DAT_00e2b118; // e.g., 0xFFFFFFFF or some ID

    // Set current family index to invalid
    *(int32*)(this + 0x214) = -1; // currentFamilyIndex

    // Initialize array of 5 family slots (families: Corleone, Tattaglia, Cuneo, Barzini, Stracci)
    FamilySlot* slot = (FamilySlot*)(this + 0x18);
    for (int i = 0; i < NUM_FAMILIES; i++)
    {
        // Reserve space at start of each slot (possibly base class data)
        slot->field_00 = defaultVal1;   // +0x00
        slot->field_04 = defaultVal1;   // +0x04
        slot->field_28 = defaultVal1;   // +0x28
        slot->field_2C = defaultVal1;   // +0x2C
        slot->maxHealth = 96000;        // +0x44
        slot->maxSomething = 96000;     // +0x4C
        slot->byte_21 = 0;              // +0x21
        slot->byte_22 = 0;              // +0x22
        slot->field_08 = 0;             // +0x08
        slot->field_24 = 0;             // +0x24
        slot->field_30 = 0;             // +0x30
        slot->field_34 = 0;             // +0x34
        slot->field_48 = 0;             // +0x48
        slot->byte_23 = 0;              // +0x23
        slot->field_0C = 1;             // +0x0C -> later overwritten
        slot->magic1 = 0xBADBADBA;      // +0x10
        slot->magic2 = 0xBEEFBEEF;      // +0x14
        slot->magic3 = 0xEAC15A55;      // +0x18
        slot->magic4 = 0x91100911;      // +0x1C
        slot->familyID = defaultVal2;   // +0x38
        slot->field_3C = defaultVal1;   // +0x3C
        slot->field_50 = 0;             // +0x50
        slot->field_54 = 0;             // +0x54
        slot->field_58 = 0;             // +0x58
        slot->field_5C = 0;             // +0x5C
        slot->field_60 = 0;             // +0x60
        slot->field_64 = 0;             // +0x64
        // Overwrite the earlier field_0C with sentinel
        slot->field_0C = 0xFFFFFFFF;    // +0x0C (marks slot as initialized/invalid)
        // Advance pointer to next slot (each slot is 0x68 bytes)
        slot = (FamilySlot*)((uint8*)slot + 0x68);
    }

    // Initialize additional global family data after the slot array
    *(uint32*)(this + 0x27C) = defaultVal2; // +0x27C
    *(uint32*)(this + 0x280) = defaultVal1; // +0x280
    *(uint32*)(this + 0x284) = defaultVal1; // +0x284
    *(uint32*)(this + 0x288) = defaultVal1; // +0x288
    *(uint32*)(this + 0x28C) = defaultVal1; // +0x28C
    *(uint32*)(this + 0x290) = defaultVal1; // +0x290
    *(uint32*)(this + 0x29C) = defaultVal1; // +0x29C
    *(uint8*)(this + 0x298) = 0;            // +0x298
    *(uint8*)(this + 0x299) = 0;            // +0x299
    *(uint32*)(this + 0x2B8) = 0;           // +0x2B8
    *(int32*)(this + 0x2BC) = -1;           // +0x2BC (700 decimal)
    return;
}