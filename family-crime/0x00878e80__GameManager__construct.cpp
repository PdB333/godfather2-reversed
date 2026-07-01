// FUNC_NAME: GameManager::construct
void __thiscall GameManager::construct(uint thisPtr, uint arg)
{
    int iVar1;
    uint uVar2;
    
    uVar2 = 4;
    iVar1 = thisPtr;
    registerWithHash(0xa5975eb2, thisPtr, 4);
    initializeWithFlag(iVar1, uVar2);
    *(void **)(thisPtr + 0x158) = &GameManager_vtable;
    uVar2 = getSomethingFromParam(arg);
    setInternalData(thisPtr, uVar2);
    iVar1 = isDebugModeEnabled();
    if (iVar1 != 0) {
        setDebugFlag(1);
        initializeDebugOutput();
    }
    if ((*(uint *)(thisPtr + 0xc88) >> 0x15 & 1) != 0) {
        handleSpecialFlag(thisPtr);
    }
    return;
}