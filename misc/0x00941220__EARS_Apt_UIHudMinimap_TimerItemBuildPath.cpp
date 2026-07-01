// Xbox PDB: EARS_Apt_UIHudMinimap_TimerItemBuildPath
// FUNC_NAME: buildMinimapTimerPath
// Function address: 0x00941220
// Constructs a file path for minimap timer assets under "mmap/minimap_timer".
// param_1: output buffer (must be at least 256 bytes)
// param_2: optional prefix (e.g., "player" or mission name)
// param_3: optional suffix (e.g., "active" or "inactive")
void buildMinimapTimerPath(char *outBuffer, char *part1, char *part2)
{
    const int bufSize = 0x100; // 256

    if (part1 != nullptr && *part1 != '\0') {
        if (part2 != nullptr && *part2 != '\0') {
            __snprintf(outBuffer, bufSize, "mmap/minimap_timer/%s.%s", part1, part2);
            return;
        }
        __snprintf(outBuffer, bufSize, "mmap/minimap_timer/%s", part1);
        return;
    }

    if (part2 != nullptr && *part2 != '\0') {
        __snprintf(outBuffer, bufSize, "mmap/minimap_timer.%s", part2);
        return;
    }

    _strncpy(outBuffer, "mmap/minimap_timer", bufSize);
}