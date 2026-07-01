// FUNC_NAME: GhostManager::handleGhostUpdate

void __thiscall GhostManager::handleGhostUpdate(uint32 this, Vector4* updateData, uint32 objectId, Vector4* responseData)
{
    char result;
    int* currentGhost;
    uint32 ghostHash;
    int32 temp1;
    uint32 flags;
    char packetFormat[84];
    Vector4 localUpdate;
    uint32 ghostHash2;
    
    // +0x78: pointer to ghost list? +0x80: flag for something
    if (*(int*)(this + 0x78) != 0 && *(int*)(this + 0x80) == 0)
    {
        // +0x94: store the object ID
        *(uint32*)(this + 0x94) = objectId;
        
        // Copy the incoming update vector
        localUpdate.x = updateData->x;
        localUpdate.y = updateData->y;
        localUpdate.z = updateData->z;
        localUpdate.w = updateData->w;
        
        ghostHash = DAT_01223410;  // Some class hash or identifier
        
        // Iterate over ghosts of the given hash
        currentGhost = FUN_00446100(&localUpdate, nullptr);
        while (currentGhost != nullptr)
        {
            int* foundGhost = nullptr;
            
            // +0x10 virtual: check if ghost matches hash
            result = (*(code**)(*currentGhost + 0x10))(0xae986323, &foundGhost);
            if (result != 0)
            {
                // Found a matching ghost
                int* tempGhost = foundGhost;
                if (foundGhost != nullptr)
                {
                    // Check if ghost is active via global debug flag
                    if (FUN_00402080(&DAT_012067c4) != 0)
                        break; // Stop searching if active
                }
                else
                {
                    tempGhost = nullptr;
                }
            }
            currentGhost = FUN_00446100(&localUpdate, currentGhost);
        }
        
        if (foundGhost != nullptr)
        {
            ghostHash = 0;  // Reset hash for next call
            
            // Resolve objectId to some local identifier
            ghostHash2 = FUN_004dafd0(objectId);
            
            // +0x98 virtual: apply the update to the ghost
            result = (*(code**)(*foundGhost + 0x98))(&ghostHash, ghostHash2);
            if (result != 0)
            {
                // Copy response data into local vector
                localUpdate.x = responseData->x;
                localUpdate.y = responseData->y;
                localUpdate.z = responseData->z;
                localUpdate.w = responseData->w;
                
                // Build the packet format string
                FUN_00412d90(packetFormat);
                
                // uStack_a4 likely comes from a previous call or register; treat as flag
                if ((flags & 1) == 0)
                {
                    // Pack fields for the response
                    int32 field84 = *(int32*)(this + 0x84);
                    uint32 field8c = *(uint32*)(this + 0x8c);
                    void* field90 = *(void**)(this + 0x90);
                    int32 field88 = *(int32*)(this + 0x88);
                    void* field78 = *(void**)(this + 0x78);
                    
                    // +0x58 virtual: serialize data to packet buffer
                    void* buffer = (*(code**)(*foundGhost + 0x58))(0, &temp1);
                    
                    // Build the actual packet with the string and data
                    void* packet = FUN_004df270(nullptr, &field84, packetFormat, buffer);
                    FUN_00414db0(packet);
                    FUN_00414df0();
                }
                else
                {
                    // Alternate packing order
                    uint32 field8c = *(uint32*)(this + 0x8c);
                    void* field90 = *(void**)(this + 0x90);
                    int32 field84 = *(int32*)(this + 0x84);
                    int32 field88 = *(int32*)(this + 0x88);
                    void* field78 = *(void**)(this + 0x78);
                    
                    void* buffer = (*(code**)(*foundGhost + 0x58))(0, &temp1);
                    void* packet = FUN_004df270(nullptr, &field84, packetFormat, buffer);
                    FUN_00414db0(packet);
                    FUN_00414df0();
                }
                
                // If the ghost update flag is set, mark as updated
                if (*(int*)(this + 0x80) != 0)
                    *(uint8*)(this + 0x70) = 1;
            }
        }
    }
}