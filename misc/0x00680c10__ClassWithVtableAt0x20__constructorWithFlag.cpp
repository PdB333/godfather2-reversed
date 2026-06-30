// FUNC_NAME: ClassWithVtableAt0x20::constructorWithFlag
int __thiscall constructorWithFlag(int thisPtr, byte flag) {
    // +0x20: vtable pointer
    int* vtableSlot;
    
    if (thisPtr == 0) {
        vtableSlot = (int*)0x0;
    } else {
        vtableSlot = (int*)(thisPtr + 0x20);
    }
    *vtableSlot = (int)&PTR_LAB_00d580cc;  // set vtable at offset 0x20
    DAT_011298bc = 0;  // global flag reset
    FUN_007edfb0();    // common initialization (unknown)
    if ((flag & 1) != 0) {
        FUN_009c8eb0(thisPtr);  // optional additional setup/cleanup (unknown)
    }
    return thisPtr;
}