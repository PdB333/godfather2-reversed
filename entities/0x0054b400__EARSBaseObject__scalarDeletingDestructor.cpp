// FUNC_NAME: EARSBaseObject::scalarDeletingDestructor
// Address: 0x0054b400

class EARSBaseObject {
public:
    // +0x00: vtable pointer
    // +0x10: pointer to allocated buffer (void*)
    // +0x18: size or index (uint)

    // Scalar deleting destructor – called by the C++ delete operator
    // deleteFlag: 0 = no delete, 1 = call operator delete
    EARSBaseObject* __thiscall scalarDeletingDestructor(uint8 deleteFlag) {
        // Set vtable to the current class vtable (ensures correct virtual dispatch during cleanup)
        *(void**)this = &PTR_FUN_00e39c48;

        uint sizeOrIndex = *(uint*)((char*)this + 0x18);
        if ((int)sizeOrIndex >= 0) {
            // Retrieve thread-local allocator handle
            void* allocatorHandle = TlsGetValue(DAT_01139810);
            // Release buffer at offset +0x10
            // Size = (sizeOrIndex & 0x3FFFFFFF) * 0x60 (96 bytes per slot)
            // Type ID 0x17 likely indicates memory pool type
            FUN_00aa26e0(*(void**)((char*)this + 0x10), (sizeOrIndex & 0x3FFFFFFF) * 0x60, 0x17);
        }

        // Set vtable to purecall (base class destructor marker)
        *(void**)this = &PTR___purecall_00dcfcf4;

        if (deleteFlag & 1) {
            // Free the object's memory via operator delete
            FUN_009c8eb0(this);
        }

        return this;
    }
};