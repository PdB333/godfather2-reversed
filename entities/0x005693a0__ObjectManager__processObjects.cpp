// FUNC_NAME: ObjectManager::processObjects
// Address: 0x005693a0
// Description: Iterates over all managed objects and notifies registered subscribers (ref-counted callbacks).

// Assumed base class for all objects managed by the manager
class ObjectBase {
public:
    // Virtual table structure (offsets in bytes)
    // vtable[0] -> first virtual function (called with subscriber pointer)
    // vtable[2] -> third virtual function (called with context when no subscribers)
    // vtable[6] -> destructor/release when refcount hits zero
    void** vtable;
    // ... other members
};

// Context passed to the update/notify routine
// Layout (offsets in bytes):
// +0x000: start of embedded subscriber pointers array? Actually the code uses:
//   param_2[0x41] at offset 0x104 -> subscriber count
//   param_2[0x42] at offset 0x108 -> some state set to 6
//   The subscriber pointers themselves are stored at param_2[1], param_2[2], ... (immediately after the start)
// This suggests the context structure has a header (maybe 0x100 bytes?) followed by an array of ints (pointers)
// For simplicity we treat it as an array of words starting at param_2, with the count and state at high offsets.
struct UpdateContext {
    int words[0x43]; // Total size unknown, but we only care about offsets 0x41,0x42 and the list starting at index 1
    // Subscriber list: starting at &words[1], each word is a pointer to a ref-counted object (intrusive_ptr-like)
    // The count of subscribers is words[0x41]
    // Some state: words[0x42] (set to 6)
};

// ObjectManager class (this pointer at param_1)
class ObjectManager {
private:
    int unknown[2]; // offset 0x00-0x07 (not used here)
    ObjectBase** objects; // offset +0x08 (array of pointers to managed objects)
    int objectCount; // offset +0x1c (number of managed objects)
    // ... other members
public:
    void processObjects(UpdateContext* context);
};

void ObjectManager::processObjects(UpdateContext* context) {
    int subscriberCount = context->words[0x41]; // +0x104
    context->words[0x42] = 6; // +0x108: set state

    if (objectCount == 0) {
        return;
    }

    for (int i = 0; i < objectCount; i++) {
        ObjectBase* obj = objects[i]; // local_8 = param_1 + 8 + i*4

        // If no subscribers, call the third virtual function (offset 8 in vtable)
        if (subscriberCount == 0) {
            // vtable[2] (since each vtable entry is 4 bytes, offset 8 => index 2)
            void (*func)(UpdateContext*) = (void (*)(UpdateContext*))(obj->vtable[2]);
            func(context);
        }

        // Iterate over all subscribers
        for (int j = 0; j < subscriberCount; j++) {
            // The subscriber pointer is stored at context->words[1+j] (since puVar3 starts at context and increments)
            // Actually: puVar3 = &context->words[0] initially, then puVar3 = &context->words[j] for j>=0
            // puVar3[1] = context->words[j+1]
            int* refCountPtr = (int*)context->words[j + 1]; // piVar2 = pointer to ref-counted object's refcount

            // Increment reference count
            (*refCountPtr)++;

            // Call the first virtual function (vtable offset 0) on the object with the subscriber's pointer
            void (*func)(int*) = (void (*)(int*))(obj->vtable[0]);
            func(refCountPtr);

            // Decrement reference count
            (*refCountPtr)--;

            // If ref count became zero, call destructor (vtable offset 0x18 => index 6)
            if (*refCountPtr == 0) {
                void (*destructor)(int*) = (void (*)(int*))(*(void***)refCountPtr)[6]; // vtable of the ref-counted object at offset 0x18
                destructor(refCountPtr);
            }
        }
    }
}