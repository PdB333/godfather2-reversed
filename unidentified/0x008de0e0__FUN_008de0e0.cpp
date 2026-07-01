// FUNC_NAME: SomeClass::checkAndExecuteAction
bool __fastcall SomeClass::checkAndExecuteAction(int thisPtr)
{
    int iVar1;
    bool bResult;
    int localArray[3]; // stack buffer for some operation

    bResult = false;
    // Check if bit 3 (0x8) of field at +0x30 is set, and if global state at DAT_01129900+0x10 and +0x14 are both zero
    if ((((*(byte *)(thisPtr + 0x30) & 8) != 0) && (*(int *)(DAT_01129900 + 0x10) == 0)) &&
       (*(int *)(DAT_01129900 + 0x14) == 0)) {
        localArray[0] = 0;
        localArray[1] = 0;
        localArray[2] = 0;
        iVar1 = FUN_008de020(localArray); // some operation that may fill localArray
        bResult = iVar1 != 0;
        if (localArray[0] != 0) {
            FUN_009c8f10(localArray[0]); // cleanup/free if allocated
        }
    }
    return bResult;
}