// FUNC_NAME: FSMNode::updateState
typedef unsigned int uint;

// Structure representing the FSM node's internal state.
// Offsets are in bytes.
struct FSMNode {
    uint state;        // +0x00: current state ID
    uint subState;     // +0x04: sub-state or counter
    uint someData;     // +0x14: data used in transitions (e.g., ID)
    void* objectPtr;   // +0x18: pointer to associated object (or sentinel 0x48)
};

// External functions
extern void FUN_007f97a0(void* p);  // likely memory deallocation
extern void FUN_0045f250(uint data); // unknown

// __fastcall convention: ecx = this (param_1)
uint __fastcall FSMNode::updateState(FSMNode* this)
{
    char cVar1;
    uint uVar2;
    int* piVar3;
    int unaff_ESI;
    uint* local_4;

    // Check if objectPtr is null or a special sentinel (0x48)
    if ((this->objectPtr == 0) || (this->objectPtr == (void*)0x48)) {
        uVar2 = 0;
        local_4 = (uint*)this;
    }
    else {
        // Interpret objectPtr as a pointer inside a larger structure with a vtable.
        // The object is located at (objectPtr - 0x48).
        if (this->objectPtr == 0) {
            piVar3 = (int*)0;
        }
        else {
            piVar3 = (int*)((char*)this->objectPtr - 0x48);
        }
        local_4 = (uint*)0;
        // Call virtual function at vtable+0x10 (4th entry) with a hash for type check
        cVar1 = (**(char(__fastcall**)(uint, uint**))(*piVar3 + 0x10))(0x55859efa, &local_4);
        uVar2 = -(uint)(cVar1 != 0) & (uint)local_4;
    }

    // If type matched (uVar2 != 0), free memory at address 0? (likely error handling)
    if (uVar2 != 0) {
        FUN_007f97a0(0);
    }

    // Only proceed if current state is 3 or 4
    if ((this->state != 3) && (this->state != 4)) {
        return 0;
    }

    // Second type check with different hash
    if ((this->objectPtr != 0) && (this->objectPtr != (void*)0x48)) {
        if (this->objectPtr == 0) {
            piVar3 = (int*)0;
        }
        else {
            piVar3 = (int*)((char*)this->objectPtr - 0x48);
        }
        local_4 = (uint*)0;
        cVar1 = (**(char(__fastcall**)(uint, uint**))(*piVar3 + 0x10))(0xae986323, &local_4);
        if ((cVar1 != 0) && (unaff_ESI != 0)) { // unaff_ESI is an uninitialized register (likely from caller)
            FUN_0045f250(this->someData);
        }
        // Transition to state 5
        this->state = 5;
        this->subState = 0;
        return 1;
    }

    // Default: transition to state 6
    this->state = 6;
    this->subState = 0;
    return 1;
}