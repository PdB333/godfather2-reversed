// FUNC_NAME: Handle::release
void __fastcall Handle::release(int *handle) // handle structure at pointer, offsets: +0 dataPtr, +4 refCount?, +8 customData?, +12 destructorFunc
{
    if (*handle != 0) {
        // Call the destructor function stored at offset +12, passing the data pointer as the argument
        ((void (__fastcall *)(int))handle[3])(*handle);
    }
    // Reset the handle to zero
    *handle = 0;
    handle[2] = 0;
    handle[1] = 0;
}