// FUNC_NAME: PacketPool::allocatePacket
struct PacketBlock {
    PacketBlock* next;           // +0x00
    uint32_t unk04;              // +0x04
    uint32_t bufferSize;         // +0x08
    uint32_t unk0C;              // +0x0C
    uint32_t unk10;              // +0x10
    uint32_t unk14;              // +0x14
    uint32_t requestedUnits;     // +0x18 (param_1 stored here)
    void* dataBuffer;            // +0x1C (allocated memory)
    uint32_t allocatedSize;      // +0x20 (actual size = requestedUnits*2)
    void* userData;              // +0x24 (param_2, possibly extra data)
    uint8_t  flags0;             // +0x28 (byte)
    uint8_t  flags1;             // +0x29 (byte, e.g. in-use flag)
    uint32_t unk2C;              // +0x2C (self pointer or 0)
    uint32_t external;           // +0x30 (some external value based on size)
};

// Global variables
extern int g_poolEnabledFlag;       // DAT_00f15a3a
extern CRITICAL_SECTION g_poolCS;   // DAT_012224f8
extern PacketBlock* g_poolHead;     // DAT_012224e0
extern int* g_memAllocator;         // DAT_01205868 (vtable pointer)
extern int g_poolCount;             // DAT_01205854
extern PacketBlock* g_poolArray[];  // DAT_011e28f0
extern uint32_t DAT_00e39f98;
extern uint32_t DAT_00e44658;

PacketBlock* PacketPool::allocatePacket(int requestedUnits, void* data, PacketBlock* outBlock, int typeId)
{
    uint actualSize = requestedUnits * 2;  // Total bytes to allocate
    bool reuseFound = false;

    if (g_poolEnabledFlag != 0) {
        EnterCriticalSection(&g_poolCS);
        PacketBlock* block = g_poolHead;
        if (block != nullptr) {
            do {
                PacketBlock* current = block->next;
                // Check if block is free, has matching type, and fits size constraints
                if ( (current->flags1 != 0) || (current->userData != (void*)typeId) ||
                     (current->allocatedSize < actualSize) ||
                     ((uint)(requestedUnits * 8) / 3 <= current->allocatedSize) )
                {
                    block = current;
                    continue;
                }
                // Block is reusable
                reuseFound = true;
                block = current;
                if (outBlock != nullptr) {
                    // Copy block header into outBlock (13 dwords)
                    uint32_t savedUnk2C = outBlock[0xB];  // We'll restore later
                    for (int i = 0; i < 13; i++) {
                        outBlock[i] = block->next[i];     // undefined4 copy loop
                    }
                    outBlock[0xB] = savedUnk2C;            // restore original?

                    // Handle child pointer at offset +0x2C
                    PacketBlock* child = (PacketBlock*)block->next[0xB];
                    if (child != nullptr) {
                        if (g_memAllocator != nullptr) {
                            (*(void (**)(void*, int))(*(int*)g_memAllocator))(child, 0);
                        }
                        if (block != child) {
                            block->next[0xB] = 0;
                        }
                    }
                }
                if (data != nullptr) {
                    void* dest = FUN_0060c760(block);   // Get writable data pointer from block
                    memcpy(dest, data, actualSize);
                    FUN_0060c7a0(block);                // Unlock/finalize?
                }
                FUN_0060d3f0();                         // Some pool maintenance?
                outBlock = block;
                break;
            } while (block != nullptr);
        }
        LeaveCriticalSection(&g_poolCS);
        if (reuseFound) goto done;
    }

    // No suitable block found -> allocate new one
    if (outBlock == nullptr) {
        outBlock = (PacketBlock*)(**(code**)(*g_memAllocator))(0x40, &local_18);
        outBlock[0xB] = outBlock;   // Self-pointer
    } else {
        outBlock[0xB] = 0;
    }

    outBlock->requestedUnits = requestedUnits;
    outBlock->allocatedSize = actualSize;
    // Allocate data buffer
    outBlock->dataBuffer = (void*)(**(code**)(*g_memAllocator))(actualSize, &stack_var);
    if (unaff_retaddr != nullptr) {   // Register-based data copy (compiler optimization)
        memcpy(outBlock->dataBuffer, unaff_retaddr, actualSize);
    }
    outBlock->userData = data;
    outBlock->flags0 = 0;
    outBlock->flags1 = 0;

    EnterCriticalSection(&g_poolCS);
    g_poolArray[g_poolCount++] = outBlock;
    LeaveCriticalSection(&g_poolCS);

done:
    if (actualSize > 0x10000) {
        outBlock->external = DAT_00e39f98;
    } else {
        outBlock->external = DAT_00e44658;
    }
    return outBlock;
}