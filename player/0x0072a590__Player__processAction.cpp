// FUNC_NAME: Player::processAction
void __thiscall Player::processAction(uint thisPlayer, int* message)
{
    // +0x1f18: Player flags field
    Player* player = (Player*)thisPlayer;
    Message* msg = (Message*)message;
    
    FUN_00738460(msg); // message validation/init
    
    int msgType = msg->type;
    void* msgData = (void*)msg->data;
    
    if (msgType == DAT_0112ad8c) // kMsg_Interact
    {
        ActionTarget* target = (ActionTarget*)msgData;
        Entity* targetEntity = FUN_007295e0(target->entityId); // get entity by ID
        if (targetEntity == 0) return;
        
        float* posPtr;
        if (target->facingMe == 0) // +0x1c bool: is target facing player?
        {
            if (target->subtype == 0 || target->subtype == 0x48) // +0x8 subtype
                posPtr = 0;
            else
                posPtr = (float*)(FUN_00471610() + 0x30); // player transform position
        }
        else
        {
            posPtr = target->position; // +0x10
        }
        
        // check if entity has line-of-sight flag (bit 1 of flags1)
        if ((targetEntity->flags1 & 2) != 0) // +0x5c
        {
            if (posPtr == 0) return;
            float* playerPos = (float*)(FUN_00471610() + 0x30);
            float dx = posPtr[0] - playerPos[0];
            float dy = posPtr[1] - playerPos[1];
            float dz = posPtr[2] - playerPos[2];
            float distSq = dx*dx + dy*dy + dz*dz;
            if (distSq > targetEntity->range) // +0x60 range
                return;
        }
        else
        {
            if ((targetEntity->flags1 & 1) != 0 && posPtr != 0) // bit 0: use distance check
            {
                float* playerPos = (float*)(FUN_00471610() + 0x30);
                float dist = FUN_0045c470(posPtr, playerPos); // Euclidean distance
                // distance stored in param_2 (reused)
                // param_2 = (int*)(float)dist;
                // but later used for comparison, skip for clarity
            }
        }
        
        int actionType = 0; // local_34
        if (target->subtype == 0)
            actionType = 0;
        else if (target->subtype == 0x48)
            actionType = 0;
        else
            actionType = FUN_006b1c70(target->subtype - 0x48, 0x55859efa); // random/hash
        
        float rangeMod = targetEntity->range;
        if ((targetEntity->flags1 & 0x40) != 0) // bit 6: use squared player speed?
        {
            uint player = FUN_0077dd80();
            FUN_00716420();
            float speed = FUN_00712ef0(player);
            rangeMod = speed * speed;
        }
        
        float score = 0.0f;
        // local_14 struct for action evaluation
        ActionEvalData evalData;
        evalData.actionType = actionType;
        evalData.actionOffset = thisPlayer - 0x3c; // player ID?
        evalData.rangeMod = rangeMod;
        evalData.target = target;
        evalData.distance = (float)(int)param_2; // the distance computed earlier (cast from int)
        
        if (((uint)(targetEntity->flags2) & 1) == 0 || FUN_007ff880() == 0) // bit 0: no combat check?
        {
            score = FUN_0077e380(targetEntity, &evalData);
        }
        
        if ((player->flags & 0x800) == 0) // bit 11: some flag check
        {
            int soundEntity = *(int*)(targetEntity + 0x54); // +0x54
            if (FUN_0072d630(targetEntity) != 0 && *(int*)(targetEntity + 0x58) != 0)
                soundEntity = *(int*)(targetEntity + 0x58); // +0x58 override
            if (soundEntity != 0 && FUN_007f7b90(targetEntity) == 0) // not dead
            {
                FUN_006fbc40(0, 0); // begin sound context
                FUN_006f3eb0(soundEntity, 0, FUN_006fbc40(0,0), 0); // play sound
                FUN_006fbc70(); // end sound context
            }
        }
        
        // Build action message and send
        ActionMessage outMsg;
        outMsg.type = DAT_0112ad84; // some message type
        outMsg.flag = 0; // local_18
        outMsg.data = target;
        FUN_00408bf0(&outMsg, (thisPlayer != 0x3c) ? thisPlayer : 0, 0);
        
        int subtype = (target->subtype == 0) ? 0 : (target->subtype - 0x48);
        FUN_00718360(subtype, targetEntity, score, posPtr);
        return;
    }
    else if (msgType == DAT_0112ad7c) // kMsg_Bully
    {
        ActionTarget* target = (ActionTarget*)msgData;
        if (target != 0 && target->subtype != 0 && 
            (targetEntity = FUN_00715cd0(target->entityId, 0, 0)) != 0) // isValidTarget
        {
            if (target->entityId == 0x3bd0fe1e) // specific ID
            {
                FUN_006fbc40(0, 0);
                FUN_007f96a0(0xbace4e2e, 0, FUN_006fbc40(0,0), 0); // spawn effect
                FUN_006fbc70();
            }
            // Send message
            ActionMessage outMsg;
            outMsg.type = DAT_0112ad8c;
            outMsg.flag = 0;
            outMsg.data = target;
            FUN_00408bf0(&outMsg, (thisPlayer != 0x3c) ? thisPlayer : 0, 0);
            return;
        }
    }
    else if (msgType == DAT_0112dc68) // kMsg_EnterSafeHouse
    {
        if (FUN_0071e670(DAT_0112a678) == 0) // player not alive?
        {
            if (FUN_00806440() == 0 && // not multiplayer
                FUN_00736300() == 0 && // not in cutscene
                FUN_009a0810(thisPlayer - 0x3c, DAT_0112a678) != 0) // nearest safe house exists
            {
                FUN_007308c0(safeHouse); // activate safe house
                return;
            }
        }
    }
    return;
}