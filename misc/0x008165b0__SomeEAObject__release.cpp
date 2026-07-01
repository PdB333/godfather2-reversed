// FUNC_NAME: SomeEAObject::release
int __thiscall SomeEAObject::release(void* thisPtr, byte flags) {
    // +0x08: pointer to owned sub-object
    // +0x14: function pointer to sub-object's destructor/cleanup
    if (*(void**)((int)thisPtr + 8) != 0) {
        (*(void(__thiscall**)(void*))((int)thisPtr + 0x14))(*(void**)((int)thisPtr + 8));
    }
    // If the low bit of flags is set, deallocate the this object itself
    if ((flags & 1) != 0) {
        FUN_009c8eb0(thisPtr); // custom memory deallocation
    }
    return (int)thisPtr;
}