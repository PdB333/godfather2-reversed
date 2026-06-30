// FUNC_NAME: TNLConnection::computeLatencyFromAckBitfield
// Address: 0x0057ece0
// This function processes the acknowledgment bitfield for a packet window
// and calculates smoothed RTT (round-trip time) values for the connection.
// It uses per-connection latency statistics stored in a separate structure.

int __thiscall TNLConnection::computeLatencyFromAckBitfield(int thisPtr) {
    int *thisObj = (int *)thisPtr;
    int *ackBitfield = *(int **)(thisObj[3]);        // +0x0C: pointer to bitfield array (packet ack bits)
    int packetCount = thisObj[5];                     // +0x14: number of packets in window
    int *latencyStats = (int *)thisObj[2];            // +0x08: pointer to latency statistics structure
    int someValue = thisObj[4];                       // +0x10: some parameter (e.g., a threshold or count)

    float10 tempFloat; // used for accumulation

    // Check if the first bit in the ack bitfield is set for the given packet index?
    // The code seems to check only one specific bit (the one at index iVar2? but it's the full check)
    // Actually the if condition checks if the bit for iVar2 (which is packetCount) is set in ackBitfield.
    // But note: iVar2 is used as the index into the bitfield; the check is for that one bit.
    // This is the main condition that determines if we process the latency or just clear output.
    if ((*(uint *)((int)ackBitfield + (packetCount >> 5) * 4) & (1 << (packetCount & 0x1f))) != 0) {
        // Latency calculation path

        int *latencyPtr = (int *)thisObj[4]; // Wait, this seems wrong. Actually iVar5 = thisObj[2] already assigned.
        // Re-read: iVar5 = thisObj[2]; iVar4 = thisObj[4]; 
        // Already set above.

        int *latencyInfo = (int *)latencyStats; // alias for clarity
        int *outputArray = *(int **)thisObj;     // +0x00: pointer to output buffer (8 ints)

        // Choose two values depending on a counter at latencyInfo[1] (offset +4) being < 10
        int sampleA, sampleB;
        if ((*(uint *)(latencyInfo + 1) & 0xff) < 10) {
            sampleA = *(int *)((int)latencyInfo + 0x24);  // +0x24
            sampleB = *(int *)((int)latencyInfo + 0x20);  // +0x20
        } else {
            sampleA = *(int *)((int)latencyInfo + 0x2c);  // +0x2c
            sampleB = *(int *)((int)latencyInfo + 0x28);  // +0x28
        }

        // local_c is a struct (probably 3 ints) used as a temporary for accumulation
        int local_c[3];
        local_c[0] = sampleA;
        local_c[1] = 0;
        local_c[2] = 0x00e2b1a4; // global constant (maybe a baseline latency)

        // The loop: for each packet index i from 0 to packetCount-1, if the bit is set, add 7 or 10 samples
        int i = 0;
        int sampleCount = 0; // not explicitly in code, but used for conditional
        if (sampleB < 0) {
            // sampleB negative: add 7 samples for each acknowledged packet
            if (packetCount > 0) {
                do {
                    if ((*(uint *)((int)ackBitfield + (i >> 5) * 4) & (1 << (i & 0x1f))) != 0) {
                        // Add 7 samples via helper function
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                    }
                    i++;
                } while (i < packetCount);
            }
        } else {
            // sampleB non-negative: add 10 samples for each acknowledged packet
            if (packetCount > 0) {
                do {
                    if ((*(uint *)((int)ackBitfield + (i >> 5) * 4) & (1 << (i & 0x1f))) != 0) {
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                        FUN_0057d3a0(local_c);
                    }
                    i++;
                } while (i < packetCount);
            }
        }

        // Now compute smoothed values using the accumulated local_c
        float currentLatency = (float)someValue;
        currentLatency = FUN_0057dc70(local_c, currentLatency);
        outputArray[0] = 0;
        currentLatency = FUN_0057dc70(local_c, currentLatency);
        outputArray[1] = 0;
        currentLatency = FUN_0057dc70(local_c, currentLatency);
        outputArray[2] = 0;
        currentLatency = FUN_0057dc70(local_c, currentLatency);
        outputArray[3] = 0;
        currentLatency = FUN_0057dc70(local_c, currentLatency);
        outputArray[4] = 0;
        currentLatency = FUN_0057dc70(local_c, currentLatency);
        outputArray[5] = 0;
        FUN_0057dc70(local_c, currentLatency);
        outputArray[7] = 0x00e2b1a4;
        outputArray[6] = 0;

        return 1;
    } else {
        // Bit not set: clear output array with zeros and set default value
        int *outputArray = *(int **)thisObj;
        outputArray[2] = 0;
        outputArray[1] = 0;
        outputArray[0] = 0;
        outputArray[3] = 0x00e2b1a4;
        outputArray[6] = 0;
        outputArray[5] = 0;
        outputArray[4] = 0;
        outputArray[7] = 0x00e2b1a4;
        return 1;
    }
}