// FUNC_NAME: GameObjectList::notifyObservers
// Address: 0x0097c610
// Description: Iterates over an array of objects (pointers) stored at +0xD8,
//   count at +0xDC. For each object, calls a virtual method at vtable+8,
//   passing the given argument. This is a common pattern for observer/event dispatch.

void __thiscall GameObjectList::notifyObservers(void* message) {
    uint32_t count = *(uint32_t*)(this + 0xDC);
    if (count != 0) {
        // +0xD8: pointer to array of object pointers
        uint32_t* objectArray = *(uint32_t**)(this + 0xD8);
        for (uint32_t i = 0; i < count; ++i) {
            // Each element is a pointer to an object with a virtual function table
            void* obj = (void*)(objectArray[i]);
            // vtable+8 is the second virtual function (index 2)
            void (*func)(void*) = *(void (**)(void*))(*((uint32_t*)obj) + 0x8);
            func(message);
        }
    }
}