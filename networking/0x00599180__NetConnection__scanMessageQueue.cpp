// FUNC_NAME: NetConnection::scanMessageQueue
ushort __fastcall NetConnection::scanMessageQueue(int thisObj)
{
    // thisObj is 'this' pointer. 
    // +0xB8 points to a linked list of message entries.
    // Each entry is a pair of ushorts: [type, offsetToNext].
    // type 0x100 indicates end of list.
    // type 0x300 is a specific message type that triggers a return 0x301.
    ushort *pMessageList = *(ushort **)(thisObj + 0xB8); // pointer to first message entry
    ushort messageType = *pMessageList;
    ushort *pCurrentMessage = pMessageList;
    
    while (messageType != 0x100) // not end-of-list marker
    {
        if (messageType == 0x300) // found the target type
        {
            return 0x301;         // return indicator that type 0x300 exists
        }
        // Check if there is a next entry: offset at pCurrentMessage[1] != 0
        if (pCurrentMessage[1] == 0)
            break; // no more entries
        // Advance to the next entry using the offset stored at index 1
        pCurrentMessage = (ushort *)((int)pCurrentMessage + (uint)pCurrentMessage[1]);
        messageType = *pCurrentMessage;
    }
    // Return the high byte of the last message type encountered
    return messageType & 0xFF00;
}