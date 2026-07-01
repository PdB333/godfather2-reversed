// FUNC_NAME: PlayerState::CheckChanged
// Address: 0x0098bc00
// Role: Checks if a state derived from two member fields has changed, using a temporary context guard mechanism.

class PlayerState {
public:
    // +0x240: Some current state value
    // +0x244: Previous state value used for comparison
    int field_0x240;
    int field_0x244;

    // ... other fields ...

    bool CheckChanged(int param);
};

// External functions (addresses as in the binary)
extern void PushContext(int param);                   // 0x004d3bc0
extern void InitContextGuard(void* guard);            // 0x004d3b50 - initializes a context guard struct
extern void ProcessSomething();                       // 0x004d5570 - intermediate processing
extern int ComputeValue(int a, int b);               // 0x0098b5d0 - computes current value from two inputs

// Context guard structure (stack-based cleanup)
struct ContextGuard {
    int data[3];        // first element used as flag
    void (*cleanup)(int); // function pointer for destructor
};

bool PlayerState::CheckChanged(int param) {
    // Push a new context using the parameter
    PushContext(param);

    // First context guard
    ContextGuard guard1;
    InitContextGuard(&guard1);

    // Intermediate processing
    ProcessSomething();

    // Destroy first guard (if active)
    if (guard1.data[0] != 0) {
        guard1.cleanup(guard1.data[0]);
    }

    // Second context guard
    ContextGuard guard2;
    InitContextGuard(&guard2);

    // Compute current value from the two member fields
    int newValue = ComputeValue(this->field_0x240, this->field_0x244);
    int oldValue = this->field_0x244;

    // Destroy second guard (if active)
    if (guard2.data[0] != 0) {
        guard2.cleanup(guard2.data[0]);
    }

    // Return true if the computed value differs from the stored previous value
    return newValue != oldValue;
}