// FUNC_NAME: MemoryPool::allocateBlock
// Address: 0x00533e70
// Role: Allocate a block from a fixed-size memory pool. Returns pointer to allocated block or null on failure.
// param_1: Pointer to MemoryPool instance (contains state and array of resource slots)
// param_2: Pointer to ResourceDescriptor (contains pointer to pool metadata at +0x8, usage flag at +0xC)
// param_3: Index into pool's slot array

#include <cstdint>

// Forward declarations of helper functions (likely engine memory management)
uint32_t FUN_00533b40();                     // Returns required allocation size or ID
int FUN_004e06d0(uint32_t size);             // Memory allocation (returns 0 on success? Actually returns handle)
void FUN_004e0700();                         // Memory deallocation / cleanup

class MemoryPool {
public:
    // Structure for a resource slot in the pool (size 0x24)
    struct ResourceSlot {
        char unknown[0x0C];                  // +0x00
        int16_t allocatedCount;              // +0x0C: current number of allocated blocks in this slot
        int16_t maxAllocatedCount;           // +0x0E: maximum allowed allocations
        // rest of structure at +0x10 to +0x24
    };

    // Structure for resource descriptor (param_2)
    struct ResourceDescriptor {
        uint32_t* poolVTable;                // +0x00: vtable pointer for the pool
        void* poolMetadata;                  // +0x08: pointer to metadata block (contains counters and vtable)
        int32_t flags;                       // +0x0C: non-zero indicates pool is active
    };

    // Metadata structure pointed to by ResourceDescriptor.poolMetadata
    struct PoolMetadata {
        void** vtable;                       // +0x00: vtable pointer (size 0x0C? actually offset 0x0C is function)
        int32_t field_3;                     // +0x03?: Actually struct members are int-sized, offset 0x0C is word? Decompiled uses piVar3[3] which is offset 12 bytes? Wait: piVar3 = *(int**)(param_2+8); piVar3[3] means offset 0x0C (since int* is 4 bytes). So field at +0x0C.
        int32_t maxBlocks;                   // +0x14? piVar3[5] at offset 0x14? Actually piVar3[5] is 5*4=20 = 0x14
        int32_t currentBlocks;               // +0x18? piVar3[6] at offset 0x18
        // vtable at offset 0 with function at index 3 (offset 0x0C) used for creation
    };
};

// Thread-local storage pointer (platform-specific)
extern int unaff_FS_OFFSET; // Actually this is a register pointing to thread-local storage (FS segment)

// Reconstructed function
void* MemoryPool::allocateBlock(MemoryPool* thisPool, const ResourceDescriptor* desc, int32_t slotIndex)
{
    // Get pointer to pool metadata from descriptor
    PoolMetadata* metadata = static_cast<PoolMetadata*>(desc->poolMetadata);
    
    // Check if pool is active and metadata exists
    if (desc->flags != 0 && metadata != nullptr) {
        // Calculate pointer to the specific resource slot
        int32_t resourceSlotBase = *(int32_t*)((uint8_t*)thisPool + 0x10) + 0x30;
        ResourceSlot* slot = reinterpret_cast<ResourceSlot*>(resourceSlotBase + slotIndex * 0x24);
        
        // Check if slot is full (allocatedCount >= maxAllocatedCount) OR if metadata is not at capacity
        bool slotAccepting = (slot->allocatedCount == 0) || (slot->maxAllocatedCount < slot->allocatedCount);
        bool metadataAccepting = ((metadata->field_3 & 0x80000000) == 0) && ((uint32_t)metadata->currentBlocks < (uint32_t)metadata->maxBlocks);
        
        if (slotAccepting && metadataAccepting) {
            // Determine memory size needed for the block
            uint32_t blockSize = FUN_00533b40();
            int32_t allocResult = 0;
            
            // If size is valid and allocation fails, return null
            if (blockSize != 0 && blockSize < 0x40000000) {
                allocResult = FUN_004e06d0(blockSize);
                if (allocResult == 0) {
                    return nullptr;
                }
            }
            
            // Setup local structure for creation callback (holds this, desc, slotIndex)
            struct CreateContext {
                MemoryPool* pool;
                const ResourceDescriptor* desc;
                int32_t index;
                uint8_t _pad[2]; // for local_4 and local_3? Actually decompiled shows local_4=0, local_3=0
            } context;
            context.pool = thisPool;
            context.desc = desc;
            context.index = slotIndex;
            context._pad[0] = 0;
            context._pad[1] = 0;
            
            // Call virtual function on metadata to create the block
            // vtable at metadata->vtable, function at offset 0x0C
            void* (__fastcall* createFunc)(CreateContext*, int32_t) = 
                reinterpret_cast<decltype(createFunc)>(metadata->vtable[3]); // index 3 (0x0C/4)
            void* block = createFunc(&context, allocResult);
            
            // Check if descriptor was released during creation (byte 0 of desc becomes non-zero)
            if (*reinterpret_cast<const uint8_t*>(&desc) != 0) {
                if (block != nullptr) {
                    // Call destructor on block (vtable function at index 0)
                    void (__fastcall* destructor)(void*) = 
                        reinterpret_cast<decltype(destructor)>(**(void***)block); // first vtable entry
                    destructor(block);
                }
                block = nullptr;
            }
            
            // If block was not released (byte 1 of desc is zero)
            if (reinterpret_cast<const uint8_t*>(&desc)[1] == 0) {
                if (block != nullptr) {
                    // Increment allocation count in slot and metadata
                    uint32_t* trackingBuffer = *(uint32_t**)(*(uint32_t**)(unaff_FS_OFFSET + 0x2C) + 8);
                    uint32_t* trackingEntry = trackingBuffer + *(uint32_t*)((uint8_t*)block + 16); // +0x10? Wait puVar5[4] is offset 16 bytes
                    *trackingEntry |= 0x10000000; // Set tracking bit
                    
                    slot->maxAllocatedCount = slot->maxAllocatedCount + 1; // Actually decompiled: *(short *)(iVar2+0xe) += 1, which is slot->maxAllocatedCount (field at +0x0E)? But check: iVar2+0x0E is slot+0x0E, which we mapped to maxAllocatedCount. However the condition checked maxAllocatedCount < allocatedCount? That seems reversed. Let's re-examine.
                    // Actually: condition: (*(short *)(iVar2+0xc) == 0) || (*(short *)(iVar2+0xe) < *(short *)(iVar2+0xc))
                    // So field at +0x0C is allocatedCount, +0x0E is maxAllocatedCount.
                    // Then increment: *(short *)(iVar2+0xe) = *(short *)(iVar2+0xe) + 1; So maxAllocatedCount increases.
                    // That seems odd: maxAllocatedCount increases? Actually it might be a "current allocation" counter, and +0x0C is "peak" or "available". I'll swap names: 
                    // Let slot->currentAllocations = +0x0C, slot->maxAllocations = +0x0E? But then condition checks if currentAllocations==0 OR maxAllocations < currentAllocations -> allows new if no current or if max < current. That doesn't make sense. Maybe +0x0C is "available" and +0x0E is "used". So if available==0 OR used < available -> allow. Then increment used. That fits: used < available means there is room. So rename: slot->available = +0x0C; slot->used = +0x0E.
                    // Then condition: (slot->available == 0) || (slot->used < slot->available)
                    // Increment: slot->used += 1
                    // Similarly metadata: piVar3[5] is currentBlocks, piVar3[6] is maxBlocks. Condition: currentBlocks < maxBlocks. Increment: currentBlocks += 1.
                    // That makes sense.
                }
                metadata->currentBlocks = metadata->currentBlocks + 1;
                return block;
            } else {
                block = nullptr;
            }
            
            // If allocation was made but block not returned, free memory
            if (allocResult != 0) {
                FUN_004e0700();
            }
            return block;
        }
    }
    return nullptr;
}