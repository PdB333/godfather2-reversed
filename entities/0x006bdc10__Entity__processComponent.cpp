// FUNC_NAME: Entity::processComponent
bool Entity::processComponent(int* componentPtr)
{
    // If no component pointer is provided, try to obtain it from the component provider at +0x60
    if (componentPtr == nullptr)
    {
        componentPtr = (int*)this->getComponentFromProvider(); // FUN_006bca80(this + 0x60)
        if (componentPtr == nullptr)
        {
            return false; // No component available, skip
        }
    }

    // Check if component updates are currently allowed (e.g., game state)
    if (this->isComponentUpdateAllowed()) // FUN_006bdb50()
    {
        // Call the component's virtual update method at vtable offset 0x1c
        // The component receives the owning Entity as the context
        void (*componentFunc)(Entity*) = (void (*)(Entity*))(componentPtr[0] + 0x1c);
        componentFunc(this);
    }

    // Return true if we had a component to process (even if update wasn't allowed)
    return componentPtr != nullptr;
}