// FUNC_NAME: BaseComponent::BaseComponent

class BaseComponent {
public:
    // Constructor at 0x00891d40
    __thiscall BaseComponent() {
        // Global pointer assignment (DAT_011299c0)
        g_pBaseComponentSingleton = this;

        // Set vtable and type info pointers (standard EA EARS engine pattern)
        this->vfptr = reinterpret_cast<void**>(0x00d777c8);   // +0x00: virtual function table
        this->typeInfo = reinterpret_cast<void*>(0x00d777b8); // +0x04: RTTI or class descriptor

        // Clear additional fields (offsets +0x08, +0x0C, +0x10)
        this->field_08 = nullptr;
        this->field_0C = nullptr;
        this->field_10 = nullptr;

        // Register this component with the component system using a hash ID
        // FUN_00463980 corresponds to ComponentSystem::RegisterComponent
        ComponentSystem::RegisterComponent(0x57600d39, this + 1, 1);
    }

private:
    void* vfptr;        // +0x00
    void* typeInfo;     // +0x04
    void* field_08;     // +0x08
    void* field_0C;     // +0x0C
    void* field_10;     // +0x10
};

// Global pointer set by the constructor
static BaseComponent* g_pBaseComponentSingleton = nullptr;