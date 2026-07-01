// FUNC_NAME: NetObject::setGuid
void __thiscall NetObject::setGuid(int thisPtr, int *guid)
{
    char isValid;
    int guid0;
    int somePtr;
    int managerPtr;

    guid0 = *guid;
    // Check if guid is all zeros or matches a known invalid GUID
    if (((((guid0 != 0) || (guid[1] != 0)) || (guid[2] != 0)) || (guid[3] != 0)) &&
       (((guid0 != 0xbbdbdbba) || (guid[1] != 0xbeefbeef)) ||
        ((guid[2] != 0xeac15a55) || (guid[3] != 0x91100911)))) {
        *(int *)(thisPtr + 0x14) = guid0;
        *(int *)(thisPtr + 0x18) = guid[1];
        *(int *)(thisPtr + 0x1c) = guid[2];
        *(int *)(thisPtr + 0x20) = guid[3];
        // If this object's type (offset 8) is non-zero and not 0x48 (perhaps a null or abstract type)
        if ((*(int *)(thisPtr + 8) != 0) && (*(int *)(thisPtr + 8) != 0x48)) {
            managerPtr = FUN_00791300(); // SimManager::get() or similar
            if (managerPtr != 0) {
                if (*(int *)(managerPtr + 0x74c) == 0) {
                    somePtr = 0;
                } else {
                    somePtr = *(int *)(managerPtr + 0x74c) - 0x48; // Adjust pointer to container
                    if (somePtr != 0) {
                        isValid = FUN_00461f90(guid); // Validate GUID
                        if (isValid == '\0') {
                            return;
                        }
                    }
                }
                FUN_0072d1e0(guid); // Register/attach GUID to manager
                int result = FUN_007f41e0(); // Get player/entity manager
                if (result != 0) {
                    FUN_004abc20(0x40); // Notify or spawn effect
                }
                if ((somePtr != 0) && (*(char *)(somePtr + 0x1a8) == '\x01')) {
                    FUN_004088c0(somePtr + 0x3c); // Update component or transform
                }
            }
        }
    }
    return;
}