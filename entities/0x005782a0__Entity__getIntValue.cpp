// FUNC_NAME: Entity::getIntValue
int Entity::getIntValue(void)
{
    int* ptr;
    
    // Check flag at +0x2c (bit 5) and count at +0x0
    if (((this->flags & 0x20) == 0) || (this->count < 3)) {
        // Special case: if flag set and count == 2, return direct value at +0x40
        if (((this->flags & 0x20) != 0) && (this->count == 2)) {
            return this->directValue;
        }
        // If pointer at +0x30 is non-null, return -1 (error)
        if (this->pointerCheck != 0) {
            return -1;
        }
        ptr = (int*)this->primaryPointer; // +0x34
    }
    else {
        // Use alternate pointer at +0x38
        ptr = (int*)this->secondaryPointer; // +0x38
    }
    
    if (ptr == (int*)0x0) {
        return -1;
    }
    return *ptr; // Dereference to get the integer value
}