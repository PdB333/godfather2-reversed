// FUN_004c3e90: UIManager::preparePromptBuffer
void __thiscall UIManager::preparePromptBuffer(void* thisPtr, char* outputBuffer) {
    char tempBuffer[12];
    int field0C = 0;      // +0x0C
    int field1C = 0;      // +0x1C
    int field2C = 0;      // +0x2C
    int field3C = DAT_00e2b1a4; // +0x3C, global integer used as padding/flag

    if (isStateActive()) {
        FUN_0044b4e0(outputBuffer, tempBuffer);
    }
}