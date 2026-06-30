// FUNC_NAME: SomeClass::initializeObject
void __thiscall SomeClass::initializeObject(int owner, int* dataPtr, int* objPtr)
{
    int iVar1;
    int uVar2;
    
    FUN_00533cc0(); // likely base constructor or memory clear
    
    *objPtr = &PTR_FUN_00e37c78; // set vtable pointer
    objPtr[0xc] = 0; // +0x30: some field
    *(char*)(objPtr + 0xd) = 0; // +0x34: byte field
    *(char*)((int)objPtr + 0x35) = 0; // +0x35: byte field
    
    if (*(char*)(owner + 0xd) == '\0') { // check owner flag
        objPtr[10] = 0; // +0x28: field
        objPtr[0xe] = DAT_00e2b1a4; // +0x38: some constant
        uVar2 = DAT_00e2eff4; // another constant
        objPtr[9] = dataPtr; // +0x24: store data pointer
        objPtr[0xf] = uVar2; // +0x3C: store constant
        iVar1 = *dataPtr; // first element of data
        objPtr[0xb] = iVar1; // +0x2C: store
        if (((iVar1 < 0) && (dataPtr[2] == 0 && dataPtr[3] == 0)) &&
           (dataPtr[4] == 0 && dataPtr[5] == 0)) {
            *(char*)(owner + 0xc) = 1; // set owner flag
            return;
        }
    }
    return;
}