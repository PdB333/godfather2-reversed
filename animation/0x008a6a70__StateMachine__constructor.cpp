// FUNC_NAME: StateMachine::constructor

#include <cstdint>

// Forward declaration of base constructor
extern void __thiscall baseConstructor(int param);

// External symbols for vtable and function tables
extern void* PTR_FUN_00d79a94;
extern void* PTR_LAB_00d79a84;
extern void* PTR_LAB_00d79a80;

class StateMachine {
public:
    // vtable pointer at +0x00
    void* vtable;
    // +0x3C: pointer to function table (e.g., state machine interface)
    void* field_0x3C;
    // +0x48: pointer to another function table
    void* field_0x48;
    // +0x58: number of states
    int stateCount;
    // +0x5C: current state index
    int currentState;
    // +0x60: flag (e.g., active/inactive)
    int someFlag;
    // +0x64: short field (e.g., sub-state or timer)
    short field_0x64;
    // +0x66: short field
    short field_0x66;
    // +0x68: int field (e.g., transition data)
    int field_0x68;

    // Constructor
    StateMachine* __thiscall constructor(int param);
};

StateMachine* __thiscall StateMachine::constructor(int param) {
    // Call base class constructor (likely EARS::Framework::Object or similar)
    baseConstructor(param);

    // Set vtable pointer for this class
    this->vtable = &PTR_FUN_00d79a94;

    // Set up function tables for multiple inheritance or interface
    this->field_0x3C = &PTR_LAB_00d79a84;
    this->field_0x48 = &PTR_LAB_00d79a80;

    // Initialize state machine parameters
    this->stateCount = 12;   // Number of states
    this->currentState = 1;  // Start in state 1
    this->someFlag = 0;      // Not active initially

    // Zero out remaining fields
    this->field_0x64 = 0;
    this->field_0x66 = 0;
    this->field_0x68 = 0;

    return this;
}