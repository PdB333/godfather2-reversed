// FUNC_NAME: AptCharacter::updateState
void __thiscall AptCharacter::updateState(int *this, int arg)
{
    // Check current state stored at this+0x00 (-0x00)
    if (*this == 1) {
        // Handle state 1 (likely eState_Active or similar)
        FUN_005bbe00(arg);
    }
    else if (*this != 0xb) {
        // Assert failed: unexpected state (only 1 and 0xb are valid)
        FUN_0059bf00(&DAT_00e36da0, "..\\source\\Apt\\AptCharacter.cpp", 0x164, 2, &DAT_01129122);
    }
    // If state is 0xb (eState_Inactive/Dead), no action
}