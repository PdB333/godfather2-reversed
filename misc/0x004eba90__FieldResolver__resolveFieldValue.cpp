// FUNC_NAME: FieldResolver::resolveFieldValue

#include <cctype>
#include <cstdlib>

// Represents a context or symbol table for string lookups
class FieldResolver {
public:
    // Processes an array of fields located at basePtr + offsets[0..count-1].
    // Each field is a 16-byte (4 int) structure.
    // If the field's bytes represent a number (after string conversion), it stores the value as int.
    // If the field's bytes represent a string identifier (starting with a letter), it looks up the
    // string in the resolver's table and stores the resulting ID.
    void resolveFieldValue(void* basePtr, int* offsets, int count);
};

void FieldResolver::resolveFieldValue(void* basePtr, int* offsets, int count) {
    if (count <= 0) {
        return;
    }

    for (int i = 0; i < count; i++) {
        // Each field is at: basePtr + offsets[i]
        int* field = (int*)((char*)basePtr + offsets[i]);

        // Check if the 4 ints are all zero – if so, skip (uninitialized field)
        if (field[0] == 0 && field[1] == 0 && field[2] == 0 && field[3] == 0) {
            continue;
        }

        // Convert the 16-byte field to a string buffer (max 24 chars)
        char buffer[24];
        convertFieldToString(field, buffer); // FUN_004eaec0

        // Trim leading spaces
        char* str = buffer;
        while (*str != '\0' && *str == ' ') {
            str++;
        }

        // Determine the type based on the first non-space character
        if (isalpha((unsigned char)*str)) {
            // It's a string reference – look up in the resolver's symbol table
            int id = lookupStringIdentifier(this, field); // FUN_0051a990
            if (id >= 0) {
                // Tag the field as "string reference" and store the ID
                field[0] = -0xe0d0c0c;  // magic constant: 0xF1F2F3F4
                field[1] = id;
            }
        } else {
            // It's a numeric value – parse as float and store as int
            float val = (float)atof(str);
            // Tag the field as "numeric" and store the value as int (truncated)
            field[0] = -0x1e1d1c1c;  // magic constant: 0xE1E2E3E4
            field[1] = (int)val;
        }
    }
}