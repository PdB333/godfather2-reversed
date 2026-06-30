// FUNC_NAME: Component::attachTo
// This function attaches this component to a target object (e.g., parent node or container).
// It validates compatibility using a class-specific validator function.
// Returns 1 on success, 0 on failure.
// Offset 0x8: pointer to type descriptor (class ID byte)
// Offset 0xc in target: set to this pointer (attachment slot)
int __thiscall Component::attachTo(Component* this, Component* target)
{
    // Obtain the class ID from the type descriptor
    char* typeDescriptor = *(char**)((char*)this + 8); // +0x8: pointer to type info
    char classID = *typeDescriptor;                    // first byte is the class ID

    // If the class ID is below the threshold (10), perform class-specific validation
    if (classID < 10)
    {
        // Look up the validator function from the global dispatch table
        ValidatorFunc validator = (ValidatorFunc)PTR_FUN_0103af90[classID];
        // The validator returns non-zero if the attachment is invalid
        if (validator(target) != 0)
        {
            return 0; // Validation failed
        }
    }

    // Store this component's pointer into the target's attachment slot at offset 0xc
    *(int*)((char*)target + 0xc) = (int)this; // +0xc: "attachedComponent" field
    return 1; // Success
}