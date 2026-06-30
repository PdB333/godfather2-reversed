// FUN_0044c730: SomeClass::setIntProperty
void __thiscall SomeClass::setIntProperty(int thisPtr, int index, int value) {
    // Array of ints at offset 0x30 (size implied by index)
    int* propertyArray = (int*)(thisPtr + 0x30);
    if (value != propertyArray[index]) {
        propertyArray[index] = value;
        // Global singleton at DAT_012233a8, call its update function twice with the same argument
        uint globalBase = *(uint*)0x012233a8;
        FUN_00432da0(*(undefined4*)(globalBase + 4));
        FUN_00432da0(*(undefined4*)(globalBase + 4));
    }
}