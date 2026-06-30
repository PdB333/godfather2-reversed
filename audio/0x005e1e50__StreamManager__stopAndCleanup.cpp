// FUNC_NAME: StreamManager::stopAndCleanup
int StreamManager::stopAndCleanup()
{
    // Check if stream is active (flag at +0x1744)
    if (this->field_0x1744 != 0)
    {
        // Build a stop command struct (value = 1,0,0,0)
        Command stopCmd;
        stopCmd.field_0 = 1;
        stopCmd.field_4 = 0;
        stopCmd.field_8 = 0;
        stopCmd.field_C = 0;

        // Send stop command to the stream
        this->sendCommand(&stopCmd); // FUN_005e2440

        // Wait 5 ticks (possibly frame delays or audio buffer drains)
        for (int i = 0; i < 5; i++)
        {
            this->tickWait(); // FUN_005e8610
        }

        // Free stream buffers and reset state
        this->field_0x173c = 0; // e.g., current sample offset or play status
        if (this->field_0x1738 != 0)
        {
            operator delete(this->field_0x1738); // FUN_009c8f10
            this->field_0x1738 = 0;
        }
        this->field_0x1740 = 0; // e.g., buffer size or pointer
        this->field_0x1744 = 0; // clear active flag
    }
    return 1; // success
}