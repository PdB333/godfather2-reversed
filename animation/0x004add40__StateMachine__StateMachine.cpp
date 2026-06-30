// FUNC_NAME: StateMachine::StateMachine
void __thiscall StateMachine::StateMachine(void* param_1) // param_1 likely the 'this' pointer; unaff_EDI is register artifact
{
    // Memory allocation debug: tag the allocation with class name
    FUN_004d3bc0("kStateMachine_"); // sets allocation tag for memory tracking
    
    // Call base class constructor or initializer with this pointer
    FUN_004d4300(param_1);
    
    // local_10 and local_4 come from stack decoration (compiler-inserted allocation cookie)
    // These are not real locals but represent the memory block header placed above the object
    undefined1* header = local_10; // pointer to allocation header (or null if no header)
    if (header == nullptr) {
        header = &DAT_0120546e; // default static header placeholder
    }
    
    // Read size/capacity from member at offset 0x18 (e.g., m_maxStates or m_stateCount)
    uint32_t uVar4 = *(uint32_t*)((uint8_t*)param_1 + 0x18);
    uint32_t uVar3 = 0;
    
    // Initialize state machine internals; returns a handle or pointer
    uint32_t uVar2 = FUN_004dafd0(header, 0, uVar4); // likely allocates state array or registers transitions
    
    // Second initialization call (e.g., set default state)
    FUN_004adc90(uVar2, uVar3, uVar4);
    
    // If a dynamic allocation header existed, call its destructor (cleanup function stored by allocator)
    // This pattern is typical of EA's memory system where the header contains a destructor callback
    if (local_10 != nullptr) {
        (*(void (*)(void*))local_4)(local_10); // call destructor on the memory block
    }
    return;
}