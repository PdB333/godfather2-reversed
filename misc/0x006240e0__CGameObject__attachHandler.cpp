// FUNC_NAME: CGameObject::attachHandler
void __thiscall CGameObject::attachHandler(int* object, int handler)
{
    // store object pointer at offset +0x04
    *(int**)(this + 4) = object;

    // call virtual function at vtable index 2 (e.g., onBeginAttach)
    (*(void (__thiscall**)(int))(*(int*)object + 8))();

    if (handler != 0) {
        // create a binding and store result at offset +0x08
        *(int*)(this + 8) = FUN_004265d0(handler, *(int*)(this + 4));

        // call virtual function at vtable index 1 (e.g., attachHandler) with handler and a flag
        (*(void (__thiscall**)(int, int, int))(*(int*)object + 4))(handler, 0);

        // call virtual function at vtable index 3 (e.g., onEndAttach)
        (*(void (__thiscall**)(int))(*(int*)object + 12))();
    } else {
        *(int*)(this + 8) = 0;
        // call virtual function at vtable index 3
        (*(void (__thiscall**)(int))(*(int*)object + 12))();
    }
}