// FUNC_NAME: ManagerBase::~ManagerBase
void __thiscall ManagerBase::~ManagerBase(ManagerBase* this) // address 0x00564b90
{
    // Set vtable to derived class vtable (likely called from derived destructor)
    *(void**)this = &PTR_FUN_00e3a574; // vtable for derived class?
    *(void**)(this + 1) = &PTR_FUN_00e3a58c; // secondary vtable or pointer?

    // Clean up child object at offset 0x20 (measured in bytes from this)
    if (this->childPtr1 != 0) {
        FUN_00569500(); // some release function
        if (this->childPtr1 != 0) {
            (*(void(__thiscall**)(int))(*((int*)this->childPtr1)))(1); // call vtable function with arg 1
        }
        this->childPtr1 = 0;
    }

    // Clean up second child object at offset 0x128 (bytes)
    if (this->childPtr2 != 0) {
        FUN_009c8eb0(this->childPtr2); // free or release function
        this->childPtr2 = 0;
    }

    // Restore vtable to base class vtable (standard C++ destructor pattern)
    *(void**)this = &PTR_LAB_00e3a598; // base class vtable

    // Clear global singleton flag
    DAT_012233c0 = 0;
}