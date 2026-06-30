// FUNC_NAME: cleanupPointer
void __fastcall cleanupPointer(int* pPointer) 
{
    // If the pointer behind the handle is non-null, release the resource and nullify
    if (*pPointer != 0) {
        releaseResource(pPointer); // Calls the resource-specific release routine
        *pPointer = 0;
    }
    return;
}