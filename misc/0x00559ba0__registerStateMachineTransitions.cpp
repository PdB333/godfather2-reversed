// FUNC_NAME: registerStateMachineTransitions
void registerStateMachineTransitions(void)
{
    // Structure: pointer to label, three function pointers, two byte fields
    struct TransitionEntry {
        const char* label;          // +0x00: pointer to label string
        void (*func1)();            // +0x04: first callback
        void (*func2)();            // +0x08: second callback
        void (*func3)();            // +0x0C: third callback
        uint8_t field1;             // +0x10: byte field
        uint8_t field2;             // +0x11: byte field
    } entry;

    // First transition: from state 0x1e to state -1 (any?)
    entry.label = (const char*)0x00559a20;  // label address
    entry.func1 = (void (*)())0x00559b20;
    entry.func2 = (void (*)())0x00559a40;
    entry.func3 = (void (*)())0x00559ac0;
    entry.field1 = 0;
    entry.field2 = 0;
    registerTransitionTable(&entry, 0x1e, 0xffffffff);  // param1=30, param2=-1

    // Second transition: from state -1 to state 0x1e
    entry.label = (const char*)0x00559a20;  // same label
    entry.func1 = (void (*)())0x00559b50;
    entry.func2 = (void (*)())0x00559a70;
    entry.func3 = (void (*)())0x00559af0;
    entry.field1 = 0;
    entry.field2 = 0;
    registerTransitionTable(&entry, 0xffffffff, 0x1e);  // param1=-1, param2=30

    return;
}