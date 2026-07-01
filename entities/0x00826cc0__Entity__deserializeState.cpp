// FUNC_NAME: Entity::deserializeState
void __thiscall Entity::deserializeState(void* this, void* stream)
{
    // +0x54: quatX (float)
    // +0x58: quatY (float)
    // +0x5c: quatZ (float)
    // +0x60: quatW (float)
    // +0x64: blendFactor (float)
    // +0x68: field68 (float)
    // +0x6c: field6c (float)
    // +0x7c: someScalar (float)

    streamBeginRead(stream);
    streamSetEndian(stream, 0x4360b1f5);

    bool finished = streamIsFinished(stream);
    while (!finished) {
        if (finished) {
            return;
        }

        streamReadBlockHeader(stream); // reads block type/size prefix
        int opcode = streamReadOpcode(stream);
        void* data;

        switch (opcode) {
        case 0:
            data = streamReadData(stream);
            this->someScalar = *(float*)((char*)data + 8);
            break;
        case 1:
            data = streamReadData(stream);
            float val = *(float*)((char*)data + 8);
            this->field68 = val;
            this->field6c = val;
            break;
        case 2:
            data = streamReadData(stream);
            setFourValues(this,
                          *(float*)((char*)data + 8),      // new x
                          this->quatY,
                          this->quatZ,
                          this->quatW,
                          this->blendFactor);
            break;
        case 3:
            data = streamReadData(stream);
            setFourValues(this,
                          this->quatX,
                          *(float*)((char*)data + 8),      // new y
                          this->quatZ,
                          this->quatW,
                          this->blendFactor);
            break;
        case 4:
            data = streamReadData(stream);
            setFourValues(this,
                          this->quatX,
                          this->quatY,
                          *(float*)((char*)data + 8),      // new z
                          this->quatW,
                          this->blendFactor);
            break;
        case 5:
            data = streamReadData(stream);
            setFourValues(this,
                          this->quatX,
                          this->quatY,
                          this->quatZ,
                          *(float*)((char*)data + 8),      // new w
                          this->blendFactor);
            break;
        case 6:
            data = streamReadData(stream);
            setFourValues(this,
                          this->quatX,
                          this->quatY,
                          this->quatZ,
                          this->quatW,
                          *(float*)((char*)data + 8));     // new blendFactor
            break;
        }

        streamEndBlock(stream);
        finished = streamIsFinished(stream);
    }
}