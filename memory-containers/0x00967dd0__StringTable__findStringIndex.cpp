// FUNC_NAME: StringTable::findStringIndex
// Address: 0x00967dd0
// Searches a linear array of C-strings stored in the object.
// Object fields:
//   +0x5C: char** m_stringArray (array of pointers to null-terminated strings)
//   +0x68: uint m_arraySize
// Returns the index if found, or 3 if not found.
// Note: Uses strncmp with the length of the input string, so it performs a prefix match.
//   This might be a bug or intentional (e.g., all stored strings are same length).

uint __thiscall StringTable::findStringIndex(char *nameToFind)
{
    uint index = 0;
    if (this->m_arraySize != 0) {
        char **current = this->m_stringArray;
        do {
            // Compute strlen of nameToFind
            char *scan = nameToFind;
            while (*scan != '\0') {
                scan++;
            }
            int nameLen = scan - (nameToFind + 1); // Equivalent to strlen(nameToFind)
            if (_strncmp(nameToFind, *current, nameLen) == 0) {
                return index;
            }
            index++;
            current++;
        } while (index < this->m_arraySize);
    }
    return 3; // Not found indicator
}