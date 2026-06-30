// FUNC_NAME: SimNpc::~SimNpc

undefined4* __thiscall SimNpc::~SimNpc(undefined4* this, byte shouldDelete) {
    // Set vtable to current class vtable for correct virtual dispatch during destruction
    *this = &PTR_LAB_00d65ae4;

    // Access member at offset 0x5C (m_pManager or similar pointer to a state/manager struct)
    // Check a flag at offset 0x8E0 (bit 10) within that pointed-to struct
    int* managerPtr = (int*)this[0x17];  // this + 0x5C
    if (((uint)managerPtr[0x238] >> 10 & 1) != 0) {
        // If flag set, call a cleanup function stored at offset 0x260 from manager struct
        (**(code**)(*(int*)managerPtr + 0x260))();
    }

    // Switch vtable to base class vtable (or derived? pattern: second vtable)
    *this = &PTR_LAB_00d63090;

    // If subobject at offset 0x68 (this + 0x68) is non-null, destroy it
    if (this[0x1a] != 0) {
        // Destructor call for subobject (likely substruct or component)
        FUN_004daf90(this + 0x1a);
    }

    // Global cleanup (e.g., manager or resource cleanup)
    FUN_0080ea60();

    // If the shouldDelete flag indicates memory deallocation, free the object
    if ((shouldDelete & 1) != 0) {
        FUN_00624da0(this);  // operator delete
    }

    return this;
}