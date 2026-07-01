// FUNC_NAME: Object::queryInterface
bool queryInterface(int* pObject) {
    if (pObject == nullptr) {
        return false;
    }

    int* vtable = (int*)*pObject;
    // Interface query function at vtable offset 0x10 (4th entry, index 4)
    // EARS engine uses FourCC-style interface IDs (0x43c8ec5b = "C\xc8\xec[")
    typedef bool (*QueryInterfaceFunc)(unsigned int, void**);
    auto query = (QueryInterfaceFunc)(vtable[4]);

    void* pInterface = nullptr;
    bool bSuccess = query(0x43c8ec5b, &pInterface); // overwrites pInterface (local variable)

    // Check if interface query succeeded and pointer is non-null
    if (bSuccess && pInterface != nullptr) {
        return true;
    }

    return false;
}