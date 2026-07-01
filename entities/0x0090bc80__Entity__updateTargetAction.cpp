// FUNC_NAME: Entity::updateTargetAction
void Entity::updateTargetAction(Entity* pEntity, Entity* pTarget, int* outActionObject, float* outDistance)
{
    if (pEntity == nullptr || pTarget == nullptr) {
        return;
    }

    *outActionObject = 0;
    *outDistance = 0.0f;

    // Get distance to target (likely from some spatial system)
    *outDistance = getDistanceToTarget(pTarget);

    // Check target flags: bit 0 at +0x1f57 must be clear, and bits 4-6 at +0x1f98 must be set
    // These likely indicate target is valid (not dead, in appropriate state)
    if (hasFlag(pTarget, 2) == false &&
        ((~pTarget->m_bFlag1F57 & 1) != 0) &&
        ((pTarget->m_nState1F98 & 0x70) != 0))
    {
        // Get global game manager (e.g., GameplayManager)
        GameManager* pManager = getGameManager(g_pGameManager);
        if (pManager != nullptr)
        {
            // Check if some condition (e.g., time or distance) is within threshold
            // Fields at +0x40 and +0x4c are likely floats (e.g., currentTime and lastEventTime)
            if ((pManager->m_fField40 - pManager->m_fField4C) <= g_fMaxDistance)
            {
                // Create or retrieve an action object (e.g., a combat action or interaction)
                int actionObj = getActionObject(0);
                *outActionObject = actionObj;
                pEntity->m_pActionObject3100 = actionObj;  // Store on entity at +0x3100
            }
        }
    }
}