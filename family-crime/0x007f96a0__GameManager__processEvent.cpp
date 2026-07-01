// FUNC_NAME: GameManager::processEvent
// Address: 0x007f96a0
// Purpose: Gateway function that checks if the game manager is initialized and not in a restricted state before dispatching an event to the actual handler.
// Offsets:
//   +0x840: Pointer to a state object (e.g., m_pGameState), must be non-null.
//   +0x8E4: Bitfield; bit 10 (0x400) checked to determine if processing is blocked.

int __thiscall GameManager::processEvent(void* eventObj, uint eventFlags, int param4, int param5)
{
    char isBlocked;

    // Check if the state object exists; if not, return 0 (failure).
    if (*(int*)((char*)this + 0x840) == 0) {
        return 0;
    }

    // If the event does not have the "bypass check" flag (0x200), verify global blocking state.
    if ((eventFlags & 0x200) == 0) {
        // Global check (e.g., is cutscene playing, or game is paused)
        isBlocked = FUN_007f7b90(); // e.g., isGameBlocked()
        if ((isBlocked != 0) || ((*(uint*)((char*)this + 0x8E4) >> 10 & 1) != 0)) {
            return 0; // Block event processing
        }
    }

    // Dispatch to the actual event handler
    return FUN_006f3eb0(eventObj, eventFlags, param4, param5);
}