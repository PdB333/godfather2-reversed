// FUNC_NAME: SomeAllocator::setCount
void __thiscall SomeAllocator::setCount(int param_1, uint param_2) // +0x4: current count
{   
    // If new count exceeds current capacity, reallocate
    if (*(uint *)(param_1 + 4) < param_2) {
        // Reallocate with new capacity
        FUN_008d6f40(param_2);
        // Update current count to new capacity
        *(uint *)(param_1 + 4) = param_2;
        return;
    }
    // If new count is smaller, simply shrink without reallocation
    if (param_2 < *(uint *)(param_1 + 4)) {
        *(uint *)(param_1 + 4) = param_2;
    }
    return;
}