// FUNC_NAME: releaseHandle
void __cdecl releaseHandle(void)
{
    // Call the resource release function with the current handle
    releaseResource(g_handle);
    // Invalidate the handle by setting it to -1 (0xFFFFFFFF)
    g_handle = 0xFFFFFFFF;
}