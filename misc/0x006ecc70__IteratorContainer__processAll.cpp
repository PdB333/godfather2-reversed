// FUNC_NAME: IteratorContainer::processAll
void __thiscall IteratorContainer::processAll(void *thisPtr, void *context)
{
    // This iterates over elements using a virtual iterator pattern.
    // The container and iterator each have two virtual methods:
    //  - vtable[2] : (container or iterator) returns a new iterator given a context
    //  - vtable[4] : (iterator) returns char (bool) indicating whether the current element is valid/processed
    // The traversal works as follows:
    //   1. Get initial iterator from container via virtual call (index 2).
    //   2. If the iterator is valid, advance to the next iterator via the iterator's own virtual call (index 2),
    //      then check if the new iterator is valid.
    //      Repeat until invalid.
    //   3. Finally, call container's virtual method again (index 2) with the context (possibly for cleanup).

    // Steps 1-3 are documented with field offsets:
    // Container vtable[2] -> offset +0x08
    // Iterator vtable[2]  -> offset +0x08
    // Iterator vtable[4]  -> offset +0x10

    Iterator *iterator = (Iterator *)((*(code **)(*(int *)thisPtr + 8)))(context); // container->begin(context)

    char isValid = (*(code **)(*(int *)iterator + 0x10))(); // iterator->isValid()
    while (isValid != 0) {
        iterator = (Iterator *)((*(code **)(*(int *)iterator + 8)))(context); // iterator = iterator->next(context)
        isValid = (*(code **)(*(int *)iterator + 0x10))(); // iterator->isValid()
    }
    (*(code **)(*(int *)thisPtr + 8))(context); // container->end(context) presumably

    return;
}