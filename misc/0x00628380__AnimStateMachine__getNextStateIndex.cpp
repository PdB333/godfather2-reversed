// FUNC_NAME: AnimStateMachine::getNextStateIndex

// Function at 0x00628380 - Extracts an integer state index from a node in a linked list.
// The class has a member at offset 0x8 that stores a pointer to the "next" field of the current node.
// Node structure (8-byte header, then data):
//   +0x00: int type (3=direct, 4=blend reference)
//   +0x04: float value (the state index as float for type 3; for type 4 it needs conversion)
//   +0x08: Node* next (pointer to next node's 'next' field?)
//   +0x0C: Node* prev (likely)
// The function reads the current node, if type is 4 it resolves the blend reference via a helper.
// If the resulting state index is 0, it retries the same node (maybe for fallback) and returns -1 if still 0.
// Finally calls a logging/cleanup function.

#include <cstdint>
#include <cstddef>

// Forward declaration
int resolveBlendValue(uint32_t* outValue); // FUN_00636850
void animationLog(); // FUN_006255e0

struct AnimBlendNode {
    int type;          // +0x00: 3 = direct value, 4 = blend reference
    float value;       // +0x04: as float for type 3; for type 4, value is an index or key
    AnimBlendNode* next; // +0x08: pointer to next node's 'next' field (head stored in container)
    AnimBlendNode* prev; // +0x0C: pointer to previous node's 'next' field
};

class AnimStateMachine {
public:
    int getNextStateIndex(); // FUN_00628380

private:
    // Members:
    // +0x00: ... (unknown)
    // +0x08: AnimBlendNode* currentNextPtr; // pointer to current node's next field (i.e., &node->next)
};

int AnimStateMachine::getNextStateIndex() {
    AnimBlendNode* node;
    int result;
    uint32_t convertedValue; // local_10
    AnimBlendNode tempNode;  // local_8 and local_c (stack-based temporary node)

    // Get the current node from the internal iterator (pointer to the node's next field)
    node = (AnimBlendNode*)(*(int*)(this + 8) - 8);
    if (node == nullptr) {
        result = 0; // fVar4 = 0.0, then iVar2 = (int)0.0 = 0
    } else {
        if (node->type != 3) {
            if (node->type == 4) {
                // Blend reference: resolve to direct value
                if (resolveBlendValue(&convertedValue) != 0) {
                    // Build a temporary node of type 3 with the resolved value
                    tempNode.type = 3;
                    tempNode.value = *(float*)&convertedValue; // reinterpret as float
                    node = &tempNode; // use temporary node
                } else {
                    goto zeroResult;
                }
            } else {
                goto zeroResult;
            }
        }
        // node->type is 3 (direct value) or resolved
        result = (int)node->value; // truncate float to int (state index)
    }
    // If the state index is 0, try to get an alternative state from the same node
    if (result == 0) {
        node = (AnimBlendNode*)(*(int*)(this + 8) - 8);
        if (node != nullptr) {
            int type2 = node->type;
            if (type2 == 3) {
                // Fall through to endpoint
            } else if (type2 == 4) {
                if (resolveBlendValue(&convertedValue) != 0) {
                    // If resolved, also fall through (but result remains 0)
                } else {
                    result = -1;
                }
            } else {
                result = -1;
            }
        } else {
            result = -1;
        }
    }
    // Logging / finalization
    animationLog();
    return result;
}