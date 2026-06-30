// FUNC_NAME: MessageDispatcher::dispatchEvent
void __fastcall CMessageDispatcher::dispatchEvent(void* thisPtr, unsigned int param2, EventHeader* event)
{
    // param2 might be a target identifier or connection handle
    // event points to a message header structure
    int* dataBlock = *(int**)((char*)event + 4);  // +0x4: pointer to a data block
    unsigned int type = *(unsigned int*)((char*)dataBlock + 4) & 0xFF;  // +0x4: low byte is message type/priority
    unsigned int payload;
    if (type < 10) {
        payload = *(unsigned int*)((char*)dataBlock + 0xC);  // +0xC: payload for small types
    } else {
        payload = *(unsigned int*)((char*)dataBlock + 0x20); // +0x20: payload for larger types
    }
    // The 8 values in EAX are likely from the caller's side (e.g., an inline data block)
    // The decompiler shows in_EAX as undefined4*, so we pass them as an array
    FUN_00586df0(param2, payload, in_EAX[0], in_EAX[1], in_EAX[2], in_EAX[3],
                 in_EAX[4], in_EAX[5], in_EAX[6], in_EAX[7]);
}