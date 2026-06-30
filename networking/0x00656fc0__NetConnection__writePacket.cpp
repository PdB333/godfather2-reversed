// FUNC_NAME: NetConnection::writePacket
void __thiscall NetConnection::writePacket(void *this, void *packetData)
{
    int *ghostManager; // from this+0x154
    int *ghostPtr;
    undefined4 *listNode;
    undefined4 *tempNode;
    char flagByte;
    uint bitOffset;
    uint uVar7;
    int *unaff_EDI;
    int packetDataPtr;
    undefined1 local_7b9;
    uint local_7b8;
    uint local_7b4;
    undefined **vtableFunc; // pointer to vtable function
    undefined4 bitStreamWriteSize;
    undefined4 bitStreamWriteSize2;
    undefined1 *bitStreamBuf; // pointer to local buffer
    undefined4 bitStreamMaxSize;
    uint local_79c;
    int local_798; // bit offset counter
    undefined1 local_794;
    undefined1 local_793;
    undefined4 local_784;
    undefined4 local_780;
    undefined4 local_77c;
    undefined1 local_778;
    undefined1 auStack_67c [4];
    undefined1 local_678 [1020]; // local bitstream buffer (0x3FC bytes)
    undefined1 auStack_27c [4];
    undefined4 *puStack_278;

    bitStreamBuf = local_678;
    bitStreamWriteSize = 0;
    bitStreamWriteSize2 = 0;
    bitStreamMaxSize = 0x400; // max 1024 bytes
    local_79c = local_79c & 0xffffff00;
    local_784 = 0x2000; // 8192 bits?
    local_780 = 0x2000;
    local_798 = 0; // bit offset = 0
    local_794 = 0;
    local_793 = 0;
    local_778 = 0;
    local_77c = 0;
    vtableFunc = &PTR_LAB_00e42f38; // static function table?
    local_7b9 = 7; // some flag?
    writeBits(8, &local_7b9); // write 8 bits (byte)
    writeBits(0x40, (int)this + 0x133); // write 0x40 bits (8 bytes) from this+0x133
    bitOffset = (local_798 + 7U) >> 3; // byte align
    local_798 = bitOffset * 8; // align to byte boundary
    uVar7 = 0;
    writeBits(0x40, (int)this + 0x13b); // write 8 bytes from this+0x13b
    flagByte = checkFlag(*(undefined1 *)((int)this + 0x131)); // check a flag byte
    if (flagByte != '\0') {
        // Ghost manager pointer at this+0x55*4 = this+0x154
        ghostManager = *(int **)(*(int *)((int)this + 0x154) + 0x18);
        if (ghostManager != (int *)0x0) {
            ghostManager[2] = ghostManager[2] + 1; // increment reference count
        }
        local_7b8 = ghostManager[4]; // some size field?
        if (local_7b8 < 0x400) {
            local_7b4 = local_7b8;
            writeBits(10, &local_7b4); // write 10 bits (size)
            writeBits(local_7b8 * 8, ghostManager[3]); // write the data
        }
        ghostPtr = ghostManager + 2;
        *ghostPtr = *ghostPtr - 1; // decrement reference count
        if (*ghostPtr == 0) {
            (**(code **)(*ghostManager + 8))(); // release ghost manager
        }
        uVar7 = (local_798 + 7U) >> 3; // byte align
        local_798 = uVar7 * 8;
        writeBits(0x80, (int)this + 0x162); // write 0x80 bits (16 bytes) from this+0x162
    }
    checkFlag((char)*(int *)((int)this + 0x198)); // this+0x66*4
    local_7b8 = *(int *)((int)this + 0xA4); // this+0x29*4 = seq number?
    writeBits(0x20, &local_7b8); // write 32 bits
    (**(code **)(*(int *)this + 0x20))(&vtableFunc); // virtual call at vtable+0x20 (offset 8)
    if (uVar7 != 0) {
        initList(auStack_27c);
        addToList(uVar7, auStack_27c);
        for (tempNode = puStack_278; tempNode != (undefined4 *)0x0; ) {
            listNode = (undefined4 *)tempNode[2];
            *tempNode = 0;
            tempNode[1] = 0;
            tempNode[2] = 0;
            tempNode = listNode;
        }
    }
    initList(auStack_27c);
    addToList(bitOffset, auStack_27c);
    *(int *)((int)this + 0x19C) = *(int *)((int)this + 0x19C) + 1; // increment counter at this+0x67*4
    *(int *)((int)this + 0x1A0) = *(int *)(packetData + 100); // copy from packetData+100 to this+0x68*4
    copyData(packetData + 0x5c, auStack_67c, (local_79c + 7) >> 3, 0);
    while (puStack_278 != (undefined4 *)0x0) {
        tempNode = (undefined4 *)puStack_278[2];
        *puStack_278 = 0;
        puStack_278[1] = 0;
        puStack_278[2] = 0;
        puStack_278 = tempNode;
    }
    finalizeBitStream();
    return;
}