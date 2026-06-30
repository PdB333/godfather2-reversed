// FUNC_NAME: Entity::Entity
// Address: 0x00653fd0
// Purpose: Constructor for an Entity object, initializes transform and state fields from a data block.
// Behavior: Copies a 20-byte block (likely a quaternion + float) from inData into this+0x100, sets flags,
// calls base class constructor with inParent, then calls internal init, and sets state/type fields.

void __thiscall Entity::Entity(Entity* this, void* inParent, const void* inDataBlock)
{
    // Clear byte flags at offsets 0x160 and 0x161 (e.g., "isActive", "isDirty")
    *(byte*)(this + 0x160) = 0;
    *(byte*)(this + 0x161) = 0;

    // Enable flag at offset 0x190 (400 decimal) (e.g., "isEnabled")
    *(byte*)(this + 0x190) = 1;

    // Copy 20-byte data block from inDataBlock to this+0x100.
    // Structure: two 8-byte values (likely quaternion components) + one 4-byte value (float).
    *(int64*)(this + 0x100) = *(int64*)inDataBlock;
    *(int64*)(this + 0x108) = *(int64*)((byte*)inDataBlock + 8);
    *(int32*)(this + 0x110) = *(int32*)((byte*)inDataBlock + 16);

    // Call base class constructor with the parent pointer (likely initializes base state)
    Entity_BaseConstructor(inParent); // FUN_00452df0

    // Internal initialization routine for this entity
    Entity_InitInternal(this); // FUN_00655070

    // Set state field to 0 (e.g., "state" at +0x19c) and type/subtype to 4 (e.g., "subtype" at +0x1b4)
    *(int32*)(this + 0x19c) = 0;
    *(int32*)(this + 0x1b4) = 4;

    // Static initialization (e.g., register with manager)
    Entity_StaticInit(); // FUN_00655f50
}