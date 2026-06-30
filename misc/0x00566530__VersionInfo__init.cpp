// FUNC_NAME: VersionInfo::init
// Function address: 0x00566530
// Initializes a version info object: stores a version string pointer and reads "version" from config into a buffer.

class VersionInfo {
public:
    const char* versionString;  // +0x00: pointer to version string
    char versionBuffer[32];     // +0x04: buffer for version from config (size 0x20)
};

// Reads a string value from configuration (FUN_00adc4f0)
bool readConfigString(const char* key, char* buffer, int bufferSize);

VersionInfo* VersionInfo::init(VersionInfo* this, const char* versionStr) {
    this->versionString = versionStr;
    if (!readConfigString("version", this->versionBuffer, 0x20)) {
        this->versionBuffer[0] = '\0';
    }
    return this;
}