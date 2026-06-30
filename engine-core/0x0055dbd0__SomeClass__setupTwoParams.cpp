// FUNC_NAME: SomeClass::setupTwoParams
void SomeClass::setupTwoParams(void)
{
    // this+0x18 is a pointer to some object (e.g., a render controller)
    int* renderCtrlPtr = *(int**)(this + 0x18);
    
    // First parameter block: likely a color or vector (4 uint32s)
    uint32_t paramBlock1[4];
    paramBlock1[0] = 0;
    paramBlock1[1] = DAT_00e44754;          // e.g., 0x00E44754 - red component?
    paramBlock1[2] = 0;
    paramBlock1[3] = DAT_00e2b1a4;          // e.g., 0x00E2B1A4 - green/blue component?
    
    // Second parameter block: different initialization
    uint32_t paramBlock2[4];
    paramBlock2[0] = 0;
    paramBlock2[1] = 0;
    paramBlock2[2] = 0;
    paramBlock2[3] = DAT_00e2b1a4;          // same constant as above
    
    FUN_009f2000(); // unknown helper, possibly stack guard or debug
    // Call virtual method at offset 0x40 in the vtable of the object pointed by renderCtrlPtr+0xd0
    (**(code**)(*(int*)(renderCtrlPtr + 0xd0) + 0x40))(&paramBlock1);
    
    FUN_009f2000(); // same helper again
    // Call virtual method at offset 0x44
    (**(code**)(*(int*)(renderCtrlPtr + 0xd0) + 0x44))(&paramBlock2);
}