// FUN_004c9250: Component::attachToParent
#include <cstdint>

// Forward declarations
class Component;

// Represents an allocation of 0x24 bytes, likely a small data structure
struct ComponentData {
    // Size 0x24 (36 bytes)
    uint8_t data[0x24];
};

// Base class with vtable (4 virtual methods at offsets: 0=destructor?, 4=method1, 8=method2, 12=method3)
class ComponentBase {
public:
    virtual ~ComponentBase() = default;                          // vtable+0
    virtual void onAttach(void* data, int param) = 0;           // vtable+4  (called with iStack_18, 0)
    virtual void onInit() = 0;                                   // vtable+8  (called twice)
    virtual void onFinish() = 0;                                 // vtable+12 (called at end)
};

// The parent class that holds references to components
class Parent {
public:
    Component* component;        // +0x10  (the allocated ComponentData pointer? but stored as int)
    Component* backPointer;      // +0x14  (stores the this pointer of the attached component)
};

// The component implementation (this class)
class Component : public ComponentBase {
public:
    int attachToParent(Parent* parent);
    
    // Virtual method implementations (simulated)
    virtual void onInit() override;    // corresponds to vtable+8
    virtual void onAttach(void* data, int param) override; // vtable+4
    virtual void onFinish() override;  // vtable+12
};

// External functions
ComponentData* allocComponentData(); // FUN_009c8e50(0x24)
int generateId(Component* comp, void* outId); // FUN_004265d0(&stackId, comp)
void registerComponent(); // FUN_004ca180

// Implementation
int Component::attachToParent(Parent* parent) {
    // Store back-pointer in parent's field at +0x14
    parent->backPointer = this;
    
    // Call our own onInit (virtual +8)
    this->onInit();
    
    // Allocate a 36-byte data structure for this component inside the parent
    ComponentData* data = allocComponentData();
    bool allocationFailed = (data == nullptr);
    
    if (!allocationFailed) {
        // Retrieve the back-pointer (which is ourselves) – redundant in this context
        Component* self = parent->backPointer;
        
        // Local storage for generated ID
        struct IdStruct {
            int32_t a;
            int32_t b;
            int32_t c;
        } id = {0, 0, 0}; // uStack_14, uStack_10, uStack_c
        
        // Call onInit again (virtual +8)
        self->onInit();
        
        // Generate a unique identifier using ourselves and the local ID storage
        int generatedId = generateId(&id, self); // iStack_18
        
        // Register this component globally (or to some manager)
        registerComponent();
        
        // Store the new data pointer into parent's component field (+0x10)
        parent->component = data; // note: assignment to pointer – but original stores iVar1 (the allocation result) as int
    } else {
        // If allocation failed, set data to null
        data = nullptr;
        parent->component = nullptr;
    }
    
    // If allocation succeeded, perform final setup steps
    if (!allocationFailed) {
        if (generatedId != 0) {
            // Call virtual +4 with the generated ID and 0
            self->onAttach(&generatedId, 0);
        }
        // Call virtual +12 to finalize attachment
        self->onFinish();
    }
    
    return 1; // always succeed
}