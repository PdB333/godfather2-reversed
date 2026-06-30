// FUNC_NAME: getDataTypeSize
// Function address: 0x0061a8f0
// Returns the size (in bytes) of a data type based on its type ID.
// Type IDs 0x1e-0x23 (30-35) are 4-byte types; all others are 1-byte types.
// Parameter is passed in EAX (likely __fastcall or register-based calling convention).

int getDataTypeSize(int dataType)
{
    // Check if the type ID is one of the special 4-byte types.
    if (dataType != 0x1e && dataType != 0x1f && dataType != 0x20 &&
        dataType != 0x21 && dataType != 0x22 && dataType != 0x23)
    {
        return 1; // 1-byte type
    }
    return 4; // 4-byte type
}