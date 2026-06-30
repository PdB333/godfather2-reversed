// FUNC_NAME: AssetLoader::waitForCompletion
void AssetLoader::waitForCompletion() {
    // +0x04: volatile int m_loadingCounter (incremented by background loader)
    int previousCounter = this->m_loadingCounter;
    if (previousCounter != 0) {
        do {
            // Output progress indicator: space, tab, carriage return, newline
            debugOutputChar(0x20); // ' '  space
            debugOutputChar(0x09); // '\t' tab
            debugOutputChar(0x0D); // '\r' carriage return
            debugOutputChar(0x0A); // '\n' newline
            // Check if counter changed since last iteration
            bool bChanged = (previousCounter != this->m_loadingCounter);
            previousCounter = this->m_loadingCounter;
        } while (bChanged); // Continue while counter is still changing; exit when stable
    }
    // If counter was already zero, no waiting needed
}