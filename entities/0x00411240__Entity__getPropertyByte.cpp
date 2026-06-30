// FUNC_NAME: Entity::getPropertyByte
bool __thiscall Entity::getPropertyByte(uint8_t* outByte)
{
    // Offset 0x4EC: pointer to array of property objects (each 4 bytes pointer to a property struct)
    uint32_t* propertyArray = *(uint32_t**)(this + 0x4EC);
    // Offset 0x565: byte index into the property array
    uint8_t propertyIndex = *(uint8_t*)(this + 0x565);

    // Each property object's first field is a vtable pointer
    uint32_t* propertyVtable = *(uint32_t**)(propertyArray + propertyIndex);
    // Vtable offset 0x1C (function index 7) - a method that fills a buffer and returns success
    typedef bool (__thiscall *PropertyGetValueFunc)(void* param, uint32_t* buffer);
    PropertyGetValueFunc getValueFunc = (PropertyGetValueFunc)(propertyVtable[7]);

    uint32_t buffer[2];
    bool success = getValueFunc(this, buffer); // Note: this might not be the correct this pointer; the function might take a property-specific this.
    if (success)
    {
        // Convert first buffer element to byte using a conversion function at 0x49A8D0
        *outByte = FUN_0049a8d0(buffer[0]); // Assume FUN_0049a8d0(uint32_t) -> uint8_t
        return true;
    }
    return false;
}