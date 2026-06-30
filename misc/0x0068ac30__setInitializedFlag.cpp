// FUNC_NAME: setInitializedFlag
// Address: 0x0068ac30
// Sets a global initialization flag to true (1).
// Called from initialization routine at 0x0067c290.
void setInitializedFlag(void)
{
    // Global flag at 0x01129a70
    g_bInitialized = 1;
}