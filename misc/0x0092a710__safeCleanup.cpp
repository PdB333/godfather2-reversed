//FUNC_NAME: safeCleanup
void safeCleanup(void* unused, void* ptr) {
    if (ptr != nullptr) {
        globalCleanup();          // FUN_009823b0 - global cleanup routine
        specificCleanup(ptr);     // FUN_009c8eb0 - cleanup for the given object
    }
}