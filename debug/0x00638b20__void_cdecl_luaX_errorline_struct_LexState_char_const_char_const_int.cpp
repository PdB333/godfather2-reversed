// Xbox PDB: void __cdecl luaX_errorline(struct LexState *,char const *,char const *,int)
// FUNC_NAME: Debug::assertFailed

void __thiscall Debug::assertFailed(const char* expression, const char* message, int lineNumber)
{
    char prefixBuf[80]; // buffer for "sourcefile:line: " prefix

    // Build prefix from current assertion context (this->sourceContext at +0x2c)
    // The source context stores file/line info; offset +0x10 points to the filename string.
    Debug::buildPrefix(prefixBuf, *(const char**)((char*)this + 0x2c) + 0x10);

    // Output formatted assertion message
    Debug::printf("%s:%d: %s near `%s'", prefixBuf, lineNumber, expression, message);

    // Trigger debug break (assert handler)
    Debug::breakExecution();
}