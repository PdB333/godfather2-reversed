// FUNC_NAME: Debug::logEvent
void Debug::logEvent(void)
{
    // 0x40 = 64, likely an event type or severity code
    // local_c is a 12-byte buffer for event data (uninitialized)
    byte dataBuffer[12];
    
    // Call the logging function with event type and empty data buffer
    // Actual implementation at 0x0064b810
    FUN_0064b810(0x40, dataBuffer);
    
    return;
}