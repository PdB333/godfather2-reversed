// FUNC_NAME: StringToIndex
// Function address: 0x0061a9f0
// Role: Looks up a string in a static table of strings (with 3-slot entries) and returns its zero-based index.
//       Returns 0 if not found (note: index 0 corresponds to the string "Invalid").
// Note: The original assembly compares two bytes at a time for efficiency. Reconstructed as standard strcmp.

#include <string.h>

int StringToIndex(const char* inputString)
{
    // Table base address (first entry is a pointer to the string "Invalid")
    // Each table entry occupies 3 pointer-sized slots (12 bytes).
    // The table ends at address 0x00f1582f (inclusive).
    const char* const* tableEntry = (const char* const*)0x00f15680;
    const int tableEndAddress = 0x00f1582f;
    int index = 0;

    while ((int)tableEntry <= tableEndAddress)
    {
        const char* tableString = *tableEntry;
        if (strcmp(inputString, tableString) == 0)
        {
            return index;
        }
        // Advance by 3 pointers (12 bytes) per entry
        tableEntry += 3;
        index++;
    }

    // Not found – return 0 (which also corresponds to "Invalid" entry)
    return 0;
}