// FUNC_NAME: ComponentManager::removeAndDestroyComponent
void __thiscall ComponentManager::removeAndDestroyComponent(int componentType, Component* pComponent)
{
    // Get the component list for the given type (e.g., via type hash table)
    ComponentList* pList = reinterpret_cast<ComponentList*>(FUN_008bee20(componentType));
    if (!pList) {
        return;
    }

    // Find pComponent in the list’s pointer array and remove it
    uint count = pList->count; // +0x14
    if (count != 0) {
        int** ppElements = reinterpret_cast<int**>(pList->pElements); // +0x10
        for (uint i = 0; i < count; ++i) {
            if (ppElements[i] == pComponent) {
                if (i < count - 1) {
                    // Move last element into the removed slot
                    ppElements[i] = ppElements[count - 1];
                }
                pList->count = count - 1; // decrement count
                break;
            }
        }
    }

    // Release the component (e.g., decrement refcount or call destructor)
    FUN_006b3c40(pComponent);

    // Determine how to finalize based on game state
    int state = FUN_00791750(); // e.g., GameStateManager::getCurrentState()
    if (state < 3) {
        // Transition to state 0 (e.g., loading/menu?)
        FUN_00790d30(0); // setState(0)
        FUN_00790110(0); // resetState(0)
        char isActive = FUN_00791230(); // e.g., isTransitioningOrActive()
        if (isActive) {
            FUN_00792d80(pComponent); // immediate destroy (e.g., remove from scene)
        }
    } else {
        // State >= 3 (e.g., in-game)
        // Check if component has flag (bit 29 at +0x5c) and this is GodfatherGameManager
        if (((pComponent->flags >> 0x1d) & 1) != 0 && (this->typeHash & 0x637b907) == 0x637b907) {
            // GodfatherGameManager detects a special condition
            FUN_008c1190(pComponent); // destroy during game
        } else {
            FUN_008bf340(pComponent); // destroy during menu (or default)
        }
    }
}