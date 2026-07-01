// FUNC_NAME: EARSComponent::constructor

void * __thiscall EARSComponent::constructor(EARSComponent *this, void *owner, int param3) {
    // Call base class initializer
    initializeBase(owner, param3); // FUN_008cf5d0

    // Set vtable pointer
    this->vtable = &PTR_FUN_00d7c328;

    // Initialize internal members
    this->componentPointer = nullptr; // +0x0D: pointer to a related component
    this->componentFlags = 0;         // +0x0E: integer flags
    *(uint8_t *)((uint8_t *)this + 0x0F) = 0; // +0x0F: byte flag

    // Search owner's component array for a specific type ID
    uint16_t componentCount = *(uint16_t *)((uint8_t *)owner + 0x20);
    if (componentCount != 0) {
        uint32_t **componentArray = *(uint32_t ***)((uint8_t *)owner + 0x1C);
        for (uint16_t i = 0; i < componentCount; ++i) {
            uint32_t *component = componentArray[i]; // Each entry points to a component header
            if (component[4] == 0x92CB0516) {        // Magic class ID (e.g., EARS::Component::ID)
                this->componentPointer = (void *)component[0]; // Copy first DWORD from found component
            }
        }
    }
    return this;
}