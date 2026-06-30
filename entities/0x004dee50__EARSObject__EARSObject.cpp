// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x004dee50 - Constructor for EARSObject with optional initialization flag.
// Calls base constructor (0x004ded60), then if the flag's lowest bit is set, calls constructorTail (0x009c8eb0).
EARSObject* __thiscall EARSObject::EARSObject(byte flag) {
    // Call base class constructor (initializes common members)
    baseConstructor(); // FUN_004ded60

    // If the allocation/construction flag has bit 0 set, perform additional setup
    if (flag & 1) {
        constructorTail(this); // FUN_009c8eb0 - likely finalizes object (e.g., add to manager, allocate subsystems)
    }

    return this;
}