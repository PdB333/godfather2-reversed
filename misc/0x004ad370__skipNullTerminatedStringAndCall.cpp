// FUNC_NAME: skipNullTerminatedStringAndCall
// Address: 0x004ad370
// Role: Traverses a null-terminated string to find its end, then calls a global subroutine (0x004ae6f0).
// The first parameter (void* context) is likely an unused object pointer or context from __fastcall.

void __fastcall skipNullTerminatedStringAndCall(void* context, char* str)
{
    char c;
    do
    {
        c = *str;      // Read current character
        str++;         // Advance to next character
    } while (c != '\0'); // Continue until null terminator found

    // Call a global function (possibly logging or state update)
    sub_004ae6f0();
}