// FUNC_NAME: InputDeviceManager::InputDeviceManager
int __fastcall InputDeviceManager::InputDeviceManager(int this)
{
    // Allocate a 0x28-byte node (likely a sentinel for a circular linked list of buttons)
    int *sentinel = (int *)allocateMemory(0x28);
    if (sentinel != nullptr) {
        sentinel[0] = 0;  // +0x00: previous pointer (initially null)
    }
    if (sentinel + 1 != nullptr) {
        sentinel[1] = 0;  // +0x04: next pointer (initially null)
    }
    if (sentinel + 2 != nullptr) {
        sentinel[2] = 0;  // +0x08: button data pointer (initially null)
    }
    // +0x24: flag byte, set to 1 (sentinel marker)
    *(int8_t *)(sentinel + 9) = 1;    // offset 0x24 (9*4 = 36)
    // +0x25: another flag byte, initially 0
    *(int8_t *)((int)sentinel + 0x25) = 0;

    // Store sentinel as the head of the button list (at +0x04 of this)
    *(int **)(this + 4) = sentinel;

    // Mark sentinel as linked (circular self-reference)
    *(int8_t *)((int)sentinel + 0x25) = 1;

    // Initialize sentinel circular links: sentinel->next = sentinel; sentinel->prev = sentinel; sentinel->data = sentinel (unusual)
    *(int *)(*(int *)(this + 4) + 4) = *(int *)(this + 4);    // +0x04: next = sentinel
    *(int *)*(int *)(this + 4) = *(int *)(this + 4);          // +0x00: prev = sentinel
    *(int *)(*(int *)(this + 4) + 8) = *(int *)(this + 4);    // +0x08: data = sentinel

    // Clear another pointer at +0x08 of this (maybe a secondary list head)
    *(int *)(this + 8) = 0;

    // Create 16 buttons (indices 0..15) and add them to the list
    for (int i = 0; i < 16; i++) {
        // Debug label (e.g., "Button.1" for i=0)
        debugPrint("Button.%d", i + 1);

        // Scoped creation pattern: FUN_00696de0 initializes a temporary structure
        // and returns a pointer to a new Button object (2 ints)
        int scopedData[3];  // stores destructor callback and object
        // local_4 is inferred as a code pointer (destructor)
        int (*destructor)(int) = nullptr;

        int *button = (int *)createButton(scopedData);  // FUN_00696de0
        button[0] = 0;       // +0x00: button identifier or state
        button[1] = i;       // +0x04: button index (0..15)

        // If scoped data contains a destructor, call it immediately (cleanup pattern)
        if (scopedData[0] != 0) {
            destructor(scopedData[0]);
        }
    }

    return this;
}