// FUNC_NAME: PoolObject::createFromPool
// Function address: 0x006a8c40
// Allocates a fixed-size block (0x10 bytes) from a memory pool identified by poolId.
// Stores the pool ID at +0x44 and the allocated pointer at +0x40.

bool PoolObject::createFromPool(int poolId) {
    // Pool::Allocate(poolId, size, flags)
    void* allocatedPtr = Pool::Allocate(poolId, 0x10, 0);
    if (allocatedPtr != nullptr) {
        this->poolId = poolId;        // offset +0x44
        this->dataPtr = allocatedPtr; // offset +0x40
        return true;
    }
    return false;
}