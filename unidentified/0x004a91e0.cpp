// FUN_004a91e0: createAndDestroyTempRefCountedObject
// Allocates a reference-counted object (0x24 bytes) with two vtables, stores a parameter,
// then immediately decrements the reference count; if zero, calls destructor.
// This pattern suggests a temporary object used for a side-effect and then destroyed.

// Structure offsets:
// +0x00: first vtable pointer (PTR_LAB_00e3560c)
// +0x04: unknown (initialized to 0)
// +0x08: reference count (initialized to 0, incremented to 1, then decremented)
// +0x0C: field3 (initialized to 1)
// +0x10: field4 (initialized to 1)
// +0x14: pointer to the second vtable slot (self-reference: &this[6])
// +0x18: second vtable pointer (PTR_LAB_00e35634)
// +0x1C: function pointer (FUN_004a92d0)
// +0x20: stored parameter (param_1)

struct TempRefCountedObject {
    int* vtable1;          // +0x00
    int unk1;              // +0x04
    int refCount;          // +0x08
    int field3;            // +0x0C
    int field4;            // +0x10
    int* selfPtr;          // +0x14 (points to &vtable2)
    int* vtable2;          // +0x18
    void (*funcPtr)();     // +0x1C
    int storedParam;       // +0x20
};

// External references
// FUN_009c8e50: custom operator new (size 0x24)
// FUN_0064d980: debug/logging function (called when DAT_01218014 != 0)
// FUN_004a92d0: function stored at offset +0x1C (possibly a method or callback)
// PTR_LAB_00e3560c, PTR_LAB_00e35634: vtable addresses

void __cdecl createAndDestroyTempRefCountedObject(int param_1) {
    TempRefCountedObject* obj = (TempRefCountedObject*)FUN_009c8e50(0x24);
    if (obj == nullptr) {
        obj = nullptr;
    } else {
        obj->unk1 = 0;          // +0x04
        obj->refCount = 0;     // +0x08
        obj->field4 = 1;       // +0x10
        obj->field3 = 1;       // +0x0C
        obj->vtable1 = (int*)&PTR_LAB_00e3560c;       // +0x00
        obj->vtable2 = (int*)&PTR_LAB_00e35634;       // +0x18
        obj->funcPtr = (void (*)())FUN_004a92d0;      // +0x1C
        obj->selfPtr = &obj->vtable2;                 // +0x14: points to the second vtable pointer
        obj->refCount++;                              // +0x08: increment reference count
    }
    obj->storedParam = param_1;   // +0x20

    if (DAT_01218014 != 0) {
        FUN_0064d980();   // debug/output
    }

    int* refPtr = &obj->refCount; // piVar1 = piVar2 + 2
    (*refPtr)--;   // decrement reference count
    if (*refPtr == 0) {
        // Call destructor via first vtable +8
        (*(void (__thiscall**)(TempRefCountedObject*))(*(obj->vtable1) + 8))(obj);
    }
    // If refCount > 0, the object is leaked? This pattern suggests immediate destruction.
}