// FUNC_NAME: compareEntityIDs
bool __cdecl compareEntityIDs(int id1, int id2, const int* handle1, const int* handle2)
{
    // Return false if any parameter is null/invalid or type bytes don't match expected values
    if (handle1 == nullptr || handle2 == nullptr)
        return false;
    if (id1 == 0 || id2 == 0)
        return false;
    // Check type bytes at offset +2: handle1 must be type 0x02, handle2 type 0x01
    if (((uint8_t*)handle1)[2] != 0x02 || ((uint8_t*)handle2)[2] != 0x01)
        return false;

    // Extract base offset from the first field
    // If the field is zero, treat as zero; otherwise subtract 0x48 to get the ID
    int derived1 = (handle1[0] != 0) ? handle1[0] - 0x48 : 0;
    if (derived1 != id2)
        return false;

    int derived2 = (handle2[0] != 0) ? handle2[0] - 0x48 : 0;
    if (derived2 != id1)
        return false;

    return true;
}