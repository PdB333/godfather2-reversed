// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __fastcall GodfatherGameManager::GodfatherGameManager(void* thisPtr)
{
    // Set primary vtable pointer (base class vtable)
    *(void**)thisPtr = (void*)0x00d5e558;                   // vtable for GodfatherGameManager

    // Set secondary vtable pointers for additional base classes / interfaces
    *(void**)((char*)thisPtr + 0x3C) = (void*)0x00d5e548;  // second vtable offset
    *(void**)((char*)thisPtr + 0x48) = (void*)0x00d5e544;  // third vtable offset

    // Call base class constructor (e.g., EARS::Framework::Object or similar)
    // DAT_0120e93c is likely a global static object used for initialization
    FUN_004086d0(&DAT_0120e93c);

    // Final initialization step (e.g., setting up manager state)
    FUN_0046c640();
}