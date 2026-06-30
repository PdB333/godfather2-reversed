// FUNC_NAME: BaseObject::postConstructor
/* Function at 0x00561830
   Calls a global initialization routine and returns the 'this' pointer.
   Likely used as a post-constructor step in object creation. */
void* __fastcall BaseObject::postConstructor(void* thisPtr)
{
    // 0x00aa6480 - Performs additional object initialization
    FUN_00aa6480();
    return thisPtr;
}