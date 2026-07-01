// FUNC_NAME: SimManager::updateActiveComponent
extern void processActiveStream(); // address 0x004df600

void SimManager::updateActiveComponent()
{
    // Check if the active component pointer (offset 0x1f0c) is non-null
    if (*(int *)(this + 0x1f0c) != 0) {
        processActiveStream();
    }
}