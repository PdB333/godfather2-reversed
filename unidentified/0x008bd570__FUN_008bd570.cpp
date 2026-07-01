// FUNC_NAME: SomeComponent::computeSpeedBonus
float __fastcall SomeComponent::computeSpeedBonus(int param_this)
{
    float result = 0.0f;
    // Check if the current weapon's state is 1 (e.g., active/equipped)
    if (*(int*)(*(int*)(param_this + 0x19c) + 0xc4) == 1)
    {
        // piVar1 points to an array or list of weapon stats
        int* piVar1 = *(int**)(*(int*)(param_this + 0x19c) + 0xc0);
        int index = getCurrentWeaponIndex(*(undefined4*)(param_this + 0x54)); // FUN_0084a470
        if (index != 0)
        {
            // Add base float at offset 8 multiplied by global speed multiplier[0]
            result = *(float*)(*(int*)(param_this + 0x1d0) + 8) * DAT_0112f938[0];
        }
        // If the returned index is the last element in the list
        if (index == *(int*)(*piVar1 + 4) - 1)
        {
            // Add next float at offset 4 multiplied by global speed multiplier[3]
            result += *(float*)(*(int*)(param_this + 0x1d0) + 4) * DAT_0112f938[3];
        }
        // Check some global mode/state
        int isModeActive = isSomeModeActive(); // FUN_0084a410 (no args)
        if (isModeActive != 0)
        {
            // Add float at offset 0xc multiplied by global speed multiplier[4]
            result += *(float*)(*(int*)(param_this + 0x1d0) + 0xc) * DAT_0112f938[4];
        }
    }
    return (float)result;
}