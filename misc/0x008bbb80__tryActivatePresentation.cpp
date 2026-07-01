// FUNC_NAME: tryActivatePresentation
void __fastcall tryActivatePresentation(void* param_1)
{
    char cVar1;
    int iVar2;
    void* pvVar3;

    cVar1 = isGamePaused(); // FUN_00481660
    if ((cVar1 == '\0') && (cVar1 = isCutsceneActive(), cVar1 == '\0')) {
        return;
    }
    iVar2 = allocateObject(128); // 0x80 bytes, FUN_009c8e50
    if (iVar2 == 0) {
        pvVar3 = 0;
    }
    else {
        pvVar3 = initializePresentation(param_1); // FUN_008b93d0
    }
    debugEnterFunction(); // FUN_00807950 (pushes stack frame)
    setActivePresentation(pvVar3); // FUN_00481690
    return;
}