// FUNC_NAME: GameObject::~GameObject
int __thiscall GameObject::destructor(GameObject* this, byte deleteFlag)
{
    // +0x28: vtable pointer for this class (set to cleanup/base vtable)
    *(void***)((int)this + 0x28) = &PTR_LAB_00e317cc;

    // Unlink from doubly-linked list (offsets relative to this):
    // +0x18: prevNode  (previous node in list)
    // +0x1c: nextNode  (next node in list)
    // +0x20: someOtherPtr (likely a self-pointer or tail sentinel)
    int* prevNode = *(int**)((int)this + 0x18);
    if (prevNode != 0) {
        int* nextNode = *(int**)((int)this + 0x1c);
        int* someOtherPtr = *(int**)((int)this + 0x20);
        if (nextNode == 0) {
            // Only previous node exists: update its "next" (offset +4) to point to someOtherPtr
            *(int*)((int)prevNode + 4) = (int)someOtherPtr;
        } else {
            // Both exist: update nextNode's "prev" (offset +8) to point to someOtherPtr
            *(int*)((int)nextNode + 8) = (int)someOtherPtr;
        }
        if (someOtherPtr != 0) {
            // Update someOtherPtr's "prev" (offset +4) to point to nextNode
            *(int*)((int)someOtherPtr + 4) = (int)nextNode;
        }
    }

    // Call base class destructor (likely a common base like Object::~Object)
    FUN_0064d150();

    // If heap-allocated (deleteFlag & 1), free memory
    if ((deleteFlag & 1) != 0) {
        FUN_009c8eb0(this); // operator delete
    }

    return (int)this;
}