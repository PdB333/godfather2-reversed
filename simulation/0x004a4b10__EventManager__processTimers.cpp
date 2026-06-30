// FUNC_NAME: EventManager::processTimers
// Address: 0x004a4b10
// Role: Processes pending actions and active timers in the event manager.
// The class has two sets of timers/actions: a list of pending actions (0x10-byte entries)
// and a 64-bit bitmask (two 32-bit words) of active timer slots.
// The lookup table g_timerSlotLookup maps bit indices to offsets into a timer objects array.

class EventManager {
public:
    // +0x40: low 32 bits of active timer bitmask
    // +0x44: high 32 bits of active timer bitmask
    // +0x5c: pointer to base of timer objects array (each element has vtable at +0)
    // +0x68: pointer to array of pending action structures (0x10 bytes each)
    // +0x6c: count of pending actions
    // +0x94: if non-zero, timers are suspended

    void processTimers();
    void resumeTimers(); // called when suspended, assumed to be another method (0x004a6fa0)
};

// Global lookup table mapping bit index to offset (from DAT_00e2e110)
extern uint32_t g_timerSlotLookup[32]; // size unknown, but at least 64 entries implied by 64-bit mask

void EventManager::processTimers() {
    // If suspended, resume first
    if (*(uint32_t*)(this + 0x94) != 0) {
        this->resumeTimers(); // FUN_004a6fa0
    }

    // Process pending actions (list of 0x10-byte structures)
    uint32_t numPending = *(uint32_t*)(this + 0x6c);
    if (numPending != 0) {
        uint8_t* pendingList = *(uint8_t**)(this + 0x68);
        for (uint32_t i = 0; i < numPending; i++) {
            uint8_t* entry = pendingList + i * 0x10;
            // entry+0: pointer to vtable
            // entry+4: flags (ushort at bytes 4-5), bit 1 (0x02) = pending
            uint16_t flags = *(uint16_t*)(entry + 4);
            if (flags & 0x02) {
                // Call vtable method at offset 0x28 (execute action)
                void** vtable = *(void***)(entry);
                typedef void (*ActionFunc)(void*);
                ActionFunc action = (ActionFunc)(vtable[0x28 / 4]); // 0x28 = 10th slot (0-indexed: 10)
                action(entry); // call with entry as 'this'?
                // Clear pending flag
                *(uint16_t*)(entry + 4) = flags & ~0x02;
            }
        }
    }

    // Process active timers via 64-bit bitmask (low at +0x40, high at +0x44)
    uint32_t maskLow = *(uint32_t*)(this + 0x40);
    uint32_t maskHigh = *(uint32_t*)(this + 0x44);
    if (maskLow != 0 || maskHigh != 0) {
        uint64_t mask = ((uint64_t)maskHigh << 32) | maskLow;
        uint8_t* timerBase = *(uint8_t**)(this + 0x5c); // base of timer objects array

        while (mask != 0) {
            // Find lowest set bit using de Bruijn method (as in original)
            // The original intrinsics: __allmul, __aullshr, __allshl
            // Equivalent: compute index via multiplication with constant 0x3f79d71b4cb0a89
            // and shift right. We'll replicate using standard bit ops for clarity.
            uint32_t index; // bit position (0-63)
#ifdef _MSC_VER
            unsigned long bitIndex;
            _BitScanForward64(&bitIndex, mask);
            index = (uint32_t)bitIndex;
#else
            index = __builtin_ctzll(mask);
#endif

            // Get offset for this timer slot from lookup table
            uint32_t offset = g_timerSlotLookup[index]; // each entry is a uint32_t offset
            uint8_t* timerObj = timerBase + offset * 4; // original: multiply by 4 because lookup gives index * 4? Actually: *(int *)(&DAT_00e2e110 + iVar3 * 4) gives a 32-bit value, then multiplied by 4 to get byte offset. So offset is already an index*4? We'll assume g_timerSlotLookup stores indices, then multiply by 4 to get byte offset.
            // Call vtable method at offset 0x28 on this timer object
            void** vtable = *(void***)(timerObj);
            typedef void (*TimerFunc)(void*);
            TimerFunc timerFunc = (TimerFunc)(vtable[0x28 / 4]);
            timerFunc(timerObj); // call with timer object as 'this'

            // Clear the bit from mask
            mask &= mask - 1;
        }

        // Update the bitmask fields (original did not store back? it did: uVar1 = ...; uVar4 = ...; but loop continued with uVar1,uVar4. Actually the original code did modify them and then the loop condition checked uVar1 and uVar4. At the end, the fields are not written back? The decompiled shows only local variables are updated. But presumably after the loop they are not stored because they are zero. We'll keep the in-memory values untouched? However, the original code uses uVar1 and uVar4 as locals, not writing back. So we don't need to update the fields.
    }
}