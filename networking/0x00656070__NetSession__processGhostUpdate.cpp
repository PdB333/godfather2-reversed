// FUNC_NAME: NetSession::processGhostUpdate
void NetSession::processGhostUpdate(void* ghostUpdatePacket, int param2, int param3)
{
    char* packetBytes = (char*)ghostUpdatePacket;
    int* ghostObject;
    int refCount;
    char success;
    
    // Check if this is a valid ghost update (byte at offset 0x7c indicates type)
    if (packetBytes[0x7c] != 0)
    {
        // Initialize local buffers
        int buffer0[4] = {0, 0, 0, 0};  // 16 bytes, but later used as 32-byte seed
        byte hashBuffer[256] = {0};
        byte guidSeed[32] = {0};         // actually 32 bytes, but stack layout may differ
        
        // Check if we can process network updates (e.g., not in menu)
        if (FUN_00655250() == 0)   // likely canProcessNetworkUpdates()
        {
            // Generate a random timestamp for duplicate detection
            int randomTime = FUN_0046d790();   // getRandomTime()
            
            // Build a GUID seed from static data
            FUN_0064b9e0(0x20, guidSeed);       // generateGUIDSeed(guidSeed, 32)
            
            // Compute a hash over the packet to verify integrity
            FUN_0064c6b0(hashBuffer);           // computePacketHash(hashBuffer, 256)
            
            // Allocate a new ghost object from the pool
            ghostObject = (int*)FUN_00652a50();  // allocateGhostObject()
            if (ghostObject != nullptr)
            {
                // Call the ghost object's initializer with param3 (likely session ID)
                ((void (*)(int))(*(int*)*ghostObject + 0x48))(param3);
                
                // Increment reference count (stored at offset +8)
                ghostObject[2]++;
                
                // Acquire exclusive access to the ghost
                FUN_00656210();   // lockGhost()
                
                // Copy the object's network ID from the packet
                *(uint64_t*)(ghostObject + 0x40) = *(uint64_t*)ghostUpdatePacket;       // offset 0x100
                *(uint64_t*)(ghostObject + 0x42) = *(uint64_t*)((byte*)ghostUpdatePacket + 8); // offset 0x108
                ghostObject[0x44] = *(int*)((byte*)ghostUpdatePacket + 16);              // offset 0x110
                
                // Set timestamps (note: iStack_178 is likely a parameter, possibly time from caller)
                int timeStamp = iStack_178;    // This variable appears uninitialized; likely a stack parameter
                ghostObject[0x28] = timeStamp; // +0xA0
                ghostObject[0x24] = timeStamp; // +0x90
                ghostObject[0x2a] = timeStamp; // +0xA8
                
                // Call initialization helper (unaff_retaddr is a return address param)
                FUN_00452df0(unaff_retaddr);
                
                // Process the ghost update data - calls vtable+0x24 (unpack)
                success = ((char (*)(int, byte*))(*(int*)*ghostObject + 0x24))(param2, (byte*)&stack0xfffffe84);
                
                if (success == 0)
                {
                    // Update processing failed – enqueue or discard
                    FUN_00656600(unaff_retaddr, ghostUpdatePacket);   // handleGhostUpdateFailed()
                }
                else
                {
                    // Update succeeded – apply to game world
                    FUN_00655420(ghostObject);           // applyGhostUpdate()
                    
                    // Set state to active (7 = activated)
                    ghostObject[0x6d] = 7;               // +0x1B4
                    
                    // Call finalization method
                    ((void (*)())(*(int*)*ghostObject + 0x14))();  // finalize()
                    
                    // Notify listeners or commit changes
                    FUN_00656440(unaff_retaddr);         // finalizeGhostUpdate()
                }
                
                // Decrement reference count
                int* refPtr = ghostObject + 2;
                (*refPtr)--;
                if (*refPtr == 0)
                {
                    // No more references – delete object
                    ((void (*)())(*(int*)*ghostObject + 8))();  // destructor
                }
            }
        }
        
        // Cleanup or unlock
        FUN_00652d00();   // unlockNetworkUpdate()
    }
}