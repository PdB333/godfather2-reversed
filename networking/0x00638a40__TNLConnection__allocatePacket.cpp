// FUNC_NAME: TNLConnection::allocatePacket

class TNLConnection
{
public:
    struct PacketManager
    {
        uint32_t mPacketHead; // +0x10
        uint32_t mTotalAllocated; // +0x24
        uint32_t mCounter; // +0x38
    };

    PacketManager* mPacketManager; // offset 0x10

    // Allocates a packet with payload size param_1 and enqueues it into the free list
    void allocatePacket(int payloadSize);
};

void __thiscall TNLConnection::allocatePacket(int payloadSize)
{
    uint32_t allocSize = payloadSize + 0x10;
    PacketHeader* newPacket = nullptr;

    if (allocSize == 0)
    {
        newPacket = nullptr;
    }
    else
    {
        if (allocSize < 0xFFFFFFFD) // Guard against overflow
        {
            // Custom allocator (likely TNL pool)
            newPacket = (PacketHeader*)(*DAT_012059dc)(0, allocSize);
            if (newPacket == nullptr)
            {
                if (this != nullptr)
                {
                    // Error handling - cleanup
                    FUN_00635a80();
                    return;
                }
                // If this is null, still return null
                newPacket = nullptr;
            }
        }
        else
        {
            // Overflow error
            FUN_00633920();
        }

        if (this != nullptr)
        {
            // Update total allocated size
            PacketManager* mgr = this->mPacketManager;
            mgr->mTotalAllocated += allocSize;
        }
    }

    // Fill packet header
    newPacket->payloadSize = payloadSize; // offset +0x0C (4*3)
    newPacket->type = 2; // offset +0x05
    newPacket->subType = 7; // offset +0x04
    newPacket->someCounter = mgr->mCounter; // offset +0x08 (2*4)
    newPacket->prev = mgr->mPacketHead; // offset +0x00 (head)
    // Link into list
    mgr->mPacketHead = newPacket; // offset +0x10
}