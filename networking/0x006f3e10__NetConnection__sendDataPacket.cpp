// FUNC_NAME: NetConnection::sendDataPacket
uint __thiscall NetConnection::sendDataPacket(int thisPtr, void* data, uint dataSize, char isReliable, undefined4 param5, uint flags, undefined4 param7, char isUrgent, int connectionOverride)
{
    int connection; // pointer to more specific connection object (+0x0C from this)
    uint result;
    int validatedConnection;

    connection = *(int*)(thisPtr + 0x0C); // +0x0C: pointer to internal connection (NetConnection*)
    result = 0;
    
    // Proceed only if we have an underlying connection and it's either not flagged as "destroyed" (bit0 at +0x8E6) or the message is urgent
    if ((connection != 0) &&
        (((*(byte*)(connection + 0x8E6) & 1) == 0) || (isUrgent != '\0'))) {
        // If reliable flag is set but not urgent, add guaranteed delivery flag
        if ((isReliable == '\x01') && (isUrgent != '\x01')) {
            flags = flags | 4; // 4 = FLAG_GUARANTEED_DELIVERY
        }
        // If urgent, add priority flag
        if (isUrgent != '\0') {
            flags = flags | 0x20; // 0x20 = FLAG_HIGH_PRIORITY
        }
        
        // Possibly a time check or debug break condition
        if ((char)FUN_00842880() != '\0') {
            return (uint)FUN_00842880() & 0xFFFFFF00; // return with modified time value
        }
        
        // Validate and prepare the actual connection to use
        validatedConnection = FUN_006f3b80(data); // returns a validated connection or zero
        if (validatedConnection == 0) {
            return 0;
        }
        if (connectionOverride == 0) {
            connectionOverride = connection;
        }
        
        // Send the packet through the validated connection
        result = FUN_006f77a0(connectionOverride, data, dataSize, param5, flags, param7, isUrgent);
    }
    return result;
}