// FUNC_NAME: SomeClass::debugPrintIndex

void __thiscall SomeClass::debugPrintIndex(void) {
    int someIndex; // from virtual call
    int nameIndex; // from second virtual call
    int *tempPtr;

    // Call virtual method at vtable offset 0x50 (likely getIndex or getID)
    tempPtr = (int *)(**(code **)(*(int *)this + 0x50))(); 
    // Log the index (size 0x20 probably indicates a debug structure or string)
    debugLog(0x20, &tempPtr);

    // Call same virtual method again
    nameIndex = (**(code **)(*(int *)this + 0x50))();
    // Look up a global table entry based on the index
    someIndex = globalNameTable[nameIndex];
    // Log the looked-up value
    debugLog(0x20, &someIndex);
}