// FUNC_NAME: ControllerManager::constructor
undefined4* __thiscall ControllerManager::constructor(undefined4* this, byte allocationFlag)
{
    undefined4* subObjectPtr;
    int i;

    // Set vtable pointer to base class vtable (temporary, will be overwritten)
    *this = &PTR_FUN_00e38908; // base vtable

    // Initialize array of 16 sub-objects (input devices/controllers) 
    // Each sub-object is 0x17 bytes, array spans from offset 0x29 to 0x199 in this object.
    // The loop sets the vtable pointer of each sub-object.
    subObjectPtr = this + 0x199 / sizeof(undefined4); // start at last element (high offset)
    i = 15;
    do {
        subObjectPtr -= 0x17 / sizeof(undefined4); // move to previous element
        i--;
        *subObjectPtr = &PTR_LAB_00e388f0; // set vtable for each sub-object (e.g., InputDevice)
    } while (i >= 0);

    // Set final vtable to derived class vtable
    *this = &PTR_LAB_00e34174; // ControllerManager vtable

    // If the allocation flag indicates the memory was allocated (e.g., via operator new),
    // call a cleanup function – perhaps to free memory on allocation failure? 
    // Note: This is unusual for a constructor; may be related to placement new or debug allocator.
    if ((allocationFlag & 1) != 0) {
        FUN_009c8eb0(this); // likely operator delete or destructor for allocation cleanup
    }

    return this;
}