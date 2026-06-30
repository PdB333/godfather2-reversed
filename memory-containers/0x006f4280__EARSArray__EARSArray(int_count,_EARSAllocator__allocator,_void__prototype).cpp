// FUNC_NAME: EARSArray::EARSArray(int count, EARSAllocator* allocator, void* prototype)
EARSArray* __thiscall EARSArray::EARSArray(int count, EARSAllocator* allocator, void* prototype)
{
    // Member layout (relative to this):
    // +0x00 : data (pointer to array elements)
    // +0x04 : unknownFlag (set to 0)
    // +0x08 : count
    // +0x0C : blockPtr (memory block from allocator)
    // +0x10 : allocator (stored for later use)

    this->unknownFlag = 0;                                          // param_1[1] = 0
    this->count = count;                                            // param_1[2] = param_2

    // Call into memory system: returns a memory block (or a sub-allocator) for the given prototype and allocator
    this->blockPtr = allocateBlock(prototype, allocator);           // param_1[3] = FUN_004265d0(param_4, param_3)

    this->allocator = allocator;                                    // param_1[4] = param_3

    // Notify the allocator that we are about to use it (virtual function at vtable offset 0x08)
    allocator->prepareMemory();                                      // (**(code **)(*param_3 + 8))();

    // Fallback to a global default block if the allocator returned null
    void* effectiveBlock = (this->blockPtr != nullptr) ? this->blockPtr : gDefaultBlock; // puVar2

    // Actually allocate the array memory: call the allocator's first virtual function (vtable offset 0x00)
    // Passes total size in bytes (count * 4) and the effective memory block
    this->data = allocator->allocateArray(count * 4, effectiveBlock); // *param_1 = (*(code **)**(undefined4 **)param_1[4])(param_2 * 4, puVar2);

    return this;
}