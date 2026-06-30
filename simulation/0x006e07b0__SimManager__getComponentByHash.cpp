// FUNC_NAME: SimManager::getComponentByHash
int* __thiscall SimManager::getComponentByHash(void* thisPtr) {
    int* componentPtr;
    char result;
    int* esi_reg; // unaff_ESI, likely preserved from caller (e.g., an outer context pointer)

    // Check this pointer and the hash table pointer at offset 0x31a8
    if (thisPtr != nullptr && *(int**)((char*)thisPtr + 0x31a8) != nullptr) {
        // The hash table stores a pointer to a node that is embedded in an object at offset 0x48.
        // Subtract 0x48 to get the base of the object holding that node.
        componentPtr = (int*)(*(int*)((char*)thisPtr + 0x31a8) - 0x48);
        if (componentPtr != nullptr) {
            // Prepare an output pointer (initially null) for a possible lookup
            int outPtr = 0;
            // Call a virtual function at vtable offset 0x10 (e.g., QueryInterface / getComponentByType)
            result = (*(int(__thiscall**)(int, int*, unsigned int))(*(int*)componentPtr + 0x10))(componentPtr, &outPtr, 0xdc51ebb1);
            if (result != 0 && esi_reg != nullptr) {
                // Check a separate condition using the preserved esi register pointer
                result = (*(int(__thiscall**)(int))(*(int*)esi_reg + 0x38))(esi_reg);
                if (result != 0) {
                    return nullptr; // Validation failed
                }
            }
            return componentPtr;
        }
    }
    return nullptr;
}