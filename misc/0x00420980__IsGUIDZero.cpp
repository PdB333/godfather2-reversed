// FUNC_NAME: IsGUIDZero
bool __fastcall IsGUIDZero(const int* guid) {
    // Check if all four 32-bit components are zero (128-bit GUID)
    if (guid[0] == 0 && guid[1] == 0 && guid[2] == 0 && guid[3] == 0) {
        return true;
    }
    return false;
}