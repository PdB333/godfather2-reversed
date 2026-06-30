// FUNC_NAME: Entity::isAnyComponentActive
bool Entity::isAnyComponentActive(int componentId) const
{
    // Check first subcomponent at offset +0x1c
    if (m_component1.isActive(componentId))
    {
        return true;
    }

    // Check second subcomponent at offset +0x28
    if (m_component2.isActive(componentId))
    {
        return true;
    }

    return false;
}