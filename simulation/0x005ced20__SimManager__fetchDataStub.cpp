// FUNC_NAME: SimManager::fetchDataStub
// Address: 0x005ced20
// Calls a lower-level function to populate two 16-byte IDs and a 76-byte struct with zeros and a final flag set to 1.
void SimManager::fetchDataStub(uint param_2)
{
    char idBuffer1[16]; // +0x00 first 16-byte identifier output
    char idBuffer2[16]; // +0x10 second 16-byte identifier output
    char dataBuffer[76]; // +0x20 76-byte data output (e.g., game object state)
    FUN_005ced60(this, param_2, idBuffer2, idBuffer1, dataBuffer, 0, 0, 0, 0, 1);
}