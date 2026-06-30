// FUNC_NAME: ObjectBase::Deinit
// Function address: 0x00433210
// Role: Deinitialization/cleanup method. Sets vtable to derived, calls two cleanup functions, frees a member pointer, resets vtable to base, clears global singleton flag.
void __thiscall ObjectBase::Deinit(ObjectBase* this) {
    // Set vtable to derived class vtable (ensures virtual dispatch during cleanup)
    this->vtable = &PTR_FUN_00e30bf0;

    // Call initialization/cleanup pair with two code pointers
    FUN_00607d50(&LAB_0042abc0, &LAB_0042abe0);

    // Offset +0x04: pointer to dynamically allocated memory
    void* dataPtr = *(void**)(reinterpret_cast<char*>(this) + 4);
    if (dataPtr != nullptr) {
        FUN_0042c630();                    // cleanup logic before free
        FUN_009c8eb0(dataPtr);             // memory deallocation
    }

    // Clear the pointer member
    *(void**)(reinterpret_cast<char*>(this) + 4) = nullptr;

    // Switch vtable to base class vtable (for subsequent base destructor)
    this->vtable = &PTR_LAB_00e30bf4;

    // Clear global singleton/state indicator
    DAT_012233a8 = 0;
}