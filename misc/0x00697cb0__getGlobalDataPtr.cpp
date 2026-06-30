// FUNC_NAME: getGlobalDataPtr
// Function at 0x00697cb0: Returns a pointer to a global data structure (DAT_01129d80).
// Likely a singleton accessor for a manager or system instance.
void* getGlobalDataPtr(void)
{
    // DAT_01129d80 is a static data area; defined elsewhere.
    return (void*)&DAT_01129d80;
}