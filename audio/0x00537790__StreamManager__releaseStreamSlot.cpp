// FUNC_NAME: StreamManager::releaseStreamSlot
// Address: 0x00537790
// Role: Releases a stream slot resource by its slot index. Handles state checks, flags update, and deferred freeing.

// Constants for slot state and flags
#define STREAM_SLOT_MAX       0x1000
#define STREAM_SLOT_SIZE      0x38
#define STREAM_STATE_MASK     0x03
#define FLAG_DELETE_PENDING   0x200000
#define FLAG_CLEAR_MASK       0xfcac8fff // clears bits 19-22, 23? actually keeps other flags

// Global array of stream slot structures at 0x011a0f28
// Each slot: byte state at +0x00, uint32 flags at +0x0C, int* pData at +0x1C
// Unknown padding between offsets.

extern uint8_t g_streamSlotArray[STREAM_SLOT_MAX * STREAM_SLOT_SIZE]; // base address 0x011a0f28

// Global pointer used to check some deferred delete queue: 0x0121b0ac + 4
extern int* g_deferredDeleteQueue;

// Helper functions (reverse-engineered names)
void releaseResourceData(int* pData, uint32 flags); // FUN_00606e60 - frees resource data with flags
void notifySlotStateChange();                        // FUN_006189c0 - triggers callback on slot change
void flushDeferredDeleteQueue();                     // FUN_006063b0 - processes pending deletions

void releaseStreamSlot(uint resourceId)
{
    // For resourceId == 0, just flush deferred deletes and return.
    if (resourceId == 0)
    {
        if (g_deferredDeleteQueue[1] != 0)
            flushDeferredDeleteQueue();
        return;
    }

    uint8_t* slotBase;
    if (resourceId < STREAM_SLOT_MAX)
    {
        slotBase = g_streamSlotArray + resourceId * STREAM_SLOT_SIZE;
    }
    else
    {
        slotBase = nullptr;
    }

    uint32 prevFlags = *(uint32*)(slotBase + 0x0C); // store current flags

    // Inner check: valid resource and state < 4 (e.g., not already freed)
    if (resourceId != 0xFFFFFFFF && resourceId < STREAM_SLOT_MAX)
    {
        uint8_t* slotBase2 = g_streamSlotArray + resourceId * STREAM_SLOT_SIZE;
        if (slotBase2 != nullptr && (*slotBase2 & STREAM_STATE_MASK) < 4)
        {
            int* pData = *(int**)(slotBase2 + 0x1C);
            if (pData != nullptr)
                releaseResourceData(pData, FLAG_DELETE_PENDING);

            // Update flags: clear certain bits, set delete pending flag
            uint32 newFlags = (*(uint32*)(slotBase2 + 0x0C) & FLAG_CLEAR_MASK) | FLAG_DELETE_PENDING;
            *(uint32*)(slotBase2 + 0x0C) = newFlags;

            notifySlotStateChange();
        }
    }

    // After possible flag update, flush deferred delete queue if needed
    if (g_deferredDeleteQueue[1] != 0)
        flushDeferredDeleteQueue();

    // Call release with resourceId and its previous flags (possibly for ref counting)
    releaseResourceData(resourceId, prevFlags);
}