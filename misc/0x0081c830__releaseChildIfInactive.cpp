// FUNC_NAME: releaseChildIfInactive
// Function at 0x0081c830: checks if a child object at this+0x7c is still active; if not, frees it.
void __thiscall releaseChildIfInactive(void* thisPtr)
{
    int** pChildPtr = (int**)((char*)thisPtr + 0x7c);  // +0x7c: pointer to child object
    int* childPtr = *pChildPtr;
    
    // Calculate base of child object structure (offset -0x48 from the stored pointer)
    int* childBase = (childPtr != 0) ? (int*)((char*)childPtr - 0x48) : 0;
    
    bool isActive = FUN_0081c790(childBase) != 0;  // Check if child is still active
    if (!isActive && childPtr != 0) {
        FUN_004daf90(pChildPtr);  // Free the child object
        *pChildPtr = 0;           // Clear the pointer
    }
}