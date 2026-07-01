// FUNC_NAME: GameComponent::onAction
bool __thiscall GameComponent::onAction(int this, int param_2, int param_3, int actionId, int param_5)
{
    uint8_t result = 0;
    int* ownerPtr;
    int ownerState;

    switch(actionId) {
        case 0xA:   // ACTION_CHECK_IS_NOT_STATE_4? Actually checks not equal to state at +0xC4
            ownerPtr = *(int**)(this + 0x50); // +0x50: m_pOwner (pointer to owning entity)
            if(ownerPtr != 0) {
                ownerState = *(int*)(ownerPtr + 0xC4); // +0xC4: m_nState (e.g. construction phase)
                return *(int*)(this + 0x54) != ownerState; // +0x54: some target state? Possibly m_nExpectedState
            }
            break;
        case 0xB:   // ACTION_CHECK_OWNER_STATE_IS_0
            ownerPtr = *(int**)(this + 0x50);
            if(ownerPtr != 0) {
                return *(int*)(ownerPtr + 0xC4) == 0;
            }
            break;
        case 0xC:   // ACTION_CHECK_OWNER_STATE_IS_1
            ownerPtr = *(int**)(this + 0x50);
            if(ownerPtr != 0) {
                return *(int*)(ownerPtr + 0xC4) == 1;
            }
            break;
        case 0xD:   // ACTION_CHECK_OWNER_STATE_IS_2
            ownerPtr = *(int**)(this + 0x50);
            if(ownerPtr != 0) {
                return *(int*)(ownerPtr + 0xC4) == 2;
            }
            break;
        case 0xE:   // ACTION_CHECK_OWNER_STATE_IS_3
            ownerPtr = *(int**)(this + 0x50);
            if(ownerPtr != 0) {
                return *(int*)(ownerPtr + 0xC4) == 3;
            }
            break;
        case 0xF:   // ACTION_CHECK_OWNER_STATE_IS_4
            ownerPtr = *(int**)(this + 0x50);
            if(ownerPtr != 0) {
                return *(int*)(ownerPtr + 0xC4) == 4;
            }
            break;
        default:
            // Delegate to base class handler
            result = FUN_004ac640(param_2, param_3, actionId, param_5);
    }
    return result;
}