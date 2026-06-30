// FUNC_NAME: EARSObject::~EARSObject

// Destructor with deletion flag (EA standard pattern).
// Called with flag=0 for automatic destruction (no delete),
// flag=1 for deleting destructor (calls operator delete after base destruction).
void __thiscall EARSObject::~EARSObject(byte deletionFlag) {
    // Call base class destructor (FUN_005db540 - assumed base destructor)
    this->Base::~Base(); // e.g., SimObject::~SimObject

    // If flagged for heap deletion, free memory
    if (deletionFlag & 1) {
        // operator delete(this) (FUN_009c8eb0)
        // In typical EA EARS implementation, this calls custom deallocation.
        operator delete(this);
    }

    // Note: The decompiled indicates this function returns param_1 (this pointer).
    // This is unusual for a destructor; possibly a leftover from the calling convention
    // or a compiler-specific optimization. We preserve the return for signature compatibility.
    // return this;
}