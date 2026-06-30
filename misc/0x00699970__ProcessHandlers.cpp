// FUNC_NAME: ProcessHandlers
// Address: 0x00699970
// This function iterates over a list of handler structures (each starting with a function pointer) and calls them if certain conditions are met.
// The list boundaries are stored in global variables DAT_01129f8c (begin) and DAT_01129f90 (end).
// For each entry, it calls somePreProcess(contextPtr) and then checkHandlerResult(result, someParam).
// If result[0] is non-zero, it invokes the handler's function with that value.
// If checkHandlerResult returns non-zero, the function exits with 1, otherwise continues.
// Returns 1 if any handler returned true, 0 otherwise.

#include <cstdint>

// Forward declarations of called functions (addresses provided)
bool somePreProcess(void* contextPtr);   // FUN_004d3bc0
int checkHandlerResult(uint32_t result[3], void* someParam); // FUN_00699680, returns char (0 or 1)

// Global variables for list boundaries
extern uint32_t* g_handlerListBegin;   // DAT_01129f8c
extern uint32_t* g_handlerListEnd;     // DAT_01129f90

// Function pointer type for handlers
typedef void (*HandlerFunc)(uint32_t arg);

int ProcessHandlers(void* contextPtr, void* someParam)
{
    int result = 0;
    uint32_t* currentPtr = g_handlerListBegin;
    
    while (currentPtr != g_handlerListEnd)
    {
        somePreProcess(contextPtr);
        
        uint32_t resultArray[3];  // local_10
        bool hasResult = checkHandlerResult(resultArray, someParam);
        
        if (resultArray[0] != 0)
        {
            // currentPtr points to a structure whose first element is a function pointer
            HandlerFunc handlerFunc = reinterpret_cast<HandlerFunc>(*currentPtr);
            handlerFunc(resultArray[0]);
        }
        
        if (hasResult)
        {
            return 1;
        }
        
        currentPtr += 1; // advance by 1 dword (sizeof(uint32_t))
    }
    
    return 0;
}