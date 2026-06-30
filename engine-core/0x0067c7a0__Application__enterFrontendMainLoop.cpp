// FUNC_NAME: Application::enterFrontendMainLoop

void __thiscall Application::enterFrontendMainLoop(int thisPtr) 
{
    int vtablePtr = *(int*)thisPtr;  // +0x00 vtable
    void* frontendState = FUN_00683280("FrontendMainLoop");  // create or get frontend state object
    // Call virtual method at vtable offset 0x14 (likely enterState or pushState)
    ((void (__thiscall*)(void*, void*))(**(code**)(vtablePtr + 0x14)))(vtablePtr, frontendState);
    
    // Set flag at offset 0x0A (byte) to 1
    *(char*)(thisPtr + 0x0A) = 1;
    
    // Global pointer check; if not null, call another function and clear a flag
    if (DAT_0112982c != 0) {
        FUN_00983190();
        *(char*)(DAT_0112982c + 0x90) = 0;  // clear flag in that object
    }
    
    // Set another flag at offset 0x09 (byte) to 1
    *(char*)(thisPtr + 0x09) = 1;
}