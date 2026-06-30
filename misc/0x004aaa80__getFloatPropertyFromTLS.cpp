// FUNC_NAME: getFloatPropertyFromTLS
#include <intrin.h>

float __fastcall getFloatPropertyFromTLS(void* obj)
{
    // Get the thread-local storage array pointer from FS:[0x2C]
    // In Windows x86, FS:[0x2C] contains the TLS array (pointer to first slot)
    int* tlsArray = (int*)__readfsdword(0x2C);
    
    // First element of TLS array – assumed to be a pointer to a per-thread data structure
    int* pThreadData = (int*)*tlsArray;
    
    // At offset +0x08 in that structure we find a base pointer to a property table
    int* pTableBase = *(int**)((char*)pThreadData + 8);
    
    // The property table starts at base +0x70
    char* pPropertyOffset = (char*)pTableBase + 0x70;
    
    // The object provides an index (byte offset) at +0x18
    int index = *(int*)((char*)obj + 0x18);
    
    // Read and return the float stored at that offset
    return *(float*)(pPropertyOffset + index);
}