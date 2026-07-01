// FUNC_NAME: EARS::Framework::Pool::~Pool

void __fastcall Pool::~Pool(Pool* this)
{
    // Iterate over all allocated chunks in the pool array
    uint32 chunkId = 0;
    if (this->chunkCount != 0) {
        do {
            PoolChunk* chunk = *(PoolChunk**)(this->chunkArray + 4 + chunkId * 8);
            // If chunk has a valid pointer to user data, release it via callback
            if (chunk->userData != 0) {
                ((void (__thiscall *)(void*))chunk->releaseFunc)(chunk->userData);
            }
            // Return chunk to free list
            *chunk = this->freeList;             // link to current head
            this->numFree -= 1;                  // +0x14
            this->numAllocated += 1;             // +0x10 (actually decremented? Wait param_1[5] = numFree, param_1[4] = numAllocated? But looks opposite: originally it had +0x10 as numAllocated and +0x14 as numFree? Let's check: param_1[5] = param_1[5] + -1, param_1[4] = param_1[4] + 1. param_1[0xe] is freeList. So param_1[5] likely numFree, param_1[4] numAllocated? But we are freeing a chunk, so numAllocated should decrease, numFree increase. Actually the code does: param_1[5]-- and param_1[4]++. That seems backwards: param_1[5] is decremented (should be numFree? but we are adding to free list so numFree increases), and param_1[4] is incremented (should be numAllocated? but we are freeing, so numAllocated should decrease). Maybe the fields are swapped? Let's re-examine: In the loop, for each chunk that is being freed, they decrement param_1[5] and increment param_1[4]. That would make param_1[5] decrease (more free?) and param_1[4] increase (more allocated?). That doesn't make sense if it's a pool. Possibly these are counts of something else. Alternatively, maybe param_1[4] is a "used count" and param_1[5] is a "free count"? Actually when freeing a chunk, used count should decrease. But here used count increases? Hmm.

Let's look at the offsets: The decompiler says param_1[4] is offset +0x10, param_1[5] is offset +0x14. The code: param_1[5] = param_1[5] + -1; param_1[4] = param_1[4] + 1. So +0x14 decreases, +0x10 increases. Perhaps these are not counts but indices or something else. Could be that param_1[4] is "freeListCount" and param_1[5] is "usedListCount"? No, typical pool has free count and used count. But the loop is freeing all allocated chunks, so used count should become 0, free count becomes total. But here used count is increasing? Unless the naming is reversed. The code might be buggy or the decompiler output might have swapped? I'll keep the logic as given, but rename variables carefully: call param_1[4] as m_allocCount (but it's incremented when freeing? That's odd). Alternatively, maybe the fields are: +0x10 = m_numAllocated but it's actually the count of items currently allocated? No, during destruction, we are freeing all, so allocated count should go to 0, free count to total. That's what we expect. But the code does: +0x10 increments and +0x14 decrements. So if initially +0x10 = allocated count, +0x14 = free count, after destroying all, allocated should become 0 (decremented), free should become total (incremented). But here allocated is incremented and free is decremented. So maybe it's the opposite: +0x10 is free count, +0x14 is used count. Let's assume that: m_freeCount at +0x10, m_usedCount at +0x14. Then freeing a chunk: freeCount++ (param_1[4]++), usedCount-- (param_1[5]--). That matches the code! Yes, param_1[4] is m_freeCount, param_1[5] is m_usedCount. So in the loop, we are *freeing* each chunk, so freeCount increases, usedCount decreases. That makes sense. So m_freeCount = param_1[4], m_usedCount = param_1[5]. 

Now, the chunk structure: each chunk entry in the array is 8 bytes? Actually the array is at this->chunkArray, and each entry is at offset 4 + chunkId*8. That suggests each entry is 8 bytes, starting at offset 4? That's weird. Possibly the array is an array of pointers to PoolChunk? The code: puVar1 = *(undefined4 **)(param_1[0xf] + 4 + uVar2 * 8). So param_1[0xf] is a pointer to an array of 8-byte structures, and for each entry, we take the first 4 bytes (offset 0) as a pointer? Actually the dereference: *(undefined4 **)(base + 4 + index*8) fetches a pointer from that address. So base+4 (skip first 4 bytes) then index*8. So each entry is 8 bytes, and the pointer is at offset 0 of that entry? Let's think: The array base is at param_1[0xf]. For index i, we read the 4-byte value at (base + 4 + i*8). So the first entry (i=0) is at base+4, second at base+12, etc. That implies the array has a header of 4 bytes before entries? Unlikely. Maybe it's an array of 8-byte structs where the first 4 bytes are something else? Actually the pattern: (base + 4 + i*8) suggests that base itself points to something like m_poolArray[0] is at base+4? Could be that the first 4 bytes are a count or something? But the count is stored separately at param_1[0x10]. So maybe the array is actually an array of pointers (4 bytes each) but the indexing is messed? Let's examine: The loop uses uVar2 < (uint)param_1[0x10], and increments uVar2 by 1 each time. So there are param_1[0x10] entries. The fetch is at offset 4 + uVar2*8. That means each entry is 8 bytes, and we skip the first 4 bytes. So perhaps the array has a 4-byte header (like total size?), then an array of 8-byte entries. That's plausible for a custom allocator.

Given the offsets, I'll model the pool structure as:

struct Pool {
    void** vtable;          // +0x00
    void** vtable2;         // +0x04 (maybe)
    int m_freeCount;        // +0x10 (param_1[4])
    int m_usedCount;        // +0x14 (param_1[5])
    PoolChunk* freeList;   // +0x38 (param_1[0xe])
    PoolChunkArray* chunkArray; // +0x3C (param_1[0xf]) - pointer to array of chunks
    int chunkCount;         // +0x40 (param_1[0x10])
    int something;          // +0x44 (param_1[0x11])
};

But we don't need the full struct; we just need to represent the function.

I'll write the code with meaningful variable names.

Also note: The function sets *this = &PTR_FUN_00d91b10; then later sets this[1] = &PTR_FUN_00d91b04; then calls FUN_004de130(); then sets *this = &PTR_LAB_00d91b0c; This is typical for a destructor: first set vtable to a "destructing" vtable, then do cleanup, then call base destructor, then set vtable to another (maybe deleted) label.

The global DAT_01129934 is set to 0 at the end.

I'll leave the function names as FUN_009c8f10 (which might be operator delete or free) and FUN_004de130 (base destructor).

Now produce the code. */
void __fastcall Pool::~Pool(Pool* this)
{
    PoolChunk* chunk;
    uint32 idx = 0;

    // Set vtable to derived class destructor vtable
    *this = &g_poolVtableDestructor;   // PTR_FUN_00d91b10

    if (this->chunkCount != 0) {
        do {
            // Get chunk from pool array (each entry is 8 bytes, skip 4-byte header)
            chunk = *(PoolChunk**)((uint8*)this->chunkArray + 4 + idx * 8);
            // If chunk has user data, release it via callback
            if (chunk->userData != 0) {
                ((void (__thiscall *)(void*))chunk->releaseFunc)(chunk->userData);
            }
            // Link chunk into free list
            chunk->next = this->freeList;
            this->m_freeCount++;
            this->m_usedCount--;
            this->freeList = chunk;
            idx++;
        } while (idx < this->chunkCount);
    }
    this->chunkCount = 0;
    // Free the pool array
    FUN_009c8f10(this->chunkArray);   // likely operator delete/free
    this->chunkArray = 0;
    this->something = 0;  // +0x44
    // Set vtable to base class destructor vtable
    this->vtable2 = &g_baseVtableDestructor; // PTR_FUN_00d91b04
    // Call base class destructor
    FUN_004de130();
    // Set vtable to "deleted" state
    *this = &g_deletedVtable; // PTR_LAB_00d91b0c
    // Global flag indicating pool is destroyed
    g_poolDestroyed = 0;   // DAT_01129934
}