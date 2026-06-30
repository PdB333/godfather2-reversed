// FUNC_NAME: GameObject::GameObject
void * __thiscall GameObject::GameObject(byte initFlag) {
    // Call base initialization
    this->baseInit();

    // If the low bit of initFlag is set, perform additional initialization
    // This likely calls a virtual method via a global class factory table
    // The global structure at g_pClassFactory has a pointer at offset +0x4
    // which points to an array of function pointers; index 1 is called.
    if ((initFlag & 1) != 0) {
        // Access global factory table:
        // g_pClassFactory + 0x4 -> pointer to function pointer array
        // array[1] -> second function pointer (cast to thiscall)
        void (__thiscall *additionalInit)(GameObject *, int) =
            *(void (__thiscall **)(GameObject *, int))(
                *(int *)((char *)g_pClassFactory + 4) + 4
            );
        additionalInit(this, 0);
    }

    return this;
}