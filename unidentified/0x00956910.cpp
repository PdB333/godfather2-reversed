// FUN_NAME: ComponentManager::processCurrentComponent
#include <cstdint>

// Forward declarations for component vtable and component object
struct ComponentVTable {
    // Virtual functions; offset 0x9c -> 0x27th entry (0x9c / 4)
    void (*functionAt0x9c)();
};

struct Component {
    ComponentVTable* vtable; // +0x00
    // ... other members (size unknown)
};

// Manager that holds an array of components and a current index
struct ComponentManager {
    // +0x54: pointer to array of Component* pointers
    Component** componentArray;
    // +0x6c: current index into the array
    uint32_t currentIndex;
};

// __thiscall: this pointer passed in ECX
void ComponentManager::processCurrentComponent() {
    // Fetch the component pointer from the array using currentIndex
    Component** arr = this->componentArray;
    uint32_t idx = this->currentIndex;
    Component* comp = arr[idx];

    // Call virtual function at vtable offset 0x9c (likely an Update or Process method)
    comp->vtable->functionAt0x9c();
}