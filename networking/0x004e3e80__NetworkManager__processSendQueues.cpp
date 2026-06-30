// FUNC_NAME: NetworkManager::processSendQueues

void NetworkManager::processSendQueues(void *context) // context param passed to flush callback
{
    int i = 0;
    if (0 < g_sendableObjectCount) {
        do {
            // Get object pointer from global list
            SendableObject *obj = g_sendableObjectList[i];
            
            // Process current sending list (linked list at obj+0x24)
            SendPacketNode *node = obj->currentSendHead; // +0x24
            while (node != nullptr) {
                obj->currentSendHead = node->next; // node[2] (next field)
                node->vtable->processPacket();
                node = obj->currentSendHead;
            }
            
            // Swap buffers: active becomes pending, current becomes old active, pending cleared
            SendPacketNode *oldActive = obj->activeSendHead; // +0x20
            obj->activeSendHead = obj->pendingSendHead; // +0x1c -> +0x20
            obj->currentSendHead = oldActive; // old active becomes new current
            obj->pendingSendHead = nullptr; // pending cleared
            
            // Call the flush/complete callback on the object
            obj->vtable->flushSendQueue(context);
            
            i++;
        } while (i < g_sendableObjectCount);
    }
}