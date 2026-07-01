// FUNC_NAME: Timeline::getSegmentAtPosition
// Function at 0x008162b0: Gets the active segment at a given position (e.g., time) with edge blending.
// Returns 1 if found, 0 if before first or beyond last.
int __thiscall Timeline::getSegmentAtPosition(uint position, void** outData, uint* outWeight)
{
    // +0x08: mCurrentIndex (uint) – current search index, updated on each call
    // +0x14: mNumSegments (uint) – total number of segments
    // +0x10: mSegments (Segment*) – array of Segment structures (0x18 bytes each)
    // +0x04: mBlendWidth (uint) – width of blend/transition at segment edges
    // Segment layout: +0x00 start (uint), +0x04 span (uint), +0x08 pData (void*)
    if (mCurrentIndex < mNumSegments) {
        do {
            int idx = mCurrentIndex;
            Segment* seg = &mSegments[idx];
            uint start = seg->start;
            if (position < start) {
                return 0; // before first segment
            }
            uint end = start + seg->span;
            if (position <= end) {
                void* data = seg->pData;
                if (data == nullptr) {
                    data = (void*)&DAT_0120546e; // default placeholder (e.g., "no data")
                }
                *outData = data;

                uint blend = mBlendWidth;
                uint distFromStart = position - start;
                uint distFromEnd = end - position;
                if (distFromStart < blend) {
                    *outWeight = (distFromStart * 0xFF) / blend;
                } else if (distFromEnd < blend) {
                    *outWeight = (distFromEnd * 0xFF) / blend;
                } else {
                    *outWeight = 0xFF;
                }
                return 1;
            }
            mCurrentIndex = idx + 1;
        } while (mCurrentIndex < mNumSegments);
    }
    return 0;
}