// FUNC_NAME: ObjectManager::registerObject
void __thiscall ObjectManager::registerObject(ObjectManager *this, void *object)
{
    void *originalObject;
    void **listPtr;
    void **slot;
    uint typeIndex;

    originalObject = object;
    // +0x38: pointer to a list or linked list node in the object
    listPtr = *(void **)((char *)object + 0x38);
    // Get a pointer to a slot where the object reference will be stored (e.g., per-list head)
    slot = (void **)getSlotPtr(&listPtr);
    *slot = originalObject;
    // +0xc4: type/category index (0-9)
    typeIndex = *(uint *)((char *)originalObject + 0xc4);
    if (typeIndex < 10) {
        // Increment per-category counter in this (offset 0x40 = array of 10 ints)
        ((int *)((char *)this + 0x40))[typeIndex] += 1;
    }
}