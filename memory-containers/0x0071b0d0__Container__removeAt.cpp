// FUNC_NAME: Container::removeAt
void __thiscall Container::removeAt(int* thisPtr, uint index)
{
    int* elementPtr;
    int nextResource;
    int currentIndex;

    if (index < thisPtr[1] - 1U) // Check if index is within removable range (excluding last element)
    {
        currentIndex = index * 0xc; // Offset to the element (12 bytes per element)
        do
        {
            elementPtr = (int*)(currentIndex + *thisPtr); // Pointer to current element
            if (elementPtr != elementPtr + 3) // Always true? Redundant check? (ensures next element exists)
            {
                nextResource = elementPtr[3]; // Resource pointer of the next element
                if (*elementPtr != nextResource) // If current resource differs from next resource
                {
                    if (*elementPtr != 0) // If current resource is not null
                    {
                        this->releaseResource(elementPtr); // Free current resource
                    }
                    *elementPtr = nextResource; // Copy next resource into current
                    if (nextResource != 0) // If next resource exists, update its back pointer? (linked list?)
                    {
                        elementPtr[1] = *(int*)(nextResource + 4); // Possibly link back to current? (reference count?)
                        *(int**)(nextResource + 4) = elementPtr; // Adjust forward pointer of next resource
                    }
                }
            }
            elementPtr[2] = elementPtr[5]; // Copy third field from next element to current (some data)
            index = index + 1;
            currentIndex = currentIndex + 0xc;
        } while (index < thisPtr[1] - 1U); // Shift all elements left
    }
    thisPtr[1] = thisPtr[1] - 1; // Decrease element count
    // Release the resource of the last element (now beyond the array)
    if (*(int*)(*thisPtr + thisPtr[1] * 0xc) != 0) // Check if last element's resource is non-null
    {
        this->releaseResource((int*)(*thisPtr + thisPtr[1] * 0xc)); // Release it
    }
}

// Helper function: FUN_004daf90 - likely releases a resource
void __thiscall Container::releaseResource(int* element)
{
    // Implementation not shown, but typical release logic (decrement refcount, free memory, etc.)
}