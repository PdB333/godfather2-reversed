// FUN_00665bd0: SimObject::compareByType
int SimObject::compareByType(SimObject* other) {
    // Offset 8 is likely a type or class ID
    int thisType = *(int*)((uint)this + 8);
    int otherType = *(int*)((uint)other + 8);

    if (thisType != otherType) {
        // Return -1 if thisType equals 1, otherwise 1
        return (thisType == 1) ? -1 : 1;
    }

    // Types match; delegate to a more detailed comparison
    if (thisType == 1) {
        return FUN_00665c30(); // detailed comparison for type 1
    }
    return FUN_00665c30(); // detailed comparison for other types
}