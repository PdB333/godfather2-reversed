// FUNC_NAME: FileParser::assertUnexpectedEndOfFile
// Address: 0x00641890
// Called when a file read operation encounters an unexpected end-of-file condition.
// Prints an error message with the filename (stored at this+0x10) and triggers a debug breakpoint.

void FileParser::assertUnexpectedEndOfFile(void) {
    // Log the error: format string with filename at offset 0x10
    debugLog(this, "unexpected end of file in %s", *(const char**)((uint8_t*)this + 0x10));
    // Trigger a debug breakpoint (int 3 / __debugbreak)
    debugBreak();
    // Unreachable after breakpoint
}