// FUNC_NAME: EventManager::dispatchWithTarget
void __thiscall EventManager::dispatchWithTarget(void* this, uint32_t param_a, uint32_t param_b, uint32_t param_c)
{
    // Delegates to a lower-level handler with an additional target address (LAB_004bb310)
    // This pattern is common for virtual callbacks or event routing in the EA EARS engine.
    FUN_004bb190(this, param_a, param_b, param_c, &LAB_004bb310);
    return;
}