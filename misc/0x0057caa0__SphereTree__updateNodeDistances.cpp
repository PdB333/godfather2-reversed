// FUNC_NAME: SphereTree::updateNodeDistances
void __thiscall SphereTree::updateNodeDistances(float *nodeData, char isDoubleWide)
{
    float fVar1;
    float fVar2;
    int count;
    float *endPtr;
    float *ptr;
    float fVar5;
    float fVar6;

    fVar2 = DAT_00e44564; // +0x00: maxDistance (some global)
    fVar1 = DAT_00e2b1a4; // +0x00: minDistance (some global)
    if (isDoubleWide == '\0') {
        // Single-width nodes (8 floats each: pos xyz, radius, ???)
        endPtr = nodeData + count * 8;
        if (nodeData != endPtr) {
            do {
                fVar5 = nodeData[0] * nodeData[0] + nodeData[1] * nodeData[1] + nodeData[2] * nodeData[2];
                if (fVar1 <= fVar5) {
                    fVar5 = 0.0;
                }
                else {
                    fVar5 = SQRT(fVar1 - fVar5);
                }
                if (nodeData[3] != 0.0) {
                    fVar5 = fVar2 - fVar5;
                }
                nodeData[3] = fVar5;
                nodeData = nodeData + 8;
            } while (nodeData != endPtr);
        }
    }
    else {
        // Double-width nodes (16 floats each: two sets of pos xyz, radius, ???)
        endPtr = nodeData + count * 0x10;
        if (nodeData != endPtr) {
            ptr = nodeData + 5;
            do {
                fVar5 = nodeData[0] * nodeData[0] + ptr[-4] * ptr[-4] + ptr[-3] * ptr[-3];
                fVar6 = ptr[-1] * ptr[-1] + ptr[1] * ptr[1] + ptr[0] * ptr[0];
                if (fVar1 <= fVar5) {
                    fVar5 = 0.0;
                }
                else {
                    fVar5 = SQRT(fVar1 - fVar5);
                }
                if (fVar1 <= fVar6) {
                    fVar6 = 0.0;
                }
                else {
                    fVar6 = SQRT(fVar1 - fVar6);
                }
                if (ptr[-2] != 0.0) {
                    fVar5 = fVar2 - fVar5;
                }
                ptr[-2] = fVar5;
                if (ptr[2] != 0.0) {
                    fVar6 = fVar2 - fVar6;
                }
                ptr[2] = fVar6;
                nodeData = nodeData + 0x10;
                ptr = ptr + 0x10;
            } while (nodeData != endPtr);
            return;
        }
    }
    return;
}