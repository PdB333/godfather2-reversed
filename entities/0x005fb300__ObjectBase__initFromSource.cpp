// FUNC_NAME: ObjectBase::initFromSource
void * __thiscall ObjectBase::initFromSource(void *this, void *sourceObj)
{
    // sourceObj is a pointer to another object (in EAX, but passed as param_2 in this convention)
    // sourceObj is actually a pointer to an array: [vtable_ptr, integer_data]
    // this is the target object being initialized

    int *vtablePtr = *(int **)sourceObj;        // +0x00: vtable pointer of source
    int sourceData = *(int *)((char *)sourceObj + 4); // +0x04: some integer from source

    // Call a virtual function at vtable offset +8 on the source object
    (*(code **)(*vtablePtr + 8))(vtablePtr);

    int resultData;
    if (sourceData == 0) {
        resultData = 0;
    } else {
        // FUN_004265d0 is likely a memory allocation or copy (e.g., strdup)
        resultData = FUN_004265d0(sourceData, vtablePtr);
    }

    // Another initialization function (FUN_005fba60) – likely copies data into this
    FUN_005fba60(this, vtablePtr, resultData);

    // Retrieve pointer at offset +0x04 of this
    void *&innerPtr = *(void **)((char *)this + 4);
    void *allocPtr;
    if (innerPtr == nullptr) {
        // Use a local dummy buffer (stack fallback)
        undefined4 stackDummy[3]; // 12 bytes on stack
        allocPtr = stackDummy;
    } else {
        allocPtr = innerPtr;
    }

    // Call a virtual function at vtable offset +0 of *this with argument 0xC and allocPtr
    // This likely allocates or initializes a sub-object
    int allocResult = (**(code *** this))(0xC, allocPtr); // vtable[0] = function

    if (allocResult != 0) {
        *(int *)allocResult = allocResult; // self-reference in allocated block
    }
    if ((int *)(allocResult + 4) != nullptr) {
        *(int *)(allocResult + 4) = allocResult; // set self-reference at offset +4
    }

    // Store the allocated block into fields at offsets 0x18 and 0x1C
    *(int *)((char *)this + 0x1C) = 0;
    *(int *)((char *)this + 0x18) = allocResult;

    return this;
}