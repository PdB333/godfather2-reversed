// FUNC_NAME: ComponentManager::CreateComponent
// Address: 0x007a0950
// Role: Checks if game is active, allocates memory for a component (0x38 bytes), constructs it via a static factory method, and registers the new instance. On allocation failure, registers null.

// Forward declarations
bool __thiscall isGameActive(void);
void* __fastcall operatorNew(size_t size); // FUN_009c8e50(0x38)

// Static factory: constructs a Component using the manager and raw memory
Component* __fastcall ComponentConstruct(ComponentManager* manager, Component* mem); // FUN_007a0800

// Registers the component in some internal list
void __fastcall registerComponent(Component* comp); // FUN_00481690

void __thiscall ComponentManager::CreateComponent(ComponentManager* this)
{
    if (isGameActive()) {
        // Allocate memory for the component (size 0x38)
        Component* mem = static_cast<Component*>(operatorNew(0x38));
        if (mem != nullptr) {
            // Construct the component (likely calls Component::Component(manager))
            Component* component = ComponentConstruct(this, mem);
            registerComponent(component);
            return;
        }
        registerComponent(nullptr);
    }
}