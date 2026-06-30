// FUNC_NAME: Entity::applyBufferedState
// Function address: 0x006101b0
// Applies buffered "next" state (offset 0x40, 16 dwords) to current state (offset 0x00)
// for this entity and recursively for all child entities.
// If the flag at +0x80 is non-zero, calls cleanup and still recurses through children.
// Children form a singly linked list: first child at +0x84, sibling pointer at +0x88.

void __fastcall Entity::applyBufferedState(Entity* this)
{
    // Check if entity is flagged for pending deletion/cleanup (offset 0x80)
    if (*(int*)((uintptr_t)this + 0x80) == 0)
    {
        // Copy 16 dwords (64 bytes) from "next" state buffer (at +0x40) to current state (at +0x00)
        // This is a memcpy-like loop
        for (int i = 0; i < 16; i++)
        {
            *(int*)((uintptr_t)this + i * 4) = *(int*)((uintptr_t)this + 0x40 + i * 4);
        }
    }
    else
    {
        // Entity flagged for cleanup – invoke the cleanup routine
        FUN_00417560(); // likely Entity::cleanup or similar
    }

    // Recursively apply state to all child entities
    Entity* child = *(Entity**)((uintptr_t)this + 0x84); // first child
    while (child != nullptr)
    {
        applyBufferedState(child);
        child = *(Entity**)((uintptr_t)child + 0x88); // next sibling
    }
}