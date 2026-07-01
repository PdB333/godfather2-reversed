// FUNC_NAME: BehaviorComponent::updateSeek
void __fastcall BehaviorComponent::updateSeek(BehaviorComponent* this)
{
    // Get target ID from manager (+0x0c pointer, +0x22c offset)
    int targetID = *(int*)(*(int*)(this + 0x0c) + 0x22c);
    
    // Check if target exists and is different from current target (+0x18)
    if ((targetID != 0) && (this->m_currentTarget != targetID))
    {
        // Current state (+0x04) must not be 7 or 1
        int currentState = this->m_state;
        if (currentState != 7)
        {
            if (currentState != 1)
            {
                // Reset seek timer (+0x14) and transition to state 1 (seek)
                this->m_seekTimer = 0;
                BehaviorComponent::setState(currentState, 1, 0);
                this->m_state = 1;
            }
            // Start movement to target
            BehaviorComponent::startMoveTo(targetID);
        }
    }
}