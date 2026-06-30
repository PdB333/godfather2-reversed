// FUNC_NAME: PacketSlotManager::releaseSlotsAndAllocateEvent

#include <windows.h> // For CRITICAL_SECTION, LARGE_INTEGER, QueryPerformanceCounter

// Constants
#define MAX_SLOTS 0x1000
#define SLOT_DESCRIPTOR_SIZE 0x38

// State bytes for slot descriptors
enum SlotState : char {
	SLOT_STATE_UNUSED = 0,
	SLOT_STATE_ACTIVE = 2,   // Currently in use
	SLOT_STATE_RELEASING = 3, // Being released
	SLOT_STATE_FREE = 5      // Fully free
};

// Slot descriptor structure (size 0x38 bytes)
struct SlotDescriptor {
	char state;          // +0x00: see SlotState
	char pad1[0x37];     // Padding to 0x38 (actual fields unknown)
};

// Global data (offsets from Ghidra)
// DAT_011d8f28, DAT_011d8f2c: 64-bit bitmap per chunk (64 chunks for 4096 slots)
static uint32 g_freeSlotBitmapLow[64];   // Low 32 bits of each 64-bit chunk mask
static uint32 g_freeSlotBitmapHigh[64];  // High 32 bits of each 64-bit chunk mask
static int g_nextFreeChunk = 0;          // DAT_011d9128: first chunk that might be empty
static CRITICAL_SECTION* g_pSlotCriticalSection = (CRITICAL_SECTION*)0x011d917c; // Critical section for bitmap access

// Slot descriptor array at DAT_011a0f28
static SlotDescriptor g_slotDescriptors[MAX_SLOTS];

// Allocation counters and performance timestamps
static int g_eventAllocationCount = 0;    // DAT_01222570
static void* g_lastPerfCounterLow = 0;    // DAT_01205930
static void* g_lastPerfCounterHigh = 0;   // DAT_01205934

// Forward declarations for internal functions
// FUN_006157d0: Allocates an event structure (retuns pointer to 6-uint32 block)
static void* allocateEventBlock();
// FUN_00ab4db0: Acquires some lock (maybe another critical section)
static void acquireEventLock(void* param);
// FUN_00ab4e70, FUN_00ab51e0, FUN_00ab67c0: Notification or scheduling helpers
static void releaseEventLock();
static void scheduleEventProcessing(int flag);
static void notifyEventAllocated();

// Helper to clear a slot in the free bitmap
static void clearSlotInBitmap(uint slotIndex) {
	uint chunkIdx = slotIndex >> 6;
	uint bitIdx = slotIndex & 0x3F;
	uint64_t mask = 1ULL << bitIdx; // 64-bit shift (__allshl equivalent)
	uint32 lowMask = (uint32)mask;
	uint32 highMask = (uint32)(mask >> 32);

	EnterCriticalSection(g_pSlotCriticalSection);

	g_freeSlotBitmapLow[chunkIdx] &= ~lowMask;
	g_freeSlotBitmapHigh[chunkIdx] &= ~highMask;

	// If the chunk became completely empty and it's the current next-free, advance
	if (chunkIdx == g_nextFreeChunk &&
		g_freeSlotBitmapLow[chunkIdx] == 0 &&
		g_freeSlotBitmapHigh[chunkIdx] == 0) {
		g_nextFreeChunk++;
	}

	LeaveCriticalSection(g_pSlotCriticalSection);
}

// Main function: releases two slots (slot1 and slot2) and allocates a new event.
// param2 is an additional parameter stored in the event.
void* PacketSlotManager::releaseSlotsAndAllocateEvent(uint slotIndex1, uint slotIndex2, uint param2) {
	SlotDescriptor* desc1 = nullptr;
	SlotDescriptor* desc2 = nullptr;

	// Validate and get descriptor for slot1
	if (slotIndex1 < MAX_SLOTS) {
		desc1 = &g_slotDescriptors[slotIndex1];
	} else {
		desc1 = nullptr;
	}

	// Check if slot1 state allows release
	if (desc1 && (desc1->state == SLOT_STATE_ACTIVE || desc1->state == SLOT_STATE_RELEASING)) {
		// Only proceed if state is exactly SLOT_STATE_RELEASING (0x03)
		if (desc1->state == SLOT_STATE_RELEASING) {
			// --- Release slot1 ---
			clearSlotInBitmap(slotIndex1);
			desc1->state = SLOT_STATE_FREE;

			// --- Release slot2 (from register EDI, passed as slotIndex2) ---
			// Get descriptor for slot2
			if (slotIndex2 < MAX_SLOTS) {
				desc2 = &g_slotDescriptors[slotIndex2];
			} else {
				desc2 = nullptr;
			}
			if (desc2) {
				clearSlotInBitmap(slotIndex2);
				desc2->state = SLOT_STATE_FREE;
			} else {
				// If slot2 index was out of range, still need to mark it? 
				// Original code does nothing if desc2 was null? Actually it will recompute from slotIndex2 and set state=5.
				// But desc2 would be null, so we skip bitmap clear (as in original: if pointer is null, it recalculates from unaff_EDI but still clears bit? 
				// The original code after the if block sets *local_c = 5 regardless, but if pointer was null it recalculates local_c from unaff_EDI (which yields null again if >=0x1000). 
				// This is likely a bug in decompilation; we'll assume valid slot2 index. 
			}

			// --- Allocate a new event block ---
			void* eventBlock = allocateEventBlock();
			if (!eventBlock) {
				return nullptr;
			}

			// Acquire event lock
			acquireEventLock(&DAT_00e2ac20); // DAT_00e2ac20 is probably a global event list

			// Populate event fields (offsets in 4-byte words)
			uint32* evt = (uint32*)eventBlock;
			evt[4] = slotIndex1;   // +0x10: first slot index
			evt[3] = slotIndex2;   // +0x0C: second slot index
			evt[5] = param2;       // +0x14: custom parameter
			evt[1] = 0;            // +0x04: unknown, cleared
			evt[0] = 2;            // +0x00: event type (maybe 2 = combined release)

			// Update allocation counter and timestamp
			if (g_eventAllocationCount == 0) {
				LARGE_INTEGER perfCounter;
				QueryPerformanceCounter(&perfCounter);
				g_lastPerfCounterLow = (void*)perfCounter.LowPart;
				g_lastPerfCounterHigh = (void*)perfCounter.HighPart;
			}
			g_eventAllocationCount++;

			// Finalize event registration
			releaseEventLock();
			scheduleEventProcessing(1);
			notifyEventAllocated();

			return eventBlock;
		}
		// If state was SLOT_STATE_ACTIVE, do nothing (only releasable if state 3)
	}
	return nullptr; // Failed conditions
}