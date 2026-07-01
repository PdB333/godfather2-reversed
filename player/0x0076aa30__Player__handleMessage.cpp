// FUNC_NAME: Player::handleMessage
void __thiscall Player::handleMessage(void *this, MessageData *msgData)
{
    int msgType = msgData->getType(); // Dereference vtable to get message type
    
    if (msgType == 0x27a0f69c) // MSG_FIRE_WEAPON
    {
        Vector3 weaponPos;
        getPosition(&weaponPos); // FUN_0076a540: Get current weapon position
        
        int playerIdx = getPlayerIndex(); // FUN_00471610: Returns player object pointer
        Vector3 playerPos = *(Vector3 *)(playerIdx + 0x30); // Player position offset
        
        Vector3 direction;
        direction.x = playerPos.x - weaponPos.x;
        direction.y = playerPos.y - weaponPos.y;
        direction.z = playerPos.z - weaponPos.z;
        
        Vector3 normalizedDir;
        normalizedDir.x = direction.x;
        normalizedDir.y = direction.y;
        normalizedDir.z = direction.z;
        vectorNormalize(&normalizedDir); // FUN_0056afa0: In-place normalization
        
        spawnEffectAtDirection(&weaponPos, &normalizedDir, 1, g_someEffectID, 0); // FUN_00755410
    }
    else if (msgType == 0x485311a7) // MSG_UPDATE_TARGET
    {
        if (this->m_isEnabled) // +0x84
        {
            msgData->targetID = this->m_ownerID; // +0x5c, set at index 0x26 (38)
            
            int targetObj;
            if (this->m_targetObject == 0) // +0x70
                targetObj = 0;
            else
                targetObj = this->m_targetObject - 0x48; // Offset to get object pointer
            
            setTargetObject(targetObj); // FUN_0075b920
            setGlobalData(g_someGlobal); // FUN_0075b540, DAT_00e51bcc
            initVector(&this->m_someVector); // FUN_0075b4d0, +0x7c
            
            Vector3 currentPos;
            getPosition(&currentPos); // FUN_0076a540
            
            Vector3 targetPos;
            if (this->m_targetObject == 0)
                targetPos = Vector3(0,0,0);
            else
                targetObj->getTargetOffset(&targetPos, &this->m_someVector); // vtable+0xa4
            
            Vector3 delta;
            delta.x = targetPos.y - currentPos.y; // Note: intentional swap? Logic from decomp
            delta.y = targetPos.z - currentPos.z;
            delta.z = currentPos.x - targetPos.x;
            
            processDelta(&delta); // FUN_0075b4f0
        }
    }
    else
    {
        defaultMessageHandler(msgData); // FUN_0073e4d0
    }
    return;
}