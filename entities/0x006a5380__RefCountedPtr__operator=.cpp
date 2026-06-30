// FUNC_NAME: RefCountedPtr::operator=
// RefCountedPtr is a smart pointer using intrusive reference counting via a linked list of references stored in the pointed-to object.
// Object structure: [vtable/refCount (0x00)], [nextRefNode (0x04)] – the linked list head.
// RefCountedPtr structure: [target (0x00)], [nextNode (0x04)] – node in the list.

// Forward declaration of the function that removes this node from the old target's list and possibly destroys the object.
void releaseRefNode(RefCountedPtr* node);

struct RefCountedObject {
    // offset 0x00: unknown (vtable or reference count)
    // offset 0x04: pointer to head of RefCountedPtr linked list
    RefCountedPtr* refListHead;
};

struct RefCountedPtr {
    RefCountedObject* target;   // +0x00
    RefCountedPtr* next;       // +0x04
};

// __thiscall: this is a member of RefCountedPtr
RefCountedPtr* __thiscall RefCountedPtr::operator=(RefCountedPtr* other) {
    RefCountedPtr* self = this;

    if (self != other) {
        RefCountedObject* newTarget = other->target;
        if (self->target != newTarget) {
            // Release old reference (remove self from old target's list, maybe free object)
            if (self->target != nullptr) {
                releaseRefNode(self);
            }
            // Assign new target
            self->target = newTarget;
            if (newTarget != nullptr) {
                // Insert self at head of new target's reference list
                self->next = newTarget->refListHead;  // newTarget->refListHead is at offset +0x04
                newTarget->refListHead = self;        // set new head
            }
        }
    }
    return self;
}