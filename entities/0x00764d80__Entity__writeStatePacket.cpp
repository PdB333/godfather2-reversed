// FUNC_NAME: Entity::writeStatePacket
void __thiscall Entity::writeStatePacket(void* thisPtr, void* packetBuffer)
{
    // thisPtr: pointer to Entity object (size unknown, but fields at known offsets)
    // packetBuffer: pointer to output packet structure (type determined by vtable signature)
    uint** packetVTable = *(uint***)packetBuffer;
    uint packetType = (*packetVTable)(); // Call first vtable function to get type hash
    
    if (packetType == 0x3c52ffda) // Type A: position/transform update
    {
        // Copy transform data from this+0x54 (8 bytes: likely position or quaternion)
        *(ulonglong*)((uint*)packetBuffer + 0x16) = *(ulonglong*)((char*)thisPtr + 0x54);
        // Copy 4-byte field from this+0x5c
        *(uint*)((uint*)packetBuffer + 0x18) = *(uint*)((char*)thisPtr + 0x5c);
        // Set flag bit 3 (0x8) at offset 0x6C in packet
        *(uint*)((uint*)packetBuffer + 0x1b) |= 8;
        // Copy three 8-byte vectors (likely velocity, angular velocity, etc.)
        *(ulonglong*)((uint*)packetBuffer + 0x1c) = *(ulonglong*)((char*)thisPtr + 0x68);
        *(ulonglong*)((uint*)packetBuffer + 0x1e) = *(ulonglong*)((char*)thisPtr + 0x70);
        *(ulonglong*)((uint*)packetBuffer + 0x20) = *(ulonglong*)((char*)thisPtr + 0x78);
        // Copy 4-byte field from this+0x80 to packet offset 0x54
        *(uint*)((uint*)packetBuffer + 0x15) = *(uint*)((char*)thisPtr + 0x80);
    }
    else if (packetType == 0x6862a74c) // Type B: full state sync
    {
        // Construct 64-bit values using function addresses and data from this+0x50
        // These are likely function pointers combined with an object ID
        uint temp1; // Uninitialized, likely from stack or register
        uint temp2; // Uninitialized
        // Note: CONCAT44(a,b) = (a<<32) | b
        *(ulonglong*)((uint*)packetBuffer + 0x24) = CONCAT44((uint)FUN_0072f880, *(uint*)((char*)thisPtr + 0x50));
        *(ulonglong*)((uint*)packetBuffer + 0x26) = (ulonglong)temp1 << 0x20;
        *(ulonglong*)((uint*)packetBuffer + 0x28) = CONCAT44((uint)LAB_007648e0, temp2);
        *(ulonglong*)((uint*)packetBuffer + 0x1e) = CONCAT44((uint)FUN_007347e0, *(uint*)((char*)thisPtr + 0x50));
        *(ulonglong*)((uint*)packetBuffer + 0x20) = (ulonglong)temp1 << 0x20;
        *(ulonglong*)((uint*)packetBuffer + 0x22) = CONCAT44((uint)LAB_007648f0, temp2);
        
        // Check state flag at this+0x0c
        if (*(int*)((char*)thisPtr + 0x0c) == 1)
        {
            // Set flag bit 0 at packet offset 0xA8 (0x2a*4)
            *(uint*)((uint*)packetBuffer + 0x2a) |= 1;
            // Dereference this+0x50 to get pointer, then read at offset 0x24c4
            uint* ptr = *(uint**)((char*)thisPtr + 0x50);
            int val = (int)ptr[0x24c4 / 4]; // Equivalent to ptr[0x24c4 / 4] but careful: offset in bytes
            if (val != 0)
                val -= 0x48;
            // Call function with modified value
            FUN_0074a210(val);
        }
        
        // Serialize the transform data at this+0x54 (helper function)
        FUN_0075cd50((char*)thisPtr + 0x54);
        
        // Copy three more 8-byte values to packet (similar to type A but different offset)
        *(ulonglong*)((uint*)packetBuffer + 0x36) = *(ulonglong*)((char*)thisPtr + 0x68);
        *(ulonglong*)((uint*)packetBuffer + 0x38) = *(ulonglong*)((char*)thisPtr + 0x70);
        *(ulonglong*)((uint*)packetBuffer + 0x3a) = *(ulonglong*)((char*)thisPtr + 0x78);
        
        // Store packet buffer pointer back to this+0x60
        *(uint**)((char*)thisPtr + 0x60) = (uint*)packetBuffer;
    }
    return;
}