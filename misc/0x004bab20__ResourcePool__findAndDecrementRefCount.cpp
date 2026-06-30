// FUNC_NAME: ResourcePool::findAndDecrementRefCount
// This function searches a dynamic array of 0x34-byte elements for one whose ID matches param_3.
// If found and the element's ref count at +0x28 is non-zero, decrements it via FUN_004babb0.
// Otherwise, constructs a failure result object in param_1 (vtable + zero + -1).

struct ResourceResult {
    void* vtable;       // +0x00
    int field_0x04;     // +0x04
    int field_0x08;     // +0x08
    int indexOrError;   // +0x0C, 0xFFFFFFFF for not found
};

struct Element {
    int field_0x00;     // +0x00
    int field_0x04;     // +0x04
    int id;             // +0x08
    // ... padding to 0x28
    int refCount;       // +0x28
    // total size 0x34
};

struct Container {
    int* array;         // +0x04
    unsigned int count; // +0x08
};

extern void FUN_004babb0(Container* cont, int id, int newRefCount);

ResourceResult* __thiscall ResourcePool::findAndDecrementRefCount(
    ResourceResult* this,
    Container* container,
    int searchId)
{
    if (container != nullptr) {
        unsigned int i = 0;
        if (container->count != 0) {
            Element* elem = reinterpret_cast<Element*>(container->array);
            do {
                if (elem->id == searchId) {
                    if (elem->refCount != 0) {
                        // Decrement ref count if non-zero (pass new value as old-1)
                        if (elem->refCount != 0) {
                            FUN_004babb0(container, searchId, elem->refCount - 1);
                            return this;
                        }
                        FUN_004babb0(container, searchId, 0);
                        return this;
                    }
                    break; // refCount already 0, treat as not found
                }
                i++;
                elem++;
            } while (i < container->count);
        }
    }
    // Construct failure result with vtable, zeros, and -1
    this->field_0x08 = 0;
    this->field_0x04 = 0;
    this->vtable = &PTR_FUN_00e35c3c; // static vtable for "not found" results
    this->indexOrError = -1;
    return this;
}