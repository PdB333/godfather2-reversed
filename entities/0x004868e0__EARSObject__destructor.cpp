// FUNC_NAME: EARSObject::destructor
// Address: 0x004868e0
// Role: Destructor for an EARS object hosting a polymorphic subobject.
//       Sets vtable, calls subobject virtual functions, then optionally frees memory.

class EARSObject {
public:
    // Vtable layout for the polymorphic subobject at offset 0x04
    struct SubObjectVTable {
        /* +0x04 */ void (__thiscall *unknownMethod1)(void* self, void* a1, void* a2); // cleanup or destroy
        /* +0x0C */ void (__thiscall *unknownMethod2)(void* self);                     // subobject destructor
    };

    struct SubObject {
        const SubObjectVTable* vtable; // always first
        // ... further data unknown
    };

    // In-memory layout:
    /* +0x00 */ const void** vtablePtr;     // set to &PTR_FUN_00e35228
    /* +0x04 */ SubObject* subObj;          // managed subobject
    /* +0x08 */ void* arg2;                 // second parameter for first virtual call
    /* +0x10 */ void* arg1;                 // first parameter for first virtual call

    // Destructor, byte flag: bit0 = free this memory
    void* __thiscall destructor(uint8_t flags) {
        // switch vtable to a special static table (PTR_FUN_00e35228)
        vtablePtr = reinterpret_cast<const void**>(0x00e35228);

        // if both auxiliary pointer and subobject exist, call first virtual method
        if (arg1 != nullptr && subObj != nullptr) {
            subObj->vtable->unknownMethod1(subObj, arg1, arg2);
        }

        // always destroy the subobject if it exists
        if (subObj != nullptr) {
            subObj->vtable->unknownMethod2(subObj);
        }

        // if low bit set, deallocate this object's memory
        if ((flags & 1) != 0) {
            // call memory deallocator (FUN_009c8eb0)
            extern void __fastcall memoryDeallocate(void* p);
            memoryDeallocate(this);
        }

        return this;
    }
};