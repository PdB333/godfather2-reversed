// FUNC_NAME: EARSObject::initFromName
void __thiscall EARSObject::initFromName(EARSObject *this, int *propertyBag, const char *nameString)
{
    // Initialize the property bag (clear and set defaults)
    propertyBagInit(propertyBag);           // FUN_004086d0
    propertyBagSetDefaults(propertyBag);    // FUN_00408310

    // If a non-empty name string is provided, compute its hash and store it
    if ((nameString != nullptr) && (*nameString != '\0')) {
        unsigned int nameHash = computeStringHash(nameString); // FUN_004dafd0
        propertyBagSetHash(propertyBag, nameHash);             // FUN_00408260

        // If the bag now contains valid data (non-zero first member), apply it to this object
        if (*propertyBag != 0) {
            applyPropertyBagToObject(this, propertyBag); // FUN_00407e60
        }
    }
}