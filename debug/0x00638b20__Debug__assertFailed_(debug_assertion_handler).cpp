// FUNC_NAME: Debug::assertFailed (debug assertion handler)
void Debug::assertFailed(const char* functionName, const char* expression, int lineNumber) {
    char buffer[80];
    // Get file:line string from this->fileInfo+0x10 (likely a FILE_LINE struct)
    formatFileLine(buffer, *(int*)((uint)this + 0x2c) + 0x10); // this+0x2c = pointer to file info block
    // Compose assertion message: "file:line: function near 'expression'"
    debugPrintf("%s:%d: %s near `%s'", buffer, lineNumber, functionName, expression);
    debugAbort(); // Trigger breakpoint/abort
}