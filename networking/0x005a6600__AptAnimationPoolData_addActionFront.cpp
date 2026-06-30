// Xbox PDB: AptAnimationPoolData::addActionFront
// FUNC_NAME: PacketBuffer::pushFront
// Address: 0x005a6600
// Likely part of the EARS networking queue system for packet buffering.
// Manages a circular buffer of 256 entries (0x14 bytes each) starting at g_queueBase.
// Pushes a new entry at the front (head - entrySize) with validation and optional processing.

// Global variables (inferred from decompiled constants)
extern uint8_t *g_queueBase;          // DAT_0119a9cc
extern uint32_t g_timestamp;          // DAT_012055ac – monotonically increasing timestamp or sequence number
extern uint32_t *g_nullPacketPtr;     // DAT_0119cbbc – sentinel value for packet pointer (likely 0)

// External functions (called within)
void handleQueueOverflow();           // FUN_0059bf00 – called when queue is full or wraps improperly
void processPacketHeader(uint32_t *packetPtr); // FUN_0059c230 – validates or processes packet header

// Offset constants (relative to g_queueBase)
const uint32_t ENTRY_SIZE = 0x14;                // 20 bytes per queue entry
const uint32_t HEAD_OFFSET = 0x1400;              // stores current head pointer (address of next free slot)
const uint32_t TAIL_OFFSET = 0x1404;              // stores tail pointer (last used slot)
const uint32_t BUFFER_SIZE = 0x1400;              // total buffer length (256 entries * 20)

// Entry field offsets (relative to entry address)
const uint32_t ENTRY_FLAGS      = 0x00;           // unknown, set to 0
const uint32_t ENTRY_TIMESTAMP  = 0x04;           // set to g_timestamp
const uint32_t ENTRY_PARAM1     = 0x08;           // user data pointer (param_1)
const uint32_t ENTRY_PARAM2     = 0x0C;           // packet pointer (param_2)

void PacketBuffer::pushFront(uint32_t userData, uint32_t *packetPtr)
{
    uint8_t *entryAddr;
    uint8_t *newHead;
    bool wrapOccurred;

    // Compute new head pointer by subtracting entry size from current head.
    // The buffer is circular; if we underflow below base, wrap to (base + BUFFER_SIZE - ENTRY_SIZE).
    newHead = *(uint8_t **)(g_queueBase + HEAD_OFFSET) - ENTRY_SIZE;
    if (newHead < g_queueBase) {
        newHead = g_queueBase + (BUFFER_SIZE - ENTRY_SIZE); // = g_queueBase + 0x13EC
    }

    // If the new head equals the tail, the queue is full – skip the push.
    if (newHead != *(uint8_t **)(g_queueBase + TAIL_OFFSET)) {
        // Check for wrap-around and call error handler if conditions are bad.
        wrapOccurred = (newHead < g_queueBase);
        entryAddr = newHead;
        *(uint8_t **)(g_queueBase + HEAD_OFFSET) = newHead; // update head pointer

        if (wrapOccurred) {
            handleQueueOverflow(); // Possible buffer wrap error
        }
        if ((uint8_t **)entryAddr <= (uint8_t **)*entryAddr) {
            handleQueueOverflow(); // Another sanity check
        }

        // Initialize the entry
        *(uint32_t *)(entryAddr + ENTRY_FLAGS) = 0;                // flags cleared
        *(uint32_t *)(entryAddr + ENTRY_PARAM1) = userData;       // store user data
        *(uint32_t **)(entryAddr + ENTRY_PARAM2) = packetPtr;     // store packet pointer

        // If packetPtr is not the sentinel null, examine its header.
        if (packetPtr != g_nullPacketPtr) {
            uint32_t packetType = *packetPtr & 0x7FFF; // lower 15 bits
            // Process the packet header unless it is a special type:
            // - type 0x19 (25)
            // - types 0x0B (11), 0x17 (23), 0x18 (24) when the high bit (0x8000) is set.
            if (packetType != 0x19) {
                bool highBitSet = ((*packetPtr >> 0xF) & 1) != 0;
                if (!highBitSet ||
                    (packetType != 0x0B && packetType != 0x18 && packetType != 0x17)) {
                    processPacketHeader(packetPtr);
                }
            }
        }

        // Store the global timestamp into the entry
        *(uint32_t *)(entryAddr + ENTRY_TIMESTAMP) = g_timestamp;
    }
    // If queue is full, the function does nothing (silent drop)
}