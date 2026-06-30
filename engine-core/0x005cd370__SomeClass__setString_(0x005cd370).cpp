// FUNC_NAME: SomeClass::setString (0x005cd370)
// Reconstructed setter for a dynamically allocated string member (char* at offset 0).
// Frees existing string, then copies source if non-empty.
// Source string is passed in EDI register (__thiscall with register parameter).
#include <cstring>

void __thiscall SomeClass::setString(const char* src) {
    // Free existing string if present
    if (this->m_string != nullptr) {
        free(this->m_string);  // DAT_0119caf4 is free/delete
    }
    this->m_string = nullptr;

    // Copy source string if non-null and non-empty
    if (src != nullptr) {
        size_t len = strlen(src);
        if (len > 0) {
            // Allocate new buffer (DAT_0119caf0 is malloc/operator new)
            this->m_string = (char*)malloc(len + 1);
            memcpy(this->m_string, src, len + 1);
        }
    }
}