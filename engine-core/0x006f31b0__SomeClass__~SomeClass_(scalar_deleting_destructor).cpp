// FUNC_NAME: SomeClass::~SomeClass (scalar deleting destructor)
void __thiscall SomeClass::~SomeClass(unsigned char deletingFlag) {
    // Call base class destructor (FUN_006f2ee0)
    BaseClass::~BaseClass();
    
    // If the deleting flag (bit 0) is set, free the object's memory
    // Size 0x90 = sizeof(SomeClass)
    if (deletingFlag & 1) {
        operator delete(this, 0x90);
    }
}