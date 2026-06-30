// FUNC_NAME: PathManager::fillPathNodes
int __thiscall PathManager::fillPathNodes(int this, PathData* outData, int count, float* multipliers)
{
    float totalRange = *(float*)(this + 0x30) * DAT_00e2a848;
    float accumulated1 = 0.0f;
    int i = 0;
    float accumulated2 = 0.0f;

    outData->count = (char)count;
    outData->countMinusOne = (unsigned short)(unsigned char)((char)count - 1);

    if (count > 0) {
        char* nodePtr = (char*)(outData + 0xf);        // +0x0f: start of node array
        unsigned short* idPtr = (unsigned short*)(outData + 0x3c); // +0x3c: ID array (stride 0x10)

        do {
            // Zero padding bytes within the node structure
            nodePtr[0x4] = 0;
            nodePtr[0x5] = 0;

            if (i != 0) {
                *idPtr = (unsigned short)(i & 0xff);
                idPtr += 16; // stride 0x10 between IDs
            }

            nodePtr[0x0] = (i != 0) + 1;   // Type: 1 for first, 2 for rest

            float scale = *(float*)(this + 0x34);
            double dVal1 = (double)accumulated1;
            MathUtil::someFunc();                    // likely random/trig
            *(float*)(nodePtr - 0xf) = (float)dVal1 * multipliers[0] * scale; // node->speed1

            // Zero four more bytes at node+0x10? (based on pattern)
            nodePtr[0x10] = 0;
            nodePtr[0x11] = 0;
            nodePtr[0x12] = 0;
            nodePtr[0x13] = 0;

            double dVal2 = (double)accumulated2;
            MathUtil::otherFunc();
            accumulated2 = totalRange / (float)(count - 1) + accumulated2;
            *(float*)(nodePtr - 7) = (float)dVal2 * multipliers[2] * scale; // node->speed2
            accumulated1 = accumulated2;

            MathUtil::thirdFunc();
            i++;
            nodePtr += 0x20; // stride 32 bytes per node
        } while (i < count);
    }

    return 1;
}