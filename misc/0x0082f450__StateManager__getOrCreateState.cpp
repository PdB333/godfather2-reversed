// FUNC_NAME: StateManager::getOrCreateState

class StateManager {
public:
    int* vtable;             // +0x00
    uint currentIndex;       // +0x04
    void*** stateArray;      // +0x08  pointer to array of state pointers
    int stateCount;          // +0x0c

    // Returns a pointer to an initialized state buffer
    // param_2: output buffer to receive the state data
    // param_3: identifier to match a state (e.g., state type)
    void* getOrCreateState(void* outputBuffer, uint identifier);
};

// Forward declarations for internal helper functions
uint mapIdentifierToIndex(uint id);               // 0x0082c4d0
void fallbackHandler();                           // 0x00825340
bool compareIdentifier(void* state, uint id);     // 0x00835a00
void applyStateToOutput(void* state, void* output); // 0x00825640  (fills output from state)
void constructDefaultState(void* output);         // 0x0081f9f0
void preInitDefaults();                           // 0x008334a0

// Global constants (probably default vector/matrix data)
extern uint gDefaultData;         // _DAT_00d5780c
extern uint gConstantData1;       // DAT_00d5d7b8
extern uint gConstantData2;       // DAT_00e44620
extern uint gConstantData3;       // DAT_00d5ef88
extern uint gConstantData4;       // DAT_00e44980

extern void* gDefaultVTable;      // PTR_LAB_00d73454

void* StateManager::getOrCreateState(void* outputBuffer, uint identifier) {
    void** fallbackPointers[20];   // local_90
    void* selectedState;

    if (stateCount != 0) {
        if (stateCount == 1) {
            // Only one state in the pool, use that one
            selectedState = *stateArray[0];
        } else {
            uint index = mapIdentifierToIndex(identifier);
            if (index == 0xFFFFFFFF) {
                // Mapping failed, use fallback
                fallbackHandler();
                selectedState = fallbackPointers; // fallback array
            } else {
                currentIndex = index;

                // Compute next index (wrap around)
                int nextIndex = (index < stateCount - 1) ? (index + 1) : 0;

                // Get state pointers for current and next
                void* currentState = stateArray[index];
                void* nextState = stateArray[nextIndex];

                // Check if we should use the next state instead
                if (compareIdentifier(nextState, identifier)) {
                    selectedState = currentState; // use current
                } else {
                    selectedState = nextState;
                }
            }
        }
        // Apply the selected state to the output buffer
        applyStateToOutput(selectedState, outputBuffer);
        return outputBuffer;
    }

    // First-time initialization: build default state from globals
    preInitDefaults();

    // Fill local fallback array with default vtable pointer
    fallbackPointers[0] = &gDefaultVTable;

    // Copy default data into the fallback array
    void* defaultData[8];
    for (int i = 0; i < 8; i++) {
        defaultData[i] = (void*)(uintptr_t)gDefaultData;
    }

    // Additional constant data
    uint constants[4] = { gConstantData1, gConstantData2, gConstantData3, gConstantData4 };

    // Construct default state from fallback array
    constructDefaultState(fallbackPointers);

    // Write the finalized state into the output buffer
    ((void**)outputBuffer)[0] = &gDefaultVTable;          // offset 0x00
    ((void**)outputBuffer)[0x14] = (void*)(uintptr_t)constants[0];
    ((void**)outputBuffer)[0x15] = (void*)(uintptr_t)constants[1];
    ((void**)outputBuffer)[0x16] = (void*)(uintptr_t)constants[2];
    ((void**)outputBuffer)[0x17] = (void*)(uintptr_t)constants[3];
    for (int i = 0; i < 8; i++) {
        ((void**)outputBuffer)[0x18 + i] = defaultData[i];
    }

    return outputBuffer;
}