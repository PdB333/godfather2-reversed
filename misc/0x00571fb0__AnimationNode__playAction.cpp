// FUNC_NAME: AnimationNode::playAction
// Address: 0x00571fb0
// This function traverses the animation tree to a specified child node (by index) and initiates an action.
// If actionId is -1, it only clears flags. Otherwise, it sets up the action with various parameters.
// The function manipulates motion pointers, speed calculations, and flag bits to control animation playback.

#include <cstdint>

// Forward declarations of called functions (from other modules)
void FUN_005826b0(void* motionPtr, void* node, uint32_t param);
void FUN_005786c0(int actionId);
int FUN_00571d70(); // Returns a pointer to some data (used for speed calculation)

// Global constants (from data section)
extern float DAT_00e2b1a4;      // Base position offset?
extern float _DAT_011260b0;     // Some scaling factor (e.g., animation length?)
extern float DAT_00e35654;      // Speed multiplier
extern float DAT_00e2cb90;      // Speed cap
extern float _DAT_00e446b8;     // Deceleration factor

// Forward declaration of the class (assumed from offsets)
class AnimationNode {
public:
    // Offsets based on decompiled code (all offsets relative to this pointer)
    // +0x10: Flags (uint32)
    // +0x14: Some previous integer (action ID?)
    // +0x24: Position or blend value (float)
    // +0x10c: Pointer to motion object
    // +0x110: Action counter / start flag (int)
    // +0x114: Previous speed (float)
    // +0x118: Computed speed (float)
    // +0x11c: Some integer (e.g., loop count or phase)
    // +0x120: Byte parameter (stores param_5)
    // +0x121: Another byte (set to 0 when instant)
    // +0x124: Next child pointer (AnimationNode*)
    // +0x2f0: Extra pointer (used for alternate speed calculation)

    uint32_t flags;                    // +0x10
    int previousActionId;              // +0x14 (saved before call)
    float positionBlend;               // +0x24
    void* motionPtr;                   // +0x10c
    int actionCounter;                 // +0x110
    float previousSpeed;               // +0x114
    float computedSpeed;               // +0x118
    int loopOrPhase;                   // +0x11c
    uint8_t byteParam;                 // +0x120
    uint8_t extraByte;                 // +0x121
    AnimationNode* nextChild;          // +0x124
    void* extraPointer;                // +0x2f0
};

uint8_t __thiscall AnimationNode::playAction(int childIndex, int actionId, bool instantFlag, uint32_t unusedParam, uint8_t paramByte, uint32_t extraParam)
{
    uint8_t result = 0;

    // Validate this pointer and child index
    if (this == nullptr || childIndex < 0)
        return 0;

    // Traverse the sibling chain to reach the specified child index
    AnimationNode* currentNode = this->nextChild; // +0x124
    int count = 0;
    if (childIndex > 0) {
        do {
            currentNode = currentNode->nextChild;
            if (currentNode == nullptr)
                return 0;
            count++;
        } while (count < childIndex);
    }

    // If no node found, return 0
    if (currentNode == nullptr)
        return 0;

    // If actionId is -1, skip all action setup and just clear flags
    if (actionId != -1) {
        result = 1; // Indicate that action was processed

        // If the node has a motion pointer, call the motion setup function
        if (currentNode->motionPtr != nullptr) {
            FUN_005826b0(currentNode->motionPtr, currentNode, extraParam);
        }

        // Save the old action ID before changing
        int savedActionId = currentNode->previousActionId; // +0x14

        // Call the action start function
        FUN_005786c0(actionId);

        // Clear bit 7 of flags (mask 0xFFFFFF7F)
        currentNode->flags &= 0xFFFFFF7F;

        // Store the byte parameter
        currentNode->byteParam = paramByte; // +0x120

        // Local constant
        float fVar8 = DAT_00e2b1a4; // Base value

        if (instantFlag) {
            // For instant transitions, save previous state
            int prevActionCount = currentNode->actionCounter; // +0x110
            float prevSpeed = currentNode->previousSpeed;    // +0x114

            // Indicate that an instant action is starting
            currentNode->actionCounter = 1;
            currentNode->extraByte = 0; // +0x121

            float speedCap = DAT_00e2cb90;

            // Compute the new speed based on available data
            if (currentNode->extraPointer == nullptr) { // +0x2f0
                // Standard calculation: ((positionBlend - base) / scale) * multiplier
                float speed = ((currentNode->positionBlend - fVar8) / _DAT_011260b0) * DAT_00e35654;
                if (speed > speedCap)
                    speed = speedCap;
                currentNode->computedSpeed = speed;
                currentNode->loopOrPhase = 0; // +0x11c
            } else {
                // Alternate calculation: retrieve data from external function
                int dataPtr = FUN_00571d70(); // Returns a pointer to a structure
                // Read speed from dataPtr+4, loop/phase from dataPtr+0xC
                currentNode->computedSpeed = *(float*)(dataPtr + 4) / _DAT_011260b0;
                currentNode->loopOrPhase = *(int*)(dataPtr + 0xC);
            }

            // If there was a previous action running (prevActionCount != 0)
            if (prevActionCount != 0) {
                if (prevActionCount < 0) {
                    // Negative counter means we need to decelerate to a stop
                    float newSpeed = (fVar8 - prevSpeed * _DAT_00e446b8) * currentNode->computedSpeed;
                    currentNode->previousSpeed = newSpeed;
                    if (newSpeed < 0.0f) {
                        // Speed has dropped below zero: clear flags and reset speed
                        currentNode->flags &= 0xEDFFFFFE; // Clear bits 0, 1, 4, 12, etc.
                        currentNode->previousSpeed = 0.0f;
                        return 1;
                    }
                    // Otherwise, go to flag clearing at the end
                    goto clearFlags;
                } else {
                    // Positive counter: if the saved action ID is -1, skip the counter reset?
                    // Fall through to later logic
                    if (savedActionId == -1) {
                        goto clearFlags;
                    }
                }
            }
        }
        // After instant block, reset action counter to 0
        currentNode->actionCounter = 0;
    }

clearFlags:
    // Clear various flag bits (mask 0xEDFFFFFE)
    currentNode->flags &= 0xEDFFFFFE;
    return result;
}