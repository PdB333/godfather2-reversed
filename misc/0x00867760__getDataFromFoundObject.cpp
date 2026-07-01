// FUNC_NAME: getDataFromFoundObject
// Function at 0x00867760: Retrieves a pointer at offset 0x18 from an object found by searching with parameters.
// Calls FUN_00867690 to locate the object, then returns the dereferenced pointer if found.

bool FUN_00867690(void* param1, void* param2, void* param3, void* param4, void* param5, int* outObjectAddr); // forward declaration

void* getDataFromFoundObject(void* param1, void* param2, void* param3, void* param4, void* param5) {
    int objectAddr = 0;
    bool found = FUN_00867690(param1, param2, param3, param4, param5, &objectAddr);
    if (found) {
        return *(void**)(objectAddr + 0x18); // +0x18: likely a pointer member (e.g., data, owner, or vtable)
    }
    return 0;
}