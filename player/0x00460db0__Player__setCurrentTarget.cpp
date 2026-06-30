// FUNC_NAME: Player::setCurrentTarget

void __thiscall Player::setCurrentTarget(int targetHandle, char bForce)
{
    int resolvedTarget = FUN_004211e0(targetHandle);  // resolveHandle(targetID)
    if (resolvedTarget != 0 && (bForce != 0 || resolvedTarget != *(int*)(this + 0x20c)))
    {
        *(int*)(this + 0x20c) = resolvedTarget;  // +0x20c: current target pointer
        FUN_0045ddf0(this, resolvedTarget);      // applyTarget(this, target)
    }
}