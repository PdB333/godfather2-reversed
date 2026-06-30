// FUNC_NAME: releaseObject
void __fastcall releaseObject(void* thisObject)
{
    // Check for null pointer before calling vtable function
    if (thisObject != nullptr)
    {
        // Calls the first virtual function (likely destroy or decRef) with argument 1
        (*(void(__fastcall**)(void*, int))thisObject)(thisObject, 1);
    }
}