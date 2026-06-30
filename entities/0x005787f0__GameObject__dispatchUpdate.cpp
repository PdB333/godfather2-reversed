// FUNC_NAME: GameObject::dispatchUpdate
void GameObject::dispatchUpdate(void* pInputState)
{
    // Check if the game is paused via global state function
    char bPaused = isGamePaused();
    if (bPaused != '\0') {
        // Process paused update – pass this object and a stack-local variable (likely a context struct)
        processPausedState(this, &someLocal);
        return;
    }
    // Not paused: check input state flags
    // pInputState is a data block; byte at offset 0x0B: bit 0x20 (0x20 = 32 decimal) is a flag (e.g., "has valid input")
    // The first int (offset 0x00) is a count (e.g., number of active input slots)
    if (((*(byte *)((int)pInputState + 0xb) & 0x20) != 0) && (*(int *)pInputState > 1)) {
        // Condition met: call virtual function at vtable+4 (normal update)
        (*(void (**)(void))(*((int *)this) + 4))();
        return;
    }
    // Default: call virtual update regardless
    (*(void (**)(void))(*((int *)this) + 4))();
    return;
}