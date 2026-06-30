// FUNC_NAME: releaseTwoResourcePointers
// Function at 0x006f7e40: Releases two resource pointers stored at offsets +4 and +0xC from this.
void __fastcall releaseTwoResourcePointers(void* thisPtr)
{
    char* base = (char*)thisPtr;
    int* pFirstResource = (int*)(base + 4);   // offset +4
    int* pSecondResource = (int*)(base + 0xC); // offset +0xC

    if (*pFirstResource != 0)
    {
        FUN_004daf90((int)pFirstResource); // Release first resource and nullify
    }
    if (*pSecondResource != 0)
    {
        FUN_004daf90((int)pSecondResource); // Release second resource and nullify
    }
}