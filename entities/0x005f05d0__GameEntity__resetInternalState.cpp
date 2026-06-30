// FUNC_NAME: GameEntity::resetInternalState
void __thiscall GameEntity::resetInternalState(void) {
    byte flag = 0;          // +0x0 local_5: temporary flag
    int dummy = 0;          // +0x4 local_4: unused placeholder
    FUN_005f0600(this, &flag); // call to internal reset helper with flag parameter
    return;
}