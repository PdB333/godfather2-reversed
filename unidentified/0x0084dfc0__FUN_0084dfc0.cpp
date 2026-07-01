// FUNC_NAME: SomeClass::initSubStructure
void SomeClass::initSubStructure(int param_1, int* pStruct)
{
    int* basePtr = pStruct;

    // Initialize two sub-objects at offsets 0 and 8
    subObjectInit(param_1, pStruct);
    subObjectInit(param_1, pStruct + 8);

    // Zero out 0x60 bytes at offsets 0x10 and 0x1c
    memset(0x60, pStruct + 0x10);
    memset(0x60, pStruct + 0x1c);

    // Zero out 0x20 bytes at the address of the local variable? (likely a bug in decompilation)
    // Actually this might be memset(&pStruct->someField, 0, 0x20) but decompiler shows &param_2
    // We'll keep as is but note the oddity
    memset(0x20, &pStruct);

    // Store the pointer to the structure itself into multiple fields
    pStruct[0x28 / 4] = (int)pStruct;  // offset 0x28
    pStruct[0x2c / 4] = (int)pStruct;  // offset 0x2c
    pStruct[0x30 / 4] = (int)pStruct;  // offset 0x30
    pStruct[0x34 / 4] = (int)pStruct;  // offset 0x34
    pStruct[0x38 / 4] = (int)pStruct;  // offset 0x38
    pStruct[0x3c / 4] = (int)pStruct;  // offset 0x3c
    pStruct[0x40 / 4] = (int)pStruct;  // offset 0x40
}