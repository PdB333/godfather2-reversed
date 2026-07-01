// FUNC_NAME: RefCountedBase::assignReplacement

#include <cstdint>

// Forward declarations
void __fastcall RefCounted_AddRef(void* ptr);  // FUN_00827800
void __fastcall RefCounted_Release(void* ptr); // FUN_00827830
void* __fastcall RefCounted_CreateOrGet(int id); // FUN_00834620

// Internal structure for each tracked weak reference entry
struct WeakRefEntry {
    uint32_t field0;      // +0x00
    uint32_t field4;      // +0x04
    void*    trackedPtr;  // +0x08 (the pointer being tracked)
};

// Main object managing two direct pointers and a list of weak references
class RefCountedBase {
public:
    // First 16 bytes of this object are copied from the assignment parameter,
    // layout: type (int), data1 (int), then flag (byte in low byte) and padding.
    // Actual fields start at offset 0x10:
    // +0x10: pointerOld (stored only temporarily during replacement)
    // +0x14: pointerNew
    // +0x0E: someFlag (byte)
    // +0x12: weakRefCount (number of entries in the weak ref list)
    // +0x18: updateFlag
    // +0x8C: weakRefList (pointer to array of WeakRefEntry)

    void __thiscall assignReplacement(const AssignParams* params);

private:
    void removeOldPointerFromWeakList(void* oldPtr);
};

// Parameter structure passed to assignReplacement
struct AssignParams {
    int32_t  type;        // +0x00: 0, 1, or 2
    int32_t  data;        // +0x04: used depending on type
    int32_t  flagAndPad;  // +0x08: only low byte used as boolean flag
    // +0x0C: padding (unused)
};

void RefCountedBase::assignReplacement(const AssignParams* params) {
    // Save old pointer at +0x10 before it might be overwritten
    void* oldPtr = *(void**)((uint8_t*)this + 0x10);

    // Copy the first two 8-byte fields from params into this
    *(uint64_t*)this = *(uint64_t*)params;         // copies type + data (8 bytes)
    *((uint64_t*)this + 1) = *(uint64_t*)((int*)params + 2); // copies flagAndPad + padding (8 bytes)

    int32_t type = params->type;  // same as first copy
    int32_t data = params->data;  // actually derived from copy
    // Actually after copy, we can read fields again, but we already have the local.

    // Now determine new pointer based on type
    void* newPtr;
    void* old2 = *(void**)((uint8_t*)this + 0x14);

    if (type == 0) {
        // Type 0: swap? Set old field to old2, then new field to data (as raw pointer?)
        *(void**)((uint8_t*)this + 0x10) = old2;
        newPtr = (void*)data;  // data is treated as pointer
    } else if (type == 1) {
        // Type 1: possibly create from ID, fallback to raw pointer
        void* converted = RefCounted_CreateOrGet(data);
        *(void**)((uint8_t*)this + 0x10) = old2;
        newPtr = (converted != nullptr) ? converted : (void*)data;
    } else if (type == 2) {
        // Type 2: just set new pointer
        newPtr = (void*)data;
    } else {
        return; // unknown type, exit
    }

    *(void**)((uint8_t*)this + 0x14) = newPtr;

    // Determine whether to add a ref and update the weak list
    bool flag = ( ( (char)params->flagAndPad ) != 0 );
    bool haveNew = (newPtr != nullptr);
    bool haveOld = (*(void**)((uint8_t*)this + 0x10) != nullptr);

    if (flag && haveNew && haveOld) {
        // Both old and new exist, flag says to update -> add ref, clear some flag
        *(uint32_t*)((uint8_t*)this + 0x18) = 1;   // updateFlag = 1
        *(uint32_t*)((uint8_t*)this + 0x0E) = 0;   // clear some flag
        RefCounted_AddRef(newPtr);
    } else {
        // No update: set flag to 0
        *(uint32_t*)((uint8_t*)this + 0x18) = 0;
        if (haveOld) {
            RefCounted_Release(oldPtr);
        }
        if (haveNew) {
            RefCounted_AddRef(newPtr);
        }
    }

    // Now check if the old pointer (the one that was at +0x10 before replacement) 
    // is still pointed to by either +0x10 or +0x14. If not, remove it from the weak list.
    if (oldPtr != nullptr &&
        oldPtr != *(void**)((uint8_t*)this + 0x14) &&
        oldPtr != *(void**)((uint8_t*)this + 0x10)) 
    {
        removeOldPointerFromWeakList(oldPtr);
    }
}

void RefCountedBase::removeOldPointerFromWeakList(void* oldPtr) {
    uint32_t count = *(uint32_t*)((uint8_t*)this + 0x12);
    if (count == 0) return;

    uint8_t* listBase = *(uint8_t**)((uint8_t*)this + 0x8C);
    for (uint32_t i = 0; i < count; ++i) {
        WeakRefEntry* entry = (WeakRefEntry*)(listBase + i * sizeof(WeakRefEntry));
        // The entry's tracked pointer is at offset 8
        void** entryPtr = (void**)&entry->trackedPtr;
        if (*entryPtr == oldPtr) {
            // Notify the weak reference object (call first vtable function with arg 1)
            void* weakObj = *entryPtr;
            if (weakObj != nullptr) {
                (*(void (**)(void*, int))(*(uint32_t*)weakObj))(weakObj, 1);
            }
            // Clear the entry
            entry->field0 = 0;
            entry->field4 = 0;
            entry->trackedPtr = nullptr;

            // Compact the list: move the last entry into this slot if not the last
            if (i != count - 1) {
                WeakRefEntry* lastEntry = (WeakRefEntry*)(listBase + (count - 1) * sizeof(WeakRefEntry));
                *entry = *lastEntry;
            }
            --count;
            *(uint32_t*)((uint8_t*)this + 0x12) = count;
            // Since entries shift, we need to re-evaluate this index
            // (the loop will increment i, so we might skip the new entry at this slot)
            // But the original code does not adjust i, so it continues. We'll replicate that.
        }
    }
}