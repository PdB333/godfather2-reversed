// FUNC_NAME: GenericCSA::initFromObject
bool __thiscall GenericCSA::initFromObject(int* thisPtr, int param_2)
{
    char cVar1;
    int iVar2;
    bool bResult;

    iVar2 = checkGlobalState(); // FUN_008fdfd0 - likely checks if system initialized
    if (iVar2 == 0) {
        return false;
    }
    if (param_2 != 0) {
        // Call virtual method at vtable+0x6c (likely clear or reset)
        (*(code**)(*thisPtr + 0x6c))();
        iVar2 = getComponentIndex(param_2); // FUN_0097f740 - gets an index from the object
        if (iVar2 != -1) {
            thisPtr[0x18] = iVar2; // +0x60: component index
            thisPtr[0x47] = *(int*)(param_2 + 0x54); // +0x11C: store field from object at +0x54
            bResult = isComponentValid(getComponentManager()); // FUN_007914e0 and FUN_0097ff40
            if (bResult != 0) {
                return true;
            }
        }
    }
    return false;
}