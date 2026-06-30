// FUNC_NAME: GameObject::Release
uint __thiscall GameObject::Release(uint8 deallocateFlag)
{
    // Decrement reference counts for three sub-objects at offsets +0x20, +0x1c, +0x18.
    // Each sub-object has a ref count at offset +8 (int32).
    RefCountedObject* subObject;

    subObject = *(RefCountedObject**)(this + 0x20);
    if (subObject) {
        int* refCount = (int*)subObject + 2; // subObject + 8
        *refCount -= 1;
        if (*refCount == 0) {
            // Call destructor via vtable at index 2
            (*(void (__thiscall**)(RefCountedObject*))(*(uint*)subObject + 8))(subObject);
        }
    }

    subObject = *(RefCountedObject**)(this + 0x1c);
    if (subObject) {
        int* refCount = (int*)subObject + 2;
        *refCount -= 1;
        if (*refCount == 0) {
            (*(void (__thiscall**)(RefCountedObject*))(*(uint*)subObject + 8))(subObject);
        }
    }

    subObject = *(RefCountedObject**)(this + 0x18);
    if (subObject) {
        int* refCount = (int*)subObject + 2;
        *refCount -= 1;
        if (*refCount == 0) {
            (*(void (__thiscall**)(RefCountedObject*))(*(uint*)subObject + 8))(subObject);
        }
    }

    // Call base class release (likely another ref count decrement)
    FUN_0064b440();

    // If deallocate flag has bit 0 set, free this object
    if (deallocateFlag & 1) {
        FUN_009c8eb0(this);
    }

    return this;
}