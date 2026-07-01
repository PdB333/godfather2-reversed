// FUNC_NAME: Player::setPoliceChaseState
// Address: 0x009411a0
// Role: Updates the police chase state for a Player object and logs the change.
// Offset +0xB4: m_policeChaseState (int) - current police chase state index

void __thiscall Player::setPoliceChaseState(int param_2)
{
    char formattedValue[16];

    // Only update if the new state differs from the current one
    if (param_2 != this->m_policeChaseState) {
        this->m_policeChaseState = param_2;

        // Format the state as a string and log it via the debug system
        __snprintf(formattedValue, 16, "%d", param_2);
        debugPrint("SetPoliceChaseState", 0, &DAT_00d8b2cc, 1, formattedValue);
    }
}