// FUNC_NAME: AptDisplayList::getElement
// Address: 0x005b3470
// Role: Bounds-checked element accessor for AptDisplayList element array.
// The array begins at offset 0x00 from the object base (elements are 4 bytes each).
// The number of elements is stored at offset +0x80.
 // __thiscall: this in ECX, index in EDI (unconventional).
int __thiscall AptDisplayList::getElement(int index) {
    // Bounds check: index >= 0 && index < nElements
    if (index >= 0 && index < *(int *)(this + 0x80)) {
        // In bounds – return the element at offset index * 4
        return *(int *)(this + index * 4);
    }

    // Assertion failure: index out of bounds
    const char *assertCond = "i >= 0 && i < nElements";
    const char *assertFile = "..\\source\\Apt\\AptDisplayList.cpp";
    int assertLine = 0x27e; // 638
    int assertLevel = 2;
    char *assertFlag = (char *)&DAT_0112901e; // global assertion enabled flag

    if (*assertFlag != '\0') {
        int **piVar1 = *(int ***)(*(int **)(__readfsdword(0x2c) + 0x30)); // thread-local assertion handler pointer
        uint uVar3 = 1;
        if (piVar1 != nullptr) {
            uVar3 = (**(code **)(*piVar1 + 8))(&assertCond, assertCond); // call handler function
        }
        if ((uVar3 & 2) != 0) {
            *assertFlag = 0; // disable further assertions
        }
    }

    // Possibly trigger debug break or terminate
    if (((piVar1 != nullptr) || (assertLevel != 4)) &&
        ((uVar3 & 1) != 0 || (assertLevel == 0 || assertLevel == 1))) {
        code *pcVar2 = (code *)__int2c(); // software interrupt 3 (debug break)
        return (*pcVar2)(); // call break handler
    }

    // Return default value (unreachable)
    return 0;
}