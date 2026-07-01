// FUNC_NAME: GameObjectComponent::GameObjectComponent
// Function address: 0x008d40f0
// Role: Constructor for a game object component (e.g., AI behavior, input handler)
// Likely part of EARS component system with vtable and type identifier

#include <cstdint>

// Forward declaration for type IDs
enum class ComponentType : uint32_t;

// Base class initialized by called function FUN_008d3ec0
class ComponentBase {
public:
    // Constructor called as base initializer
    void initBase();
};

// Main component class
class GameObjectComponent : public ComponentBase {
public:
    // Vtable pointer at +0x0 (set to &PTR_FUN_00d7d5e0)
    void* vtable; // not a direct field but vtable location

    // +0x1C: Pointer to owning entity or parent object
    void* m_owner;

    // +0x48: Component type identifier (e.g., enum, resource ID)
    ComponentType m_componentType;

    // +0x4C: Debug label / class name string pointer
    const char* m_debugName;

    // Constructor
    GameObjectComponent(ComponentType type, void* owner) {
        // Base class initialization (likely sets vtable for parent)
        initBase();

        // Set core fields
        m_componentType = type;
        m_owner = owner;

        // Assign vtable pointer for this class
        vtable = (void*)0x00d7d5e0; // Symbol: PTR_FUN_00d7d5e0

        // Debug label (might be a compiler-generated string constant)
        m_debugName = (const char*)0x00d7d5d0; // Symbol: PTR_LAB_00d7d5d0
    }
};