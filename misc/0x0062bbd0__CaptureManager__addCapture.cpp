// FUNC_NAME: CaptureManager::addCapture
// Function address: 0x0062bbd0
// Adds a capture entry to the capture list (array of 8-byte entries).

void __thiscall CaptureManager::addCapture(uint32_t sourceId, uint32_t targetId, uint32_t data)
{
    int32_t index = this->captureCount; // +0x0c

    if (index > 31) // maximum 32 captures
    {
        FUN_00627bd0("too many captures", sourceId); // debug assert
    }

    this->captureArray[index].sourceId = sourceId;   // +0x10 + index*8
    this->captureArray[index].targetId = data;        // +0x14 + index*8 (offset 4 in each entry)
    this->captureCount = index + 1;                   // +0x0c

    int32_t result = FUN_0062bd60();                  // update or validate captures
    if (result == 0)
    {
        this->captureCount--; // remove the last added capture if validation fails
    }
}