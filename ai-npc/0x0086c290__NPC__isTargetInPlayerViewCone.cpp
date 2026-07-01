// FUNC_NAME: NPC::isTargetInPlayerViewCone
// Address: 0x0086c290
// This function checks if the NPC's current target is within the player's view cone.
// It uses the player's position and forward direction to determine if the target is in front of the player.
// The target pointer is stored at offset +0x50 of the NPC object.
// If the target is valid (non-zero and not 0x48), it computes the vector from player to target,
// normalizes it, and compares the dot product with the player's forward vector against a global threshold.
// Returns 1 if the target is within the cone, 0 otherwise.

#include <cstdint>

// Forward declarations of helper functions (assumed global or static)
float* getTargetPosition();          // Returns position of the target (likely from global state or this pointer)
int getPlayerPosition();             // Returns pointer to player's position (x,y,z at +0x30)
int getPlayerForward();              // Returns pointer to player's forward vector (x,y,z at +0x20)
void normalizeVector(float* vec);    // Normalizes the vector in place

// Global threshold for view cone (cosine of half-angle)
extern float playerViewConeThreshold; // DAT_00d62364

// NPC class with target pointer at +0x50
class NPC {
public:
    // +0x50: pointer to target entity (0 = none, 0x48 = invalid/dead)
    uint32_t targetPtr;

    // Checks if the target is within the player's view cone
    bool isTargetInPlayerViewCone() {
        // Validate target pointer
        if (targetPtr == 0 || targetPtr == 0x48) {
            return false;
        }

        // Get target position (assumed from global function)
        float* targetPos = getTargetPosition();

        // Get player position and forward direction
        int playerPosPtr = getPlayerPosition();
        int playerForwardPtr = getPlayerForward();

        // Compute vector from player to target
        float vecToTarget[3];
        vecToTarget[0] = targetPos[0] - *(float*)(playerPosPtr + 0x30);
        vecToTarget[1] = targetPos[1] - *(float*)(playerPosPtr + 0x34);
        vecToTarget[2] = targetPos[2] - *(float*)(playerPosPtr + 0x38);

        // Normalize the vector
        normalizeVector(vecToTarget);

        // Dot product with player's forward direction
        float dot = vecToTarget[0] * *(float*)(playerForwardPtr + 0x20) +
                    vecToTarget[1] * *(float*)(playerForwardPtr + 0x24) +
                    vecToTarget[2] * *(float*)(playerForwardPtr + 0x28);

        // Compare against global threshold
        if (playerViewConeThreshold < dot) {
            return true;
        }
        return false;
    }
};