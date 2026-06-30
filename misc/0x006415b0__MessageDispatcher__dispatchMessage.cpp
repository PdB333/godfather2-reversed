// FUNC_NAME: MessageDispatcher::dispatchMessage
void MessageDispatcher::dispatchMessage(int thisObj)
{
    // +0x1c: pointer to ListenerList
    ListenerList* listenerList = *(ListenerList**)(thisObj + 0x1c);
    // +0x14: head of listener node chain
    ListenerNode* node = *(ListenerNode**)(listenerList + 0x14);
    // +0x4: stored previous message ID
    int prevMsgId = *(int*)(thisObj + 4);
    // +0x8: preserve original message ID
    *(int*)(thisObj + 8) = prevMsgId;

    uint combinedFlags = 0;
    // +0x14: current message type ID
    int currentMsgId = *(int*)(thisObj + 0x14);
    if (currentMsgId == 0x11f) { // 0x11f = 287 (some specific message type)
        // +0x10: convert ID to new value
        int newId = FUN_00639c70(thisObj + 0x10); // likely converts or generates new ID
        *(int*)(thisObj + 0xc) = newId;
    }
    else {
        // +0x14: not 0x11f, so propagate ID and set target ID to 0x11f
        *(int*)(thisObj + 0xc) = *(int*)(thisObj + 0x14);
        *(int*)(thisObj + 0x10) = *(int*)(thisObj + 0x18);
        *(int*)(thisObj + 0x14) = 0x11f;
    }

    // Iterate through the listener node chain
    for (; node != (ListenerNode*)0x0; node = (ListenerNode*)*node) {
        // node[4] is the active/processed flag (non-zero means already handled)
        if (node->active != 0) {
            goto endLoop;
        }
        // node[3] is the flag to OR into combinedFlags
        combinedFlags = combinedFlags | node->flags;
    }
    // If we exit the loop without encountering an active node, it's a bug
    FUN_00638b80("no loop to break");

endLoop:
    // +0xc: pointer to some target object; +8 is the actual target (e.g., a message queue)
    int targetQueue = *(int*)(*(int*)(thisObj + 0xc) + 8);
    if (combinedFlags != 0) {
        // Build message ID: node[2] << 0x18 | 0x21 (0x21 = 33, likely a flag)
        int msgId = (node->someId << 0x18) | 0x21;
        FUN_006438e0(msgId, targetQueue); // send message to queue
    }
    *(int*)(thisObj + 0x20) = -1; // mark as processed
    FUN_006438e0(0x7fff94, targetQueue); // send destroy/finish message
    FUN_00642880(thisObj); // release reference (first)
    FUN_00642880(thisObj); // release reference (second)
}