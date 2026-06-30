// FUNC_NAME: NetConnection::buildPacket
void __thiscall NetConnection::buildPacket(int *this, int bitStream, int outPacket)
{
    undefined4 *node;
    undefined4 *prevNode;
    undefined4 *nextNode;
    undefined4 *node2;
    int iVar5;
    char cVar6;
    byte bVar7;
    int iVar8;
    byte *pbVar9;
    int iVar10;
    void *pvVar11;
    uint uVar12;
    undefined4 *local_14;
    undefined4 *local_10;
    int savedBitPos;
    int savedBitPos2;
    uint uStack_4;

    iVar5 = bitStream;
    // If debug flag is set, write a special marker
    if ((char)this[0x66] != '\0') {
        bitStream = -0xff24553; // Some constant marker
        FUN_0064b810(0x20, &bitStream);
    }

    iVar8 = this[0x75]; // First reliable packet list head
    local_14 = (undefined4 *)0x0;
    local_10 = (undefined4 *)0x0;
    prevNode = local_14;

    while (iVar8 != 0) {
        // Check if bitstream has enough space (capacity * 8 < current bit position)
        if (*(uint *)(iVar5 + 0x10) * 8 < *(uint *)(iVar5 + 0x18)) break;

        node = (undefined4 *)this[0x75];
        // If bitstream is nearly full, reallocate
        if (*(uint *)(iVar5 + 0x30) < *(uint *)(iVar5 + 0x18) + 1) {
            uVar12 = (*(uint *)(iVar5 + 0x30) + 8 >> 3) + 0x5dc;
            if (*(uint *)(iVar5 + 0x10) < uVar12) {
                if (*(char *)(iVar5 + 0x14) != '\0') {
                    *(uint *)(iVar5 + 0x10) = uVar12;
                    pvVar11 = _realloc(*(void **)(iVar5 + 0xc), uVar12);
                    *(void **)(iVar5 + 0xc) = pvVar11;
                    *(uint *)(iVar5 + 0x2c) = uVar12 * 8;
                    *(uint *)(iVar5 + 0x30) = uVar12 * 8;
                    goto LAB_0064e746;
                }
            }
            else {
                *(uint *)(iVar5 + 0x10) = uVar12;
            }
            *(undefined1 *)(iVar5 + 0x1c) = 1; // Overflow flag
        }
        else {
LAB_0064e746:
            // Write a 1 bit to mark the start of a packet
            pbVar9 = (byte *)(*(int *)(iVar5 + 0xc) + (*(uint *)(iVar5 + 0x18) >> 3));
            *pbVar9 = *pbVar9 | '\x01' << ((byte)*(uint *)(iVar5 + 0x18) & 7);
            *(int *)(iVar5 + 0x18) = *(int *)(iVar5 + 0x18) + 1;
        }

        bitStream = *(int *)(iVar5 + 0x18);
        if ((char)this[0x66] != '\0') {
            *(int *)(iVar5 + 0x18) = bitStream + 0x10; // Add debug padding
        }

        node2 = (undefined4 *)*node; // Get the packet data pointer
        savedBitPos = (**(code **)(*this + 0x50))(); // Get some class ID or type
        iVar8 = (**(code **)*node2)(); // Get packet type
        savedBitPos = *(int *)(iVar8 + 0x10 + savedBitPos * 4); // Lookup something
        FUN_0064b810((char)this[0x7d], &savedBitPos); // Write type info

        // Call virtual function to write packet data
        (**(code **)(*(int *)*node + 0xc))(this, iVar5);

        if ((char)this[0x66] != '\0') {
            iVar8 = *(int *)(iVar5 + 0x18);
            *(int *)(iVar5 + 0x18) = bitStream;
            savedBitPos = iVar8;
            FUN_0064b810(0x10, &savedBitPos); // Write debug padding
            *(int *)(iVar5 + 0x18) = iVar8;
        }

        // Check if we need to stop due to overflow or low space
        if ((*(char *)(iVar5 + 0x1c) != '\0') ||
           ((uint)(*(int *)(iVar5 + 0x30) - *(int *)(iVar5 + 0x18)) < 0x80)) {
            *(int *)(iVar5 + 0x18) = bitStream + -1;
            *(undefined1 *)(iVar5 + 0x1c) = 0;
            break;
        }

        // Move to next node in the list
        this[0x75] = node[2];
        node[2] = 0;
        local_14 = node;
        if (prevNode != (undefined4 *)0x0) {
            local_10[2] = node;
            local_14 = prevNode;
        }
        prevNode = local_14;
        local_10 = node;
        iVar8 = this[0x75];
    }

    // Write a 0 bit to mark end of reliable packets
    if ((*(int *)(iVar5 + 0x18) + 1U <= *(uint *)(iVar5 + 0x30)) ||
       (cVar6 = FUN_0064b7c0(), cVar6 != '\0')) {
        pbVar9 = (byte *)(*(int *)(iVar5 + 0xc) + (*(uint *)(iVar5 + 0x18) >> 3));
        *pbVar9 = *pbVar9 & ~('\x01' << ((byte)*(uint *)(iVar5 + 0x18) & 7));
        *(int *)(iVar5 + 0x18) = *(int *)(iVar5 + 0x18) + 1;
    }

    // Now process the second list (unreliable packets?) at offset 0x73
    iVar8 = this[0x73];
    bitStream = -2;
    uVar12 = uStack_4;
    while (node = prevNode, iVar8 != 0) {
        uStack_4 = *(uint *)(iVar5 + 0x18);
        if ((*(uint *)(iVar5 + 0x10) * 8 < uStack_4) ||
           (node2 = (undefined4 *)this[0x73], this[0x7b] + 0x7e < (int)node2[1])) break;

        if (*(uint *)(iVar5 + 0x30) < uStack_4 + 1) {
            uVar12 = (*(uint *)(iVar5 + 0x30) + 8 >> 3) + 0x5dc;
            if (*(uint *)(iVar5 + 0x10) < uVar12) {
                if (*(char *)(iVar5 + 0x14) != '\0') {
                    *(uint *)(iVar5 + 0x10) = uVar12;
                    pvVar11 = _realloc(*(void **)(iVar5 + 0xc), uVar12);
                    *(void **)(iVar5 + 0xc) = pvVar11;
                    *(uint *)(iVar5 + 0x2c) = uVar12 * 8;
                    *(uint *)(iVar5 + 0x30) = uVar12 * 8;
                    goto LAB_0064e909;
                }
            }
            else {
                *(uint *)(iVar5 + 0x10) = uVar12;
            }
            *(undefined1 *)(iVar5 + 0x1c) = 1;
        }
        else {
LAB_0064e909:
            pbVar9 = (byte *)((*(uint *)(iVar5 + 0x18) >> 3) + *(int *)(iVar5 + 0xc));
            *pbVar9 = *pbVar9 | '\x01' << ((byte)*(uint *)(iVar5 + 0x18) & 7);
            *(int *)(iVar5 + 0x18) = *(int *)(iVar5 + 0x18) + 1;
        }

        cVar6 = node2[1] == bitStream + 1;
        bitStream = CONCAT31(bitStream._1_3_, cVar6);

        if (*(uint *)(iVar5 + 0x30) < *(int *)(iVar5 + 0x18) + 1U) {
            uVar12 = (*(uint *)(iVar5 + 0x30) + 8 >> 3) + 0x5dc;
            if (*(uint *)(iVar5 + 0x10) < uVar12) {
                if (*(char *)(iVar5 + 0x14) != '\0') {
                    *(uint *)(iVar5 + 0x10) = uVar12;
                    pvVar11 = _realloc(*(void **)(iVar5 + 0xc), uVar12);
                    *(void **)(iVar5 + 0xc) = pvVar11;
                    *(uint *)(iVar5 + 0x2c) = uVar12 * 8;
                    *(uint *)(iVar5 + 0x30) = uVar12 * 8;
                    cVar6 = (char)bitStream;
                    goto LAB_0064e986;
                }
            }
            else {
                *(uint *)(iVar5 + 0x10) = uVar12;
            }
            *(undefined1 *)(iVar5 + 0x1c) = 1;
LAB_0064e9b0:
            bitStream = node2[1];
            FUN_0064b810(7, &bitStream);
        }
        else {
LAB_0064e986:
            pbVar9 = (byte *)(*(int *)(iVar5 + 0xc) + (*(uint *)(iVar5 + 0x18) >> 3));
            bVar7 = '\x01' << ((byte)*(uint *)(iVar5 + 0x18) & 7);
            if (cVar6 == '\0') {
                *pbVar9 = *pbVar9 & ~bVar7;
            }
            else {
                *pbVar9 = *pbVar9 | bVar7;
            }
            *(int *)(iVar5 + 0x18) = *(int *)(iVar5 + 0x18) + 1;
            if (cVar6 == '\0') goto LAB_0064e9b0;
        }

        bitStream = node2[1];
        if ((char)this[0x66] != '\0') {
            *(int *)(iVar5 + 0x18) = *(int *)(iVar5 + 0x18) + 0x10;
        }

        savedBitPos2 = *(int *)(iVar5 + 0x18);
        node2 = (undefined4 *)*node2;
        savedBitPos = (**(code **)(*this + 0x50))();
        iVar8 = (**(code **)*node2)();
        savedBitPos = *(int *)(iVar8 + 0x10 + savedBitPos * 4);
        FUN_0064b810((char)this[0x7d], &savedBitPos);
        (**(code **)(*(int *)*node2 + 0xc))(this, iVar5);

        iVar8 = *(int *)(iVar5 + 0x18);
        iVar10 = (*(code *)**(undefined4 **)*node2)();
        *(int *)(iVar10 + 0x68) = *(int *)(iVar10 + 0x68) + 1;
        *(int *)(iVar10 + 0x60) = *(int *)(iVar10 + 0x60) + (iVar8 - savedBitPos2);

        if ((char)this[0x66] != '\0') {
            iVar8 = *(int *)(iVar5 + 0x18);
            *(int *)(iVar5 + 0x18) = savedBitPos2 + -0x10;
            savedBitPos2 = iVar8;
            FUN_0064b810(0x10, &savedBitPos2);
            *(int *)(iVar5 + 0x18) = iVar8;
        }

        uVar12 = uStack_4;
        if ((uint)(*(int *)(iVar5 + 0x30) - *(int *)(iVar5 + 0x18)) < 0x80) {
            *(uint *)(iVar5 + 0x18) = uStack_4;
            *(undefined1 *)(iVar5 + 0x1c) = 0;
            break;
        }

        this[0x73] = node2[2];
        node2[2] = 0;
        local_14 = node2;
        if (prevNode != (undefined4 *)0x0) {
            local_10[2] = node2;
            local_14 = prevNode;
        }
        prevNode = local_14;
        local_10 = node2;
        iVar8 = this[0x73];
    }

    // Clean up: call destructor on each processed node
    for (; uStack_4 = uVar12, prevNode != (undefined4 *)0x0; prevNode = (undefined4 *)prevNode[2]) {
        (**(code **)(*(int *)*prevNode + 0x1c))(this);
        uVar12 = uStack_4;
    }

    // Store the list of remaining nodes in output
    *(undefined4 **)(outPacket + 0x14) = prevNode;

    // Write final 0 bit to mark end of packet
    if (*(int *)(iVar5 + 0x18) + 1U <= *(uint *)(iVar5 + 0x30)) {
LAB_0064eb2d:
        pbVar9 = (byte *)((*(uint *)(iVar5 + 0x18) >> 3) + *(int *)(iVar5 + 0xc));
        *pbVar9 = *pbVar9 & ~('\x01' << ((byte)*(uint *)(iVar5 + 0x18) & 7));
        *(int *)(iVar5 + 0x18) = *(int *)(iVar5 + 0x18) + 1;
        return;
    }

    uVar12 = (*(uint *)(iVar5 + 0x30) + 8 >> 3) + 0x5dc;
    if (*(uint *)(iVar5 + 0x10) < uVar12) {
        if (*(char *)(iVar5 + 0x14) != '\0') {
            *(uint *)(iVar5 + 0x10) = uVar12;
            pvVar11 = _realloc(*(void **)(iVar5 + 0xc), uVar12);
            *(void **)(iVar5 + 0xc) = pvVar11;
            *(uint *)(iVar5 + 0x2c) = uVar12 * 8;
            *(uint *)(iVar5 + 0x30) = uVar12 * 8;
            goto LAB_0064eb2d;
        }
    }
    else {
        *(uint *)(iVar5 + 0x10) = uVar12;
    }
    *(undefined1 *)(iVar5 + 0x1c) = 1;
    return;
}