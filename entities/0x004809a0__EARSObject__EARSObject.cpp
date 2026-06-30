// FUNC_NAME: EARSObject::EARSObject

class EARSObject {
public:
    // Initializes basic fields (likely sets vtable pointer, refcount, etc.)
    void init(); // FUN_00480a00

    // Constructor with allocation flag
    EARSObject(byte flags) {
        init();

        if (flags & 1) {
            // Global pointer to a manager or allocator (e.g., ObjectFactory)
            // Offset 0x2d4 holds a pointer to a vtable-like structure.
            // The second virtual function (offset +4) is called with (this, 0).
            // This likely registers the newly allocated object or handles heap allocation.
            void* manager = reinterpret_cast<void*>(DAT_01223410); // global pointer
            void* vtablePtr = *reinterpret_cast<void**>(static_cast<char*>(manager) + 0x2d4);
            using VirtualFunc = void (__thiscall*)(void*, int);
            VirtualFunc func = reinterpret_cast<VirtualFunc>(*reinterpret_cast<void**>(vtablePtr) + 4);
            func(this, 0);
        }
    }
};