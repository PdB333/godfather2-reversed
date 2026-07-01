// FUNC_NAME: Entity::equals
// Address: 0x008d0180
// Role: Compares two Entity objects for equality, likely using an internal comparison function.
bool Entity::equals(Entity* other) {
    int comparisonResult = 0; // +0x00 (local variable for output)
    char isEqual = FUN_004480d0(this, other, &comparisonResult); // Internal comparison helper
    return isEqual != 0;
}