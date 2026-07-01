// FUNC_NAME: checkAndNotifyOnMatch
void __thiscall checkAndNotifyOnMatch(int thisPtr, int matchedId)
{
    // The expected identifier is stored at offset +0x14 in the object
    if (matchedId == *(int *)(thisPtr + 0x14))
    {
        // Invoke the callback function when the IDs match
        FUN_00814d90();
    }
}