// FUNC_NAME: MovementController::setTarget
void __thiscall MovementController::setTarget(int this, float targetX, float targetY)
{
    // Store the target coordinates
    *(float *)(this + 0xe4) = targetX;   // +0xe4: m_targetX
    *(float *)(this + 0xe8) = targetY;   // +0xe8: m_targetY

    // Check if movement is idle, and navigation resources are present
    int navState = *(int *)(this + 0xe0); // +0xe0: m_navState (0 = idle)
    int pathfinder = *(int *)(this + 0x88); // +0x88: m_pathfinder
    int steering = *(int *)(this + 0x90);   // +0x90: m_steering

    if (navState == 0 && pathfinder != 0 && steering != 0)
    {
        // Snap current position/orientation to the stored target data
        *(float *)(this + 0xfc) = *(float *)(this + 0xf8);   // +0xf8: m_desiredX, +0xfc: m_currentX
        *(float *)(this + 0x108) = *(float *)(this + 0x104); // +0x104: m_desiredY, +0x108: m_currentY
        *(float *)(this + 0x10c) = *(float *)(this + 0x110); // +0x110: m_desiredZ? +0x10c: m_currentZ? (or angle)
        FUN_005fea70(1); // Trigger movement start (probably applies velocity/steering)
    }
}