// FUNC_NAME: resourceCleanup
void resourceCleanup(void)
{
    // Check if the resource pointer at global manager offset 0xc is non-null
    if (*(int*)((char*)g_pManager + 0xc) != 0)
    {
        // Release the resource (calls cleanup/release function at 0x006063b0)
        releaseResource();
    }
    return;
}