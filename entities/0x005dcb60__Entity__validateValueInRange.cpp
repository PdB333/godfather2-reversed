// FUNC_NAME: Entity::validateValueInRange
bool __thiscall Entity::validateValueInRange(float* valueToCheck, float* otherValue)
{
    // Call some validation/initialization function; returns non-zero if valid
    int validationResult = FUN_005dc670(valueToCheck); 
    if (validationResult != 0) {
        // Perform a computation involving otherValue and this object
        FUN_005dd8a0(otherValue, this); // likely modifies or reads internal state

        // Check if the first float member of this object (offset +0x00) is in [0.0, DAT_00e2b1a4]
        // and if the external valueToCheck is also non-negative
        if ((0.0f <= this->firstFloat) && (this->firstFloat <= DAT_00e2b1a4) && (0.0f <= *valueToCheck)) {
            return true; // condition satisfied
        }
    }
    return false;
}