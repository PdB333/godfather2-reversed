// FUNC_NAME: NetConnection::processReliablePacket
void NetConnection::processReliablePacket(ReliablePacket *packet, int sequence)
{
    // +0x8: m_expectedSequence
    if (sequence != *(int*)((int)this + 8)) {
        return;
    }
    // +0x18: m_bProcessingReliable
    *(unsigned char*)((int)this + 0x18) = 1;
    FUN_00497ca0(packet); // decode packet into list structure (modifies stack vars indirectly)
    
    // Local list fields set by FUN_00497ca0 (not shown in decompilation due to inlining)
    uint count = local_10; // packet->ghostCount
    int* items = (int*)local_14; // packet->ghostIds
    
    // +0x4: m_localPlayerId
    int localId = *(int*)((int)this + 4);
    
    for (uint i = 0; i < count; i++) {
        int ghostId = items[i];
        if (ghostId == localId) {
            continue;
        }
        // Check if ghostId is related to localId (e.g., same scope)
        if (FUN_00497a60(ghostId, localId) != '\0') {
            continue;
        }
        
        int* objPtrWrapper = (int*)FUN_004986e0(&ghostId);
        bool hasObj = (objPtrWrapper != 0 && *objPtrWrapper != 0);
        int objPtr = (hasObj) ? *objPtrWrapper + 8 : 0;
        
        bool condition = false;
        if (sequence == 1) {
            // +0x1c: m_ackMask
            condition = (FUN_00497040(*(unsigned char*)((int)this + 0x1c)) != '\0');
        } else if (sequence == 2) {
            condition = (FUN_004971f0() != -1);
        }
        
        if (objPtr != 0 && condition) {
            GhostUpdate update;
            update.ghostId = ghostId;
            // local_1c is passed as pointer to update
            FUN_004866e0(&update);
        }
    }
    
    if (local_14 != 0) {
        FUN_009c8f10(local_14); // free decoded list buffer
    }
}