// FUNC_NAME: Entity::setParent
// Function address: 0x006657a0
// Sets the parent pointer (at offset +0x08) after validating that the new parent is valid and not self.
// Returns the validated pointer on success, or 0 on failure (also clears the parent pointer).

int __thiscall Entity::setParent(void* this, void* newParent) {
    // Check if newParent is not the same object and if validation succeeds
    if (newParent != this) {
        int validationResult = FUN_00665ce0(); // Returns non-zero (the validated parent pointer) on success
        if (validationResult != 0) {
            return validationResult; // Return the validated pointer
        }
    }
    // Clear parent pointer (offset +0x8) and return failure
    *(int*)((int)this + 8) = 0;
    return 0;
}