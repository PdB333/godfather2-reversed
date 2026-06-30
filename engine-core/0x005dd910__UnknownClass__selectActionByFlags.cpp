// FUNC_NAME: UnknownClass::selectActionByFlags

uint UnknownClass::selectActionByFlags(uint inputFlags)
{
    // Mask input flags with global filter at 0x00f15b80
    uint maskedFlags = gActionFlagMask & inputFlags;

    // Combine two global flags: required set at 0x00f15b78 and 0x00f15b7c
    uint requiredFlags = gActionRequiredFlag1 | gActionRequiredFlag2;
    uint testFlags = requiredFlags & maskedFlags;

    // Condition:
    // 1. Not all required flags present?
    // 2. (Exclusion flag at 0x012056c0 set) OR (some required flags present AND member field at +0x2BC lacks the mask)?
    if (testFlags != requiredFlags &&
        ((gActionExclusionFlag & maskedFlags) != 0 ||
         (testFlags != 0 && (*(uint*)(this + 0x2BC) & maskedFlags) == 0)))
    {
        // Alternative action pointer at +0x294
        return *(uint*)(this + 0x294);
    }
    // Default action pointer at +0x254
    return *(uint*)(this + 0x254);
}