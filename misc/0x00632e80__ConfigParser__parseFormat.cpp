// FUNC_NAME: ConfigParser::parseFormat
int __thiscall ConfigParser::parseFormat(char *format, int flag)
{
    char *fmtPtr = format;
    char ch = *format;
    int result = 1; // return value
    if (ch == '\0') {
        return 1;
    }
    do {
        switch (ch) {
        case 'S': // read string
            this->readString(); // completes string parsing (FUN_00632d40)
            break;
        default:
            result = 0; // unsupported format character
            break;
        case 'f': // read float
            // Write float from current stream position (in_EAX) to the float pointer stored at this+0x08
            *(float *)(this + 0x08) = *(float *)streamPtr;
            *(float *)((this + 0x08) + 4) = *(float *)(streamPtr + 4);
            break;
        case 'l': // read long (or ID)
            if (flag == 0) {
                *(int *)(this + 0x14) = -1;
            } else {
                int val = FUN_00632aa0(); // likely reads a long from stream
                *(int *)(this + 0x14) = val;
            }
            break;
        case 'n': // read name
            if (flag == 0) {
                *(int *)(this + 0x08) = 0;
            } else {
                int namePtr = FUN_00633640(this + 4); // allocate/read name
                *(int *)(this + 0x08) = namePtr;
                if (namePtr == 0) {
                    int defaultName = FUN_00632da0(); // get default name?
                    *(int *)(this + 0x04) = defaultName;
                    if (defaultName == 0) {
                        *(char **)(this + 0x08) = &DAT_00e2f044; // some static data
                    } else {
                        *(char **)(this + 0x08) = "global";
                    }
                }
            }
            break;
        case 'u': // read unsigned byte?
            // streamPtr is assumed to point to some data, but here streamPtr[1]+7 is used
            *(unsigned int *)(this + 0x18) = (unsigned int)*(unsigned char *)(streamPtr[1] + 7);
            break;
        }
        ch = fmtPtr[1];
        fmtPtr++;
    } while (ch != '\0');
    return result;
}