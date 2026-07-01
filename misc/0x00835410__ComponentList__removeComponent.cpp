// FUNC_NAME: ComponentList::removeComponent
void ComponentList::removeComponent(ComponentOwner* owner) // owner has a pointer at +0x50 to the component to remove
{
    uint index = 0;
    if (count != 0) {
        void** arrayPtr = reinterpret_cast<void**>(array); // +0x14: pointer to array of component pointers
        while (true) {
            void* currentComponent = *arrayPtr; // current array element
            if (currentComponent == *reinterpret_cast<void**>(reinterpret_cast<char*>(owner) + 0x50)) {
                break; // found the component to remove
            }
            index++;
            arrayPtr++;
            if (index >= count) { // guard against overflow
                return;
            }
        }
        // Notify removal (likely decrements ref count or detaches)
        notifyComponentRemoval(currentComponent); // FUN_008341c0
        // Fill gap with last element (O(1) removal)
        if (index != count - 1) {
            reinterpret_cast<void**>(array)[index] = reinterpret_cast<void**>(array)[count - 1];
        }
        count--;
        // Release the removed component (vtable call with argument 1)
        if (currentComponent != nullptr) {
            (*(void (__thiscall**)(void*, int))currentComponent)(currentComponent, 1);
        }
    }
}