// FUNC_NAME: ActivePairManager::getActivePair
void __thiscall ActivePairManager::getActivePair(int* pOutputPair, int input)
{
    int newId = FUN_006948e0(input); // Convert input to an ID
    int storedId = *(int*)(this + 4); // Current active ID stored at +0x04

    if (this == 0)
    {
        FUN_00b97aea(); // Assertion or error handling for null this
    }

    // Determine which pair to output
    if (newId != storedId)
    {
        int checkResult = FUN_004d4b20(newId + 0xC); // Validate newId + offset
        if (checkResult >= 0)
        {
            // Use the new ID: output (this, newId)
            *pOutputPair = this;
            pOutputPair[1] = newId;
            return;
        }
    }

    // Fallback: output (this, storedId)
    *pOutputPair = this;
    pOutputPair[1] = storedId;
}