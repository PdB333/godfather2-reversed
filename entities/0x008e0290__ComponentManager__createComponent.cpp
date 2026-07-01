// FUNC_NAME: ComponentManager::createComponent
void __thiscall ComponentManager::createComponent(void *thisPtr)
{
    char ready;
    int mem;
    void *obj;

    ready = isSystemReady();
    if (ready != 0) {
        mem = operator_new(0x38);                  // allocate 0x38 bytes
        if (mem != 0) {
            obj = SomeComponent_constructor(mem, thisPtr); // construct with owner reference
            registerComponent(obj);                 // add to manager
            return;
        }
        registerComponent(0);                       // registration on failure
    }
    return;
}