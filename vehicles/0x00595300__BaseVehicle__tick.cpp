// FUNC_NAME: BaseVehicle::tick
void BaseVehicle::tick(float deltaTime)
{
    // Update motion/physics with delta time
    updateMotion(deltaTime);

    // Check if some condition (e.g., active state) is met
    bool isActive = isEnabled();  // FUN_00595610

    // Set/clear flag at offset 0x7c, bit 0x200 (corresponds to some state flag)
    if (!isActive) {
        m_flags &= ~0x200;  // +0x7c
    } else {
        m_flags |= 0x200;
    }

    // Call virtual method (likely offset 4 in vtable) to apply movement or rendering
    // Parameters: (0, m_someScale * deltaTime, 0, 1.0f, &m_position)
    // m_someScale is at +0x158, m_position is at +0xc0
    (this->vtable[1])(0, m_someScale * deltaTime, 0, 1.0f, &m_position);
}