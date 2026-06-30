// FUNC_NAME: AnimationManager::updateAnimations
// Address: 0x005715d0
// This function updates a linked list of animation nodes, starting from the manager node itself (which acts as a sentinel).
// It handles forward/reverse playback, time scaling, and triggers completion callbacks.

#include <cstdint>

// Forward declarations
uint32_t ScaleAndConvert(float value); // FUN_00578990 - converts scaled time to tick/frame
void HandleAnimationFinish(); // FUN_00572580 - called when an animation finishes

// Global time scale factor (_DAT_011260b0)
extern float gTimeScale;

class AnimationNode {
public:
    uint32_t flags;           // +0x10: bitmask: bit0-1 = playing? bit18 = reverse, bit28 = finished
    char     state;           // +0x30: 0 = active, non-zero = paused/stopped
    float    elapsedTime;     // +0x78: accumulated time
    void*    callbackData;    // +0x110: pointer to associated data (non-null indicates callback pending)
    float    callbackAccum;   // +0x114: additional time accumulator for callback
    AnimationNode* next;      // +0x124: next node in list
    float    speed;           // +0x130: playback speed multiplier
};

// The manager object itself is a node in the list (sentinel).
// It possesses the same fields as AnimationNode.

class AnimationManager : public AnimationNode {
public:
    // __thiscall: this in ESI (by convention)
    uint32_t UpdateAnimations(float deltaTime) {
        AnimationNode* currentNode = this; // start at sentinel
        uint32_t result = 0;

        do {
            // Update direction flag based on deltaTime sign
            if (deltaTime >= 0.0f) {
                flags &= ~0x40000; // clear reverse flag
            } else {
                flags |= 0x40000;  // set reverse flag
            }

            // Compute scaled time step
            float timeScale = currentNode->speed * gTimeScale;
            float scaledDelta = timeScale * deltaTime;

            // Check if this is a non-sentinel, active, playing animation that just finished
            if ((currentNode != this) &&
                (currentNode->state == 0) &&
                ((currentNode->flags & 3) != 0) &&
                ((currentNode->flags >> 28) & 1) != 0) {
                // Clear finished flag and trigger completion
                currentNode->flags &= ~0x10000000;
                HandleAnimationFinish();
            }

            // Convert scaled time to some tick/unit
            result = ScaleAndConvert(scaledDelta);

            // Update callback accumulator if callback data is present
            if (currentNode->callbackData != nullptr) {
                currentNode->callbackAccum += deltaTime;
            }

            // Update main elapsed time
            currentNode->elapsedTime += deltaTime;

            // Advance to next node
            currentNode = currentNode->next;
        } while (currentNode != nullptr);

        // Return high byte of the last conversion (used for status/alignment?)
        return result & 0xffffff00;
    }
};
// Note: The function uses register ESI to hold 'this' (the AnimationManager*).
// The sentinel node is processed first, then all subsequent nodes in the linked list.
// Flags at +0x10: bit18 (0x40000) for play direction, bits 0-1 for play state, bit28 for finished.