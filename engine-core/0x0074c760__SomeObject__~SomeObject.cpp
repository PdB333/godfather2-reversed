// FUNC_NAME: SomeObject::~SomeObject
// Function address: 0x0074c760
// Scalar deleting destructor: destroys internal object if present, then optionally frees memory.
int* __thiscall SomeObject::~SomeObject(int* this, byte deletingFlag)
{
    // If the internal pointer (or flag) is non-zero, call the internal destructor
    if (*this != 0) {
        FUN_004daf90(this); // Destroys the sub-object associated with this
    }
    // If the deleting flag is set (bit 0), deallocate the memory for this object
    if ((deletingFlag & 1) != 0) {
        FUN_009c8eb0(this); // operator delete or similar memory deallocation
    }
    return this;
}