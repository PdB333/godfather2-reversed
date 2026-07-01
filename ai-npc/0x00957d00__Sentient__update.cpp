// FUNC_NAME: Sentient::update
// Function address: 0x00957d00
// Role: Per-frame update for Sentient entities (players, NPCs, etc.). 
// Checks global pause state, then either handles a special state (if flag at +0x51 is set) or normal update.

struct Sentient {
    // +0x51: flag indicating a special state (e.g., knocked down, stunned, or cinematic)
    char m_bSpecialFlag;
};

// Forward declarations of internal update helpers
char isGlobalPaused();          // 0x00976440 – returns true if global pause is active
void handleSpecialState();      // 0x00956e50 – update logic for special state
void handleNormalState();       // 0x00957880 – default update logic

char Sentient::update() {
    // If the game is globally paused (e.g., menu, cutscene), skip all updates
    if (isGlobalPaused()) {
        return 0;
    }

    // Check special flag at offset +0x51
    if (this->m_bSpecialFlag) {
        handleSpecialState();
        return 1;
    }

    // Normal update path
    handleNormalState();
    return 1;
}