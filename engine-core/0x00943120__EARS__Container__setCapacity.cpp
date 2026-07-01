// FUNC_NAME: EARS::Container::setCapacity
// Address: 0x00943120
// Sets the container's capacity. If newCapacity > current capacity, triggers a reallocation via setBuffer(newCapacity).
// If newCapacity < current, just updates the capacity field without freeing memory.
void __thiscall EARS::Container::setCapacity(uint newCapacity)
{
    if (capacity < newCapacity) {
        EARS::Container::allocateBuffer(newCapacity); // +0x4: capacity
        capacity = newCapacity;
        return;
    }
    if (newCapacity < capacity) {
        capacity = newCapacity;
    }
}