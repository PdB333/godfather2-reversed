// FUNC_NAME: PropertyManager::setPropertyValue
// Function: Sets a property by index (or ID) to a given value.
// Internally calls a lookup function returning a pointer to the property's storage.
// Param1: propertyIndex - the index/ID of the property to set.
// Param2: value - the new value to write.
void setPropertyValue(int propertyIndex, uint value) {
    // getPropertyPointer returns a pointer to the property's memory location.
    // It expects a pointer to the property index (likely to handle dynamic lookup).
    uint* propertyPtr = (uint*) getPropertyPointer(&propertyIndex);
    if (propertyPtr != nullptr) {
        *propertyPtr = value;   // Write the value only if the property was found.
    }
}