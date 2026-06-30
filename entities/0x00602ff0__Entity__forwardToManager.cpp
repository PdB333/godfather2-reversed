// FUNC_NAME: Entity::forwardToManager
void __thiscall Entity::forwardToManager(uint32_t param_2) {
    // Calls a function on the manager stored at offset 0x20
    // The manager pointer is passed as the first argument (this might be e.g., SimManager or StreamManager)
    FUN_006054b0(*(uint32_t *)(this + 0x20), param_2);
}