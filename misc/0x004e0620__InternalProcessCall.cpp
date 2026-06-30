// FUNC_NAME: InternalProcessCall
// Function address: 0x004e0620 - Simple wrapper that delegates to another function at 0x0051ca90.
void InternalProcessCall(void)
{
    // Forward the call to the actual processing routine (likely engine tick or update).
    processInternalTick();
    return;
}