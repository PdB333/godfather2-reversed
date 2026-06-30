// FUNC_NAME: BaseObject::BaseObject
// Function address: 0x005091c0
// Constructor with allocation flag. If allocFlag bit 0 is set, calls the virtual release function at vtable+4.
undefined4 __thiscall BaseObject::BaseObject(undefined4 thisParam, byte allocFlag) {
    int *vtablePtr;
    
    // Call base class constructor
    FUN_005091f0(); // likely baseConstructor()
    
    // If allocFlag indicates heap allocation (bit 0 set), invoke virtual destructor/release at vtable offset 4
    if ((allocFlag & 1) != 0) {
        vtablePtr = (int *)FUN_009c8f80(); // get vtable pointer (likely global function returning this class's vtable)
        (**(code **)(*vtablePtr + 4))(thisParam, 0); // call virtual function at vtable+4 (destructor with '0' flag)
    }
    
    return thisParam;
}