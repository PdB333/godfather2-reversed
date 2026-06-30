// FUNC_NAME: NetConnection::initialize
// Reconstructed C++ for function at 0x006a6000 (constructor/initializer for networking connection)
// This function initializes a TNL-style connection object with packet window and queue arrays.
// Offsets documented below.

#include <cstdint>

// Forward declarations for external functions (not defined here)
void deallocateMemory(void* ptr);          // FUN_004daf90
void initBase();                           // FUN_006a5740 (base initialization)
void registerMemoryBlock(NetConnection* conn, void* table, uint32_t size); // FUN_00408900

class NetConnection {
public:
    // Offset +0x10: pointer to a global config/table (DAT_00d5d7b8)
    void* mConfigPointer;

    // +0x14, +0x18, +0x1c: counters or flags
    int mField14;
    int mField18;
    int mField1C;

    // +0x530, +0x534: appears to be head/tail of a queue? (written in loop with index -1)
    int mQueueHead;    // +0x530
    int mQueueTail;    // +0x534

    // +0x538: array of 8 pointers (or something) used as sentinel? See init loop.
    // Actually the loop starts at +0x53c, but references +0x538 via piVar5[-1]
    int mSomethingPrev[8]; // +0x538 (each 4 bytes)

    // +0x53c: array of 8 entries, each 0x28 (40) bytes
    // Each entry likely a packet queue entry with pointer and two ints
    struct PacketQueueEntry {
        void* mData;     // +0x00 (offset relative to entry)
        // ... (other fields not fully clear)
    } mPacketQueue[8];   // +0x53c, each 40 bytes

    // +0x558, +0x55c: perhaps indices or pointers into the queue, used with mCurrentId
    int mQueueIndexA[8];   // +0x558
    int mQueueIndexB[8];   // +0x55c

    // +0x678: current slot/index (set to -1)
    int mCurrentId;

    // +0x67c - +0x688: more counts/flags
    int mField67C;
    int mField680;
    int mField684;
    int mField688;

    // +0x68c: pointer to something (freed if non-zero)
    void* mPointer68C;

    // +0x694: another pointer to free
    void* mPointer694;

    // +0x69c: some constant (set to 6)
    int mVersion;

    // +0x6a0: flag
    int mField6A0;

    // +0x6a4: flag
    int mField6A4;

    // +0x6a8: flags or counters
    int mField6A8;
    int mField6AC;
    int mField6B0;

    // +0x6b4: copied from global DAT_00d5780c
    void* mGlobalPointer;

    // +0x6b8: flag
    int mField6B8;

    // +0x6c0: array of 32 slots, each 6 ints (24 bytes) – packet window slots
    struct PacketSlot {
        int field0;
        int field4;
        int field8;
        int fieldC;
        int field10;
        int field14;
    } mPacketSlots[32];   // +0x6c0, each 24 bytes

    // +0x9bc: byte flag (set to 1)
    uint8_t mFlag9BC;
};

void NetConnection::initialize() {
    // Set initial values
    this->mConfigPointer = (void*)DAT_00d5d7b8;
    this->mCurrentId = -1;                // +0x678
    this->mVersion = 6;                   // +0x69c
    this->mField6A0 = 0;
    this->mField6B8 = 0;
    this->mField14 = 0;
    this->mField18 = 0;
    this->mField1C = 0;

    // Initialize the packet queue (8 entries, each 0x28 bytes)
    // The loop variable iVar4=8, pointer piVar5 walks forward by 0x28 (10 ints)
    // piVar5 starts at &mPacketQueue[0].mData (which is at +0x53c)
    // piVar5[-1] refers to the preceding int at +0x538 (mSomethingPrev array entry)
    // Also sets two index fields using mCurrentId (which is -1) – writing to +0x530/+0x534 repeatedly
    int* piVar5 = &this->mPacketQueue[0].mData; // Actually points to first entry's first int
    for (int i = 0; i < 8; i++) {
        // Clear the preceding word (likely a linked list head)
        *(piVar5 - 1) = 0;   // writes to mSomethingPrev[i]

        // If current entry has a pointer, free it
        if (*piVar5 != 0) {
            deallocateMemory((void*)*piVar5);
            *piVar5 = 0;
        }

        // The next two lines write to offsets +0x558 and +0x55c indexed by mCurrentId (=-1)
        // Essentially writing to mQueueHead and mQueueTail (at +0x530 and +0x534) repeatedly
        // This might be setting the queue head/tail to zero for all slots? Or a bug in decomp?
        this->mQueueIndexA[this->mCurrentId] = 0;  // writes to *(this + 0x558 + mCurrentId*0x28)
        this->mQueueIndexB[this->mCurrentId] = 0;  // writes to *(this + 0x55c + mCurrentId*0x28)

        // Move to next entry (advance by 10 ints = 40 bytes)
        piVar5 += 10;
    }

    // Call base initialization (likely sets up vtable or other base members)
    initBase();

    // Initialize the packet window (32 slots, each 6 ints)
    // puVar2 starts at &mPacketSlots[0]
    int32_t* puVar2 = (int32_t*)this->mPacketSlots;
    for (int i = 0; i < 32; i++) {
        puVar2[-1] = 0;           // clear preceding word (maybe a flag)
        *(uint8_t*)(puVar2 + 4) = 0; // clear a byte (maybe state)
        puVar2[0] = 0;
        puVar2[1] = 0;
        puVar2[2] = 0;
        puVar2[3] = 0;
        puVar2[4] = 0;
        puVar2[5] = 0;
        // Move to next slot (6 ints = 24 bytes)
        puVar2 += 6;
    }

    // Set additional fields
    this->mField6A8 = 0;
    this->mField6AC = 0;
    this->mField6B0 = 0;
    this->mFlag9BC = 1;          // byte at +0x9bc
    this->mField6A4 = 0;
    this->mGlobalPointer = (void*)DAT_00d5780c;

    // Clear pointer fields
    this->mField67C = 0;
    this->mField680 = 0;
    this->mField684 = 0;
    this->mField688 = 0;

    // Free any existing allocated memory at +0x68c and +0x694
    if (this->mPointer68C != 0) {
        deallocateMemory(this->mPointer68C);
        this->mPointer68C = 0;
    }
    if (this->mPointer694 != 0) {
        deallocateMemory(this->mPointer694);
        this->mPointer694 = 0;
    }

    // Register memory blocks with global tables (size 0x8000 = 32KB)
    if (DAT_01206794 != 0) {
        registerMemoryBlock(this, &DAT_01206794, 0x8000);
    }
    if (DAT_0120678c != 0) {
        registerMemoryBlock(this, &DAT_0120678c, 0x8000);
    }
    if (DAT_01206780 != 0) {
        registerMemoryBlock(this, &DAT_01206780, 0x8000);
    }
    if (DAT_012067b4 != 0) {
        registerMemoryBlock(this, &DAT_012067b4, 0x8000);
    }
    if (DAT_012069c4 != 0) {
        registerMemoryBlock(this, &DAT_012069c4, 0x8000);
    }
}