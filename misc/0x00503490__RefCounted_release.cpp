// FUNC_NAME: RefCounted_release
void* __fastcall RefCounted_release(void* unusedParam, int flags, int* obj)
{
    int dummySuccess = 0;
    if (obj == nullptr) {
        return nullptr;
    }

    // Call virtual function at offset +8 (likely canRelease or shouldNotify)
    // Returns non-zero to indicate success flag.
    bool successFlag = (*(bool (__thiscall**)(void*, int))(*(int*)obj + 8))(obj, flags);

    // Decrement reference count at offset +4
    obj[1]--;

    // If refcount reaches zero, call virtual destructor at offset +4
    if (obj[1] == 0) {
        (*(void (__thiscall**)(void*))(*(int*)obj + 4))(obj);
    }

    return successFlag ? (void*)&dummySuccess : nullptr;
}