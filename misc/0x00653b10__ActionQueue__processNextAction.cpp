// FUNC_NAME: ActionQueue::processNextAction

// This function is part of a timed action queue system.
// It advances the linked list of pending actions and either processes
// or skips the current node based on the 'instant' flag and timer state.
// The object layout and constants are derived from Ghidra decompilation.

struct ActionNode {
    char active;          // +0x00: boolean – node is active (non-zero)
    int  actionId;        // +0x04: identifier for this action
    ActionNode* next;     // +0x10: next node in the queue
};

// Forward declaration of global release function (FUN_009c8eb0)
void releaseActionNode(ActionNode* node);

class ActionQueue {
private:
    void** vtable;                               // +0x00
    int currentActionId;                         // +0x2b
    uint8_t flags;                               // +0x2e – bit 2 and 3 control timer modes
    uint8_t actionActiveFlag;                    // +0x3d – set when processing a non‑active node
    ActionNode* currentNode;                     // +0x47
    float timerAccumulator;                      // +0x6e (stored as int but used as float)
    float timerMax;                              // +0x6f

public:
    // __thiscall – the 'instant' parameter is passed in AL register
    void processNextAction(char instant);
};

void ActionQueue::processNextAction(char instant) {
    // Get the current node and advance the queue to the next one
    ActionNode* oldNode = this->currentNode;                   // pcVar2 = param_1[0x47]
    this->currentNode = oldNode->next;                         // param_1[0x47] = *(pcVar2+0x10)

    if (oldNode->active == 0) {
        // Node is inactive
        if (instant != 0) {
            // Fall through to the processing path (active check passed)
            goto process_node;
        }
    } else {
        // Node is active
        if (instant != 0) {
process_node:
            // Store the action ID
            this->currentActionId = oldNode->actionId;         // param_1[0x2b] = *(pcVar2+4)

            // Check timer update flags
            if ((this->flags & 0x0C) != 0) {
                float acc = this->timerAccumulator;            // fVar1 = (float)param_1[0x6e]
                if (acc < this->timerMax) {
                    // Timer still below maximum — accumulate more time
                    this->timerAccumulator = acc + *(float*)0x00e2b1a4;   // DAT_00e2b1a4 (kTimerIncrement)
                    // Call virtual function at vtable+0x3c to process this node
                    typedef void (*ProcessNodeFunc)(ActionNode*);
                    ProcessNodeFunc process = (ProcessNodeFunc)(this->vtable[0x3c / 4]);
                    process(oldNode);
                    releaseActionNode(oldNode);
                    return;
                }
                // Check additional threshold
                if (acc < *(float*)0x00e2afb8) {               // DAT_00e2afb8 (kAccMin)
                    this->timerAccumulator = *(float*)0x00e2b1a4 / acc + acc; // non‑linear update
                }
            }
            // Process the node (no timer condition or timer already satisfied)
            typedef void (*ProcessNodeFunc)(ActionNode*);
            ProcessNodeFunc process = (ProcessNodeFunc)(this->vtable[0x3c / 4]);
            process(oldNode);
            releaseActionNode(oldNode);
            return;
        } else {
            // instant == 0 and node active: set the active flag
            this->actionActiveFlag = 1;                        // *(param_1+0x3d) = 1
        }
    }

    // Fall‑through path: node either inactive with instant==0, or active with instant==0
    // (also reached if node inactive but instant!=0 ??? actually the goto jumps out)
    // This section updates the idle timers and then calls the skip virtual.

    float minTimer = *(float*)0x00e2b04c;                     // DAT_00e2b04c (kTimerMin)

    if ((this->flags & 0x0C) != 0) {
        // Scale timerMax down by a constant multiplier
        float newMax = this->timerMax * *(float*)0x00e2cd54;  // DAT_00e2cd54 (kTimerMaxMultiplier)
        if (newMax < minTimer) {
            newMax = minTimer;
        }
        this->timerMax = newMax;
        // Decrement timerAccumulator
        float acc = this->timerAccumulator - *(float*)0x00e2b1a4; // subtract the constant
        this->timerAccumulator = acc;
        if (acc < minTimer) {
            this->timerAccumulator = minTimer;
        }
    }

    // Call virtual function at vtable+0x40 for skipping the node
    typedef void (*SkipNodeFunc)(ActionNode*);
    SkipNodeFunc skip = (SkipNodeFunc)(this->vtable[0x40 / 4]);
    skip(oldNode);
    releaseActionNode(oldNode);
}