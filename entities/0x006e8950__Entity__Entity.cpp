// FUNC_NAME: Entity::Entity
// Constructor for Entity class (size ~0x8C bytes)
// Initializes debug markers, flags, and default values from globals

struct Entity {
    void** vtable; // +0x00
    int field_0x04; // +0x04
    int field_0x08; // +0x08
    int field_0x0C; // +0x0C
    int debugMarker1; // +0x10 (0xBADBADBA)
    int debugMarker2; // +0x14 (0xBEEFBEEF)
    int debugMarker3; // +0x18 (0xEAC15A55)
    int debugMarker4; // +0x1C (0x91100911)
    // ... gap ...
    float field_0x50; // +0x50 (from DAT_00d5fb70)
    float field_0x54; // +0x54 (from DAT_00d5f010)
    int field_0x58; // +0x58 (from DAT_00d5ddec)
    int field_0x5C; // +0x5C (from DAT_00d5fb6c)
    int field_0x60; // +0x60
    int field_0x64; // +0x64
    int field_0x68; // +0x68 (from DAT_00d58cbc)
    int field_0x6C; // +0x6C
    int field_0x70; // +0x70 (from DAT_00d58cbc)
    int field_0x74; // +0x74
    int field_0x78; // +0x78
    int field_0x7C; // +0x7C (from DAT_00d58cbc)
    int field_0x80; // +0x80
    int field_0x84; // +0x84 (from DAT_00d5ccf8)
    unsigned char byte_0x88; // +0x88 (set to 1)
    unsigned char byte_0x89; // +0x89 (set to 0)
    unsigned char flags_0x8A; // +0x8A (init 2, then OR 8)
    unsigned char byte_0x8B; // +0x8B (set to 0)
};

// External globals (likely from config or random seed)
extern float DAT_00d5fb70;
extern float DAT_00d5f010;
extern int DAT_00d5ddec;
extern int DAT_00d5fb6c;
extern int DAT_00d58cbc;
extern int DAT_00d5ccf8;
extern void* PTR_FUN_00d5faf8; // vtable pointer

// External function (likely random number generator update)
void FUN_00b99e20();

Entity* __fastcall Entity::Entity(Entity* this) {
    // Initialize basic fields
    this->field_0x04 = 0;
    this->field_0x08 = 0;
    this->field_0x0C = 0;
    this->vtable = &PTR_FUN_00d5faf8;

    // Debug sentinel values for memory corruption detection
    this->debugMarker1 = 0xBADBADBA;
    this->debugMarker2 = 0xBEEFBEEF;
    this->debugMarker3 = 0xEAC15A55;
    this->debugMarker4 = 0x91100911;

    // Zero out some fields
    this->field_0x60 = 0;
    this->field_0x64 = 0;
    this->byte_0x8B = 0;
    this->flags_0x8A = 2;

    // Update random seed (or similar)
    FUN_00b99e20();
    this->field_0x50 = (float)DAT_00d5fb70;

    FUN_00b99e20();
    this->field_0x54 = (float)DAT_00d5f010;

    // Assign more fields from globals
    this->field_0x58 = DAT_00d5ddec;
    this->field_0x5C = DAT_00d5fb6c;
    this->field_0x68 = 0;
    this->field_0x70 = 0;
    this->field_0x6C = DAT_00d58cbc;
    this->field_0x74 = 0;
    this->field_0x7C = 0;
    this->field_0x78 = DAT_00d58cbc;
    this->field_0x80 = 0;
    this->field_0x7C = 0;
    this->field_0x78 = DAT_00d58cbc;
    this->field_0x44 = 0; // offset 0x44? Actually param_1[0x11] = 0 -> offset 0x44
    this->field_0x4C = 0; // param_1[0x13] = 0 -> offset 0x4C
    this->field_0x48 = DAT_00d58cbc; // param_1[0x12] = uVar1 -> offset 0x48

    // Set flags
    this->flags_0x8A |= 8;
    this->byte_0x89 = 0;
    this->field_0x80 = 0; // param_1[0x20] = 0 -> offset 0x80
    this->byte_0x88 = 1; // *(undefined1 *)(param_1 + 0x22) = 1 -> offset 0x88
    this->field_0x84 = DAT_00d5ccf8; // param_1[0x21] = uVar2 -> offset 0x84

    return this;
}