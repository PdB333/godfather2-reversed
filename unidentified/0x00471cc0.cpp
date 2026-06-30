// FUN_00471cc0: Entity::getOrientation
// Retrieves the orientation/rotation of the entity as a 4-component vector.
// If the external flag (+0x130) is set, copies from an external source (likely world transform).
// Otherwise constructs from local members (+0xC0, +0xC4, +0xC8) and sets w to 0.
// Note: The w component is forced to 0 in the local case, suggesting non-quaternion usage (e.g., direction or Euler padding).
void __thiscall Entity::getOrientation(Entity* this, Math::Vector4* outOrientation)
{
    if (*(int*)((char*)this + 0x130) != 0) {
        // Use externally supplied orientation (e.g., from parent or physics)
        Math::Vector4* extOrientation = (Math::Vector4*)FUN_004a4ce0(); // External orientation source
        *outOrientation = *extOrientation;
        return;
    }

    // Build orientation from local rotation members
    outOrientation->x = *(float*)((char*)this + 0xC0);
    outOrientation->y = *(float*)((char*)this + 0xC4);
    outOrientation->z = *(float*)((char*)this + 0xC8);
    outOrientation->w = 0.0f; // Last component forced zero
}