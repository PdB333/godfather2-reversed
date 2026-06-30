// FUNC_NAME: BaseObject::~BaseObject (scalar deleting destructor)
// Address: 0x007672e0
// Role: Scalar deleting destructor for BaseObject (calls destructor body and deallocates if disposing)

// Callee functions:
//   - destructorBody (FUN_00766c00): actual destructor implementation
//   - operatorDelete (FUN_00624da0): memory deallocation

int __thiscall BaseObject::~BaseObject(void* this, byte disposing) {
    // Call the main destructor body
    destructorBody(this);
    if (disposing & 1) {
        // If this is a disposing delete, deallocate memory
        operatorDelete(this);
    }
    // Return the this pointer (though usually ignored)
    return reinterpret_cast<int>(this);
}