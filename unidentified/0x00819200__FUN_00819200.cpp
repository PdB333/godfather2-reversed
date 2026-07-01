// FUNC_NAME: SomeClass::getOutputData
struct OutputData {
    double unknownDouble; // +0x00 (from global +0x30)
    int unknownInt;       // +0x08 (from global +0x38)
};

// Returns global data and optionally delegates to a virtual handler
void __thiscall SomeClass::getOutputData(OutputData* outData) {
    int* globalManager = GetGlobalManager(); // FUN_00471610 returns pointer to some global singleton
    outData->unknownDouble = *(double*)(globalManager + 0x30);
    outData->unknownInt = *(int*)(globalManager + 0x38);

    int** vtablePtr = *(int***)(this + 0x18); // pointer to virtual function table
    if (*vtablePtr != 0) {
        if (*(int*)(this + 8) != 0) {
            // Call virtual function on derived instance (adjust this by -0x48)
            (*(void (__thiscall*)(int, OutputData*))(*vtablePtr))(*(int*)(this + 8) - 0x48, outData);
            return;
        }
        // Call virtual function with null this
        (*(void (__thiscall*)(int, OutputData*))(*vtablePtr))(0, outData);
    }
}