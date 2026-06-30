// FUNC_NAME: AptSet::remove

#include <cstddef>

// Assertion macro from EA's APT library
#define APT_ASSERT(exp, file, line) \
    do { \
        if (!(exp)) { \
            if (g_bAssertEnabled) { \
                if (g_pAssertHandler) { \
                    g_pAssertHandler(#exp, file, line); \
                } else { \
                    __debugbreak(); \
                } \
            } \
        } \
    } while(0)

// External globals used by the assertion system
extern bool g_bAssertEnabled;
extern void (*g_pAssertHandler)(const char* expr, const char* file, int line);
extern const char* g_pszAssertFile;
extern int g_nAssertLine;

// Assuming the element type has a virtual destructor at offset 8
typedef void (*DestructorFunc)(void* obj);

// External table for destructor dispatch (indexed by vtable & 0x7FFF)
extern DestructorFunc g_DestructorTable[];

// ---------------------------------------------------------------------------
// This method removes an element from a fixed-size AptSet (array-based).
// Returns 1 if the element was found and removed, 0 if not found.
// The set does not compact; it simply zeros out the slot.
// ---------------------------------------------------------------------------
int AptSet::remove(void* element)
{
    // +0x00: count of elements currently in the set
    int count = this->count;

    // Assert that the count does not exceed the maximum capacity
    APT_ASSERT(count <= 512,
               "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptSet.h",
               59);

    // +0x04: first element of the array (max 512 pointers)
    void** elements = reinterpret_cast<void**>(&this->elements[0]);

    int i;
    for (i = 0; i < 512; i += 4)
    {
        // Manual loop unrolling for 4 elements per iteration
        if (elements[i + 0] == element) {
            goto found;
        }
        if (elements[i + 1] == element) {
            i += 1;
            goto found;
        }
        if (elements[i + 2] == element) {
            i += 2;
            goto found;
        }
        if (elements[i + 3] == element) {
            i += 3;
            goto found;
        }
    }

    // Element not found
    return 0;

found:
    if (i > 511) {
        return 0;   // index out of bounds
    }

    // Decrement the count
    this->count--;

    // Call the destructor via the vtable table
    // The vtable pointer is stored at offset 0 of the element object
    uintptr_t vtable = *reinterpret_cast<uintptr_t*>(elements[i]);
    DestructorFunc dtor = g_DestructorTable[(vtable & 0x7FFF)];
    dtor(elements[i]);

    // Clear the slot
    elements[i] = nullptr;

    return 1;
}