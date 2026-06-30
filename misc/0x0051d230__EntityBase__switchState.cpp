// FUNC_NAME: EntityBase::switchState
void EntityBase::switchState(int newState)
{
    // If leaving state 4 and there's an active handle, stop it
    if (m_currentState == 4 && m_activeHandle != nullptr)
    {
        // Call stop/release function at vtable offset 4 on the handle object
        // g_soundManagerVtable is a global pointer to a function table
        ((void (*)(void*, int))(*g_soundManagerVtable + 4))(m_activeHandle, 0);
        m_activeHandle = nullptr;
    }
    m_currentState = newState;
    // Load state-specific data pointer from table (indexed by state)
    // s_stateDataTable is a static array of void* defined elsewhere
    m_stateData = s_stateDataTable[newState];
}