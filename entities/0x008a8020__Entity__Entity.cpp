// FUNC_NAME: Entity::Entity

// Constructor for Entity class. Initializes base, copies name, sets IDs, and links into global list.
// Object layout (offsets from this):
// +0x00: vtable pointer
// +0x04: field1 (int) - e.g., entityType
// +0x08: field2 (int) - e.g., entitySubType
// +0x0C: field3 (int) - e.g., entityId
// +0x10: field4 (int) - zeroed
// +0x14: field5 (int) - zeroed
// +0x18: field6 (int) - zeroed
// +0x1C: field7 (int) - zeroed
// +0x20: name[64] (char[64]) - copied from param2, max 63 chars + null
// +0x70: next (Entity*) - linked list pointer to previous head

void __thiscall Entity::Entity(Entity *this, const char *name, int entityType, int entityId, int entitySubType)
{
    // Call base class constructor (likely initializes vtable and other base fields)
    FUN_0064cc90();
    
    // Set vtable pointer
    this->vtable = &PTR_LAB_00d79c30;
    
    // Copy name string (max 63 characters)
    _strncpy(this->name, name, 0x3f);
    this->name[0x3f] = '\0'; // Ensure null termination
    
    // Set type and ID fields
    this->entityType = entityType;      // +0x04
    this->entityId = entityId;          // +0x0C
    this->entitySubType = entitySubType; // +0x08
    
    // Zero out additional fields
    this->field4 = 0;  // +0x10
    this->field5 = 0;  // +0x14
    this->field6 = 0;  // +0x18
    this->field7 = 0;  // +0x1C
    
    // Link this entity into the global singly-linked list (head stored at DAT_012059ec)
    this->next = g_entityListHead;  // +0x70
    g_entityListHead = this;
    
    return this;
}