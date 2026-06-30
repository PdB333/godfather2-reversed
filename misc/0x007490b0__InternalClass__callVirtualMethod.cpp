// FUNC_NAME: InternalClass::callVirtualMethod
void __thiscall InternalClass::callVirtualMethod(int thisPtr, uint param_2) {
    int memberPtr = *(int *)(thisPtr + 0x58); // this->member_0x58
    int baseObj;
    int *vtablePtr;
    if (memberPtr == 0) {
        vtablePtr = (int *)0x0;
        baseObj = 0;
    } else {
        vtablePtr = (int *)(memberPtr - 0x48); // adjust to containing object
        baseObj = memberPtr - 0x48;
    }
    // Call virtual function at vtable offset 0xa4 (index 41)
    (**(code **)(*vtablePtr + 0xa4))(param_2, baseObj + 0x6ec);
    return;
}