// FUNC_NAME: Entity::Entity

// address: 0x0067f430
// Constructor for Entity class. Takes a flags byte (bit 0 indicates heap allocation).
// Calls base class constructor and conditionally initializes vtable.

typedef void (__thiscall *BaseCtor)();
extern void __thiscall BaseObjectConstructor(); // FUN_00416bf0

extern int* __cdecl GetClassVTable(); // FUN_009c8f80

int __thiscall Entity::Entity(Entity* this, byte flags)
{
    BaseObjectConstructor();

    if ((flags & 1) != 0)
    {
        int* vtable = GetClassVTable();
        // Call virtual function at offset 4 (placement new/init) with size 0x70 (112 bytes)
        (*(void(__thiscall**)(Entity*, int))(*vtable + 4))(this, 0x70);
    }

    return (int)this;
}