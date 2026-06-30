// FUNC_NAME: Entity::checkOwnerAndActivate
byte __thiscall Entity::checkOwnerAndActivate(int this, uint ownerParam, int activationParam)
{
    byte retVal = 0;
    // Get pointer to owner field from ownerParam (maybe an ID or pointer)
    int* ownerFieldPtr = (int*)lookupOwnerField(&ownerParam, ownerParam); // FUN_00698c00

    // Check if the stored owner does not equal this+4 (presumably this->owner)
    if (*ownerFieldPtr != (this + 4)) {
        // Call method at offset 0x20 on the current owner (vtable slot?)
        invokeOwnerAction(*ownerFieldPtr + 0x20); // FUN_004d3e20
        // Dispatch an event using string ID and activation parameter
        retVal = dispatchEvent(&DAT_0120546e, activationParam); // FUN_004d6f20
    }
    return retVal;
}