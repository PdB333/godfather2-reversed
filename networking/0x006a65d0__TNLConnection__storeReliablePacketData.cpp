// FUNC_NAME: TNLConnection::storeReliablePacketData
// Address: 0x006a65d0
// This function finds an empty slot in the reliable packet send window (0x20 slots of 0x18 bytes each)
// and stores the current packet data (sequence number + 16-byte payload) into it.
// Returns immediately after storing.

void __fastcall TNLConnection::storeReliablePacketData(TNLConnection* this)
{
    int slotIndex;
    int* slotFlagPtr;
    int iVar4;
    int local_8[2];
    
    iVar4 = 0;
    slotFlagPtr = (int*)(this + 0x6bc); // Pointer to first slot's flag field (slot[0].flag)
    
    do {
        if (*slotFlagPtr == 0) { // Slot is empty (flag == 0)
            // Slot base address
            int slotBase = (int)this + iVar4 * 0x18;
            
            // Copy 4-byte sequence number from this+0x6a4 to slot+0x00
            *(int*)(slotBase + 0x6bc) = *(int*)(this + 0x6a4);
            
            // Copy 16-byte data from this+0x6a8 to slot+0x04
            // Slot data offset: (iVar4*3 + 0xd8) * 8 = iVar4*24 + 0x6C0 = slotBase+0x6BC + 4
            undefined8* dest = (undefined8*)(this + (iVar4 * 3 + 0xd8) * 8);
            dest[0] = *(undefined8*)(this + 0x6a8);
            dest[1] = *(undefined8*)(this + 0x6b0);
            
            // Prepare local buffer (could be for processing)
            local_8[0] = 0;
            local_8[1] = 0;
            
            // Call pack/process function on the 4-byte value, returning a status byte
            byte status = FUN_006a62a0(*(int*)(this + 0x6a4), local_8, 0, 0);
            
            // Store status byte at slot offset 0x14 (slotBase+0x6D0)
            *(byte*)(slotBase + 0x6d0) = status;
            
            // If local_8[0] indicates an allocated buffer, free it
            if (local_8[0] != 0) {
                FUN_004daf90(local_8);
            }
            return;
        }
        iVar4++;
        slotFlagPtr += 6; // Advance to next slot (6 ints = 0x18 bytes)
    } while (iVar4 < 0x20);
    
    // If no empty slot found, simply return (packet dropped?).
    return;
}