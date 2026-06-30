//FUNC_NAME: BaseClass::releaseContainedObject
int __fastcall BaseClass::releaseContainedObject(void* thisPtr)
{
    // +0xc: pointer to a contained object (likely with a vtable)
    void** containedObj = *(void***)((char*)thisPtr + 0xc);
    if (containedObj != nullptr)
    {
        // Call the first vtable entry (typically destructor or release)
        (*(void(__thiscall**)(void*))containedObj)(containedObj);
        *(void**)((char*)thisPtr + 0xc) = nullptr;
    }
    return 1;
}