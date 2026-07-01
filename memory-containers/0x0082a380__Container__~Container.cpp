// FUNC_NAME: Container::~Container
// Address: 0x0082a380
// Role: Destructor for a container that owns a dynamically allocated array of pointers to objects with virtual destructors (or Release method).

void __fastcall Container::~Container(void* this_ptr /* ECX */)
{
    Container* self = (Container*)this_ptr;

    // Set vtable pointer (likely to a base class or pure virtual call handler during destruction)
    self->vtable = &PTR_FUN_00d73788;

    // Release all owned objects
    if (self->itemCount != 0) {
        for (int i = 0; i < self->itemCount; i++) {
            void* item = self->itemsArray[i]; // +0x08: array of object pointers
            if (item != nullptr) {
                // Call virtual function at vtable[0] with argument 1
                // This is typically a Release() or destructor call
                (*(void(__thiscall**)(void*, int))item)(item, 1);
            }
        }
    }

    // Free the array itself
    if (self->itemsArray != nullptr) {
        FUN_009c8f10(self->itemsArray); // likely operator delete[] or custom dealloc
    }
}