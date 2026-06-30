// FUNC_NAME: Animated::interpolateVertices
void Animated::interpolateVertices(void)
{
    float *pArrayA = *(float **)(this + 0x2224);   // +0x2224: array A (e.g., position/rotation)
    float *pArrayB = *(float **)(this + 0x2220);   // +0x2220: array B (e.g., delta or target)
    char  *pFlags  = *(char  **)(this + 0x2228);   // +0x2228: per‑vertex flags (0 = inactive / skip)
    int segmentCount = *(short *)(this + 0x221c);  // +0x221c: number of vertex segments

    int **pSegmentStarts = *(int ***)(this + 0x2214); // +0x2214: array of segment start indices (shorts)
    int **pSegmentEnds   = *(int ***)(this + 0x2218); // +0x2218: array of segment end indices (shorts)

    for (int segIdx = 0; segIdx < segmentCount; segIdx++)
    {
        int segStart = (int)(*(short *)(pSegmentStarts + segIdx));
        int segEnd   = (int)(*(short *)(pSegmentEnds + segIdx));
        int count    = (segEnd - segStart) + 1;

        // Find first non‑flagged vertex in the segment
        int curIdx = segStart;
        while (pFlags[curIdx] == '\0')
        {
            curIdx++;
        }

        // Load first valid vertex pair
        float vecPrevA = *(pArrayA + curIdx);
        float vecPrevB = *(pArrayB + curIdx);

        // Process remaining vertices in the segment
        while (count > 0)
        {
            curIdx++;
            if (curIdx > segEnd)
                curIdx = segStart;

            float vecCurA = *(pArrayA + curIdx);
            float vecCurB = *(pArrayB + curIdx);

            if (pFlags[curIdx] == '\0')
            {
                // This vertex is flagged; perform three‑point interpolation
                int idx2 = curIdx + 1;
                if (idx2 > segEnd)
                    idx2 = segStart;

                curIdx = idx2 + 1;
                if (curIdx > segEnd)
                    curIdx = segStart;

                float vecNextA = *(pArrayA + curIdx);
                float vecNextB = *(pArrayB + curIdx);

                triLerpVertices(this,
                                vecPrevA, vecPrevB,
                                vecCurA, vecCurB,
                                *(pArrayB + idx2), *(pArrayA + idx2),
                                vecNextA, vecNextB);
                count -= 3;

                vecPrevA = vecNextA;
                vecPrevB = vecNextB;
            }
            else
            {
                // Normal vertex: linear interpolation between previous and current
                lerpVertices(vecPrevA, vecPrevB, vecCurA, vecCurB);
                count--;

                vecPrevA = vecCurA;
                vecPrevB = vecCurB;
            }
        }
    }
}