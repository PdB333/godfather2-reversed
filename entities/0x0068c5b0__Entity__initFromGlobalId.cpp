// FUNC_NAME: Entity::initFromGlobalId
void __fastcall Entity::initFromGlobalId(Entity* const this)
{
    // Local struct to hold a custom object identifier (possibly a truncated GUID or asset ID)
    struct ObjectId {
        uint32_t data1; // +0x00
        uint32_t data2; // +0x04
        uint8_t  data3; // +0x08
    } id;

    // Load primary identifier from a global constant
    id.data1 = DAT_01129a98;
    id.data2 = 0;
    id.data3 = 0;

    // Call the initialization routine with the constructed ID and a flag (0)
    FUN_00408a00(&id, 0);

    // Set the object's type to 2 (e.g., SimNpc, Entity subtype, etc.)
    this->type = 2; // +0x10
}