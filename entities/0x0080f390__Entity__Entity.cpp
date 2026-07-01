// FUNC_NAME: Entity::Entity
// Address: 0x0080f390
// Role: Constructor for Entity that optionally handles self-deallocation based on flag bit 0.
// Called functions: baseInitialize (0x0080ee50), dealloc (0x00624da0)
// +0x00: this pointer

void __cdecl baseInitialize();   // Internal initialization routine
void __cdecl dealloc(void* ptr); // Memory deallocation (likely operator delete)

Entity* __thiscall Entity::Entity(Entity* this, byte flag) {
    baseInitialize();
    if (flag & 1) {
        dealloc(this);
    }
    return this;
}