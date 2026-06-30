// FUNC_NAME: GameObject::shutdownComponent

class Component {
public:
    int handle; // +0x14
};

class GameObject {
public:
    void* pResource;    // +0x8
    Component* pComponent; // +0x36c
};

// External engine functions
bool IsComponentActive(int handle);
void DeactivateComponent(Component* comp);
void FreeComponentHandle(int handle);

void __thiscall GameObject::shutdownComponent(void) {
    // If both resource and component are valid, check if component is active
    if (pResource != nullptr && pComponent != nullptr) {
        if (IsComponentActive(pComponent->handle)) {
            DeactivateComponent(pComponent);
        }
    }
    // Always release the component's handle if it exists
    if (pComponent != nullptr) {
        FreeComponentHandle(pComponent->handle);
    }
}