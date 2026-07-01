// FUNC_NAME: SomeManager::findAndProcessObject
void __fastcall SomeManager::findAndProcessObject(int this) {
    // +0x2494: pointer to a container (list/array) of objects
    int containerPtr = *(int *)(this + 0x2494);
    bool firstIteration = false;
    int currentIndex = 0;
    int totalCount = 0;
    int *foundObject = nullptr;

    do {
        int state = getContainerState(containerPtr); // e.g., returns 4 when container is empty/end
        if (state == 4) {
            return;
        }

        if (firstIteration) {
            // Subsequent iterations: get next object and update index
            currentIndex = getNextObject(containerPtr, &foundObject, &currentIndex);
            if (totalCount == currentIndex) {
                return; // No more objects
            }
        } else {
            // First iteration: initialize iteration, get first object and total count
            currentIndex = getNextObject(containerPtr, &foundObject, 0);
            firstIteration = true;
            totalCount = currentIndex;
        }
    } while ((foundObject == nullptr) ||
             (*(void **)(*(int *)(*foundObject + 0x10))() != (void *)0x00e078fa)); // Check if object's virtual function returns a specific address (type marker)

    if (foundObject != nullptr) {
        processFoundObject(); // Handle the matched object
    }
    return;
}