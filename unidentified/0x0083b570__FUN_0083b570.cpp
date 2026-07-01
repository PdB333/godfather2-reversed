// FUNC_NAME: UnknownClass::containsStruct
// Function address: 0x0083b570
// Role: Linear search for a 16-byte (4 int) struct in an array.
// Parameters: array (ECX), key (ESI), count (EDI) – passed in registers.
// Returns 1 if found, 0 otherwise.

bool __fastcall containsStruct(int const* array, int const* key, int count)
{
    for (int i = 0; i < count; i++)
    {
        // Each array element is 4 ints (16 bytes)
        if (array[i * 4 + 0] == key[0] &&
            array[i * 4 + 1] == key[1] &&
            array[i * 4 + 2] == key[2] &&
            array[i * 4 + 3] == key[3])
        {
            return true;
        }
    }
    return false;
}