// FUNC_NAME: Entity::getValidatedID
void __thiscall Entity::getValidatedID(uint32_t inputID, int outPair[2])
{
    // Compute an ID from the input parameter (likely a hash or resource reference)
    int computedID = FUN_00694950(inputID);
    int storedID = *(int *)(this + 4); // +0x04: stored object ID

    // Handle null this pointer (assertion or error check)
    if (this == 0) {
        FUN_00b97aea(); // null this handler (likely assertion failure)
    }

    int firstVal;
    int secondVal;

    if (computedID != storedID) {
        // Validate the computed ID by checking a field at offset 0x0c inside some structure
        int validationResult = FUN_004d4b20(computedID + 0xc); // checks validity of resource/ID
        if (validationResult >= 0) {
            // Computed ID is valid, output (this, computedID)
            firstVal = (int)this;
            secondVal = computedID;
        } else {
            // Fall back to stored ID
            firstVal = (int)this;
            secondVal = storedID;
        }
    } else {
        // IDs match, output (this, storedID)
        firstVal = (int)this;
        secondVal = storedID;
    }

    outPair[0] = firstVal;
    outPair[1] = secondVal;
}