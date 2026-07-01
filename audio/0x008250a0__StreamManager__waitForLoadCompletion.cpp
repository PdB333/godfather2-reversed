// FUNC_NAME: StreamManager::waitForLoadCompletion
void __thiscall StreamManager::waitForLoadCompletion(int fileHandle) {
  // Initialize the load process with the given file handle
  loadResourceInit(fileHandle);
  // Start loading with a specific hash identifier (0xee204f17)
  loadResourceWithHash(fileHandle, 0xee204f17);

  // Poll until the entire loading operation is complete
  while (!isLoadingComplete()) {
    // Advance to the next load item (or get the current one)
    int currentItem = getCurrentLoadItem();

    // Check if the current item is ready (returns 0 if ready)
    int itemReady = isLoadItemReady();
    if (itemReady == 0) {
      // Get the actual ready item and store its data pointer
      int readyItem = getCurrentLoadItem();
      this->loadedData = *(void**)(readyItem + 8); // Store pointer at offset +0x8 in the item
    }

    // Update load progress (may trigger callbacks)
    updateLoadProgress();

    // Re-check completion status for next iteration
  }
  // Loading is complete; all items processed
}