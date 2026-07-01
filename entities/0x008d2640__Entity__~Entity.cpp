// FUNC_NAME: Entity::~Entity
// Address: 0x008d2640
// Role: Destructor for base Entity class. Releases owned sub-objects at offsets 0x28 and 0x3C, then optionally deallocates memory.

#pragma once

// Forward declarations
class Entity;
void releaseSubObject(void* pObject);  // FUN_009c8f10
void operatorDelete(void* pObject);    // FUN_009c8eb0

// VTable pointer (set during destruction to base class vtable)
extern void* g_EntityVTable; // PTR_FUN_00d7d3d8

// Assumed class layout (partial)
// Offset 0x00: vtable pointer
// Offset 0x28: m_pSubObjectB
// Offset 0x3C: m_pSubObjectA
// ... other members

Entity* __thiscall Entity::~Entity(byte flags)
{
    // Set vtable to base class to avoid calling derived virtual functions during destruction
    *(void**)this = &g_EntityVTable;

    // Release sub-object at offset 0x3C
    if (*(void**)((uintptr_t)this + 0x3C) != nullptr) {
        releaseSubObject(*(void**)((uintptr_t)this + 0x3C));
    }

    // Release sub-object at offset 0x28
    if (*(void**)((uintptr_t)this + 0x28) != nullptr) {
        releaseSubObject(*(void**)((uintptr_t)this + 0x28));
    }

    // If flag bit 0 is set, deallocate memory (operator delete)
    if (flags & 1) {
        operatorDelete(this);
    }

    return this;
}