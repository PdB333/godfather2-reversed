// FUNC_NAME: Allocator::init
void __fastcall Allocator::init(int unused, uint32_t* poolBase)
{
    // Zero out header fields (7 words = 28 bytes)
    poolBase[0] = 0;            // header +0x00
    poolBase[1] = 0;            // header +0x04
    *(uint16_t*)(poolBase + 2) = 0; // header +0x08 (short)
    poolBase[4] = 0;            // header +0x10
    poolBase[5] = 0;            // header +0x14  - used as head pointer for large node chain
    poolBase[6] = 0;            // header +0x18

    // ---- Initialize large nodes (24 nodes, each 0xC18 words = 0x3060 bytes) ----
    const uint32_t LARGE_NODE_COUNT = 24;
    const int32_t LARGE_NODE_STRIDE = 0xC18;            // words between node bases
    const int32_t LARGE_NODE_BASE_OFF = 0x120A6;        // word offset from poolBase to first node's base

    uint32_t* nodeBase = poolBase + LARGE_NODE_BASE_OFF; // start at highest address

    for (int i = 0; i < LARGE_NODE_COUNT; i++)
    {
        // Level 0: offset -2 words from nodeBase (the "bottom" of the hierarchy)
        nodeBase[-2] = poolBase[5];          // link to previous node's level 5 pointer
        nodeBase[-1] = 0;
        nodeBase[ 0] = 0;
        nodeBase[ 1] = 0;

        // Level 1: offset -0x206
        nodeBase[-0x206] = (uint32_t)(nodeBase - 2);   // points back to level 0
        nodeBase[-0x205] = 0;
        nodeBase[-0x204] = 0;
        nodeBase[-0x203] = 0;

        // Level 2: offset -0x40A
        nodeBase[-0x40A] = (uint32_t)(nodeBase - 0x206);
        nodeBase[-0x409] = 0;
        nodeBase[-0x408] = 0;
        nodeBase[-0x407] = 0;

        // Level 3: offset -0x60E
        nodeBase[-0x60E] = (uint32_t)(nodeBase - 0x40A);
        nodeBase[-0x60D] = 0;
        nodeBase[-0x60C] = 0;
        nodeBase[-0x60B] = 0;

        // Level 4: offset -0x812
        nodeBase[-0x812] = (uint32_t)(nodeBase - 0x60E);
        nodeBase[-0x811] = 0;
        nodeBase[-0x810] = 0;
        nodeBase[-0x80F] = 0;

        // Level 5: offset -0xA16 (the "top" of the hierarchy)
        uint32_t* level5 = nodeBase - 0xA16;
        *level5 = (uint32_t)(nodeBase - 0x812);
        nodeBase[-0xA15] = 0;
        nodeBase[-0xA14] = 0;
        nodeBase[-0xA13] = 0;

        // Update the head pointer to this node's level 5 address
        poolBase[5] = (uint32_t)level5;

        // Move to the next node (backward in memory)
        nodeBase -= LARGE_NODE_STRIDE;
    }

    // ---- Initialize small nodes (144 nodes, each 8 words = 32 bytes) ----
    const uint32_t SMALL_NODE_COUNT = 144;
    const int32_t SMALL_NODE_START_OFF = 0x122AA; // word offset to first small node
    uint32_t* smallBase = poolBase + SMALL_NODE_START_OFF;

    for (int i = 0; i < SMALL_NODE_COUNT; i++)
    {
        // Zero out selected fields within the node (6 out of 8 words)
        smallBase[-2] = 0;   // offset -8 from current base
        smallBase[-1] = 0;   // offset -4
        smallBase[ 0] = 0;   // offset  0
        smallBase[ 1] = 0;   // offset +4
        smallBase[ 3] = 0;   // offset +12  (skipping word at index 2)
        smallBase[ 4] = 0;   // offset +16

        smallBase += 8;      // move to next node (8 words forward)
    }
}