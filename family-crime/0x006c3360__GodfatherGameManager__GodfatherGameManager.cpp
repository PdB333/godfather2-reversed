// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Constructor for GodfatherGameManager, initializes all fields to default/zero states.
// Base constructor call at 0x6c9760 with argument and global data, then internal init at 0x6c1360.
// Derived from base class with vtable at +0x00 and second vtable at +0x08.
// Offsets are in bytes from this pointer.

GodfatherGameManager* __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this, int initParam)
{
    FUN_006c9760(initParam, _DAT_00d5cf70);  // call base class constructor with global data
    this->vtable = &PTR_FUN_00d5ef34;        // +0x00
    this->field_0x08 = &PTR_LAB_00d5ef2c;    // +0x08 (second vtable)
    FUN_006c1360();                          // internal initializations

    // Zero 3D vector fields (or triple int arrays) – pattern of four triplets
    this->field_0x210 = 0;   // +0x210
    this->field_0x20C = 0;   // +0x20C
    this->field_0x208 = 0;   // +0x208
    this->field_0x21C = 0;   // +0x21C
    this->field_0x218 = 0;   // +0x218
    this->field_0x214 = 0;   // +0x214
    this->field_0x228 = 0;   // +0x228
    this->field_0x224 = 0;   // +0x224
    this->field_0x220 = 0;   // +0x220
    this->field_0x234 = 0;   // +0x234
    this->field_0x230 = 0;   // +0x230
    this->field_0x22C = 0;   // +0x22C
    this->field_0x240 = 0;   // +0x240
    this->field_0x23C = 0;   // +0x23C
    this->field_0x238 = 0;   // +0x238

    this->field_0x244 = 0;   // +0x244
    this->field_0x258 = 0;   // +0x258
    this->field_0x25C = 0;   // +0x25C
    this->field_0x2B0 = 0;   // +0x2B0

    // Zero more fields in groups (often 3 consecutive ints)
    this->field_0x268 = 0;   // +0x268
    this->field_0x26C = 0;   // +0x26C
    this->field_0x274 = 0;   // +0x274
    this->field_0x280 = 0;   // +0x280
    this->field_0x27C = 0;   // +0x27C
    this->field_0x284 = 0;   // +0x284
    this->field_0x294 = 0;   // +0x294

    // Byte fields (booleans/flags)
    *(uint8_t*)(this + 0x270) = 0;   // +0x270
    *(uint8_t*)(this + 0x278) = 0;   // +0x278
    this->field_0x290 = 0;   // +0x290 (int)
    this->field_0x28C = 0;   // +0x28C
    this->field_0x288 = 0;   // +0x288
    this->field_0x298 = 0;   // +0x298

    // Second group
    this->field_0x2A4 = 0;   // +0x2A4
    this->field_0x2A0 = 0;   // +0x2A0
    this->field_0x29C = 0;   // +0x29C
    *(uint8_t*)(this + 0x2BC) = 0;   // +0x2BC
    this->field_0x2C8 = 0;   // +0x2C8
    this->field_0x2A8 = 0;   // +0x2A8
    this->field_0x2AC = 0;   // +0x2AC

    // Set active flag and pointer/id
    this->field_0x2D8 = 1;   // +0x2D8 (bool/enable)
    this->field_0x2DC = _DAT_00d5780c;   // +0x2DC (global constant)

    // Zero remaining fields
    this->field_0x248 = 0;   // +0x248
    this->field_0x260 = 0;   // +0x260
    this->field_0x264 = 0;   // +0x264
    this->field_0x2B4 = 0;   // +0x2B4
    this->field_0x2B8 = 0;   // +0x2B8
    this->field_0x2C0 = 0;   // +0x2C0
    this->field_0x2C4 = 0;   // +0x2C4
    this->field_0x2CC = 0;   // +0x2CC
    this->field_0x2D0 = 0;   // +0x2D0
    this->field_0x2D4 = 0;   // +0x2D4
    this->field_0x2E0 = 0;   // +0x2E0
    this->field_0x2E4 = 0;   // +0x2E4
    this->field_0x2E8 = 0;   // +0x2E8
    this->field_0x2EC = 0;   // +0x2EC
    this->field_0x2F0 = 0;   // +0x2F0
    this->field_0x2F4 = 0;   // +0x2F4
    this->field_0x254 = 0;   // +0x254
    this->field_0x250 = 0;   // +0x250
    this->field_0x24C = 0;   // +0x24C
    this->field_0x304 = 0;   // +0x304
    this->field_0x300 = 0;   // +0x300
    this->field_0x2FC = 0;   // +0x2FC
    *(uint8_t*)(this + 0x308) = 0;   // +0x308
    this->field_0x30C = 0;   // +0x30C

    return this;
}