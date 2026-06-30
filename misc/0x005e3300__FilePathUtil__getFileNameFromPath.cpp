// FUNC_NAME: FilePathUtil::getFileNameFromPath
// Address: 0x005e3300
// Role: Extract the file name portion from a path string (after last '/' or '\'), 
// then call an internal processing function (likely duplicate/copy). If no path provided or no separator found, returns 0.

int FilePathUtil::getFileNameFromPath(char *path)
{
    char *fileNameStart;
    char ch;
    char *walkPtr;

    if (path == (char *)0x0) {
        return 0;
    }

    ch = *path;
    fileNameStart = path;
    while (ch != '\0') {
        if ((ch == '\\') || (ch == '/')) {
            fileNameStart = path + 1; // start of filename after separator
        }
        walkPtr = path + 1; // advance
        path = path + 1;
        ch = *walkPtr;
    }

    if (fileNameStart != (char *)0x0) {
        // Internal function – likely duplicates or processes the extracted filename
        return (int)processExtractedFileName();
    }
    return 0;
}