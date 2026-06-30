// FUNC_NAME: Entity::Entity
void __thiscall Entity::Entity(int createComponentA, int componentBParam)
{
    // +0x10: componentA pointer
    // +0x14: componentB pointer

    if (createComponentA)
    {
        this->componentA = allocComponentA(); // FUN_0060a380 - allocate/initialize componentA
    }
    if (componentBParam)
    {
        this->componentB = allocComponentB(componentBParam); // FUN_0060a2e0 - create componentB from parameter
    }

    postConstructStep1(); // FUN_006127d0 - complete initialization
    postConstructStep2(); // FUN_006181d0 - finalize setup
}