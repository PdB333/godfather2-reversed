// FUNC_NAME: SystemManager::constructor
void __thiscall SystemManager::constructor(SystemManager *this, int someValue) {
    // Save this pointer to global singleton
    g_systemManager = this;

    // Set vtable pointer (EA engine virtual dispatch)
    this->vtable = &__vtable_SystemManager;

    // Store the parameter (likely an initialization flag or object ID)
    this->field_8 = someValue;

    // Structure for sub-object creation
    struct SubObjectInitData {
        int size;     // 0x10004
        int param2;   // 1
        int param3;   // 0
    };
    SubObjectInitData initData;
    initData.size = 0x10004;
    initData.param2 = 1;
    initData.param3 = 0;

    // Allocate memory for sub-object (72 bytes)
    void *subObjectBase = memoryAllocate(0x48);
    if (subObjectBase != nullptr) {
        // Initialize the sub-object and store its handle
        this->field_4 = subObjectConstructor(&initData);
    } else {
        this->field_4 = 0;
    }
}