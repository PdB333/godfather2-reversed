// FUNC_NAME: Debug::showObjectByType
void Debug::showObjectByType()
{
    // Get the type ID from the object's type info structure.
    // The object has a pointer to a type info structure at offset +0x10.
    // That structure's vtable has a virtual function at index 1 (offset 4) that returns a FourCC.
    uint32_t typeId = this->m_pTypeInfo->getTypeId();

    // Store the FourCC as a big-endian string in a global buffer.
    g_typeIdString[0] = (typeId >> 24) & 0xFF;
    g_typeIdString[1] = (typeId >> 16) & 0xFF;
    g_typeIdString[2] = (typeId >> 8) & 0xFF;
    g_typeIdString[3] = typeId & 0xFF;
    g_typeIdString[4] = 0; // null terminator

    // Build the property name: "<FourCC>._visible"
    char propertyName[16];
    _sprintf(propertyName, "%s._visible", g_typeIdString);

    // Set the global property to 1 (visible).
    setGlobalProperty(propertyName, 1);
}