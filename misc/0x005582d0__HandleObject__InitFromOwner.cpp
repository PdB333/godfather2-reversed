// FUNC_NAME: HandleObject::InitFromOwner
void __thiscall HandleObject::InitFromOwner(void* owner) // this in ESI, owner passed in EAX (first arg)
{
    // Initialize this->owner (offset 0x00)
    this->owner = owner;

    // Zero out fields at offsets 0x08..0x28 (10 ints + 1 byte)
    this->field_08 = 0;
    this->field_0C = 0;
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_18 = 0;
    this->field_1C = 0;
    this->field_20 = 0;
    this->field_24 = 0;
    this->field_28 = 0;

    // Allocate internal object (20 bytes = 5 ints)
    int* internalObj = (int*)HeapAlloc(0x14); // FUN_009c8e50
    this->internalObject = internalObj; // offset 0x04

    if (internalObj != nullptr)
    {
        // Parameters for object creation
        struct InitParams {
            int count;   // = 2
            int size;    // = 0x10
            int flags;   // = 0
        } params = {2, 0x10, 0};

        // Get memory manager singleton
        int* memoryManager = (int*)GetMemoryManager(); // FUN_009c8f80

        // Create object within memory manager
        int createdObj = CreateObject(&params, memoryManager); // FUN_004265d0

        // Store results into internal object
        internalObj[3] = createdObj;     // offset 0x0C: pointer to created
        internalObj[4] = (int)memoryManager; // offset 0x10: memory manager

        // Call virtual function at slot 2 on the memory manager
        ((void (*)())(memoryManager[1] /*vtable*/ + 8))(); // vtable+8

        // Clear first three fields of internal object
        internalObj[0] = 0; // offset 0x00
        internalObj[2] = 0; // offset 0x08
        internalObj[1] = 0; // offset 0x04
    }
    else
    {
        // Allocation failed, clear internal pointer
        this->internalObject = nullptr;
    }
}