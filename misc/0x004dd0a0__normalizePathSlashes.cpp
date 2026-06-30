// FUNC_NAME: normalizePathSlashes
// Address: 0x004dd0a0
// Role: Converts forward slashes to backslashes in a wide-character path string.
// Parameters: (fastcall) first param (ECX) is unused, second param (EDX) points to a struct { wchar_t* buffer; int length; }.
// The buffer is modified in-place.
void __fastcall normalizePathSlashes(void* unused, int* params)
{
    // params[0] = pointer to wide-character string
    // params[1] = length of string in characters
    int length = params[1];
    if (length != 0) {
        wchar_t* buffer = (wchar_t*)params[0];
        for (unsigned int i = 0; i < (unsigned int)length; i++) {
            if (buffer[i] == L'/') {
                buffer[i] = L'\\';
            }
        }
    }
}