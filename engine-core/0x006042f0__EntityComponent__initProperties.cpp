// FUNC_NAME: EntityComponent::initProperties
void __thiscall EntityComponent::initProperties(PropertyManager* propertyManager, const char* value1, const char* value2, void* unknownContext) {
    // Call base initialization
    baseInitialize();

    // Set a flag (0x1f = 31, possibly a bitmask for properties to load)
    setGlobalFlag(0x1f);

    // Set first property: key stored at DAT_00e325c4, value from param_2 (value1)
    propertyManager->setStringProperty(DAT_00e325c4, value1);

    // Initialize member object at offset +0xb4 (size unknown)
    initMemberObject(this + 0xb4);

    // Set second property: key stored at DAT_00e4086c, value from param_3 (value2)
    propertyManager->setStringProperty(DAT_00e4086c, value2);

    // Initialize member object at offset +0xc4
    initMemberObject(this + 0xc4);
}