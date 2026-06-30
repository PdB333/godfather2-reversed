// FUNC_NAME: resolveDataElement
// Function address: 0x004eba90
// Role: Parses an array of data elements (offsets into a data block) and converts raw 128-bit data into either a float stored as int, or a string ID (hash index).
// Used by multiple data loading routines (callers at 0x004e6900, 0x004f05b0, etc.).
// The element structure (pointed by elementPtr) is 4 ints (16 bytes). If all zero, it is considered empty and skipped.
// Two markers are written to elementPtr[0]: 0xE1E2E3E4 for numeric values, 0xF1F2F3F4 for string IDs.
// The second int elementPtr[1] stores the value.

#include <cctype>  // for isalpha
#include <cstdlib> // for atof

// Constants for data type markers
static const int DATA_TYPE_NUMERIC = 0xE1E2E3E4;   // Numeric value (stored as int, but parsed from float string? see comment)
static const int DATA_TYPE_STRING  = 0xF1F2F3F4;   // String ID (index into a string table)

/**
 * Converts a 128-bit data element (4 ints) into a string representation.
 * @param element Pointer to the 4-int element.
 * @param out     Output buffer (at least 24 characters expected).
 */
extern void elementToString(const int* element, char* out);

/**
 * Looks up a string (or hash) in the string table and returns its index.
 * @param stringTable Pointer to the string table object.
 * @param element     Pointer to the element (used as key?).
 * @return Index if found, -1 otherwise.
 */
extern int lookupStringTableIndex(void* stringTable, const int* element);

/**
 * Resolves an array of data elements by converting raw binary data into typed values.
 * @param stringTable    Opaque pointer to a string table/hash table object.
 * @param baseDataPtr    Base address of the data block where elements reside.
 * @param offsetArray    Array of 4-byte offsets relative to baseDataPtr (one per element).
 * @param elementCount   Number of elements to process.
 */
void resolveDataElement(void* stringTable, int baseDataPtr, const int* offsetArray, int elementCount)
{
    for (int i = 0; i < elementCount; i++)
    {
        // Each offset points to a 16-byte element (4 ints)
        int* elementPtr = (int*)(*(int*)(offsetArray + i) + baseDataPtr);

        // Skip if all four ints are zero (empty element)
        if (elementPtr[0] == 0 && elementPtr[1] == 0 &&
            elementPtr[2] == 0 && elementPtr[3] == 0)
        {
            continue;
        }

        // Convert the raw element to a string (e.g., a text representation of the data)
        char tempString[24];
        elementToString(elementPtr, tempString);

        // Trim leading spaces from the string
        char* str = tempString;
        while (*str != '\0' && *str == ' ')
        {
            str++;
        }

        // Check if the first character is alphabetic
        if (isalpha((unsigned char)*str) == 0)
        {
            // Non‑alphabetic: treat as a numeric value (integer parsed from float string)
            elementPtr[0] = DATA_TYPE_NUMERIC;
            double val = atof(str);
            elementPtr[1] = (int)(float)val;  // Note: Casts double->float->int; loses fractional part.
        }
        else
        {
            // Alphabetic: treat as a string identifier
            int index = lookupStringTableIndex(stringTable, elementPtr);
            if (index >= 0)
            {
                elementPtr[0] = DATA_TYPE_STRING;
                elementPtr[1] = index;   // Store the table index
            }
        }
    }
}