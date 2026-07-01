// FUNC_NAME: Entity::Entity
// Function address: 0x008dfbe0
// Constructor for Entity (or derived class). Inserts into a global linked list.
// Class layout (based on assumed offsets):
// +0x00: vtable pointer (set to 0x00d7fbe8)
// +0x04: field1 (param_3) – possibly entity ID
// +0x08: field2 (param_5) – possibly type or another ID
// +0x0c: field3 (param_4) – possibly subtype or status
// +0x10: field4 (initialized to 0) – could be position component
// +0x14: field5 (0) – possibly rotation
// +0x18: field6 (0)
// +0x1c: field7 (0)
// +0x20: name buffer (64 bytes, copied from param_2)
// +0x60: ... (other fields)
// +0x70: next pointer in global list (param_1[0x1c])
// The global pointer DAT_012059ec (s_entityListHead) is updated to point to the new object.

Entity* __thiscall Entity::Entity(Entity* this, char* name, uint32_t id, uint32_t param4, uint32_t param5)
{
    // Call base class constructor (likely generic object or core entity)
    EntityBase* base = FUN_0064cc90();

    // Set vtable to this specific class's vtable
    this->vtable = &ENTITY_VTABLE_00d7fbe8;

    // Copy name into buffer at +0x20 (32 bytes from this)
    _strncpy(reinterpret_cast<char*>(reinterpret_cast<uint32_t>(this) + 0x20), name, 0x3f);

    // Store parameters
    this->field1 = id;       // +0x04
    this->field3 = param4;   // +0x0c
    this->field2 = param5;   // +0x08

    // Initialize other fields to zero
    this->field4 = 0;        // +0x10
    this->field5 = 0;        // +0x14
    this->field6 = 0;        // +0x18
    this->field7 = 0;        // +0x1c

    // Link into global entity list (head stored at DAT_012059ec)
    this->next = s_entityListHead;  // +0x70
    s_entityListHead = this;

    return this;
}