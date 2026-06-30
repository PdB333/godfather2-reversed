// FUNC_NAME: ObjectPool::freeObject
// Address: 0x00673160
// Releases an object back to the pool. The object pointer (param_1) points to user data.
// Allocation header at negative offsets: slot index at -8, allocation base at -0x10.
void ObjectPool::freeObject(void* objPtr) {
    if (objPtr != nullptr) {
        // Retrieve the slot index from the allocation header
        int slotIndex = *reinterpret_cast<int*>(static_cast<char*>(objPtr) - 8); // -8: slot index
        // Clear the entry in the managed pointer array (this+0xC)
        reinterpret_cast<void**>(this->mArray)[slotIndex] = nullptr;
        // Decrement the count of active objects (this+0x4)
        this->mCount--;
        // Deallocate the entire block (header + object) via a global deallocator
        s_poolDeallocFunc(static_cast<char*>(objPtr) - 0x10); // -0x10: allocation base
    }
}