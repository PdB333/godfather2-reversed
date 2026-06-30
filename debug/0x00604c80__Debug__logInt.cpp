// FUNC_NAME: Debug::logInt
void Debug::logInt(int value) {
    char buffer[256];
    __snprintf(buffer, sizeof(buffer), "%d", value);
    // Call to internal string output method (address 0x00604c10)
    this->outputString(buffer);
}