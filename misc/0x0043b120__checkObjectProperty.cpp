// FUNC_NAME: checkObjectProperty
// Function at 0x0043b120: checks a property of an object based on its first byte
// If the first byte is non-zero (object has a name string?), compares two ints at +0x0C and +0x10
// If the first byte is zero (no name), checks whether a pointer at +0x5C is null
// Returns a 32-bit value packing the upper 3 bytes of the relevant field with a boolean equality flag

int __fastcall checkObjectProperty(char* thisPtr)
{
    // +0x00: first byte of object – if non-zero, use offset 0x0C/0x10; if zero, use offset 0x5C
    if (*thisPtr != '\0')
    {
        // +0x0C: integer field (e.g., an ID or index)
        int leftValue = *(int*)(thisPtr + 0x0C);
        // +0x10: another integer field for comparison
        int rightValue = *(int*)(thisPtr + 0x10);
        // Return: upper 3 bytes of leftValue, with low byte = (leftValue == rightValue)
        return (leftValue & 0xFFFFFF00) | (leftValue == rightValue ? 1 : 0);
    }
    else
    {
        // +0x5C: pointer to pointer (e.g., a resource handle)
        int* ptr = *(int**)(thisPtr + 0x5C);
        // Return: upper 3 bytes of pointer value, with low byte = (ptr == NULL)
        return ((int)ptr & 0xFFFFFF00) | (ptr == NULL ? 1 : 0);
    }
}