// FUNC_NAME: TNLConnection::processReliablePackets
// Address: 0x00667910
// This function processes multiple reliable packet channels, handling acknowledgements and retransmissions.
// It manages a set of 8 channel buffers (pairs of count and pointer) and coordinates packet flow.

#include <cstdint>

struct ChannelBuffer {
    int32_t count;      // number of packets/items in this channel
    uint8_t* data;      // pointer to packet data or flag array
};

int TNLConnection::processReliablePackets(int* thisPtr) {
    int iVar1;
    int* piVar2;
    int* piVar3;
    bool bVar4;

    // Local channel buffers: [count, pointer] pairs (8 channels)
    ChannelBuffer ch[8]; // local_14,local_24,local_44,local_54,local_64,local_34,local_84,local_74

    // Check if connection is in invalid state
    if ((thisPtr[2] == 1) || (*thisPtr == 0)) {
        return -3;
    }

    // If we have pending data and the flag indicates it's ready, process a single channel via a helper
    if ((0 < *thisPtr) && ((*(uint8_t*)thisPtr[3] & 1) != 0)) {
        iVar1 = FUN_00664cf0(); // Possibly handle a single immediate packet
        return iVar1;
    }

    // Initialize all 8 channel buffers from some internal state
    iVar1 = initChannelBuffers(ch, 0); // FUN_00667820
    if (iVar1 == 0) {
        iVar1 = getNextPacket(); // FUN_00665ce0 - get packet from first channel?
        if ((iVar1 == 0) && (iVar1 = getNextPacket(), iVar1 == 0)) {
            // Check if some channels have data
            if ((ch[0].count < 1) ||
               (((*(ch[0].data) & 1) != 0 || (ch[1].count < 1) || ((*(ch[1].data) & 1) != 0)))) {
                // No immediate data in certain channels, proceed to main loop
                iVar1 = getNextPacket();
                if ((iVar1 == 0) && (iVar1 = getNextPacket(), iVar1 == 0)) {
                    popPacket(); // FUN_0066a550
                    popPacket();
                    do {
                        bVar4 = (ch[2].count == 0);
                        // Inner loop: process channels until we can move forward
                        while ((bVar4 || ch[2].count < 0 || ((*(ch[2].data) & 1) != 0))) {
                            while ((0 < ch[3].count && ((*(ch[3].data) & 1) == 0))) {
                                iVar1 = dequeuePacket(&ch[3]); // FUN_00666240
                                if (((iVar1 != 0) ||
                                    ((((0 < ch[6].count && ((*(ch[6].data) & 1) != 0)) ||
                                      ((0 < ch[7].count && ((*(ch[7].data) & 1) != 0)))) &&
                                     ((iVar1 = checkAck(&ch[6]), iVar1 != 0 ||
                                      (iVar1 = processPacketPair(&ch[7], &ch[0]), iVar1 != 0)))))) ||
                                   ((iVar1 = dequeuePacket(&ch[6]), iVar1 != 0 ||
                                    (iVar1 = dequeuePacket(&ch[7]), iVar1 != 0)))) goto exit_cleanup;
                            }
                            iVar1 = tryAdvanceChannel(); // FUN_00665bd0
                            if (iVar1 == -1) {
                                iVar1 = processPacketPair(&ch[3], &ch[2]); // combine channels
                                if ((iVar1 != 0) || (iVar1 = processPacketPair(&ch[6], &ch[4]), iVar1 != 0))
                                    goto exit_cleanup;
                                piVar3 = &ch[7];
                                piVar2 = &ch[5];
                            } else {
                                iVar1 = processPacketPair(&ch[2], &ch[3]);
                                if ((iVar1 != 0) || (iVar1 = processPacketPair(&ch[4], &ch[6]), iVar1 != 0))
                                    goto exit_cleanup;
                                piVar3 = &ch[5];
                                piVar2 = &ch[7];
                            }
                            iVar1 = processPacketPair(piVar3, piVar2);
                            if (iVar1 != 0) goto exit_cleanup;
                            bVar4 = (ch[2].count == 0);
                            if (bVar4) {
                                iVar1 = popAndCheck(); // FUN_00665c00
                                if (iVar1 != 0) goto combined_label;
                                iVar1 = popAndCheck();
                                goto inner_loop_continue;
                            }
                        }
                        iVar1 = dequeuePacket(&ch[2]);
                    } while ((iVar1 == 0) &&
                            (((((ch[4].count < 1 || ((*(ch[4].data) & 1) == 0)) &&
                               ((ch[5].count < 1 || ((*(ch[5].data) & 1) == 0)))) ||
                              ((iVar1 = checkAck(&ch[4]), iVar1 == 0 &&
                               (iVar1 = processPacketPair(&ch[5], &ch[0]), iVar1 == 0)))) &&
                             ((iVar1 = dequeuePacket(&ch[4]), iVar1 == 0 &&
                              (iVar1 = dequeuePacket(&ch[5]), iVar1 == 0))))));
                }
            } else {
combined_label:
                iVar1 = -3;
            }
        }
        goto exit_cleanup;
    }
    return iVar1;

inner_loop_continue:
    if (iVar1 != -1) goto post_inner_loop;
    iVar1 = checkAck(&ch[6]); // check acknowledgement for channel 6
    if (iVar1 != 0) goto exit_cleanup;
    iVar1 = popAndCheck();
    goto inner_loop_continue;

post_inner_loop:
    iVar1 = getNextReadyPacket(); // FUN_00665c30
    while (iVar1 != -1) {
        iVar1 = processPacketPair(&ch[6], thisPtr); // process packet against this connection
        if (iVar1 != 0) goto exit_cleanup;
        iVar1 = getNextReadyPacket();
    }
    finalizeProcessing(); // FUN_00666970
    iVar1 = 0;

exit_cleanup:
    releaseChannelBuffers(ch, 0); // FUN_00665b80 - cleanup
    return iVar1;
}