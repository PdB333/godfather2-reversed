// FUNC_NAME: VehicleParams::loadFromStream
void __thiscall VehicleParams::loadFromStream(void *this, void *stream)
{
    float *pfVar1;
    float fVar2;
    char isEnd;
    int tag;
    int nodePtr;
    float fVar6;

    // Initialize stream and set magic identifier
    initStream(stream);
    setStreamMagic(stream, 0x3907babb);

    // Loop through all nodes in the stream
    isEnd = streamIsEnd(stream);
    while (isEnd == '\0') {
        advanceStream(stream);
        tag = readNodeType(stream);
        switch(tag) {
        case 0:
            nodePtr = advanceStream(stream); // note: advanceStream returns int? actually it might be readNode
            *(float *)(this + 0x60) = *(float *)(nodePtr + 8) * DAT_00e445c8;
            break;
        case 1:
            nodePtr = advanceStream(stream);
            *(float *)(this + 0x80) = *(float *)(nodePtr + 8) * DAT_00e445c8;
            break;
        case 2:
            nodePtr = advanceStream(stream);
            *(float *)(this + 0x70) = *(float *)(nodePtr + 8) * DAT_00e445c8;
            break;
        case 3:
            nodePtr = advanceStream(stream);
            *(float *)(this + 100) = *(float *)(nodePtr + 8) * DAT_00e445c8;
            break;
        case 4:
            nodePtr = advanceStream(stream);
            *(float *)(this + 0x84) = *(float *)(nodePtr + 8) * DAT_00e445c8;
            break;
        case 5:
            nodePtr = advanceStream(stream);
            *(float *)(this + 0x74) = *(float *)(nodePtr + 8) * DAT_00e445c8;
            break;
        case 6:
            nodePtr = advanceStream(stream);
            *(float *)(this + 0x68) = *(float *)(nodePtr + 8) * DAT_00e445c8;
            break;
        case 7:
            nodePtr = advanceStream(stream);
            *(float *)(this + 0x88) = *(float *)(nodePtr + 8) * DAT_00e445c8;
            break;
        case 8:
            nodePtr = advanceStream(stream);
            *(float *)(this + 0x78) = *(float *)(nodePtr + 8) * DAT_00e445c8;
            break;
        case 9:
            nodePtr = advanceStream(stream);
            *(float *)(this + 0xa0) = *(float *)(nodePtr + 8) * DAT_00e445c8;
            break;
        case 10:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0xa4) = *(int *)(nodePtr + 8);
            break;
        case 0xb:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0xac) = *(int *)(nodePtr + 8);
            break;
        case 0xc:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0xb8) = *(int *)(nodePtr + 8);
            break;
        case 0xd:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0xa8) = *(int *)(nodePtr + 8);
            break;
        case 0xe:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0xb0) = *(int *)(nodePtr + 8);
            break;
        case 0xf:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0xe8) = *(int *)(nodePtr + 8);
            break;
        case 0x10:
            nodePtr = advanceStream(stream);
            *(float *)(this + 0xe4) = *(float *)(nodePtr + 8) * DAT_00e445c8;
            break;
        case 0x11:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0xcc) = *(int *)(nodePtr + 8);
            break;
        case 0x12:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0xbc) = *(int *)(nodePtr + 8);
            *(int *)(this + 0xc0) = *(int *)(nodePtr + 8);
            break;
        case 0x13:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0xc4) = *(int *)(nodePtr + 8);
            break;
        case 0x14:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0xe0) = *(int *)(nodePtr + 8);
            break;
        case 0x15:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0xec) = *(int *)(nodePtr + 8);
            break;
        case 0x16:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0xf0) = *(int *)(nodePtr + 8);
            break;
        case 0x17:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0xf4) = *(int *)(nodePtr + 8);
            break;
        case 0x18:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0xf8) = *(int *)(nodePtr + 8);
            break;
        case 0x19:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0x100) = *(int *)(nodePtr + 8);
            break;
        case 0x1a:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0x108) = *(int *)(nodePtr + 8);
            break;
        case 0x1b:
            nodePtr = advanceStream(stream);
            *(int *)(this + 0x10c) = *(int *)(nodePtr + 8);
            break;
        }
        advanceNode(stream);
        isEnd = streamIsEnd(stream);
    }

    // Copy four floats from offset 0x80-0x8c to offset 0x90-0x9c (likely a 'blended' parameter set)
    pfVar1 = (float *)(this + 0x90);
    *pfVar1 = *(float *)(this + 0x80);
    *(int *)(this + 0x94) = *(int *)(this + 0x84);
    *(int *)(this + 0x98) = *(int *)(this + 0x88);
    *(int *)(this + 0x9c) = *(int *)(this + 0x8c);

    // Interpolate values based on a speed range
    fVar6 = *(float *)(this + 0xac); // lowSpeed
    fVar2 = *(float *)(this + 0xb8); // highSpeed
    *(float *)(this + 0xb4) = fVar6;
    if (fVar2 < fVar6) {
        // If highSpeed < lowSpeed, use lowTorque directly
        *pfVar1 = *(float *)(this + 0x70);
        return;
    }
    // Normalized factor between lowSpeed and highSpeed, using reference value at +0xa4
    fVar6 = (fVar2 - fVar6) / (fVar2 - *(float *)(this + 0xa4));
    // Quadratic interpolation between lowTorque (0x70) and highTorque (0x60)
    *pfVar1 = *(float *)(this + 0x70) -
              (*(float *)(this + 0x70) - *(float *)(this + 0x60)) * fVar6 * fVar6;
    return;
}