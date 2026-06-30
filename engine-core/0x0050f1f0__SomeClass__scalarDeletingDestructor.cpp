// FUNC_NAME: SomeClass::scalarDeletingDestructor
// Function address: 0x0050f1f0
// Role: Scalar deleting destructor for a class of size 0xA0 (160 bytes).
//       Calls a base destructor (0x004bfcf0) and optionally frees memory if flag & 1 is set.
//       The class has a vtable at offset 0, and operator delete is retrieved via a global vtable getter.

extern void baseDestructor(void* obj);        // FUN_004bfcf0 - base destructor
extern int* getDeleterVtable();               // FUN_009c8f80 - returns pointer to vtable containing operator delete

class SomeClass {
public:
    // Standard vtable pointer at offset 0
    void* vtable; // +0x00

    // Scalar deleting destructor: if flags & 1, delete this after destructor.
    // Returns this pointer.
    void* __thiscall scalarDeletingDestructor(byte flags) {
        baseDestructor(this);
        if (flags & 1) {
            int* vtablePtr = getDeleterVtable();
            // vtablePtr[0] = destructor (complete or scalar), vtablePtr[1] = operator delete
            // Call operator delete with size 0xA0
            typedef void (__thiscall* OpDelete)(void* obj, int size);
            OpDelete del = (OpDelete)(*vtablePtr + 4); // +4 offset for operator delete
            del(this, 0xA0);
        }
        return this;
    }

    // Padding to reach total class size 0xA0 (vtable pointer: 4 bytes)
    char _pad_[0xA0 - 4];
};