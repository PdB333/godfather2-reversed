// FUNC_NAME: Entity::checkAndTrigger
void __thiscall Entity::checkAndTrigger(void) {
    // offset 0x360: some flag (e.g., mission active, damage state, or input)
    if (*(int*)(this + 0x360) != 0) {
        // 0x0055d7d0: unknown function, called with argument 2 (likely a message or event)
        FUN_0055d7d0(2);
    }
}