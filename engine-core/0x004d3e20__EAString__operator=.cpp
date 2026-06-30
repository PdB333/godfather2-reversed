// FUNC_NAME: EAString::operator=
// Function address: 0x004d3e20
// EA EARS engine custom string assignment operator.
// String structure layout:
//   +0x00: char* buffer
//   +0x04: int length
//   +0x08: int capacity
//   +0x0C: void (*deallocator)(char*)

// Forward declarations for internal allocator functions
char* allocateStringBuffer(uint size);
void freeStringBuffer(char* buffer);

int* __thiscall EAString::operator=(int* thisString, int* otherString)
{
    char c;
    uint otherLen;
    int newBuffer;
    char* src;
    char* dst;

    // Self-assignment check
    if (thisString != otherString) {
        otherLen = otherString[1]; // +0x04: length of other string

        if (otherLen != 0) {
            // Check if current capacity is sufficient
            if ((uint)thisString[2] <= otherLen) { // +0x08: capacity
                // Free old buffer if it exists
                if (thisString[0] != 0) {
                    // Call deallocator function pointer at +0x0C
                    ((void (*)(char*))thisString[3])((char*)thisString[0]);
                }
                // Allocate new buffer with room for null terminator
                newBuffer = (int)allocateStringBuffer(otherLen + 1);
                thisString[0] = newBuffer; // +0x00: buffer pointer
                thisString[2] = otherLen;  // +0x08: update capacity
                thisString[3] = (int)freeStringBuffer; // +0x0C: set deallocator
            }
            // Copy string byte by byte until null terminator
            src = (char*)otherString[0];
            dst = (char*)thisString[0];
            do {
                c = *src;
                *dst = c;
                src++;
                dst++;
            } while (c != '\0');
            // Update length
            thisString[1] = otherLen; // +0x04
            return thisString;
        }
        // Source string is empty
        thisString[1] = 0; // +0x04: length = 0
        if (thisString[0] != 0) {
            *(char*)thisString[0] = '\0'; // Null-terminate existing buffer
        }
    }
    return thisString;
}