// FUNC_NAME: resolveStringDescriptor
bool __stdcall resolveStringDescriptor(const StringDescriptor* desc, const char** outStr)
{
    // desc structure: +0x00: string pointer, +0x04: valid flag (non-zero means descriptor is populated)
    if (desc->valid != 0) {
        const char* str = desc->str;                     // +0x00
        if (str == nullptr) {
            str = "";                                    // fallback to empty string (DAT_0120546e)
        }
        const char* resolved;
        if (FUN_004d6f20(str, &resolved)) {              // intern lookup or hash resolution
            *outStr = resolved;
            return true;
        }
    }
    return false;
}