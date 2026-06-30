// FUNC_NAME: EARSObject::registerHandleInGlobalTable

#include <windows.h>

// Forward declaration of unknown function that returns a pointer to some data (likely a handle)
extern int* __fastcall FUN_004fc3d0(int* param);

// Class representing an EA EARS engine object or handle container
class EARSObject {
public:
    // Fields:
    // +0x00: vtable pointer (implicit)
    void* m_refCountOwner;          // +0x04 – pointer to some object that owns a reference count
    // ... other fields ...
    int m_globalSlotIndex;          // +0x40 – index into a global handle table

    // Method: register a handle for this object in a global table (accessed via TLS)
    void __fastcall registerHandleInGlobalTable();
};

void __fastcall EARSObject::registerHandleInGlobalTable()
{
    // Get a pointer to a reference-counted object from the owner's structure
    int* refCountedObj = *reinterpret_cast<int**>(
        *reinterpret_cast<int*>(this->m_refCountOwner) + 0x20);

    // Increment reference count at offset +0x04 of that object, if valid
    if (refCountedObj != nullptr) {
        refCountedObj[1]++;   // refCountedObj[1] is equivalent to *(refCountedObj + 4)
    }

    // Call some engine function that extracts a handle/value from the object
    int* handleData = FUN_004fc3d0(refCountedObj);

    // Store the handle into a global array (indexed by m_globalSlotIndex)
    if (handleData != nullptr) {
        // Obtain the global handle table base pointer via thread-local storage (FS:[0x2C])
        // FS:[0x2C] typically points to thread-local storage area or engine context
        int* tlsPointer = *reinterpret_cast<int**>(__readfsdword(0x2C));  // Read FS:[0x2C]
        // First dereference yields a pointer to the engine's global context
        int engineContext = *reinterpret_cast<int*>(tlsPointer);
        // At offset +8 from that context is the base of the handle table
        int* handleTableBase = reinterpret_cast<int*>(
            *reinterpret_cast<int*>(engineContext + 8));
        // Write the handle value (from handleData + 8) into the table at the given slot
        int* targetSlot = handleTableBase + 0x84 / sizeof(int) + this->m_globalSlotIndex;
        *targetSlot = *reinterpret_cast<int*>(handleData + 8);
    }
}