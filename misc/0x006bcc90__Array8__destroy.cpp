// FUNC_NAME: Array8::destroy
// Function at 0x006bcc90: Destructor/cleanup for a dynamic array of 8-byte elements (each containing a pointer and possibly another field).
// The class has two fields: m_pElements (pointer to array of Element8, offset +0x00) and m_count (int, offset +0x04).
struct Element8 {
    void* ptr;      // +0x00: pointer to the actual object (or null)
    int   extra;    // +0x04: unknown field (not used in this function)
};

// Forward declarations of called functions (likely static helpers)
void destroyElement(Element8* elem);   // FUN_004daf90: destructor for the element
void deallocateMemory(void* ptr);      // FUN_009c8f10: free/delete the array memory

class Array8 {
public:
    Element8* m_pElements;  // +0x00
    int       m_count;      // +0x04

    void __fastcall destroy();
};

void __fastcall Array8::destroy() {
    // Iterate from last element down to first
    for (int i = m_count - 1; i >= 0; --i) {
        Element8* elem = &m_pElements[i];
        if (elem->ptr != nullptr) {
            destroyElement(elem);
        }
    }
    // Free the array memory itself
    if (m_pElements != nullptr) {
        deallocateMemory(m_pElements);
    }
}