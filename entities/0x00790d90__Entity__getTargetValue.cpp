// FUNC_NAME: Entity::getTargetValue
// Function at 0x00790d90: Returns a value from either a direct member or a nested component, depending on state.
// Offsets:
// +0x9c: m_pComponent (pointer to a component/state object)
// +0xcc: m_directValue (direct member value)
// +0x20ec: offset within component for the target value (e.g., m_targetValue)
// 0x48: constant representing a specific component type (e.g., kComponentTypeDisabled)

int __fastcall Entity::getTargetValue(Entity* this) {
    char isValid;
    
    // Check if component pointer is valid and not a disabled type (0x48)
    if ((this->m_pComponent != nullptr) && (this->m_pComponent != (Component*)0x48)) {
        // Additional validity check via helper function
        isValid = FUN_007f4800(); // likely isComponentActive() or similar
        if (isValid != 0) {
            // Return value from component's target field
            if (this->m_pComponent != nullptr) {
                return *(int*)((char*)this->m_pComponent + 0x20ec);
            }
            // Fallback to global default (should not reach here normally)
            return g_defaultValue;
        }
    }
    // Return direct member value
    return this->m_directValue;
}