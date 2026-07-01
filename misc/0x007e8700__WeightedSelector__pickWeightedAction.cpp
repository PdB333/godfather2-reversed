// FUNC_NAME: WeightedSelector::pickWeightedAction
// Address: 0x007e8700
// This function performs weighted random selection from two sets of actions (primary and secondary),
// respecting cooldowns and validity checks. It is used by AI or dialog systems to pick a behavior or dialog line.

// Based on global timestamp g_currentTime (DAT_01205224) and cooldown per action.

// Structures
struct WeightedAction1 {
    float weight;          // +0x00
    int actionId;          // +0x04 (index into g_allowedActionIDs)
    int padding;           // +0x08 (unused in this function)
};

struct WeightedAction1Cooldown {
    uint32_t cooldownEnd;  // +0x00 (if currentTime < cooldownEnd, action is available)
    uint32_t unknown;      // +0x04 (unused here)
};

struct WeightedAction2 {
    int actionId;          // +0x00 (nonzero means valid)
    int unknown1;          // +0x04
    float weight;          // +0x08
    int unknown2;          // +0x0c
    uint32_t cooldownEnd;  // +0x10
    int unknown3;          // +0x14
};

// External globals (approximate names)
extern uint32_t g_currentTime;              // DAT_01205224
extern int* g_allowedActionIDs[];           // DAT_00d6fc18 (array of action IDs for first set)
extern float g_randScale;                   // DAT_00e44590 (1.0 / RAND_MAX)

// External helper declarations (implemented elsewhere)
bool isActionValid(int actionId);           // FUN_00800ee0
bool triggerAction(int actionId, uint32_t type, uint32_t target, int unused); // FUN_007f96a0

// __thiscall method
int WeightedSelector::pickWeightedAction(int* parentObj, uint32_t target, char isImportant) {
    // parentObj likely is a pointer to some container (e.g., a character or manager)
    // +0x1c: array of WeightedAction1 (69 entries)
    // +0x354: array of WeightedAction1Cooldown (69 entries, stride 8)
    // +0x57c: array of WeightedAction2 (20 entries, stride 24)

    float totalWeight = 0.0f;
    uint32_t chosenIndex1 = 0xFFFFFFFF; // -1
    int chosenAction2 = 0;
    uint32_t numAvailable1 = 0;
    uint32_t numAvailable2 = 0;
    uint32_t availableIndices1[69]; // auStack_114
    uint32_t availableIndices2[20]; // auStack_164

    uint32_t currentTime = g_currentTime;

    // Parse primary actions (set 1)
    WeightedAction1* actions1 = reinterpret_cast<WeightedAction1*>(this + 0x1c);
    WeightedAction1Cooldown* cooldowns1 = reinterpret_cast<WeightedAction1Cooldown*>(this + 0x354);

    for (uint32_t i = 0; i < 69; ++i) {
        if ((currentTime < cooldowns1[i].cooldownEnd) && (i < 69)) {
            if (isActionValid(g_allowedActionIDs[i])) {
                totalWeight += actions1[i].weight;
                availableIndices1[numAvailable1++] = i;
            }
        }
    }

    // Parse secondary actions (set 2)
    WeightedAction2* actions2 = reinterpret_cast<WeightedAction2*>(this + 0x57c);
    for (uint32_t i = 0; i < 20; ++i) {
        if ((actions2[i].actionId != 0) && (currentTime < actions2[i].cooldownEnd)) {
            if (isActionValid(actions2[i].actionId)) {
                totalWeight += actions2[i].weight;
                availableIndices2[numAvailable2++] = i;
            }
        }
    }

    if (numAvailable1 + numAvailable2 == 0) {
        return 0; // No available actions
    }

    // Weighted random selection
    float randomVal = (float)rand() * g_randScale * totalWeight; // [0, totalWeight)

    // First try primary set
    uint32_t i = 0;
    for (; i + 3 < numAvailable1; i += 4) {
        float w;
        w = actions1[availableIndices1[i]].weight;
        if (randomVal <= w) { chosenIndex1 = availableIndices1[i]; break; }
        randomVal -= w;

        w = actions1[availableIndices1[i+1]].weight;
        if (randomVal <= w) { chosenIndex1 = availableIndices1[i+1]; break; }
        randomVal -= w;

        w = actions1[availableIndices1[i+2]].weight;
        if (randomVal <= w) { chosenIndex1 = availableIndices1[i+2]; break; }
        randomVal -= w;

        w = actions1[availableIndices1[i+3]].weight;
        if (randomVal <= w) { chosenIndex1 = availableIndices1[i+3]; break; }
        randomVal -= w;
    }
    for (; i < numAvailable1; ++i) {
        float w = actions1[availableIndices1[i]].weight;
        if (randomVal <= w) { chosenIndex1 = availableIndices1[i]; break; }
        randomVal -= w;
    }

    // If no selection from set 1, try secondary set
    if (chosenIndex1 == 0xFFFFFFFF) {
        i = 0;
        for (; i + 3 < numAvailable2; i += 4) {
            float w;
            w = actions2[availableIndices2[i]].weight;
            if (randomVal <= w) { chosenAction2 = actions2[availableIndices2[i]].actionId; break; }
            randomVal -= w;

            w = actions2[availableIndices2[i+1]].weight;
            if (randomVal <= w) { chosenAction2 = actions2[availableIndices2[i+1]].actionId; break; }
            randomVal -= w;

            w = actions2[availableIndices2[i+2]].weight;
            if (randomVal <= w) { chosenAction2 = actions2[availableIndices2[i+2]].actionId; break; }
            randomVal -= w;

            w = actions2[availableIndices2[i+3]].weight;
            if (randomVal <= w) { chosenAction2 = actions2[availableIndices2[i+3]].actionId; break; }
            randomVal -= w;
        }
        for (; i < numAvailable2; ++i) {
            float w = actions2[availableIndices2[i]].weight;
            if (randomVal <= w) { chosenAction2 = actions2[availableIndices2[i]].actionId; break; }
            randomVal -= w;
        }

        if (chosenAction2 != 0) {
            uint32_t type = (isImportant != 0) ? 3 : 1;
            if (triggerAction(chosenAction2, type, target, 0)) {
                // Mark cooldown? (set timestamp on parent object?)
                *(uint32_t*)(parentObj + 0x205c) = g_currentTime;
                return 1;
            }
        }
    } else {
        uint32_t type = (isImportant != 0) ? 3 : 1;
        if (triggerAction(g_allowedActionIDs[chosenIndex1], type, target, 0)) {
            *(uint32_t*)(parentObj + 0x205c) = g_currentTime;
            return 1;
        }
    }

    return 0;
}