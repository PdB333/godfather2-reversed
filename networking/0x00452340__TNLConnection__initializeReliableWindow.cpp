// FUNC_NAME: TNLConnection::initializeReliableWindow

// Structure for each reliable packet window slot (40 bytes each, 32 slots)
struct TNLReliablePacketSlot {
    byte   mActive;      // +0x00  (set to 1 during init)
    byte   _pad1[19];    // +0x01
    int    mSequence;    // +0x14 (offset 20)
    int    mAck;         // +0x18 (offset 24)
    int    mData;        // +0x1C (offset 28) - points to slot data
    int    mSize;        // +0x20 (offset 32)
    byte   mFlags;       // +0x24 (offset 36)
    byte   _pad2[3];     // +0x25 to +0x27 (pads to 40 bytes)
};

// Initializes the 32-slot reliable packet window
// param_1: this pointer (TNLConnection)
int __thiscall TNLConnection_initializeReliableWindow(int this)
{
    TNLReliablePacketSlot *pSlot;
    int i;

    i = 31;                                    // 32 slots (0x1f to 0 inclusive)
    pSlot = (TNLReliablePacketSlot *)(this + 0x1C); // start of the slot array

    do {
        pSlot->mActive = 1;                    // set active flag at struct start
        FUN_004d9500(0);                      // likely a system call (e.g., memset)
        pSlot->mSequence = 0;                 // zero out slot fields
        pSlot->mAck = 0;
        pSlot->mData = 0;
        pSlot->mSize = 0;
        pSlot->mFlags = 0;
        pSlot++;                              // advance to next slot (40 bytes)
        i--;
    } while (i >= 0);

    *(int *)(this + 0x500) = 0;              // clear reliable window count/status after the array
    return this;
}