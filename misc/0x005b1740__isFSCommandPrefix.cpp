// FUNC_NAME: isFSCommandPrefix
bool isFSCommandPrefix(const char* str) {
    return _strncmp(str, "FSCommand:", 10) == 0;
}