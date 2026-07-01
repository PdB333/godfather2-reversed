// FUNC_NAME: advanceTimedComponent
bool advanceTimedComponent(void* owner, float timeDelta, bool applyToAll) {
    void* component = getTimedComponent(owner);
    if (component != nullptr) {
        updateComponentTime(component, 
                           *(float*)((intptr_t)component + 8) + timeDelta, 
                           applyToAll, 
                           0);
    }
    return component != nullptr;
}