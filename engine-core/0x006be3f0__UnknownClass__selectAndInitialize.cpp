// FUNC_NAME: UnknownClass::selectAndInitialize
void __thiscall selectAndInitialize(int thisPtr, int param2) {
    undefined4 selectedValue;
    undefined4 zero1;
    undefined1 zero2;

    if (param2 == *(int *)(thisPtr + 0x54)) {  // +0x54: current state?
        selectedValue = *(undefined4 *)(thisPtr + 0x60);  // +0x60: primary value
    } else {
        selectedValue = *(undefined4 *)(thisPtr + 0x68);  // +0x68: alternate value
    }
    zero1 = 0;
    zero2 = 0;
    FUN_00408a00(&selectedValue, 0);  // clear or initialize based on selectedValue
    return;
}