// FUNC_NAME: MemoryPool::getElement
unsigned char __thiscall MemoryPool::getElement(unsigned int index, unsigned int* outData)
{
    unsigned char bVar1;
    int iVar2;
    unsigned int uVar3;
    unsigned int uVar4;
    unsigned int uVar5;
    unsigned char uVar6;
    int esi;

    // +0x1c: poolCount (number of allocated elements)
    bVar1 = *(unsigned char*)(esi + 0x1c);
    uVar6 = 0;
    
    // Mask and bounds check: the index is XORed with 0xad103100 (maybe a hash or obfuscation)
    // Only proceed if the index is within range and the pool has elements
    if ((((index ^ 0xad103100) < (unsigned int)bVar1) && (bVar1 != 0)) &&
        ((unsigned char)index < bVar1) &&
        // +0x4: elementPointer array (4 bytes each)
        (iVar2 = *(int*)(esi + 4 + (index & 0xff) * 4), iVar2 != 0)) {
        // Copy 16 bytes of data from element at offsets +0x50 to +0x5c into outData
        // +0x50: data field 0
        // +0x54: data field 1
        // +0x58: data field 2
        // +0x5c: data field 3
        uVar3 = *(unsigned int*)(iVar2 + 0x54);
        uVar4 = *(unsigned int*)(iVar2 + 0x58);
        uVar5 = *(unsigned int*)(iVar2 + 0x5c);
        *outData = *(unsigned int*)(iVar2 + 0x50);
        outData[1] = uVar3;
        outData[2] = uVar4;
        outData[3] = uVar5;
        uVar6 = 1;
    }
    return uVar6;
}