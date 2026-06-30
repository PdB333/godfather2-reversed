// FUNC_NAME: GameObject::~GameObject

int __thiscall GameObject::~GameObject(void *this, byte flags)
{
    // Destroy sub-object at +0xC (second member pointer)
    if (*(int **)((uint)this + 0xC) != (int *)0x0) {
        destroySubObject((int *)this + 0xC);
    }
    // Destroy sub-object at +0x4 (first member pointer)
    if (*(int **)((uint)this + 0x4) != (int *)0x0) {
        destroySubObject((int *)this + 0x4);
    }
    // If flag bit 0 is set, free the object's memory
    if ((flags & 1) != 0) {
        operatorDelete(this);
    }
    return (int)this;
}