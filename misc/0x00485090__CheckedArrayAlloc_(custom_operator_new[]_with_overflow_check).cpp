// FUNC_NAME: CheckedArrayAlloc (custom operator new[] with overflow check)
// Address: 0x00485090
// Role: Allocates an array of count elements each of size 24 bytes with multiplication overflow protection.
//       Uses a global exception translator and throws std::exception on overflow.

#include <new>  // For std::_Throw (MSVC internal)

typedef void (*ExceptionTranslator)(void*);

void CheckedArrayAlloc(uint count)  // Count passed in ESI
{
    // Overflow check: if 0xFFFFFFFF / count < 24 (the element size), multiplication would overflow
    if ( (0xFFFFFFFFu / count) < 24 )
    {
        // Set up structured exception handling block
        int local_4 = 0;
        void* exceptionBlock = &PTR_LAB_00e31050;  // Global exception type info

        // If a custom translator is installed, call it
        if ( DAT_0113d3a0 != nullptr )
        {
            ((ExceptionTranslator)DAT_0113d3a0)(&exceptionBlock);
        }

        // Call the translator's second function (likely terminate/throw)
        ((void (*)())(*(void**)exceptionBlock + 8))();  // local_8[2]()

        // Throw std::exception
        std::_Throw((std::exception*)&exceptionBlock);
    }

    // Safe allocation: count * 24 bytes
    // FUN_009c8e50 is the underlying memory allocator (e.g., malloc)
    FUN_009c8e50(count * 24);
}