// FUNC_NAME: Entity::processDeferredActions
void Entity::processDeferredActions()
{
    // Release resource pair at +0xa0/+0xa4 if not null
    if (m_pResource1 != nullptr)
    {
        releasePair(m_pResource1, m_pResource2);
    }

    // State check: if state not 0, 3, or 5, call reset function
    if (m_state != 0 && m_state != 3 && m_state != 5)
    {
        resetState();
    }

    // Set flag bit 3 (0x8) to indicate processing
    m_flags |= 0x8;

    int count = m_deferredCount;
    if (m_flags & 0x200)
    {
        // If deferred flag set, decrement global counter and exit early
        g_globalCounter -= count;
        return;
    }

    // Process each deferred action pair
    for (int i = 0; i < count; i++)
    {
        int* pairBase = &m_deferredActions[i * 2];
        int first = pairBase[0];
        int second = pairBase[1];
        if (first != 0 && g_actionEnabled != 0)
        {
            executeDeferredAction(first, second);
        }
    }
}