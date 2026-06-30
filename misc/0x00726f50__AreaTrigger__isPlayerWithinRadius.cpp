// FUNC_NAME: AreaTrigger::isPlayerWithinRadius
class AreaTrigger {
public:
    // Checks if the player is within the trigger's radius.
    // Offsets:
    // +0x7c : float radiusSquared (squared distance threshold)
    // +0x130: float posX (trigger's own position)
    // +0x134: float posY
    // +0x138: float posZ
    bool __fastcall isPlayerWithinRadius() {
        // Get pointer to player's position struct (likely from a singleton or manager)
        PlayerPosition* playerPos = getPlayerPositionPointer(); // iVar1
        float dx = playerPos->x - this->posX;
        float dy = playerPos->y - this->posY;
        float dz = playerPos->z - this->posZ;
        float distSq = dx*dx + dy*dy + dz*dz;
        if (distSq <= this->radiusSquared) {
            return true;
        }
        return false;
    }
};

// Helper structure for player position (offsets 0x30, 0x34, 0x38)
struct PlayerPosition {
    float x; // +0x30
    float y; // +0x34
    float z; // +0x38
};

// Forward declaration of external function returning player position pointer
// This function likely returns a pointer to a Player object or a static position buffer.
// In the binary, it's at 0x00471610.
PlayerPosition* getPlayerPositionPointer();