// FUNC_NAME: PathFollower::advanceWaypoints

// Function address: 0x0058b530
// This function appears to handle advancing through waypoints in a path following system.
// It manages swapping waypoint nodes based on a callback and applies speed adjustments.

#include <cstdint>

// Forward declarations of called functions
void assertIndex(float* stackValue); // FUN_00591c00
bool evaluatePathCondition(void* thisPtr, int nodeData, int* stackData, uint32_t flags); // FUN_005918f0
float* getStackFloat(int* stackData); // FUN_0058abc0
void onPathChangedCallback(); // FUN_00581e90 (likely empty or logging)
uint32_t computePathProgress(void* thisPtr, int* stackData, float param4, float param5, uint32_t param6, uint32_t param9); // FUN_00590360
void applySpeedModifier(float param4); // FUN_0058aca0
uint32_t clampToRange(float value, uint32_t param6); // FUN_005832d0
void recordDebugPush(); // FUN_0056fb60 (called twice)

// Assumed constants (from data references)
extern float DAT_00e2eff4;  // Some maximum threshold (e.g., 1.0f)
extern float DAT_00e2b05c;  // Some comparison value (e.g., 0.0f)
extern float DAT_00e2b1a4;  // Some speed factor (e.g., 0.5f)

// Structure for path data (param_2)
struct WaypointData {
    int unknown1;           // +0x0
    short* indexArray;      // +0x4  Points to array of short indices
    short someOtherIndex;   // +0x2 (note: offset 2 from start of param_2? Actually param_2+2 is short)
    int nodeEntries[1];     // +0xC  Array of pointers to node data (variable length)
};

// Structure for stack data (param_3)
struct StackData {
    float* values;          // +0x0
    int size;               // +0x4
};

// Structure for path state (accessed via this+0x7c)
struct PathState {
    int field_0x10;         // +0x10 (used as bitmask)
    int field_0x1c;         // +0x1c
    float field_0x20;       // +0x20
    int field_0x68;         // +0x68 (node index)
};

// Main function
uint32_t PathFollower::advanceWaypoints(void* thisPtr, WaypointData* pathData, StackData* stackData,
                                        float distance, float lateralOffset, uint32_t flags,
                                        bool (*callback)(void*, WaypointData*, StackData*),
                                        uint32_t mode, uint32_t extraParam, float speed)
{
    short* indices = pathData->indexArray;
    short currentShort = *indices;
    if ((uint32_t)stackData->size <= (uint32_t)(int16_t)currentShort) {
        float tempZero = 0.0f;
        assertIndex(&tempZero);
    }
    int nextNodeIndex = (int)*(float*)(stackData->values + currentShort * sizeof(float));
    currentShort = indices[1];
    if ((uint32_t)stackData->size <= (uint32_t)(int16_t)currentShort) {
        float tempZero = 0.0f;
        assertIndex(&tempZero);
    }
    int prevNodeIndex = (int)*(float*)(stackData->values + currentShort * sizeof(float));
    
    bool isMode2 = (mode == 2);
    bool needSwap = false;
    
    // Determine if we need to swap the order based on direction flags
    if (((flags >> 1) ^ flags) & 1) {
        // Odd parity: move forward if distance < lateralOffset
        if (lateralOffset < distance) {
            needSwap = true;
        }
    } else {
        // Even parity: move forward if distance >= lateralOffset and not (lateralOffset < 0 && distance < 0)
        if (distance >= 0.0f || (lateralOffset < 0.0f)) {
            // No swap
        } else {
            if (distance < lateralOffset) {
                needSwap = true;
            }
        }
    }
    
    int currentIndex = nextNodeIndex;
    bool pathChanged = false;
    
    // Check if we need to update the waypoint (e.g., if current index is invalid, or mode==2, or mode<2 and needSwap != isMode2)
    if ((nextNodeIndex == -1) || isMode2 || ((mode < 2) && (needSwap != isMode2))) {
        int newIndex = (*callback)(thisPtr, pathData, stackData);
        if (nextNodeIndex != newIndex) {
            // Update the stack: swap the two waypoint indices
            currentShort = *indices;
            if ((uint32_t)stackData->size <= (uint32_t)(int16_t)currentShort) {
                float tempZero = 0.0f;
                assertIndex(&tempZero);
            }
            stackData->values[currentShort * sizeof(float)] = (float)newIndex;
            
            currentShort = indices[1];
            if ((uint32_t)stackData->size <= (uint32_t)(int16_t)currentShort) {
                float tempZero = 0.0f;
                assertIndex(&tempZero);
            }
            stackData->values[currentShort * sizeof(float)] = (float)nextNodeIndex;
            
            currentShort = indices[3]; // Third index?
            if ((uint32_t)stackData->size <= (uint32_t)(int16_t)currentShort) {
                float tempZero = 0.0f;
                assertIndex(&tempZero);
            }
            stackData->values[currentShort * sizeof(float)] = distance;
            
            pathChanged = true;
            currentIndex = newIndex;
            prevNodeIndex = nextNodeIndex;
        }
    }
    
    // Validate current index
    if ((currentIndex < 0) || (currentIndex >= (int)(pathData->nodeEntries[0] & 0xFF))) {
        return 0;
    }
    
    int nodeDataPtr = *(int*)((char*)pathData + 0xC + currentIndex * 4);
    uint32_t floatIndex = (uint32_t)(*(short*)(nodeDataPtr + 2)); // Some offset into stack
    if ((uint32_t)stackData->size <= floatIndex) {
        float tempZero = 0.0f;
        assertIndex(&tempZero);
    }
    float currentStackValue = stackData->values[floatIndex];
    
    uint32_t anotherIndex = (uint32_t)(*(short*)((char*)pathData + 2)); // offset 2 from pathData
    if ((uint32_t)stackData->size <= anotherIndex) {
        uint32_t zeroIdx = 0;
        assertIndex((float*)&zeroIdx);
    }
    uint32_t anotherValue = *(uint32_t*)(stackData->values + anotherIndex * sizeof(float));
    
    if (pathChanged) {
        // Update state flags
        uint32_t newFlag = ((uint32_t)(*(char*)((*(uint32_t*)((char*)thisPtr + 0x7c) + 0x10) >> 5)) << 8) | (anotherIndex & 0xFFFFFF01);
        bool conditionResult = evaluatePathCondition(thisPtr, nodeDataPtr, stackData, newFlag);
        float maxSpeed = DAT_00e2eff4;
        
        if (conditionResult) {
            // Path changed successfully? Set state values
            PathState* state = (PathState*)((char*)thisPtr + 0x7c);
            state->field_0x1c = 0;
            state->field_0x20 = maxSpeed;
            state->field_0x68 = currentIndex;
            distance = 0.0f;
            lateralOffset = maxSpeed;
            prevNodeIndex = -1;
            float* stackFloat = getStackFloat(stackData);
            *stackFloat = maxSpeed;
        } else {
            if (isMode2) {
                // Save parameters on stack and call callback? Probably records debug info.
                float savedDistance = distance;
                float savedLateral = lateralOffset;
                uint32_t savedAnother = anotherValue;
                float savedStackValue = currentStackValue;
                uint32_t savedExtra = extraParam;
                uint32_t savedFlags = flags;
                onPathChangedCallback();
                distance = savedDistance;
                lateralOffset = savedLateral;
            }
        }
    }
    
    // Compute main progress along path
    uint32_t result = computePathProgress(thisPtr, stackData, distance, lateralOffset, flags, extraParam);
    
    // Apply speed-based offset if conditions met
    if ((speed != DAT_00e2b05c) && (prevNodeIndex >= 0) && (prevNodeIndex != currentIndex) &&
        (prevNodeIndex < (int)(*(char*)((char*)pathData + 1)))) {
        float* stackFloat = getStackFloat(stackData);
        float currentStackFloat = *stackFloat;
        uint32_t secondResult = computePathProgress(thisPtr, stackData, currentStackFloat, currentStackFloat, flags, extraParam);
        stackFloat = getStackFloat(stackData);
        float newStackFloat = *stackFloat;
        
        if ((currentStackValue < newStackFloat) && (currentStackValue - DAT_00e2b1a4 <= currentStackFloat)) {
            currentStackFloat = currentStackFloat - (currentStackValue - DAT_00e2b1a4);
        }
        
        float startVal = currentStackValue;
        float speedFactor = DAT_00e2b1a4;
        applySpeedModifier(distance);
        float offset = (startVal - currentStackFloat) * (speedFactor / speed);
        if (offset < 0.0f) {
            offset = ((newStackFloat + startVal) - currentStackFloat) * (speedFactor / speed);
        }
        if (speedFactor <= offset) {
            stackFloat = getStackFloat(stackData);
            *stackFloat = DAT_00e2eff4;
            offset = speedFactor;
        }
        uint32_t clampedResult = clampToRange(offset, flags);
        recordDebugPush();
        recordDebugPush();
        return clampedResult;
    }
    
    return result;
}