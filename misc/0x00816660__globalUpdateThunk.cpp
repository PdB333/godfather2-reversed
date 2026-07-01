// FUNC_NAME: globalUpdateThunk
void globalUpdateThunk(void)
{
    // Delegates to the core update routine called by multiple subsystems.
    // This wrapper allows the real update to be swapped or patched.
    internalGameUpdate();
    return;
}