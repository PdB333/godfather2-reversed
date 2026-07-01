// FUNC_NAME: EAString::parseInteger
// Address: 0x008f4bf0
// Parses an integer from the start of the string, skipping leading non-digit characters.
// Uses a static empty wide string (DAT_00e2df14) as fallback if internal buffer is null.
void EAString::parseInteger(int* outResult) {
    wchar_t* str;
    
    str = *(wchar_t**)this;               // +0x00: mData (pointer to wide character buffer)
    if (str == nullptr) {
        str = (wchar_t*)&DAT_00e2df14;    // static empty wide string
    }
    
    int index = 0;                        // reuse local variable as index
    while ((unsigned short)str[index] - 0x30 > 9) {  // skip characters that are not '0'..'9'
        index++;
    }
    
    FUN_008f3be0(str, &index);            // call actual conversion (likely wcstol equivalent)
    // Note: This function modifies outResult via index? Or the result is stored elsewhere.
    // Based on original code, param_1 (index) is passed as pointer, but no assignment.
    // Possibly outResult is set inside FUN_008f3be0.
}