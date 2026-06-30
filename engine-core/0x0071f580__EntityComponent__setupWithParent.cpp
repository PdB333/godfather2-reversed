// FUNC_NAME: EntityComponent::setupWithParent
void __fastcall EntityComponent::setupWithParent(EntityComponent* this)
{
    uint flags;
    int* parentBasePtr;
    int temp;

    // Clear bit 5 (0x20) and set bit 3 (0x08) in flags at +0x20
    flags = this->flags;
    flags &= 0xFFFFFFDF;  // Clear bit 5
    flags |= 0x08;        // Set bit 3
    this->flags = flags;

    // Assign global unique ID to +0x0C
    this->uniqueId = DAT_00d5ccf8;

    // +0x04: pointer to an embedded parent subobject (or another object)
    // If non-null, compute base pointer of the containing object (parent at offset -0x48)
    if (this->parentSubobjectPtr != 0) {
        parentBasePtr = (int*)(this->parentSubobjectPtr - 0x48);
    } else {
        parentBasePtr = 0;
    }

    // Call virtual function at vtable+0x260 on the parent object
    // This is typically an 'activate' or 'onAttach' method
    (**(code**)(*parentBasePtr + 0x260))();

    // Clear bit 2 (0x04) in flags
    this->flags &= 0xFFFFFFFB;

    // If parentSubobjectPtr is non-zero and not equal to a sentinel (0x48, maybe a special marker),
    // fetch a value from a global manager and store it at +0x18
    if ((this->parentSubobjectPtr != 0) && (this->parentSubobjectPtr != 0x48)) {
        temp = FUN_0043b870(DAT_0112afb8);  // Get singleton manager
        if (temp != 0) {
            this->playerIdOrSimilar = *(int*)(temp + 0x40);  // Copy ID from manager
        }
    }
}