// FUNC_NAME: CooldownManager::tryExecute
// Function address: 0x00652fe0
// Role: Checks if an action is allowed based on cooldown timer and usage count.
// Returns 1 if action can be executed (and executes if needed), 0 otherwise.

class CooldownManager {
public:
    // +0x124: Block flag - if nonzero, action is blocked
    int m_blockFlag;
    // +0x118: Timestamp of last action (ms)
    int m_lastActionTime;
    // +0xb0: Base delay between actions (ms)
    unsigned int m_baseDelayMs;
    // +0xb4: Maximum usage count before unlimited mode
    unsigned int m_maxUses;
    // +0xb8: State flags (bit2=0x4, bit3=0x8 checked)
    unsigned char m_flags[4]; // actually 4 bytes but only byte accessed
    // +0x94: First target/context pointer (for comparison)
    void* m_targetA;
    // +0x98: Second target/context pointer
    void* m_targetB;
    // +0x114: Current usage count
    unsigned int m_useCount;

    // Called when action is performed (from FUN_006539b0)
    void onActionPerformed();
};

__thiscall int CooldownManager::tryExecute(int currentTimeMs) // currentTimeMs likely from ESI (game timer)
{
    if (m_blockFlag != 0) {
        return 0; // blocked
    }

    // Initialize last action time to current time if not set
    if (m_lastActionTime == 0) {
        m_lastActionTime = currentTimeMs;
    }

    unsigned int delay = m_baseDelayMs;
    unsigned int maxUses = m_maxUses;

    // Check special state flags (bits 0x4 and 0x8)
    if ((m_flags[0] & 0xc) != 0) {
        // Special mode: compare target pointers
        if (m_targetB == m_targetA) {
            // Same target: restrict to 4 uses, long delay (60000) if not used yet
            maxUses = 4;
            if (m_useCount == 0) {
                delay = 60000;
            } else {
                delay = 3000;
            }
        } else {
            // Different target: shorter delay (3000)
            delay = 3000;
        }
    }

    // Check if enough time has passed
    if (currentTimeMs - m_lastActionTime >= (int)delay) {
        if (m_useCount >= maxUses) {
            // Already reached limit – action allowed without further throttling
            return 1;
        }
        // Perform action: update timer, increment count, and call handler
        m_lastActionTime = currentTimeMs;
        m_useCount++;
        onActionPerformed(); // FUN_006539b0
    }
    return 0; // not ready yet
}