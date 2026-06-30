// FUNC_NAME: EARSFileSystem::openFile
int __thiscall EARSFileSystem::openFile(void *this, char *filename) {
    // File open context structure (stack allocated)
    struct FileOpenContext {
        int field0; // +0x00: initialized from global DAT_01206a28 (likely base timestamp or handle)
        int field4; // +0x04: zeroed
        char field8; // +0x08: zeroed
    };
    FileOpenContext ctx;
    ctx.field0 = DAT_01206a28;
    ctx.field4 = 0;
    ctx.field8 = 0;

    // Initialize the context (e.g., set up timing or handle reference)
    fileOpenInit(&ctx, 0); // FUN_00408a00

    // Determine open mode:
    // - If filename is null or empty, use mode 2 (existing file, read/write).
    // - Otherwise, use mode 6 (open existing or create new file, read/write).
    int mode = 2;
    if (filename != 0 && *filename != '\0') {
        mode = 6;
    }

    // Attempt to open the file; returns non-zero handle on success.
    int result = openFileInternal(this, 0, mode, 0, filename); // FUN_00403a50
    if (result != 0) {
        // Notify success (e.g., register handle, fire callback)
        onFileOpened(); // FUN_00411840
    }

    return 1; // Always returns success
}