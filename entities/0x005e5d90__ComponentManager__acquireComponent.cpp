// FUNC_NAME: ComponentManager::acquireComponent
int __thiscall ComponentManager::acquireComponent(int this, int *outComponent, int *outData)
{
    int component;
    char isValid;

    if (this != 0 && outComponent != 0 && outData != 0) {
        component = FUN_005f0330(*(void **)(this + 8), *(int *)(this + 0x14), 0);
        if (component != 0) {
            *(int *)(component + 0xc) = (int)this; // +0x0c : backlink to manager/owner
            if (*(int *)(component + 0x10) != 0) {
                isValid = FUN_005f0490();
                if (isValid) {
                    *outComponent = component;
                    *outData = **(int **)(component + 0x10); // dereference pointer at +0x10
                    return 1;
                }
            }
        }
    }
    return 0;
}