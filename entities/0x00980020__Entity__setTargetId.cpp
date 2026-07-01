// FUNC_NAME: Entity::setTargetId
undefined Entity::setTargetId(int this, int targetId) {
    undefined result;
    if (targetId != -1) {
        *(int *)(this + 0x130) = targetId; // +0x130 = m_targetId
        result = FUN_0097ff40(); // Notify or update
        return result;
    }
    *(int *)(this + 0x130) = -1; // Clear target
    return 0;
}