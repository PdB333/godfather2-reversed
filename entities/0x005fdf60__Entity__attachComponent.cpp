// FUNC_NAME: Entity::attachComponent
void Entity::attachComponent(Component* pComponent, uint unkParam) {
    // Release existing component if any
    if (m_pComponent != nullptr) {
        releaseComponent(m_pComponent);
        m_pComponent = nullptr;
    }

    if (pComponent != nullptr) {
        // If different component, replace and set backlink
        if (m_pComponent != pComponent) {
            if (m_pComponent != nullptr) {
                releaseComponent(m_pComponent);
            }
            m_pComponent = pComponent;
            // Store pointer to owner (backlink) in component's field at +0x04
            m_pComponentOwner = pComponent->m_ownerRef; // pComponent[1]
            pComponent->m_ownerRef = &m_pComponent; // +0x04
        }

        // Store the parameter (could be an ID or flag)
        m_componentData = unkParam; // +0x120

        // Retrieve component data via vtable
        int size = pComponent->vtable->getComponentSize(); // vtable+8
        ComponentData* pData = pComponent->vtable->getComponentData(size - 1); // vtable+12

        if (pData->m_valid != 0) {
            // Copy three values from a sub-structure (offset +0x08 in data)
            ComponentValues* pValues = pData->m_pValues; // pData[2]
            m_componentValues[0] = pValues->value0; // +0x130
            m_componentValues[1] = pValues->value1; // +0x134
            m_componentValues[2] = pValues->value2; // +0x138
        }
    }
}