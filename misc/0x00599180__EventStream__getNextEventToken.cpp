// FUNC_NAME: EventStream::getNextEventToken
ushort __thiscall EventStream::getNextEventToken(void) {
    // this +0xB8: pointer to ushort array (event stream)
    ushort* pStream = *(ushort**)(this + 0xB8);
    ushort currentType = *pStream;
    ushort* pCurrentEntry = pStream;

    while (currentType != 0x100) // 0x100 = EVENT_END marker
    {
        if (currentType == 0x300) // special event type
        {
            return 0x301; // returns a response token
        }
        if (pCurrentEntry[1] == 0) // if length field is zero, end of list
            break;

        // advance by the length field (offset in bytes)
        pCurrentEntry = (ushort*)((int)pCurrentEntry + (uint)pCurrentEntry[1]);
        currentType = *pCurrentEntry;
    }
    // return the high byte of the last processed event (or initial if none processed)
    return currentType & 0xff00;
}