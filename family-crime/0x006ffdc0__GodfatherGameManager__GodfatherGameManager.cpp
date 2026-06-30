// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Function at 0x006ffdc0 - Constructor for GodfatherGameManager singleton
// Note: Uses __fastcall calling convention (this in ECX)

#include <cstdint>

class GodfatherGameManager {
public:
    // Vtable pointer at offset 0x00
    void* vtable;
    // +0x04: Unknown flag
    uint32_t field_04;
    // +0x08: Unknown flag
    uint32_t field_08;
    // +0x0C: Some pointer (set twice)
    void* field_0C;
    // +0x10: ptr/flag
    uint32_t field_10;
    // +0x14: ptr/flag
    uint32_t field_14;
    // +0x18: ptr/flag
    uint32_t field_18;
    // +0x1C: uVar2 (result from FUN_004265d0)
    void* field_1C;
    // +0x20: piVar1 (result from FUN_004dddd0)
    void* field_20;
    // +0x24: zeroed
    uint32_t field_24;
    // +0x28: zeroed
    uint32_t field_28;
    // +0x2C: zeroed
    uint32_t field_2C;
    // +0x30: zeroed
    uint32_t field_30;
    // +0x40: zeroed (hard to tell alignment, but based on indices)
    uint32_t field_40;
    // +0x44: zeroed
    uint32_t field_44;

    // Global singleton pointer
    static GodfatherGameManager* s_instance;

    GodfatherGameManager() {
        // Initialize fields
        this->field_04 = 1;
        this->field_08 = 0;
        this->field_0C = (void*)&PTR_LAB_00d60c94; // Some static label
        this->vtable = (void*)&PTR_FUN_00d60ccc;    // Set vtable
        this->field_0C = (void*)&PTR_LAB_00d60cc8;  // Overwrite with another label

        // Store this as the global singleton
        s_instance = this;

        // Local variables for initialization
        uint32_t local_c[3] = {0, 0, 0}; // Actually 3 undefined4 vars
        uint32_t* piVar1; // result from FUN_004dddd0
        void* uVar2;      // result from FUN_004265d0

        // Get some object pointer (likely a subsystem)
        piVar1 = (uint32_t*)FUN_004dddd0(); // e.g., memory allocation or factory
        // Create another object using local_c and piVar1
        uVar2 = (void*)FUN_004265d0(&local_c, piVar1);

        // Store results
        this->field_1C = uVar2;
        this->field_20 = piVar1;

        // Call a virtual function on the piVar1 object (offset +8 in its vtable)
        (*(void (**)(void))(*piVar1 + 8))();

        // Zero out many remaining fields
        this->field_14 = 0;
        this->field_10 = 0;
        this->field_18 = 0;
        this->field_30 = 0;
        this->field_2C = 0;
        this->field_28 = 0;
        this->field_24 = 0;
        this->field_40 = 0;
        this->field_44 = 0;
    }
};

// Global instance pointer
GodfatherGameManager* GodfatherGameManager::s_instance = nullptr;