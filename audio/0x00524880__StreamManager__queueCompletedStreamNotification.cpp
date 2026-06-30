// FUNC_NAME: StreamManager::queueCompletedStreamNotification
void StreamManager::queueCompletedStreamNotification(int streamSlotIndex, int param2)
{
    // param_1 = this (StreamManager*)
    // param_2 = streamSlotIndex
    
    uint queuedCount = DAT_01194a9c; // global counter of queued notifications +0x0
    int queueIndex;
    int currentSlot = *(int *)(*(int *)(&DAT_01197d10 + streamSlotIndex * 4) + 0x458); // stream slot data +0x458 = stream state?
    
    if (currentSlot == 0) {
        currentSlot = 0;
    }
    else {
        currentSlot = currentSlot + -4; // adjust pointer to previous element?
    }
    
    int streamInfo = *(int *)(*(int *)(this + 0x10) + 0x5c); // this+0x10 -> stream manager internal, +0x5c = current stream ID?
    
    // Check if the stream matches or if it's an async load that completed
    if (((streamInfo == currentSlot) ||
        (((*(byte *)(streamInfo + 0xac) & 8) != 0 && // +0xac = flags, bit 3 = e.g. "isAsync"
         (*(char *)(*(int *)(&DAT_01197d10 + streamSlotIndex * 4) + 0x451) != '\0')))) && // +0x451 = stream slot completed flag
        (queuedCount < 0x400)) { // max 1024 queued notifications
        
        int notificationData = FUN_005247a0(streamInfo); // allocate notification struct
        if (notificationData != 0) {
            queueIndex = queuedCount * 0xc; // each notification is 0xC bytes
            *(undefined4 *)(&DAT_01194d10 + queueIndex) = *(undefined4 *)(this + 0x10); // +0x00 = stream manager pointer
            *(undefined4 *)(&DAT_01194d14 + queueIndex) = *(undefined4 *)(this + 0xc);  // +0x04 = stream ID?
            DAT_01194a9c = queuedCount + 1; // increment queue count
            *(undefined4 *)(&DAT_01194d18 + queueIndex) = *(undefined4 *)(notificationData + 0x14); // +0x14 = next pointer
            *(undefined **)(notificationData + 0x14) = &DAT_01194d10 + queueIndex; // link into notification list
        }
    }
    return;
}