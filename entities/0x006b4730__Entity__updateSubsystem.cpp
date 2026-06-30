// FUNC_NAME: Entity::updateSubsystem
void __thiscall Entity::updateSubsystem(int param_2, int param_3) {
    // +0x9c: embedded subsystem object (e.g., MovementComponent, AIBehavior)
    FUN_006b45e0(reinterpret_cast<int>(this) + 0x9c, param_2, param_3);
}