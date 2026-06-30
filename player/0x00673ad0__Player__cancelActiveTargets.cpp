// FUNC_NAME: Player::cancelActiveTargets
void Player::cancelActiveTargets(int isCancel)
{
    // Clear active flag
    this->m_bActionInProgress = 0; // +0x104

    if (isCancel > 0)
    {
        // Primary target slot
        if (this->m_targetId1 != 0 && this->m_targetObject1 != 0) // +0x118 and +0x30
        {
            if (this->m_targetId1 == this->m_pOwner->m_currentInteractionId) // +0x4 -> +0x48
            {
                // Mark as re-usable
                this->m_pOwner->m_bInteractionReserved = 1; // +0x80
            }
            else
            {
                this->deactivateTarget(); // FUN_00673160
            }
            this->m_targetId1 = 0; // +0x118
        }

        // Secondary target slot
        if (this->m_targetId2 != 0 && this->m_targetObject2 != 0) // +0x11c and +0x34
        {
            this->deactivateTarget();
            this->m_targetId2 = 0; // +0x11c
        }
    }
}