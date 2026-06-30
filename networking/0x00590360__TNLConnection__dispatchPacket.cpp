// FUNC_NAME: TNLConnection::dispatchPacket
undefined4 __thiscall TNLConnection::dispatchPacket(byte* this, undefined4 arg1, undefined4 arg2, undefined4 arg3, undefined4 arg4, undefined4 arg5, undefined4 arg6)
{
    // The low 6 bits of the first byte indicate the message type (0-34)
    uint8_t messageType = *this & 0x3F;

    // If the message type is valid (less than 35), dispatch via jump table at 0x0103afc0
    if (messageType < 0x23)
    {
        // Table of function pointers indexed by messageType
        // Each function takes 7 parameters: this (the packet data? actually arg1?), arg1, arg2, ...
        return ((code**)(&DAT_0103afc0 + messageType * 4))(arg1, this, arg2, arg3, arg4, arg5, arg6);
    }

    // Invalid message type, return 0
    return 0;
}