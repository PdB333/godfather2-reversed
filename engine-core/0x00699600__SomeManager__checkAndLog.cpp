// FUNC_NAME: SomeManager::checkAndLog  
byte __thiscall SomeManager::checkAndLog(int this, int param2, int param3)  
{  
    byte result = 0;  
    int* ptr = (int*)FUN_00698c00(&param2, param2); // retrieve a pointer based on param2  
    if (*ptr != this + 4) // compare with an offset (might be a stored pointer)  
    {  
        FUN_004d3e20(*ptr + 0x20); // possibly initialize or process at ptr+0x20  
        result = FUN_004d7280(&DAT_0120546e, param3); // log or output with format string  
    }  
    return result;  
}