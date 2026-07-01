// FUNC_NAME: Object::updateStep
void __thiscall Object::updateStep(Object* this) {
    // Call virtual function at vtable offset 0x2c (likely an update or process method)
    (*(void(__thiscall**)(Object*))*((int*)this + 0x2c / 4))();

    // Build a small event structure from a global constant and zeros, then dispatch it
    struct DebugEvent {
        int type;   // +0x00
        int param1; // +0x04
        char param2; // +0x08
    };
    DebugEvent event;
    event.type = *(int*)0x01130310; // Global constant, likely an event type ID
    event.param1 = 0;
    event.param2 = 0;
    dispatchDebugEvent(&event, 0); // FUN_00408a00 - sends event to debug/log system
}