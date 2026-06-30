// FUNC_NAME: SomeClass::~SomeClass
void SomeClass::~SomeClass(void* this) {
    // Call base class destructor
    BaseClass::~BaseClass(this);
    
    // Call additional cleanup function
    this->cleanupFunction();
    
    // Free dynamically allocated buffer if it was allocated
    if (buffer != stackBuffer && buffer != nullptr) {
        g_freeFunc(buffer);
    }
    
    // Copy member at offset 0x1c from this to some global/static location
    *(int*)(g_globalObject + 0x1c) = *(int*)((char*)this + 0x1c);
}