// FUNC_NAME: RichTextParser::parseNextTag
uint __thiscall RichTextParser::parseNextTag(void)
{
    char *pCurrentPos;
    char *pBracketStart;
    char *pBracketEnd;
    int iTextBeforeTag;
    int iProcessedSoFar;
    uint uResult;

    pCurrentPos = this->m_pCurrentPos; // +0x04
    pBracketEnd = NULL;

    if (pCurrentPos == NULL) {
        // No more data, return status from previous call (preserve high bits)
        return (uResult & 0xFFFFFF00);
    }

    do {
        pBracketStart = _strchr(pCurrentPos, '[');
        pCurrentPos = pBracketEnd;
        if ((pBracketStart == NULL) || (pBracketEnd = _strchr(pBracketStart, ']'), pBracketEnd == NULL))
            goto skipTag;
        iTextBeforeTag = __strnicmp(pBracketStart + 1, "c=", 2);
        pBracketEnd = pBracketEnd; // stays the same
    } while (iTextBeforeTag == 0); // Skip [c=...] tags

    if (pBracketEnd == NULL) {
skipTag:
        // No valid tag found; mark entire remaining string as processed
        uResult = (uint)(this->m_pCurrentPos - this->m_pStreamStart); // +0x18 offset
        this->m_uProcessedBeforeTag = uResult; // +0x20
        this->m_uRemainingData = (this->m_uStreamEnd - uResult); // +0x1c - +0x20
        uResult = uResult & 0xFFFFFF00;
    } else {
        // Found a tag that is not [c=...]; check for [b=...]
        int iIsBold = __strnicmp(pBracketStart + 1, "b=", 2);
        char *pTagStart = pBracketStart;
        if (iIsBold == 0) {
            pTagStart = pBracketStart + 2; // Skip "b="
        }
        // Store pointer to the beginning of the tag content (after the tag header)
        this->m_pTagContentStart = pTagStart + (1 - this->m_iBaseOffset); // +0x08, +0x10
        // Calculate length of tag content (excluding brackets)
        int iTagContentLen = (int)(pBracketEnd + (-1 - (int)pTagStart));
        if (iTagContentLen < 0) {
            this->m_iTagContentLength = this->m_iSomething - this->m_pTagContentStart; // +0x0c, +0x14
        } else {
            this->m_iTagContentLength = iTagContentLen; // +0x14
        }
        // Compute number of characters before the tag opening bracket
        iTextBeforeTag = (int)pBracketStart - (int)this->m_pCurrentPos;
        iProcessedSoFar = (int)this->m_pCurrentPos - this->m_pStreamStart; // +0x18
        this->m_uProcessedBeforeTag = iProcessedSoFar; // +0x20
        if (iTextBeforeTag < 0) {
            this->m_uRemainingData = this->m_uStreamEnd - iProcessedSoFar; // +0x1c - +0x24
            uResult = (iProcessedSoFar & 0xFFFFFF00) | 1;
        } else {
            this->m_uRemainingData = iTextBeforeTag; // +0x24
            uResult = (iProcessedSoFar & 0xFFFFFF00) | 1;
        }
    }

    if (pBracketEnd == NULL) {
        this->m_pCurrentPos = NULL; // No more data
    } else {
        this->m_pCurrentPos = pBracketEnd + 1; // Advance past the closing bracket
    }

    return uResult;
}