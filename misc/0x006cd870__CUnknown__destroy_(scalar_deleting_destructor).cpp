// FUNC_NAME: CUnknown::destroy (scalar deleting destructor)
// Address: 0x006cd870
// Role: Scalar deleting destructor for an object of size 0x170 (368 bytes)
// Calls base destructor at 0x006cd480, then optionally deletes memory via vtable.

undefined4 __thiscall CUnknown::destroy(CUnknown* this, byte deallocFlag)
{
    int *vtablePtr;

    // Call base class destructor (likely at offset 0x006cd480)
    CUnknown::baseDestroy();

    // If the calling convention flag indicates memory was allocated with 'new',
    // call the virtual delete operator (vtable[1]) with the object size.
    if ((deallocFlag & 1) != 0) {
        vtablePtr = (int *)getVtable(); // FUN_009c8f80() returns a pointer to the vtable
        (**(code **)(*vtablePtr + 4))(this, 0x170); // vtable[1] call: operator delete(size)
    }

    return this; // typical MSVC scalar deleting destructor returns this
}