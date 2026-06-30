// FUNC_NAME: ComponentManager::initializeComponent
int __thiscall ComponentManager::initializeComponent(void* thisPtr, void* componentData, int extraParam)
{
    if (componentData != nullptr) {
        performGlobalSetup();                     // static initialization
        initializeInternal(thisPtr, componentData, extraParam, 0); // param4 = 0
    }
    return 1; // success
}