// FUNC_NAME: PacketBuffer::reserveSlots
// Function address: 0x006254f0
// Role: Allocate space for a number of 8-byte slots in a packet buffer.
// Checks against max slot count (0x4000 = 16384) and grows buffer if needed.
// Tracks the maximum write position via an external high-water mark.

class PacketBuffer
{
public:
    // +0x08: current write pointer
    // +0x0C: base/start pointer of allocated memory
    // +0x14: pointer to an external struct with max usage at offset +4
    // +0x18: capacity pointer (end of allocated memory)
    
    bool __thiscall reserveSlots(int count)
    {
        // current number of slots used
        int usedSlots = (*(int*)(this + 0x08) - *(int*)(this + 0x0C)) >> 3;
        
        // Check if adding 'count' slots would exceed the maximum allowed (16384 slots)
        if (0x4000 < usedSlots + count)
            return false;
        
        // Check if remaining space is sufficient (each slot = 8 bytes)
        if (*(int*)(this + 0x18) - *(int*)(this + 0x08) <= count * 8)
        {
            // Not enough space – grow the buffer
            FUN_00635c70();
        }
        
        // Advance write pointer
        uint newPos = *(int*)(this + 0x08) + count * 8;
        *(int*)(this + 0x08) = newPos;
        
        // Update the high-water mark if this is the furthest we've written
        uint* maxUsagePtr = (uint*)(*(int*)(this + 0x14) + 4);
        if (*maxUsagePtr < newPos)
        {
            *maxUsagePtr = newPos;
        }
        
        return true;
    }
};