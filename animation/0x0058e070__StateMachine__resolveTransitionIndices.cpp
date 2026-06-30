// FUNC_NAME: StateMachine::resolveTransitionIndices
// Address: 0x0058e070
// Reconstructed from Ghidra decompiler output. The function resolves a chain of up to four state transitions
// from the given input index using the current state's transition table. It writes the input and four resolved
// indices into the output array. The function then validates the path by calling a validation member function
// (FUN_0058dd70) five times; all must return true for the overall function to return true.
// Structure offsets: this+0x70 = pointer to transition table header, this+0x74 = current state (short index).
// Transition table header at +0x18 = number of states, +0x1c = pointer to array of StateData (0x18 bytes each).
// Each StateData: +0x08 = sub-array size, +0x0c = pointer to array of TransitionEntry (0x10 bytes each).
// TransitionEntry: first int at offset 0x00 is the target index.

class StateMachine {
public:
    bool resolveTransitionIndices(int input, int outIndices[5]) __thiscall {
        outIndices[0] = input;

        // Resolve first transition: from input index using current state
        short currentState = *(short*)((char*)this + 0x74);
        int index1;
        if (currentState < 0) {
            index1 = -1;
        } else {
            index1 = currentState;
            void* transitionTable = *(void**)((char*)this + 0x70);
            int numStates = *(int*)((int)transitionTable + 0x18);
            if (index1 >= numStates || input < 0) {
                index1 = -1;
            } else {
                StateData* states = *(StateData**)((int)transitionTable + 0x1c);
                int subArraySize = *(int*)((int)&states[index1] + 0x08);
                if (input >= subArraySize) {
                    index1 = -1;
                } else {
                    TransitionEntry* subArray = *(TransitionEntry**)((int)&states[index1] + 0x0c);
                    index1 = *(int*)((int)subArray + input * 0x10); // first int in struct
                }
            }
        }
        outIndices[1] = index1;

        // Resolve second transition: from index1 using same current state
        currentState = *(short*)((char*)this + 0x74);
        int index2;
        if (currentState < 0) {
            index2 = -1;
        } else {
            index2 = currentState;
            void* transitionTable = *(void**)((char*)this + 0x70);
            int numStates = *(int*)((int)transitionTable + 0x18);
            if (index2 >= numStates || index1 < 0) {
                index2 = -1;
            } else {
                StateData* states = *(StateData**)((int)transitionTable + 0x1c);
                int subArraySize = *(int*)((int)&states[index2] + 0x08);
                if (index1 >= subArraySize) {
                    index2 = -1;
                } else {
                    TransitionEntry* subArray = *(TransitionEntry**)((int)&states[index2] + 0x0c);
                    index2 = *(int*)((int)subArray + index1 * 0x10);
                }
            }
        }
        outIndices[2] = index2;

        // Resolve third transition: from index2 using same current state
        currentState = *(short*)((char*)this + 0x74);
        int index3;
        if (currentState < 0) {
            index3 = -1;
        } else {
            index3 = currentState;
            void* transitionTable = *(void**)((char*)this + 0x70);
            int numStates = *(int*)((int)transitionTable + 0x18);
            if (index3 >= numStates || index2 < 0) {
                index3 = -1;
            } else {
                StateData* states = *(StateData**)((int)transitionTable + 0x1c);
                int subArraySize = *(int*)((int)&states[index3] + 0x08);
                if (index2 >= subArraySize) {
                    index3 = -1;
                } else {
                    TransitionEntry* subArray = *(TransitionEntry**)((int)&states[index3] + 0x0c);
                    index3 = *(int*)((int)subArray + index2 * 0x10);
                }
            }
        }
        outIndices[3] = index3;

        // Resolve fourth transition: from index3 using same current state
        currentState = *(short*)((char*)this + 0x74);
        int index4;
        if (currentState >= 0) {
            index4 = currentState;
            void* transitionTable = *(void**)((char*)this + 0x70);
            int numStates = *(int*)((int)transitionTable + 0x18);
            if (index4 < numStates && index3 >= 0) {
                StateData* states = *(StateData**)((int)transitionTable + 0x1c);
                int subArraySize = *(int*)((int)&states[index4] + 0x08);
                if (index3 < subArraySize) {
                    TransitionEntry* subArray = *(TransitionEntry**)((int)&states[index4] + 0x0c);
                    index4 = *(int*)((int)subArray + index3 * 0x10);
                    goto validation;
                }
            }
        }
        index4 = -1;
validation:
        outIndices[4] = index4;

        // Validate all indices are non-negative and run validation function five times
        if (input >= 0 && index1 >= 0 && index2 >= 0 && index3 >= 0 && index4 >= 0) {
            if (!FUN_0058dd70()) return false;
            if (!FUN_0058dd70()) return false;
            if (!FUN_0058dd70()) return false;
            if (!FUN_0058dd70()) return false;
            if (!FUN_0058dd70()) return false;
            return true;
        }
        return false;
    }

private:
    // Declared as member function for validation; actual signature unknown.
    // Likely checks properties of the current state or transition chain.
    bool FUN_0058dd70() __thiscall;
};

// Helper structures matching the decompiled layout
struct StateData {
    char field_0x00[0x08]; // padding
    int subArraySize;       // +0x08
    TransitionEntry* subArray; // +0x0c pointer to array of TransitionEntry
};

struct TransitionEntry {
    int targetIndex;        // +0x00
    // 0x0C bytes padding to 0x10? Not used in this function
};