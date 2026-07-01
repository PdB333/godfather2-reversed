//FUNC_NAME: InputDeviceManager::setInputConfigPath
int __thiscall InputDeviceManager::setInputConfigPath(int this, char *path)
{
    char pathBuffer[192];
    char *slashPos;
    int cmpResult;

    // Validate the path; if invalid, return 0
    if (FUN_0098bc00(path) != 0) {
        return 0;
    }

    // Copy the path into a local buffer (max 192 bytes)
    _strncpy(pathBuffer, path, 192);

    // Find the last '/' in the path
    slashPos = _strrchr(pathBuffer, '/');
    if (slashPos != NULL) {
        // Replace the part after the last '/' with "/input"
        _strncpy(slashPos, "/input", (int)&stack0x00000000 - (int)slashPos);
    }

    // If the stored flag at +0x5c is non-zero, compare the new path with the stored one at +0x60
    if (*(int *)(this + 0x5c) != 0) {
        // Manual strcmp (byte-by-byte, two bytes per iteration)
        char *storedPath = (char *)(this + 0x60);
        char *newPath = pathBuffer;
        do {
            char c1 = *newPath;
            char c2 = *storedPath;
            if (c1 != c2) {
                cmpResult = (c1 < c2) ? -1 : 1;
                break;
            }
            if (c1 == 0) {
                cmpResult = 0;
                break;
            }
            c1 = newPath[1];
            c2 = storedPath[1];
            if (c1 != c2) {
                cmpResult = (c1 < c2) ? -1 : 1;
                break;
            }
            newPath += 2;
            storedPath += 2;
        } while (c1 != 0);

        // If paths are identical, call the load/register functions
        if (cmpResult == 0) {
            int out1, out2;
            FUN_00926810(&out1, &out2);
            FUN_0098ab10(out1, out2);
        }
    }

    return 1;
}