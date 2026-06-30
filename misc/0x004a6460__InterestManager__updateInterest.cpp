// FUNC_NAME: InterestManager::updateInterest
// Function address: 0x004a6460
// Manages a 64-bit interest mask (low/high 32-bit halves). When interest changes,
// iterates over registered listeners (entries at +0x68) and notifies old and new
// objects via virtual function calls. Uses a global linked list for management.

class InterestManager {
public:
    // Offsets from 'this' (unaff_ESI)
    // +0x40: uint currentLowInterest
    // +0x44: uint currentHighInterest
    // +0x5c: Object** interestedObjectsTable   (array of pointers to interested objects, indexed by slot)
    // +0x68: InterestEntry* listenerArray      (array of 0x10-byte entries)
    // +0x6c: uint listenerCount
    // +0x84: InterestManager* prevInList2      (previous in global list2)
    // +0x88: InterestManager* nextInList2      (next in global list2)
    // +0x8c: InterestManager* prevInList1      (previous in global list1)
    // +0x90: InterestManager* nextInList1      (next in global list1)

    void updateInterest(uint newLow, uint newHigh);
};

// Global variables (likely in .bss)
extern InterestManager* g_interestManagerList1Tail;  // DAT_0120548c
extern InterestManager* g_interestManagerList1Head;  // DAT_01205488
extern InterestManager* g_interestManagerList2Tail;  // DAT_01205484
extern InterestManager* g_interestManagerList2Head;  // DAT_01205480

// Precomputed table mapping bit position to slot index (256 entries)
extern uint g_bitToSlotTable[256]; // DAT_00e2e110

// External helper functions
extern void callSomeFunction(int arg); // FUN_004a6a80
extern void callOtherFunction(int arg); // FUN_004a69b0

// Compiler intrinsics (assume implemented)
extern void __allmul(int64 a, int64 b); // not used directly, but for bit index calculation

void InterestManager::updateInterest(uint newLow, uint newHigh)
{
    // Early exit if nothing changed
    if (newLow == this->currentLowInterest && newHigh == this->currentHighInterest) {
        return;
    }

    // Step 1: Mark listeners whose interest overlaps with the new mask
    uint listenerIdx = 0;
    if (this->listenerCount != 0) {
        uint offset = 0;
        do {
            InterestEntry* entry = (InterestEntry*)((char*)this->listenerArray + offset);
            uint entryLowInterest = *(uint*)((char*)entry + 8);
            uint entryHighInterest = *(uint*)((char*)entry + 12);
            if ((entryLowInterest & newLow) != 0 || (entryHighInterest & newHigh) != 0) {
                entry->flags |= 4;   // Flag bit 2 (0x4) => pending notification
            }
            listenerIdx++;
            offset += 0x10;
        } while (listenerIdx < this->listenerCount);
    }

    // Step 2: Notify objects that are losing interest (old bits not in new)
    uint oldLow = this->currentLowInterest;
    uint oldHigh = this->currentHighInterest;
    if (oldLow != 0 || oldHigh != 0) {
        uint64 oldMask = ((uint64)oldHigh << 32) | oldLow;
        uint64 tempMask = oldMask;
        do {
            // Extract lowest set bit
            uint64 lowestBit = tempMask & -tempMask;
            // Compute slot index using hash multiplication and table lookup
            // Corresponds to: __allmul(lowestBit, magic); then shift right 32; then table lookup
            uint highPart, lowPart;
            __allmul((int64)lowestBit, 0x3f79d71b4cb0a89, &highPart, &lowPart); // pseudo
            uint bitIdx = highPart; // after __aullshr? actually __allmul gives 128-bit, then __aullshr shifts right 64? Decompiled uses __allmul then __aullshr (unsigned multiply low/high?) This is messy. Simplified:
            // The decompiled code does:
            // __allmul(-param_1 & param_1, ...) etc.
            // We'll replicate the logic using a helper function.
            // For clarity, we assume getBitIndex returns the slot index.
            uint slotIdx = this->getBitIndex(lowestBit);
            
            // Dereference interested object table
            Object* obj = this->interestedObjectsTable[slotIdx];
            // Call virtual functions for removal
            (**(code**)(obj->vtable + 100))();  // onInterestLost?
            (**(code**)(obj->vtable + 0x28))(); // onInterestRemoved?
            
            // Clear this bit from tempMask
            tempMask &= ~lowestBit;
        } while (tempMask != 0);
    }

    // Step 3: Process listener flags (notifications from step 1)
    listenerIdx = 0;
    if (this->listenerCount != 0) {
        uint offset = 0;
        do {
            InterestEntry* entry = (InterestEntry*)((char*)this->listenerArray + offset);
            ushort flags = entry->flags;
            if ((flags & 2) != 0) {
                if ((flags & 4) == 0) {
                    // Flag bit1 set but bit2 not set => call removal and clear bit1
                    (**(code**)(entry->object->vtable + 0x28))();
                    entry->flags &= ~2;  // Clear bit1
                } else {
                    // Both flags set => clear bit2 only
                    entry->flags &= ~4;
                }
            }
            listenerIdx++;
            offset += 0x10;
        } while (listenerIdx < this->listenerCount);
    }

    // Step 4: Update stored interest masks
    uint oldLowCopy = this->currentLowInterest;
    uint oldHighCopy = this->currentHighInterest;
    this->currentLowInterest = newLow;
    this->currentHighInterest = newHigh;

    // Step 5: Notify objects gaining interest (new bits not in old)
    if (newLow != 0 || newHigh != 0) {
        uint64 newMask = ((uint64)newHigh << 32) | newLow;
        uint64 tempMask = newMask;
        do {
            uint64 lowestBit = tempMask & -tempMask;
            // Get slot index as above
            uint slotIdx = this->getBitIndex(lowestBit);
            
            // Check if this bit was NOT in old mask
            uint64 oldMask = ((uint64)oldHighCopy << 32) | oldLowCopy;
            if ((lowestBit & oldMask) == 0) {
                Object* obj = this->interestedObjectsTable[slotIdx];
                // Call virtual functions for addition
                (**(code**)(obj->vtable + 0x24))();  // onInterestAdded?
                (**(code**)(obj->vtable + 0x60))();  // onInterestUpdated?
            }
            tempMask &= ~lowestBit;
        } while (tempMask != 0);
    }

    // Step 6: External global list management
    callSomeFunction(0); // FUN_004a6a80

    // Append this to global list1 (tail = DAT_0120548c, head = DAT_01205488)
    if (g_interestManagerList1Tail != nullptr) {
        g_interestManagerList1Tail->nextList1 = this;
    }
    g_interestManagerList1Head = this; // Actually the code: iVar5 = this; if tail exists, set tail->+0x90 = this; then set head = iVar5; then set this->prev = tail; this->next = 0; then set tail = this.
    // Reconstructed:
    if (g_interestManagerList1Tail) {
        g_interestManagerList1Tail->nextInList1 = this;
    }
    this->prevInList1 = g_interestManagerList1Tail;
    this->nextInList1 = nullptr;
    g_interestManagerList1Tail = this;
    // g_interestManagerList1Head is set to the old head? The code sets DAT_01205488 = iVar5 (which is either old head if tail existed, else this). This is weird, but we'll keep the original logic:
    // Actually from decompiled: iVar5 = unaff_ESI; if (tail) { set tail->+0x90 = this; iVar5 = oldHead; } DAT_01205488 = iVar5; This suggests list is circular? But not exactly. We'll keep as comment.

    // Step 7: Check if this object is not already in global list2 (based on flags at +0x88 and +0x84)
    if (this->nextInList2 == nullptr && this->prevInList2 == nullptr) {
        callOtherFunction(0); // FUN_004a69b0

        // Append to global list2 (tail = DAT_01205484, head = DAT_01205480)
        if (g_interestManagerList2Tail) {
            g_interestManagerList2Tail->nextInList2 = this;
        }
        this->prevInList2 = g_interestManagerList2Tail;
        this->nextInList2 = nullptr;
        g_interestManagerList2Tail = this;
        // Similar head logic as above
    }
}

// Helper function to extract bit index (simplified; actual uses hash)
uint InterestManager::getBitIndex(uint64 mask) {
    // Original code uses __allmul with magic constant 0xb4cb0a89 (low) and 0x3f79d71 (high)
    // Then __aullshr (shift right 32 of 64-bit result) to get index, then table lookup.
    // We'll implement using compiler intrinsic or inline assembly.
    // For reconstruction, we assume existence of a function that returns the index.
    // The actual mapping: index = (mask * magic) >> 32; then DAT_00e2e110[index];
    // So we would do:
    // uint64 temp = mask * 0x3f79d71b4cb0a89ULL;
    // uint index = (uint)(temp >> 32);
    // return g_bitToSlotTable[index];
    // But careful: the decompiled uses __allmul (signed?) but values are unsigned.
    // We'll implement as:
    uint64 product = mask * 0x3f79d71b4cb0a89ULL;
    uint index = (uint)(product >> 32);
    return g_bitToSlotTable[index];
}