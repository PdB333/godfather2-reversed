// FUNC_NAME: initThreeStaticObjects
// Function address: 0x008f6c20
// Role: Initializes three static objects/data blocks by calling a common registration/init function

extern void __cdecl FUN_008f6770(void* param);

void __cdecl initThreeStaticObjects(void)
{
    // Register/init first static object at address 0x00472420
    FUN_008f6770((void*)0x00472420);
    // Register/init second static object at address 0x00472440
    FUN_008f6770((void*)0x00472440);
    // Register/init third static object at address 0x008bb3a0
    FUN_008f6770((void*)0x008bb3a0);
}