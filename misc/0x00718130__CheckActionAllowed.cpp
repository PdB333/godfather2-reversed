// FUNC_NAME: CheckActionAllowed
bool __fastcall CheckActionAllowed(int thisPtr)
{
    // Get pointer from offset 0x330 (likely a component pointer)
    int component = *(int*)(thisPtr + 0x330);
    int componentBase;
    if (component == 0) {
        componentBase = 0;
    } else {
        // Subtract 0x48 to get the containing structure (e.g., base class offset)
        componentBase = component - 0x48;
    }

    if (componentBase != 0) {
        // Resolve the actual component object (e.g., behavior or state)
        int behavior = FUN_0071ce70(componentBase);
        if (behavior != 0 &&
            // Check type at offset +8: not null and not 0x48 (invalid type)
            *(int*)(behavior + 8) != 0 &&
            *(int*)(behavior + 8) != 0x48) {
            // Check if action is allowed via flag at offset 0x324
            char flag = FUN_0071c320(*(int*)(thisPtr + 0x324));
            if (flag != 0) {
                return true;
            }
        }
    }
    return false;
}