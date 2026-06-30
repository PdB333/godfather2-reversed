// FUNC_NAME: TNLConnection::processReliableSendOrAck
uint __thiscall TNLConnection::processReliableSendOrAck(uint this)
{
    uint randomBits;
    uint uVar1;
    uint uVar2;
    uint uVar5;
    uint uVar6;
    uint sendSeq;
    uint recvSeq;
    uint local_8;
    uint ackMask;
    uint state;
    int iVar4;
    int iVar7;
    float fVar8;
    uint local_10;
    uint local_c;
    uint uStack_4[?]; // Actually stack based on loop

    // Extract random bit fields for packet type and sequence randomization
    randomBits = 0;
    getRandomBits(2, &randomBits);
    uVar2 = randomBits & 3; // 2-bit type field

    randomBits = 0;
    getRandomBits(5, &randomBits);
    uVar6 = randomBits & 0x1f; // 5-bit random sequence offset

    // Window advancement check
    if (*(uint *)(this + 0x2c) < *(uint *)(this + 0x18)) {
        *(byte *)(this + 0x1c) = 1; // Flag: packet pending
    } else {
        *(uint *)(this + 0x18) += 1; // Advance window
    }

    local_10 = 0;
    getRandomBits(6, &local_10); // 6 more bits for sequence number

    randomBits = 0;
    getRandomBits(10, &randomBits);
    uVar5 = randomBits & 0x3ff; // 10-bit receive sequence

    // Build send sequence from base at +0x90 and random offset
    sendSeq = *(uint *)(this + 0x90); // Base send sequence
    local_10 = uVar6 | ((local_10 & 0x3f) << 5) | (sendSeq & 0xFFFFF800);
    if (local_10 < sendSeq) {
        local_10 += 0x800; // Wrap around
    }

    // Check if within window (max 32 packets ahead)
    if (local_10 - sendSeq < 0x20) {
        recvSeq = *(uint *)(this + 0x94); // Base receive sequence
        uVar5 = uVar5 | (recvSeq & 0xFFFFFC00);
        if (uVar5 < recvSeq) {
            uVar5 += 0x400; // Wrap around
        }

        // Verify receive sequence within max sequence
        if (uVar5 <= *(uint *)(this + 0x98)) {
            if (*(int *)(this + 0x1b0) != 0) {
                // Build packet header with sequences and type
                buildPacketHeader(*(int *)(this + 0x1b0), local_10, uVar5, uVar2);
                sendSeq = sendPacket(this, *(undefined4 *)(this + 0x1b0));
                if ((char)sendSeq == '\0') {
                    goto LAB_0065374c;
                }
            }

            iVar7 = 0;
            state = getConnectionState(this);
            if ((state < 5) && (uVar2 < 3)) {
                // Process reliable acknowledges
                local_c = (state + 3) >> 2; // Number of ack blocks (4 packets per block)
                randomBits = 0;
                if (local_c != 0) {
                    do {
                        if (randomBits == local_c - 1) {
                            iVar4 = (state - iVar7) * 8; // Remaining bits
                        } else {
                            iVar4 = 0x20; // Full 32-bit block
                        }
                        uVar3 = allocateAckBlock(iVar4);
                        *(undefined4 *)((int)&uStack_4 + iVar7) = uVar3;
                        randomBits++;
                        iVar7 += 4;
                    } while (randomBits < local_c);
                }

                randomBits = 0;
                getRandomBits(8, &randomBits);
                local_8 = (randomBits & 0xff) * 8 + 4; // Random delay offset in bits? 

                uVar6 = local_10 - *(int *)(this + 0x90);
                if (0x20 < uVar6) {
                    // Skip ahead to first unacknowledged packet
                    iVar4 = (uVar6 - 0x21) >> 5;
                    do {
                        uVar6 -= 0x20;
                        iVar4--;
                    } while (iVar4 != 0);
                    *(uint *)(this + 0x9c) = 0; // Clear ack mask
                }
                // Update ack mask: shift left by gap bits and set lsb if type 0
                *(uint *)(this + 0x9c) = (*(int *)(this + 0x9c) << (uVar6 & 0x1f)) | (uint)(uVar2 == 0);

                // Iterate over received packets to process acks
                local_c = uVar5 - *(int *)(this + 0x94);
                uVar6 = 0;
                if (local_c != 0) {
                    do {
                        uVar1 = *(int *)(this + 0x94) + 1 + uVar6;
                        // Check if the packet sequence is acknowledged in the ack blocks
                        randomBits = CONCAT31(randomBits._1_3_,
                            ((&uStack_4)[(uVar5 - uVar1) >> 5] & (1 << ((uVar5 - uVar1) & 0x1f))) != 0);
                        *(uint *)(this + 0xac) = 0;
                        processAcknowledgedPacket(); // Updates +0xac based on ack
                        if (*(int *)(this + 0xac) != 0) {
                            // Update timeout value based on RTT and factor
                            fVar8 = (float)(int)((*(int *)(*(int *)(this + 0x1a4) + 100) -
                                *(int *)(this + 0xac)) - local_8) * DAT_00e2fc48 +
                                *(float *)(this + 0xc0) * DAT_0110a440;
                            *(float *)(this + 0xc0) = fVar8;
                            if (fVar8 < 0.0) {
                                *(uint *)(this + 0xc0) = 0;
                            }
                        }
                        if ((char)randomBits != '\0') {
                            // Copy acknowledged packet data from the send window
                            *(uint *)(this + 0xa0) = *(uint *)(this + 0x10 + (uVar1 & 0x1f) * 4);
                        }
                        uVar6++;
                    } while (uVar6 < local_c);
                }

                // Update next sendable sequence
                if (0x20 < local_10 - *(int *)(this + 0xa0)) {
                    *(uint *)(this + 0xa0) = local_10 - 0x20;
                }

                *(uint *)(this + 0x94) = uVar5; // Update receive sequence
                uVar6 = *(uint *)(this + 0x90);
                *(uint *)(this + 0x118) = 0;
                *(uint *)(this + 0x114) = 0;
                *(uint *)(this + 0x90) = local_10; // Update send sequence

                if ((uVar2 == 1) || (0x10 < local_10 - *(int *)(this + 0xa0))) {
                    flushSendBuffer(); // Trigger send if needed
                }

                if ((uVar6 != local_10) && (uVar2 == 0)) {
                    return 1; // Indicate packet sent
                }
                return 0;
            }
        }
    }

LAB_0065374c:
    return sendSeq & 0xFFFFFF00; // Error code from send
}