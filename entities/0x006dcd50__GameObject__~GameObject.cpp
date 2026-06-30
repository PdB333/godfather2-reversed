// FUNC_NAME: GameObject::~GameObject
undefined4 * __thiscall GameObject::~GameObject(GameObject *this, byte destroyFlag)
{
    // Set vtable pointers (multiple inheritance: main vtable at +0x00, 
    // secondary at +0x3C, +0x48, +0x50)
    this->vfptr = &PTR_FUN_00d5f678;
    *(void **)((uint)this + 0x3C) = &PTR_LAB_00d5f668;
    *(void **)((uint)this + 0x48) = &PTR_LAB_00d5f664;
    *(void **)((uint)this + 0x50) = &PTR_LAB_00d5f660;

    // Release owned sub-objects at offsets +0x68 and +0x70 if they exist
    if (this->subObject1 != 0) {
        releaseObject(&this->subObject1);
    }
    if (this->subObject2 != 0) {
        releaseObject(&this->subObject2);
    }

    // Global cleanup (e.g., static resource manager decrement)
    staticCleanup();

    // If a full delete is requested, deallocate the object's memory (size 0x1C8)
    if ((destroyFlag & 1) != 0) {
        deallocateMemory(this, 0x1C8);
    }
    return this;
}