// Xbox PDB: EARS_Apt_UIMonopoly_NotifySetMonopolyIndex
// FUNC_NAME: Monopoly::initVenueControl

#include <cstring>
#include <cstdio>

typedef void (*DeallocFunc)(char*);

void __fastcall Monopoly::initVenueControl(int this)
{
    // +0x74: venue index (or -1 if none)
    int venueIndex = *(int*)(this + 0x74);
    if (venueIndex != -1) {
        // +0x58: pointer to an array of data entries (each 4 bytes)
        int* dataArray = *(int**)(this + 0x58);
        // Get data for this venue index
        char* rawData = (char*)FUN_0084aea0(*(int*)(dataArray + venueIndex));
        if (rawData != nullptr) {
            // +0x78: venue ID from first field of the data
            *(int*)(this + 0x78) = *(int*)rawData;

            // Retrieve default string from global string table #1
            int stringTable1 = FUN_0084a4b0();
            char* defaultStr1 = *(char**)(stringTable1 + 4);
            if (defaultStr1 == nullptr) {
                defaultStr1 = &DAT_0120546e; // empty string
            }
            // Copy to +0x7c buffer (size 0x80)
            FUN_005c4660(*(char**)(this + 0x7c), defaultStr1, 0x80, /* unknown */ 0);

            // Retrieve default string from global string table #2
            int stringTable2 = FUN_0084a4e0();
            char* defaultStr2 = *(char**)(stringTable2 + 4);
            if (defaultStr2 == nullptr) {
                defaultStr2 = &DAT_0120546e;
            }
            // Copy to +0x80 buffer
            FUN_005c4660(*(char**)(this + 0x80), defaultStr2, 0x80, 0);

            // Format a numeric ID into +0x84 buffer
            unsigned int numericId = FUN_0084a150();
            FUN_005c4630(*(char**)(this + 0x84), 0x20, "{#%u}", numericId);

            // Resolve localized string from hash (0x637b907 → "mono_venue_control")
            char* resolvedStr = (char*)FUN_0084a470(0x637b907);
            unsigned int coordY = rawData[2];      // rawData[2] is a 4-byte int
            // Format a complex venue control string
            char* formattedStr = nullptr;
            int fmtResult = FUN_004d4a60(&formattedStr, 1, "{x:%u}{y:%u}{$dv_mono_venue_control}", resolvedStr, coordY);
            // Note: the first argument to FUN_004d4a60 is a pointer to receive the allocated string,
            // the second is a boolean (1 means allocate?), then format, then args.
            // The last argument local_c is used as a dummy? Actually the decompiled shows local_c.
            // We'll pass a dummy value for local_c.
            int dummy = 0; // value from local_c
            char* finalStr = formattedStr;
            if (formattedStr == nullptr) {
                finalStr = &DAT_0120546e;
            }
            // Copy to +0x88 buffer
            FUN_005c4660(*(char**)(this + 0x88), finalStr, 0x80, dummy);
            if (formattedStr != nullptr) {
                // Free the allocated string using the deallocator function (stored in local_4)
                // local_4 is a function pointer that was passed implicitly or is a global deallocator
                // In the decompiled, it's a local variable assigned from somewhere.
                // We'll assume it's a free function.
                void (*dealloc)(char*) = (void (*)(char*))local_4;
                dealloc(formattedStr);
            }
            goto LAB_0095bc1e;
        }
    }
    // Default: set all to empty/disabled
    *(int*)(this + 0x78) = -1; // or 0xffffffff
    **(char**)(this + 0x7c) = 0; // null terminate first byte
    **(char**)(this + 0x80) = 0;
    **(char**)(this + 0x84) = 0;
    **(char**)(this + 0x88) = 0;

LAB_0095bc1e:
    // Clear additional fields
    *(int*)(this + 0x90) = 0;
    *(int*)(this + 0x94) = -1; // 0xffffffff
    **(char**)(this + 0x98) = 0;
    **(char**)(this + 0x9c) = 0;
    **(char**)(this + 0xa0) = 0;
    *(int*)(this + 0xa4) = 0; // not a char**? The decompiled uses **(undefined1 **) for 0xa4, but offset 0xa4 is 4-byte aligned.
    // Actually the pattern from 0x98 to 0xac is consistent: each is a char**, so we set all to empty strings
    **(char**)(this + 0xa8) = 0;
    **(char**)(this + 0xac) = 0;
    *(char*)(this + 0xb0) = 0; // bool
    *(int*)(this + 0xb4) = 0;
    *(int*)(this + 0xb8) = 0;

    // Call second initialization function (likely another member function)
    FUN_0095ae90();
    return;
}