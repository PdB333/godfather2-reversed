// FUNC_NAME: GameCountManager::decrementPendingCount
// Function address: 0x006a5690
// Role: Decrements a pending operation count on the global manager when a specific condition (param_2 == 0) is met.
// Global pointer DAT_011299b0 points to the singleton GameCountManager instance.
// Offset 0x6a0 is the pending count member.

class GameCountManager {
public:
    static GameCountManager* sInstance; // DAT_011299b0

    // +0x6a0: int pendingCount
    void decrementPendingCount(int conditionFlag) {
        // Only decrement if conditionFlag == 0, the manager is valid, and count is positive
        if ((conditionFlag == 0) && (sInstance != nullptr) && (sInstance->pendingCount > 0)) {
            sInstance->pendingCount--;
        }
    }

private:
    int pendingCount; // offset 0x6a0 (read as int at sInstance + 0x6a0)
};

// Static definition (actual address in binary)
GameCountManager* GameCountManager::sInstance = (GameCountManager*)0x011299b0; // Approximated from DAT