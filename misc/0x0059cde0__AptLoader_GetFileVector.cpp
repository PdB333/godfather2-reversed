// Xbox PDB: AptLoader::GetFileVector
// FUNC_NAME: RefCountedPool::assignHandles
// Function at 0x0059cde0: Assigns an array of refcounted handles from a fixed-size pool (max 64 entries).
// Each pool node contains a pointer to a refcounted object (offset 0) and a next pointer (offset 4).
// The destination array (dest) is updated: old objects are released, new objects are retained.
void RefCountedPool::assignHandles(int* destArray)
{
    // Get head of the global pool linked list
    Node** head = DAT_0119a9c8;   // pool head pointer
    Node* currentNode = *head;
    int index = 0;

    while (currentNode != nullptr)
    {
        // Assert that we don't exceed the maximum allowed size (64)
        if (index > 0x3F)
        {
            // Assertion failure: "j < nMaxSize"
            const char* condition = "j < nMaxSize";
            const char* file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptLoad.h";
            int line = 0x3B;
            int assertType = 2;
            // ... (assertion handling omitted for brevity)
            // In release builds, this might trigger a breakpoint or abort.
        }

        // Get the object pointer from the current node (first field)
        RefCountedObject* newObject = (RefCountedObject*)currentNode->objectPtr;
        index++;

        if (newObject != nullptr)
        {
            newObject->refCount++;
        }

        // Handle the current destination slot
        // The code contains a strange label which appears to handle self-assignment.
        // For clarity, we implement the standard smart pointer assignment:
        // Release the old object, then assign the new one and retain it.
        int* oldObject = (int*)*destArray;
        if (oldObject != nullptr)
        {
            oldObject->refCount--;
            if (oldObject->refCount == 0)
            {
                // Finalize and free the object (size 0x30)
                RefCountedPool::finalizeObject(oldObject);
                DAT_0119caf8(oldObject, 0x30);
            }
        }

        *destArray = (int)newObject;

        if (newObject != nullptr)
        {
            newObject->refCount++;
        }

        // Move to the next node and next destination slot
        currentNode = currentNode->next;
        destArray++;
    }
}