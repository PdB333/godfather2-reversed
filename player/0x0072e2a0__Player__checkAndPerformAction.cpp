// FUNC_NAME: Player::checkAndPerformAction
void __thiscall Player::checkAndPerformAction()
{
    // Bit 25 of m_flags (offset 0x1f58) indicates if action is blocked (e.g., in cutscene)
    if (!(m_flags & (1 << 25)))
    {
        // Check if global input is allowed (game not paused, etc.)
        if (isGlobalActionAllowed())
        {
            // Execute the contextual action
            performAction();
        }
    }
}