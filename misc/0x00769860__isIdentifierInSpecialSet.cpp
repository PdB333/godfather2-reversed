// FUNC_NAME: isIdentifierInSpecialSet
// Function at 0x00769860: checks if some identifier (from FUN_0045eea0) matches a set of hardcoded IDs.
// First set: 7 IDs at 0xd65c04 to 0xd65c20 (exclusive). Second set: 1 ID at 0xd65c24.
// Returns 1 if match found, 0 otherwise.

#define ARRAY1_START 0xd65c04
#define ARRAY1_END   0xd65c20  // exclusive, so 7 ints
#define ARRAY2_START 0xd65c24
#define ARRAY2_END   0xd65c28  // exclusive, so 1 int

int getSomeIdentifier(void); // from FUN_0045eea0

bool isIdentifierInSpecialSet(void)
{
    int identifier;
    int *arrayPtr;

    identifier = getSomeIdentifier();

    // Check first array (7 entries)
    arrayPtr = (int *)ARRAY1_START;
    while (arrayPtr < (int *)ARRAY1_END)
    {
        if (identifier == *arrayPtr)
        {
            return true;
        }
        arrayPtr++;
    }

    // Check second array (1 entry)
    arrayPtr = (int *)ARRAY2_START;
    while (arrayPtr < (int *)ARRAY2_END)
    {
        if (identifier == *arrayPtr)
        {
            return true;
        }
        arrayPtr++;
    }

    return false;
}