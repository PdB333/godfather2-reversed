// Xbox PDB: EARS::Online::PlasmaGameManagerListener::ParseGameConfig
// FUNC_NAME: ConfigurationParser::parseSections
// Address: 0x005684b0
// Likely part of EA EARS config system. Parses a buffer into numbered "GameConfiguration" sections.
// this+0x350: m_pConfigBuffer (null-terminated string or concatenated data)
// this+0x354: m_configBufferLength (int, remaining bytes to process)
// this+0x8: pointer to a manager object with virtual methods (to get max sections or buffer limit)

void __thiscall ConfigurationParser::parseSections(void)
{
    int *pManager;           // piVar2
    uint sectionCount;       // uVar3
    int maxSections;         // iVar4
    char *pChunk;            // puVar5
    char savedByte;          // uVar6
    uint chunkSize;          // uVar7
    int index;               // iStack_28
    char sectionName[32];    // acStack_20

    // Get manager object (likely a settings/registry interface)
    pManager = (int *)(**(code **)(**(int **)(this + 8) + 0x78))();
    // Get total section count from manager (or buffer length)
    sectionCount = (**(code **)(*pManager + 0x1c))();
    if (sectionCount < 0x41) {
        maxSections = (**(code **)(*pManager + 0x1c))();
    }
    else {
        maxSections = 0x40; // cap at 64 sections
    }

    // Get pointer to config data
    pChunk = *(char **)(this + 0x350);
    // Increment remaining length? Actually this is the initial offset/length
    sectionCount = *(int *)(this + 0x354) + 1;

    // If no buffer, use fallback static string (DAT_0120546e likely "GameConfiguration\0")
    if (pChunk == (char *)0x0) {
        pChunk = &DAT_0120546e;
    }

    index = 0;
    while (true) {
        // Determine chunk size: min(maxSections-1, sectionCount)
        chunkSize = maxSections - 1;
        if (sectionCount <= maxSections - 1) {
            chunkSize = sectionCount;
        }

        savedByte = 0;
        char *pToken = (char *)0x0;
        if (chunkSize < sectionCount) {
            // Save the byte at the end of this chunk and null-terminate
            savedByte = pChunk[chunkSize];
            pChunk[chunkSize] = '\0';
            pToken = pChunk + chunkSize;
        }

        // Advance pointer to this chunk
        pChunk = pToken;

        // Build section name
        if (index == 0) {
            _sprintf(sectionName, "GameConfiguration");
        }
        else {
            _sprintf(sectionName, "GameConfiguration%d", index);
        }

        if (pChunk == (char *)0x0) break;

        // Update remaining length
        sectionCount = sectionCount - chunkSize;
        index++;

        // Restore the original byte (so the buffer remains intact)
        *pChunk = savedByte;
    }
    // sectionName is built but not used? Possibly for a log or callback not shown.
    return;
}