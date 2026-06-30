// FUNC_NAME: EARSObject::releaseChild
void __fastcall EARSObject::releaseChild(int thisPtr)
{
    // Check if child pointer at +0xC is non-null
    if (*(int*)(thisPtr + 0xC) != 0)
    {
        // Release/deallocate the child object
        FUN_0064d980(); // Likely delete or release function
    }
    return;
}