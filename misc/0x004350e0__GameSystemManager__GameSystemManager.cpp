// FUNC_NAME: GameSystemManager::GameSystemManager

class GameSystemManager {
public:
    void *vtable;                  // +0x00
    void *field_0x4;               // +0x04
    void *field_0x8;               // +0x08
    void *param2Object;            // +0x0C
    void *field_0x10;              // +0x10
    void *field_0x14;              // +0x14
    void *field_0x18;              // +0x18
    void *field_0x1C;              // +0x1C
};

// Global singleton pointer
GameSystemManager* g_pGameSystemManager = nullptr; // DAT_012233ec

// External function declarations
void FUNCTION_004dafd0(int param); // Returns a handle/pointer
void FUNCTION_0049c6e0(void* param, int flag);

// Constructor at address 0x004350e0
GameSystemManager* __thiscall GameSystemManager::GameSystemManager(GameSystemManager* this, int* param_2, int param_3)
{
    // Zero-initialize fields
    this->field_0x4 = 0;
    this->field_0x8 = &g_vtableLAB_00e30c10; // Initial vtable pointer (will be overwritten)
    
    // Store global singleton pointer
    g_pGameSystemManager = this;
    
    // Set the main vtable pointer
    this->vtable = &g_vtableFUN_00e30c00;
    
    // Overwrite the second vtable pointer
    this->field_0x8 = &g_vtableLAB_00e30c0c;
    
    // Clear remaining fields
    this->field_0x10 = 0;
    this->field_0x14 = 0;
    this->field_0x18 = 0;
    this->field_0x1C = 0;
    
    // Store the second parameter (some object)
    this->param2Object = param_2;
    
    // Call a virtual method on param_2 (offset +8 in its vtable)
    (reinterpret_cast<void (*)()>(*(reinterpret_cast<int*>(param_2) + 2)))();
    
    // Call an initialization function with a global table pointer and flag 1
    FUNCTION_0049c6e0(&g_globalLAB_00e30bfc, 1);
    
    // If param_3 is provided, load a resource/handle and store it
    if (param_3 != 0) {
        this->field_0x1C = reinterpret_cast<void*>(FUNCTION_004dafd0(param_3));
    }
    
    return this;
}