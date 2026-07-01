// FUNC_NAME: ManagerContainer::clearAndDeallocate

// Forward declaration for memory deallocation
extern void FreeMemory(void* ptr);

class DestroyableObject {
public:
    virtual void release(int flag) = 0;
};

class ManagerContainer {
public:
    void clearAndDeallocate();
    
private:
    // offsets from this:
    int elementCount;       // +0x90 - number of elements in the array
    DestroyableObject** elements; // +0x8c - pointer to array of object pointers
    // (also likely other members not shown)
};

void __thiscall ManagerContainer::clearAndDeallocate()
{
    unsigned int idx = 0;

    // If there are any elements
    if (this->elementCount != 0) {
        int elementIndex = 0;
        do {
            DestroyableObject* obj = this->elements[elementIndex]; // each element pointer is at offset i*0x0c from elements base? Actually decomp shows index*0xc + elements.
            // Wait, careful: the decomp uses iVar3 = iVar3 + 0xc each iteration, and reads from (iVar3 + 8 + *(int *)(param_1 + 0x8c)).
            // This suggests the array is not a simple pointer array but an array of structures with 0xc bytes per entry, where offset +8 is the pointer.
            // Let's reinterpret: elements is a pointer to an array of structures of size 0xc. Each structure has a pointer at offset +0x8? Actually the access is: puVar1 = *(undefined4 **)(iVar3 + 8 + *(int *)(param_1 + 0x8c));
            // So it's: base = elements; then at base + iVar3 + 8, we read a pointer. So each entry is 0xc bytes, and the pointer is at offset 8 within the entry.
            // The code also uses vtable at *puVar1.
            // So we need to model the entry structure.
        } while (idx < (unsigned int)this->elementCount);
    }
    // Then free the elements array itself
    if (this->elements != nullptr) {
        FreeMemory(this->elements);
    }
}

// The above is incomplete due to misinterpretation. Let's correct based on decompiled logic.
// The decompiled loop: iVar3 starts at 0, then each iteration iVar3 += 0xc. uVar2 is index counter.
// The read: puVar1 = *(uint**)(iVar3 + 8 + *(int*)(param_1+0x8c));
// So in first iteration: puVar1 = *(uint**)(0 + 8 + elements) = elements[8]? But elements is pointer to array, so it's (char*)elements + 0 + 8. That is offset 8 from start of first entry (sizeof entry is at least 8+4). Actually we read a pointer at offset 8 relative to the base+index*0xc. So each entry is 0xc bytes, and the pointer we care about is at offset +8 within the entry. The pointer itself points to an object whose vtable is at offset 0.
// So we have an array of structures of size 0xc, and each structure contains a pointer (at +8) to some object. The code calls the first vfunc on that object.
// Also, the loop increments iVar3 by 0xc each time, so it advances to the next entry.
// Therefore, we need to model the entry struct:
struct Entry {
    char unknown[8]; // +0x00..+0x07
    DestroyableObject* obj; // +0x08
    // possibly more? The structure is 0xc = 12 bytes, so +0x08 to +0x0B is the pointer (4 bytes), then maybe another field at +0x0c? No, stride is 0xc, so entry ends at +0x0c.
};
// Then the loop:
for (unsigned int i = 0; i < this->elementCount; ++i) {
    Entry* entry = &((Entry*)this->elements)[i];
    DestroyableObject* obj = entry->obj;
    if (obj != nullptr) {
        obj->release(1); // calling vtable[0] with argument 1
    }
}
// Finally, free the whole array.

// Correcting the previously posted code:

// FUNC_NAME: ManagerContainer::clearAndDeallocate

extern void FreeMemory(void* ptr);

class DestroyableObject {
public:
    virtual void release(int flag) = 0; // corresponds to calling vtable[0] with argument 1
};

// Structure for each element in the dynamic array
struct ElementEntry {
    char unknown_field_0[8]; // offsets 0x00-0x07
    DestroyableObject* object; // offset 0x08 (4 bytes)
    // total size 0x0C (12 bytes)
};

class ManagerContainer {
public:
    void clearAndDeallocate();
    
private:
    int elementCount;        // offset +0x90
    ElementEntry* elements;  // offset +0x8C - pointer to array of ElementEntry
};

void __thiscall ManagerContainer::clearAndDeallocate()
{
    unsigned int idx = 0;
    if (this->elementCount != 0) {
        ElementEntry* entryArray = this->elements;
        do {
            DestroyableObject* obj = entryArray[idx].object;
            if (obj != nullptr) {
                obj->release(1); // call virtual destructor / release with flag 1
            }
            ++idx;
        } while (idx < (unsigned int)this->elementCount);
    }
    if (this->elements != nullptr) {
        FreeMemory(this->elements);
    }
}