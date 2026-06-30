// FUNC_NAME: ChildObject::removeFromParentContainer
// Function address: 0x006726e0
// This function removes an element from a dynamic array container and frees associated memory.
// The 'this' pointer points to a child object embedded within a parent structure.
// Offsets relative to 'this':
//   -0x10: parent object start (freed)
//   -0x08: index of this child in the container (int)
//   +0x28: pointer to container structure (Container*)
// Container structure offsets:
//   +0x04: count of elements (int)
//   +0x0C: pointer to array of pointers (int**)

struct Container {
    int field_0;          // +0x00
    int count;            // +0x04
    int field_8;          // +0x08
    int** array;          // +0x0C
};

void __thiscall ChildObject::removeFromParentContainer(int* outPtr) {
    int index = *(int*)((char*)this - 8);          // index of this child in the container
    Container* container = *(Container**)((char*)this + 0x28); // container holding the array

    *outPtr = 0;                                   // clear output pointer

    // Remove the element from the array by setting its pointer to null
    container->array[index] = 0;

    // Decrement the element count
    container->count--;

    // Free the parent object (starting at this - 0x10)
    operator delete((void*)((char*)this - 0x10));

    // Call cleanup function (likely for the child object itself)
    someCleanupFunction(); // FUN_00672fd0

    // Free the array and the container structure
    operator delete(container->array);
    operator delete(container);
}