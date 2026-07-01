// FUNC_NAME: GodfatherGameManager::GodfatherGameManager (constructor)
class GodfatherGameManager;
GodfatherGameManager* g_GodfatherGameManager = nullptr; // DAT_011299bc

void initSomething(uint32_t* data, int zero);      // FUN_00837d90
void registerObjectWithHash(uint32_t hash, void* obj, int size); // FUN_00463980

class GodfatherGameManager {
public:
    void** vtable;            // +0x00 – base class vtable
    void** vtable2;           // +0x04 – secondary vtable (interface)
    uint8_t  field_08;        // +0x08
    uint8_t  field_09;        // +0x09
    // padding to align next integers
    int32_t  field_0C;        // +0x0C
    int32_t  field_10;        // +0x10
    int32_t  field_14;        // +0x14
    int32_t  field_18;        // +0x18
    int32_t  field_1C;        // +0x1C
    // ... other members up to offset 0x4C
    int32_t  debugFill1;      // +0x4C – initially 0xBADBADBA
    int32_t  debugFill2;      // +0x50 – initially 0xBEEFBEEF
    int32_t  debugFill3;      // +0x54 – initially 0xEAC15A55
    int32_t  debugFill4;      // +0x58 – initially 0x91100911

    GodfatherGameManager() {
        // Temporary vtable2 write (likely overwritten by derived class)
        this->vtable2 = (void**)&PTR_LAB_00d73d84;

        // Store global singleton reference
        g_GodfatherGameManager = this;

        // Set both vtable pointers
        this->vtable  = (void**)&PTR_FUN_00d73d94;
        this->vtable2 = (void**)&PTR_LAB_00d73d90;

        // Zero small fields
        *(uint8_t*)((uintptr_t)this + 8) = 0;   // field_08
        *(uint8_t*)((uintptr_t)this + 9) = 0;   // field_09

        // Zero integer fields
        this->field_0C = 0;
        this->field_10 = 0;
        this->field_14 = 0;
        this->field_18 = 0;
        this->field_1C = 0;

        // Engine-level initialization with static data
        initSomething(&DAT_00d73d88, 0);

        // Write magic debug fill pattern (then immediately clear it)
        this->debugFill1 = 0xBADBADBA;
        this->debugFill2 = 0xBEEFBEEF;
        this->debugFill3 = 0xEAC15A55;
        this->debugFill4 = 0x91100911;

        // Clear the debug fill (these fields should be zero)
        this->debugFill4 = 0;
        this->debugFill3 = 0;
        this->debugFill2 = 0;
        this->debugFill1 = 0;

        // Register this instance with the EARS object factory (hash 0xC14C90E8, size 0xB)
        registerObjectWithHash(0xC14C90E8, this, 0xB);
    }
};