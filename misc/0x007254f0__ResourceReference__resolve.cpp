// FUNC_NAME: ResourceReference::resolve
// 0x007254f0 - Resolves a 128-bit resource GUID handle into a pointer to a resource interface,
// then queries for a specific interface (hash 0x8a859764) and retrieves two data values if supported.
// Fields:
// +0x10c..+0x118: mGuid[4] (uint32) - 128-bit GUID representing the resource
// +0xc0: mResolvedData0 (uint64) - first part of resolved resource data
// +0xc8: mResolvedData1 (uint32) - second part of resolved resource data
// Sentinel values for invalid handles: {0xBAEDBBBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911}

#include <cstdint>

// External function: converts a 128-bit GUID to a raw object pointer
extern int* __fastcall resolveGuidToPointer(uint32_t* guid, int unknown);

// Virtual function table offset constants for the interface queried by hash 0x8a859764
// vtable[1] : method that outputs a structure (uStack_1c and uStack_14)
// vtable[4] : method that checks interface support

// Vtable layout for the raw object returned by resolveGuidToPointer
struct IResourceObject {
    void** vtable;
};

// Vtable layout for the resolved interface (from QueryInterface)
struct IResourceInterface {
    void** vtable;
};

int __fastcall ResourceReference::resolve(ResourceReference* this) {
    uint32_t* guid = (uint32_t*)(this + 0x10c);

    // Sentinel values representing an invalid/uninitialized handle
    static const uint32_t invalidGuid[4] = { 0xBAEDBBBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911 };

    // Check if handle is non-zero and not the sentinel
    bool nonZero = (guid[0] != 0) || (guid[1] != 0) || (guid[2] != 0) || (guid[3] != 0);
    bool notSentinel = (guid[0] != invalidGuid[0]) || (guid[1] != invalidGuid[1]) || (guid[2] != invalidGuid[2]) || (guid[3] != invalidGuid[3]);

    if (!nonZero || !notSentinel) {
        return 0;
    }

    // Resolve the GUID to a raw object pointer
    IResourceObject* obj = (IResourceObject*)resolveGuidToPointer(guid, 0);
    if (!obj) {
        return 0;
    }

    // Temporary buffer for QueryInterface result / interface pointer
    void* interfaceBuffer[10]; // Large enough for stack alignment
    interfaceBuffer[0] = 0; // Clear first pointer (will be overwritten by QueryInterface?)

    // Query if the object supports interface with hash 0x8a859764 (likely a compile-time GUID hash)
    // Virtual function at vtable[4] (offset 0x10) takes the hash as argument, returns nonzero if supported
    bool supportsInterface = false;
    typedef bool (__thiscall IResourceObject::*CheckInterface)(uint32_t);
    CheckInterface checkFnc = (CheckInterface)(obj->vtable[4]); // index 4 = offset 16
    supportsInterface = (obj->*checkFnc)(0x8a859764);

    if (supportsInterface && interfaceBuffer) { // interfaceBuffer is always non-null (stack)
        // Now call a method on the obtained interface (via interfaceBuffer) to fill output data
        // Virtual function at vtable[1] (offset 4) takes a pointer to output structure
        typedef void (__thiscall IResourceInterface::*GetData)(uint64_t* out0, uint32_t* out1);
        IResourceInterface* iface = (IResourceInterface*)interfaceBuffer;
        GetData getFnc = (GetData)(iface->vtable[1]); // index 1 = offset 4

        // Output values are stored at offsets from the stack after the call
        uint64_t data0;
        uint32_t data1;
        (iface->*getFnc)(&data0, &data1);

        // Store the retrieved data into this object's fields
        *(uint64_t*)(this + 0xc0) = data0;
        *(uint32_t*)(this + 0xc8) = data1;
    }

    // Return the pointer to the resolved data field (used as an address for chaining)
    return (int)(this + 0xc0);
}