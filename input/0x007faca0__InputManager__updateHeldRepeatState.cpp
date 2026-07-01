// FUNC_NAME: InputManager::updateHeldRepeatState
void InputManager::updateHeldRepeatState()
{
    // Counter at +0x1eb0: likely repeat timer for held/repeated input
    if (*(int*)(this + 0x1eb0) > 0)
    {
        *(int*)(this + 0x1eb0) = *(int*)(this + 0x1eb0) - 1;
    }

    if (*(int*)(this + 0x1eb0) == 0)
    {
        // Clear bit 9 (0x200) from flags at +0x1b94 — maybe "held" flag
        *(uint*)(this + 0x1b94) &= ~0x200;
        *(int*)(this + 0x1ea4) = 0;  // +0x1ea4: repeat value X
        *(int*)(this + 0x1ea8) = 0;  // +0x1ea8: repeat value Y
    }

    // Clear bit 14 (0x4000) — maybe "repeat active" flag
    *(uint*)(this + 0x1b94) &= ~0x4000;

    // Second decrement (unusual — likely two-stage repeat timing)
    if (*(int*)(this + 0x1eb0) > 0)
    {
        *(int*)(this + 0x1eb0) = *(int*)(this + 0x1eb0) - 1;
    }

    if (*(int*)(this + 0x1eb0) == 0)
    {
        // Clear bit 8 (0x100) — maybe "first press" flag
        *(uint*)(this + 0x1b94) &= ~0x100;
        *(int*)(this + 0x1ea4) = 0;
        *(int*)(this + 0x1ea8) = 0;
    }

    // Again clear bit 14 (redundant)
    *(uint*)(this + 0x1b94) &= ~0x4000;
}