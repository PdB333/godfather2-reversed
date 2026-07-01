// FUNC_NAME: SomeManager::addFromSource
undefined4 __thiscall SomeManager::addFromSource(int this, int sourceObject)
{
    undefined4 *newElement;
    undefined4 newId;
    int temp;

    // Generate a new unique ID for the element
    newId = generateId();

    // Attempt to allocate memory for the element (size 4? possibly a placeholder)
    temp = allocateMemory(4);
    if (temp == 0) {
        newElement = 0;
    } else {
        // Construct the element: pass the new ID and some data from sourceObject at offset +0x18
        newElement = (undefined4 *)constructElement(newId, *(undefined4 *)(sourceObject + 0x18));
    }

    // Initialize the element (dereferencing newElement – likely a pointer-to-pointer?)
    initializeElement(*newElement);

    // Check if array needs to grow (capacity at +0x14, count at +0x10)
    int capacity = *(int *)(this + 0x14);
    if (*(int *)(this + 0x10) == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        growArray(capacity);
    }

    // Get pointer to next free slot (base pointer at +0x0c, count offset)
    undefined4 *slot = (undefined4 *)(*(int *)(this + 0xc) + *(int *)(this + 0x10) * 4);
    // Increment count
    *(int *)(this + 0x10) += 1;

    // Store the new element pointer in the slot
    if (slot != 0) {
        *slot = newElement;
    }

    // Conditionally store first element as "first added" (fields at +0x18 and +0x1c)
    temp = checkCondition();
    if ((temp != 0) && (*(int *)(this + 0x18) == 0)) {
        *(int *)(this + 0x18) = temp;          // +0x18: some flag/state
        *(undefined4 **)(this + 0x1c) = newElement; // +0x1c: pointer to first element
    }

    return newId;
}