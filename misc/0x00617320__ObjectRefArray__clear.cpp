// FUNC_NAME: ObjectRefArray::clear

// Reconstructed C++ for function at 0x00617320
// This function clears an array of reference-counted object pointers.
// Structure offsets:
//   this+0x0: entryArray (pointer to array of 8-byte entries)
//   this+0x4: count (int, number of entries)
// Each 8-byte entry:
//   +0x0: unknown (int)
//   +0x4: objectPtr (pointer to a ref-counted object)
// Object layout (relevant offset):
//   +0x8: refCount (short)
// The global DAT_01205964 holds the object's vtable, with destructor at vtable[1].

#include <cstddef>

typedef unsigned int uint;

struct RefCountedObject {
    // ... other members ...
    short refCount;  // offset 0x8
};

struct Entry {
    uint field_0;           // offset 0x0
    RefCountedObject* obj;  // offset 0x4
};

struct ObjectRefArray {
    Entry* entries; // offset 0x0
    int count;      // offset 0x4
};

// External functions (from EA EARS)
void FUN_00616dc0(RefCountedObject* obj); // Release internal resources?
void FUN_009c8f10(void* ptr);             // Free memory (operator delete?)

// Global vtable pointer
extern void* DAT_01205964;

void __thiscall ObjectRefArray::clear(ObjectRefArray* this) {
    int i = this->count;
    while (--i >= 0) {
        RefCountedObject* obj = this->entries[i].obj;
        if (obj != nullptr) {
            obj->refCount -= 1;
            if (obj->refCount == 0) {
                FUN_00616dc0(obj);
                // Call virtual destructor (vtable[1])
                void** vtable = *(void***)DAT_01205964;
                void (*destructor)(RefCountedObject*, int) = (void (*)(RefCountedObject*, int))vtable[1];
                destructor(obj, 0);
            }
            this->entries[i].obj = nullptr;
        }
    }
    if (this->entries != nullptr) {
        FUN_009c8f10(this->entries);
    }
}