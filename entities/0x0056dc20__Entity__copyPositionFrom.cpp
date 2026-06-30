// FUNC_NAME: Entity::copyPositionFrom
void Entity::copyPositionFrom(Entity* source) {
    // Call internal initialization/copy helper
    DoSomethingPre(this, source);

    // Copy 3-component vector from source offset +0x10 to this offset +0x30
    // Typically a position or direction in local space
    m_transform.position.x = source->m_localPosition.x;   // +0x10 -> +0x30
    m_transform.position.y = source->m_localPosition.y;   // +0x14 -> +0x34
    m_transform.position.z = source->m_localPosition.z;   // +0x18 -> +0x38
    m_transform.position.w = DAT_00e2b1a4;                // +0x1c not used; set w to default (likely 1.0f for homogeneous coordinate)
}