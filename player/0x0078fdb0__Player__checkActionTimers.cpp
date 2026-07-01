// FUNC_NAME: Player::checkActionTimers
// Address: 0x0078fdb0
// Checks two timers for player actions. Uses EARS engine time if global game time flag is set.

extern bool g_useGameTime; // DAT_0112a53c
extern void getEarsTime(int* timeLow, int* timeHigh); // FUN_00826510

void Player::checkActionTimers() {
    // Check first action timer (using index at +0xA0)
    if (m_activeActionIndex != -1) {
        int currentTime = 0;
        if (g_useGameTime) {
            int timeLow, timeHigh;
            getEarsTime(&timeLow, &timeHigh); // reads 8-byte timestamp
            currentTime = timeHigh + timeLow * 0x3c; // some conversion (seconds? frames?)
        }
        // Array of timestamps at +0x54, stride 8 bytes; compare against deadline
        int* deadlines = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x54);
        if (deadlines[m_activeActionIndex * 2] < currentTime) {
            handleActionTimeout(); // FUN_0078fcd0
        }
    }

    // Check second action timer (index at +0x9C)
    if (m_secondaryActionIndex != -1) {
        int state = checkSomeState(); // FUN_00791300; returns 0 if ready
        if (state == 0) {
            char canPerform = canTriggerAction(); // FUN_0078f680
            if (canPerform) {
                performSecondaryAction(); // FUN_0078fd60
                return; // early exit after performing action
            }
        }
    }
}