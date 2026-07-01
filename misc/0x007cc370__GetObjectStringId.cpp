// FUNC_NAME: GetObjectStringId
int GetObjectStringId(void)
{
    // Global manager pointers (likely GameManager and some other singleton)
    // +0x58 and +0x6c are offsets into the game state structure? Not sure.
    if ((g_gameManager != 0) && (g_otherManager != 0))
    {
        // Get some object from the game manager (e.g., current player or focus target)
        // FUN_00849cf0 probably returns a pointer to an entity or object
        void* pObject = GetObjectFromManager(g_gameManager);
        if (pObject != 0)
        {
            // +0x5c likely stores a string pointer (e.g., debug name or resource ID)
            char* pNameStr = *(char**)((int)pObject + 0x5c);
            if (pNameStr == 0)
            {
                pNameStr = &defaultString; // Address 0x0120546e
            }
            // Convert the string to an integer ID (hash or resource handle)
            // FUN_004dafd0 likely returns a hash or ID from the string
            return ComputeStringId(pNameStr);
        }
    }
    return 0;
}