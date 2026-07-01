// FUNC_NAME: SomeClass::updateFlagBasedOnType
void SomeClass::updateFlagBasedOnType()
{
    // Call first virtual function (likely RTTI getClassID)
    int classID = (*(code **)*this)(); // VTable call to first function
    const int TARGET_CLASS_ID = 0x8ADE428D; // -0x7521bd73

    if (classID == TARGET_CLASS_ID)
    {
        // Check some condition via external function
        char condition = FUN_008a4380(); // Possibly checks game state or object property
        if (condition != 0)
        {
            // Set flag at offset 0x94 (bit 2, 4 = 0x04)
            this[0x25] |= 4; // +0x94 (0x25 * 4 = 0x94)
        }
    }
}