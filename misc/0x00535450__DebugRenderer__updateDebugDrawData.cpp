// FUNC_NAME: DebugRenderer::updateDebugDrawData
void DebugRenderer::updateDebugDrawData(char enableDebugDraw, uint param2)
{
    // Global debug context pointers (likely renderer or debug manager)
    static DebugContextBase* g_debugContext1 = (DebugContextBase*)DAT_01219a80; // global debug context 1
    static DebugContextBase* g_debugContext2 = (DebugContextBase*)DAT_01219a84; // global debug context 2

    // Index into arrays of stride 0x30
    static int s_currentIndexA = DAT_01219b20;   // index for array A (size 0x30 per entry)
    static int s_currentIndexB = DAT_01219b21;   // index for array B (size 0x3c per entry)

    // Arrays of debug draw objects (pointers)
    DebugDrawObject* objA = (DebugDrawObject*)(DAT_01219cbc + s_currentIndexA * 0x30);
    DebugDrawObject* objB = (DebugDrawObject*)(DAT_01219cc0 + s_currentIndexA * 0x30);
    DebugDrawObject* objC = (DebugDrawObject*)(DAT_01219cb8 + s_currentIndexA * 0x30);
    DebugDrawObject* objD = (DebugDrawObject*)(DAT_01219cb4 + s_currentIndexA * 0x30);

    // Objects for the second index (stride 0x3c)
    DebugDrawObject* objE = (DebugDrawObject*)(DAT_01219d54 + s_currentIndexB * 0x3c);
    DebugDrawObject* objF = (DebugDrawObject*)(DAT_01219d58 + s_currentIndexB * 0x3c);

    if (objA != nullptr) {
        FUN_0060b020(g_debugContext1, objA); // likely begin rendering
    }
    if (objB != nullptr) {
        FUN_0060aea0(g_debugContext1, objB); // likely end or submit
    }
    if (objE != nullptr) {
        // Determine if we have a valid transform source
        int* transformPtr = nullptr;
        if ((enableDebugDraw == 0) || (*(int*)(DAT_012234c4 + 0x24) == 0)) {
            transformPtr = 0;
        } else {
            // Virtual call to get transformation data (vtbl offset 4)
            ITransformSource* src = *(ITransformSource**)(DAT_012234c4 + 0x24);
            transformPtr = (int*)src->GetTransform(in_EAX + 0x30); // in_EAX is the implicit this
        }

        if (objC != nullptr) {
            FUN_0060add0(g_debugContext1, objC, DAT_012054dc + 0x70); // draw with some constant color/offset
        }
        if (transformPtr != nullptr) {
            // Copy transform data (3 floats at +0x20, +0x24, +0x28) and extra param
            Vector3 vec;
            vec.x = *(float*)(transformPtr + 0x20);
            vec.y = *(float*)(transformPtr + 0x24);
            vec.z = *(float*)(transformPtr + 0x28);
            vec.w = param2; // fourth component (e.g., alpha or radius)

            FUN_0060add0(g_debugContext2, objE, &vec); // draw with transform
            FUN_0060add0(g_debugContext2, objF, &vec); // draw with transform (maybe text)

            // Draw final object with transform
            FUN_0060add0(g_debugContext1, objD, transformPtr);
            return;
        }

        // No transform: clear the draw data
        Vector3 zeroVec = {0,0,0,0};
        FUN_0060add0(g_debugContext1, objD, &zeroVec);

        uint clearData[4] = {0};
        zeroVec = {0,0,0,0};
        FUN_0060ab00(g_debugContext2, objE, &clearData, 4); // clear 4 bytes? or size of one entry
    }
}