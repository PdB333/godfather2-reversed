// FUNC_NAME: NetSession::processPacket
// Function address: 0x005c3d80
// Role: Thunk that adjusts the this pointer by 5 bytes and calls the virtual function at vtable offset 0xc.
// This is typical of multiple inheritance where a derived class's method must call the overridden virtual
// on the correct base class subobject.

#include <cstdint>

// Helper: retrieves a pointer to the base class's vtable pointer location.
// Implemented at 0x005c3df0.
extern int* __thiscall getVtablePointer(NetSession* this);

void __thiscall NetSession::processPacket(uint32_t param2) {
    // Get a pointer to the vtable structure (likely a pointer to the base class's vtable pointer)
    int* vtableBase = getVtablePointer(this);
    // Dereference to obtain the actual vtable pointer
    int* vtable = *reinterpret_cast<int**>(vtableBase);
    // Function at vtable offset 0xc (index 3) – 4th virtual function
    using VirtualFunc = void (__thiscall*)(NetSession*, uint32_t);
    VirtualFunc func = reinterpret_cast<VirtualFunc>(vtable[3]);
    // Adjust this pointer by the base class offset (5 bytes)
    NetSession* adjustedThis = reinterpret_cast<NetSession*>(
        reinterpret_cast<uint8_t*>(this) + 5
    );
    func(adjustedThis, param2);
}