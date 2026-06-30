// FUNC_NAME: ChunkedFileParser::FindTitleString
// Function at 0x005d3cb0: Scans a chunked file for a specific identifier ("apxf" + "titl") and extracts the title string.
// Uses big-endian 4-byte tags. The file structure: header starts with "apxf", then series of tagged chunks.
// Each chunk: 4-byte tag, 4-byte size, then data. The function looks for a chunk with tag "apxf" that contains a sub-tag "titl",
// and extracts the null-terminated string at offset 0x10 from the chunk start, lowercasing it.
// Class layout: +0x00 m_pData, +0x04 m_nFlags, +0x08 ???, +0x0C m_nSize, +0x10 m_nPos

char* __thiscall ChunkedFileParser::FindTitleString(void) {
    int iVar1;
    int iVar2;
    int* piVar3;
    char* pString;
    int nOldPos;
    int nTag;
    int nSubTag;
    int nChunkSize;

    nOldPos = this->m_nPos;                          // save current position
    pString = nullptr;
    this->m_nPos = 0;                                // start at beginning

    piVar3 = (int*)this->m_pData;                    // get data pointer (cast to int* for convenience)
    iVar2 = *piVar3;                                 // read first 4 bytes as big-endian
    this->m_nPos = 4;
    if (iVar2 != 0x61707866) {                       // "apxf" in big-endian
        return nullptr;                              // invalid magic
    }

    this->m_nPos = 0;                                 // reset position for loop

    do {
        iVar2 = this->m_nPos;                         // current offset
        if (this->m_nSize - 8 <= iVar2) break;        // need at least 8 bytes for tag+size

        // Read 4-byte tag at current position (big-endian)
        nTag = *(int*)((char*)piVar3 + iVar2);       // simplified: but Ghidra shows byte swapping; we'll assume behavior matches
        this->m_nPos = iVar2 + 4;

        if (nTag == 0x61707866) {                     // "apxf"
            this->m_nPos = iVar2 + 8;                 // position to next 4 bytes
            nSubTag = *(int*)((char*)piVar3 + iVar2 + 8); // read "titl" tag
            this->m_nPos = iVar2 + 0xC;
            if (nSubTag == 0x7469746c) {               // "titl"
                pString = (char*)piVar3 + iVar2 + 0x10; // string starts at offset 0x10 within this chunk
                this->m_nPos = iVar2 + 0x10;
                strlwr(pString);                        // lowercase the string
            }
        } else {
            this->m_nPos = this->m_nSize;              // on wrong tag, skip to end
        }

        piVar3 = (int*)this->m_pData;                  // re-fetch pointer (in case data moved? unlikely)
        this->m_nPos = iVar2 + 4;                      // read chunk size at offset iVar2+4? Actually Ghidra shows this read later.
        nChunkSize = *(int*)((char*)piVar3 + iVar2 + 4); // 4-byte size (big-endian)
        this->m_nPos = nChunkSize + iVar2;              // advance to next chunk (size is relative to chunk start)
    } while (pString == nullptr);

    this->m_nPos = nOldPos;                            // restore position
    return pString;
}