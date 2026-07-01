// FUNC_NAME: Player::getSomeFloatValue
float Player::getSomeFloatValue(void* param_1) // __thiscall? Actually param_1 is passed as undefined4, likely this pointer
{
    int iVar1;
    float local_4;
    
    local_4 = *(float*)0x00d5780c; // Global float value, maybe default
    iVar1 = FUN_008c7490(param_1); // Likely a getter or lookup function, returns pointer to something
    if (iVar1 != 0) {
        local_4 = *(float*)(iVar1 + 0x174); // +0x174: some float field in the returned structure
    }
    return (float)local_4;
}