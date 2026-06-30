// FUNC_NAME: InputDeviceManager::~InputDeviceManager
// Function address: 0x0068f0b0
// Role: Scalar deleting destructor for InputDeviceManager.
// Sets vtable to derived class, performs cleanup via global function pointer,
// resets global flag, then calls operator delete if needed.

undefined4* __thiscall InputDeviceManager::~InputDeviceManager(InputDeviceManager* this, byte scalarDeletingFlag)
{
    // Set vtable pointer to this class's vtable (for proper virtual destructor chain)
    this->vtable = &PTR_FUN_00d5c8d4;

    // If global input manager singleton is active, call its first virtual function with 1
    // This likely decrements a reference count or performs global cleanup
    if (gInputManagerGlobal != (undefined4*)0x0) {
        (**(code**)*gInputManagerGlobal)(1);
    }

    // Set vtable pointer to base class's vtable (destructor chain continues)
    this->vtable = &PTR_LAB_00d5c858;

    // Clear global instantiation flag
    gInputManagerInstantiated = 0;

    // If scalar deleting flag has bit 0 set, free the memory
    if ((scalarDeletingFlag & 1) != 0) {
        operatorDelete(this);
    }

    return this;
}