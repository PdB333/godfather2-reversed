// FUNC_NAME: GameManager::~GameManager

void __thiscall GameManager::~GameManager() {
    // Perform initial cleanup (sub-function at 0x005e4d30)
    cleanupSub(this);

    // Zero out and free member pointers
    this->field_6018 = 0;                // +0x6018
    freeMemory(this->ptr_6014);          // +0x6014
    this->ptr_6014 = 0;                  // +0x6014
    this->field_601c = 0;                // +0x601c
    this->field_6024 = 0;                // +0x6024
    freeMemory(this->ptr_6020);          // +0x6020
    this->ptr_6020 = 0;                  // +0x6020
    this->field_6028 = 0;                // +0x6028
    this->field_6030 = 0;                // +0x6030
    freeMemory(this->ptr_602c);          // +0x602c
    this->ptr_602c = 0;                  // +0x602c
    this->field_6034 = 0;                // +0x6034

    // Virtual base destructor call via vtable at DAT_01223510
    void* vtable = *(void**)g_someGlobalVtable;
    typedef void (*BaseDestructor)(void*);
    ((BaseDestructor)((uintptr_t*)vtable)[3])(this);
}