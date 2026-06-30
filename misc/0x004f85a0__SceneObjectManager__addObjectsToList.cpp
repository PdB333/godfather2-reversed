// FUNC_NAME: SceneObjectManager::addObjectsToList
bool __thiscall SceneObjectManager::addObjectsToList(SceneObjectManager *this, AddResult *result)
{
    int objCount;
    int *objectPtr;
    int idx;
    int *pairPtr;
    int curObjKey;
    int globalBase;
    int slotOffset;
    int keyVal, valVal;
    int *vtablePtr;
    int newSlotIndex;
    int linkOffset;
    
    objCount = getObjectCountFromResult(result->capacity, EAX_UNKNOWN);  // FUN_004f7a90
    *(byte *)result = 0;
    if (objCount == 0) {
        return false;
    }
    if (0 < objCount) {
        objectPtr = (int *)(this + 0x1c);  // +0x1c: pointer to array of object pointers to process
        do {
            idx = 0;
            if (0 < result->count) {
                pairPtr = (int *)result;  // Start of struct
                do {
                    pairPtr = pairPtr + 2;  // Move to next key-value pair (skip two ints)
                    // Compare current object pointer with key stored in result's pair list
                    // The key is derived from some global table lookup using pair's first element
                    if (*objectPtr == *(int *)(*(int *)(**(int **)(__readfsdword(0x2c) + 8) + 0x24) + *pairPtr)) {
                        goto SkipObject;
                    }
                    idx = idx + 1;
                } while (idx < result->count);
            }
            if (result->count < result->capacity) {
                vtablePtr = (int *)*objectPtr;  // The actual object pointer (vtable base)
                newSlotIndex = allocateSlot(&slotInfo);  // FUN_00519c80, returns slot index
                idx = newSlotIndex;
                if (newSlotIndex != 0) {
                    globalBase = **(int **)(__readfsdword(0x2c));  // Thread-local global manager
                    slotOffset = *(int *)(globalBase + 8) + newSlotIndex;  // Offset into slot array
                    // Call vtable method at offset 4 (likely getKey)
                    keyVal = (**(code **)(*vtablePtr + 4))();
                    *(int *)(slotOffset + 0x10) = keyVal;
                    if (keyVal != 0) {
                        // Call vtable method at offset 8 (likely getValue)
                        valVal = (**(code **)(*vtablePtr + 8))();
                        *(int *)(slotOffset + 0x1c) = valVal;
                    }
                    // Store pointer to the object vtable in slot
                    *(int **)(slotOffset + 0x24) = vtablePtr;
                    // Initialize slot's next/prev (linked list) to null (this is a doubly-linked list node)
                    *(int *)(*(int *)(globalBase + 8) + 8 + newSlotIndex) = 0;  // prev
                    *(int *)(*(int *)(globalBase + 8) + 0xc + newSlotIndex) = 0; // next
                    // Insert at head of this's linked list
                    *(int *)(*(int *)(globalBase + 8) + newSlotIndex) = this->head;  // prev = this->head
                    *(int *)(*(int *)(globalBase + 8) + 4 + newSlotIndex) = this->tail; // next = this->tail (used as second pointer? maybe a different list)
                    if (this->head != 0) {
                        // Update the next pointer of the previous head
                        *(int *)(this->head + 8 + *(int *)(globalBase + 8)) = newSlotIndex;
                        *(int *)(this->head + 0xc + *(int *)(globalBase + 8)) = this->tail;  // maybe second tail stored?
                    }
                    this->head = newSlotIndex;
                    this->tail = this->tail;  // tail remains same? Actually the code sets this->tail = iStack_8 which is uninitialized; likely a bug or missing context. Let's just set:
                    this->tail = this->tail;  // Placeholder - original code uses iStack_8 which is stack variable not initialized? Actually iStack_8 is from the splice? Might be a second tail pointer.
                    // Increment reference count for the slot
                    *(int *)(*(int *)(globalBase + 8) + 0x30 + newSlotIndex) += 1;
                    if (result->count == 0) {
                        result->count = 1;
                        result->headKey = newSlotIndex;
                        result->headValue = this->tail;  // iStack_8 - unclear
                    }
                    *(byte *)result = 1;  // Indicate success
                }
            }
SkipObject:
            objectPtr = objectPtr + 1;  // Move to next object in input array
            objCount = objCount - 1;
        } while (objCount != 0);
    }
    return (char)result->flag != 0;  // Return whether any additions were made
}