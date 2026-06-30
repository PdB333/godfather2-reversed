// FUNC_NAME: GodfatherGameManager::GodfatherGameManager

void * __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager *this)
{
    // Call base constructor (likely EARSObject or similar)
    baseConstructor(this); // FUN_00544320

    // Set primary vtable pointer (offset 0x00)
    *(int **)this = (int *)&PTR_FUN_00e3a080;

    // Set secondary vtable pointers for multiple inheritance
    this->vtable2 = (int *)&PTR_LAB_00e3a2e0;   // +0x0F (0x3C)
    this->vtable3 = (int *)&PTR_LAB_00e3a2f0;   // +0x12 (0x48)
    this->vtable4 = (int *)&PTR_LAB_00e3a2f4;   // +0x14 (0x50)
    this->vtable5 = (int *)&PTR_LAB_00e3a2f8;   // +0x15 (0x54)
    this->vtable6 = (int *)&PTR_LAB_00e3a358;   // +0x16 (0x58)
    this->vtable7 = (int *)&PTR_LAB_00e3a3bc;   // +0xB8 (0x2E0)
    this->vtable8 = (int *)&PTR_LAB_00e3a3d0;   // +0xB9 (0x2E4)

    // Initialize several fields to zero
    this->field_0x3a4 = 0;  // +0xE9
    this->field_0x3a8 = 0;  // +0xEA
    this->field_0x3ac = 0;  // +0xEB
    this->field_0x3b0 = 0;  // +0xEC
    this->field_0x480 = 0;  // +0x120
    this->field_0x484 = 0;  // +0x121

    // Perform 4 calls to some initialization routine (likely random seed or memory fill)
    for (int i = 0; i < 4; i++)
    {
        FUN_0049ccc0();
    }

    // Zero a large contiguous block of fields (offset 0x1C4 through 0x1E3)
    this->field_0x710 = 0;  // +0x1C4
    this->field_0x714 = 0;  // +0x1C5
    this->field_0x718 = 0;  // +0x1C6
    this->field_0x71c = 0;  // +0x1C7
    this->field_0x720 = 0;  // +0x1C8
    this->field_0x724 = 0;  // +0x1C9
    this->field_0x728 = 0;  // +0x1CA
    this->field_0x72c = 0;  // +0x1CB
    this->field_0x730 = 0;  // +0x1CC
    this->field_0x734 = 0;  // +0x1CD
    this->field_0x738 = 0;  // +0x1CE
    this->field_0x73c = 0;  // +0x1CF
    this->field_0x740 = 0;  // +0x1D0
    this->field_0x744 = 0;  // +0x1D1
    this->field_0x748 = 0;  // +0x1D2
    this->field_0x74c = 0;  // +0x1D3
    this->field_0x754 = 0;  // +0x1D5
    this->field_0x758 = 0;  // +0x1D6
    this->field_0x750 = 0;  // +0x1D4
    this->field_0x75c = 0;  // +0x1D7
    this->field_0x760 = 0;  // +0x1D8
    this->field_0x768 = 0;  // +0x1DA
    this->field_0x76c = 0;  // +0x1DB
    this->field_0x764 = 0;  // +0x1D9
    this->field_0x770 = 0;  // +0x1DC
    this->field_0x774 = 0;  // +0x1DD
    this->field_0x77c = 0;  // +0x1DF
    this->field_0x780 = 0;  // +0x1E0
    this->field_0x778 = 0;  // +0x1DE
    this->field_0x784 = 0;  // +0x1E1
    this->field_0x788 = 0;  // +0x1E2
    this->field_0x78c = 0;  // +0x1E3

    // Copy values from global data (likely configuration or manager pointers)
    uint32 uVar1 = DAT_00e2b1a4;
    this->field_0x790 = uVar1;           // +0x1E4
    this->field_0x794 = DAT_00e2cd14;    // +0x1E5
    this->field_0x798 = DAT_00e2b050;    // +0x1E6
    this->field_0x79c = DAT_00e2e230;    // +0x1E7
    this->field_0x7a0 = 0;               // +0x1E8

    // Perform 4 more calls to another initialization routine
    for (int i = 0; i < 4; i++)
    {
        FUN_004bfcf0();
    }

    return this;
}