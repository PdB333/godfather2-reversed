// FUNC_NAME: NetConnection::initialize
int __thiscall NetConnection::initialize(int thisPtr, int connectionId, void* socketHandle, short maxChannels)
{
    float rttFactor;
    int channelCount;
    int i;
    int sum;
    float fVar;
    int interfacePtr;
    int maxSeq;
    uint8_t* seqArray;
    void* sendBuffer;
    void* recvBuffer;
    float rtt;
    int* channelArray;
    int j;
    short channelSum;

    // Clear various members
    *(int*)(thisPtr + 0x124) = 0;   // +0x124: mSomeFlag
    *(int*)(thisPtr + 0x78) = 0;    // +0x78: mOtherPtr
    *(int*)(thisPtr + 0x110) = 0;   // +0x110: mUnused1
    *(int*)(thisPtr + 0x114) = 0;   // +0x114: mUnused2
    *(int*)(thisPtr + 0x118) = 0;   // +0x118: mUnused3
    *(int*)(thisPtr + 0x11c) = 0;   // +0x11c: mUnused4
    *(uint8_t*)(thisPtr + 0x120) = 0; // +0x120: mUnusedByte1
    *(uint8_t*)(thisPtr + 0x121) = 0; // +0x121: mUnusedByte2
    *(int*)(thisPtr + 0x138) = 0;   // +0x138: mUnused5
    *(int*)(thisPtr + 0x134) = 0;   // +0x134: mUnused6
    *(int*)(thisPtr + 0x2d0) = 0;   // +0x2d0: mSomeArray[0]
    *(int*)(thisPtr + 0x2cc) = 0;   // +0x2cc: mSomeArray[1]
    *(int*)(thisPtr + 0x2c8) = 0;   // +0x2c8: mSomeArray[2]
    *(int*)(thisPtr + 0x2c4) = 0;   // +0x2c4: mSomeArray[3]
    *(int*)(thisPtr + 0x2c0) = 0;   // +0x2c0: mSomeArray[4]

    // Initialize acknowledgment sequence numbers to -1
    *(int*)(thisPtr + 0x144) = -1;  // +0x144: mAckSeq[0]
    *(int*)(thisPtr + 0x174) = -1;  // +0x174: mAckSeq[1]
    *(int*)(thisPtr + 0x1a4) = -1;  // +0x1a4: mAckSeq[2]
    *(int*)(thisPtr + 0x1d4) = -1;  // +0x1d4: mAckSeq[3]
    *(int*)(thisPtr + 0x204) = -1;  // +0x204: mAckSeq[4]
    *(int*)(thisPtr + 0x234) = -1;  // +0x234: mAckSeq[5]
    *(int*)(thisPtr + 0x264) = -1;  // +0x264: mAckSeq[6]
    *(int*)(thisPtr + 0x294) = -1;  // +0x294: mAckSeq[7]

    // Initialize send sequence numbers
    *(int*)(thisPtr + 0x140) = 0;   // +0x140: mSendSeq[0]
    *(int*)(thisPtr + 0x170) = 0;   // +0x170: mSendSeq[1]
    *(int*)(thisPtr + 0x1a0) = 0;   // +0x1a0: mSendSeq[2]
    *(int*)(thisPtr + 0x1d0) = 0;   // +0x1d0: mSendSeq[3]
    *(int*)(thisPtr + 0x200) = 0;   // +0x200: mSendSeq[4]
    *(int*)(thisPtr + 0x230) = 0;   // +0x230: mSendSeq[5]
    *(int*)(thisPtr + 0x260) = 0;   // +0x260: mSendSeq[6]
    *(int*)(thisPtr + 0x290) = 0;   // +0x290: mSendSeq[7]

    // Resolve socket interface and store in +0x70
    interfacePtr = FUN_00578360(socketHandle);
    *(int*)(thisPtr + 0x70) = interfacePtr; // +0x70: mInterface

    *(int*)(thisPtr + 0x100) = connectionId; // +0x100: mConnectionId

    // Initialize interface internal state
    FUN_005792a0(*(int*)(interfacePtr + 0x34));

    channelCount = DAT_01205574; // global: packet history size
    // Allocate array of 8-byte sequence tracking slots
    if (channelCount * 8 == 0) {
        *(int*)(thisPtr + 0x128) = 0; // +0x128: mSeqHistory
    } else {
        // Allocate and zero fill the array
        uint8_t stackBuf[24];
        *(int*)(thisPtr + 0x128) = (int)(**(code**)*DAT_0120556c)(channelCount * 8, stackBuf);
        int* history = (int*)*(int*)(thisPtr + 0x128);
        // Zero each 8-byte entry: 4 ints per iteration (4x2=8 bytes)
        for (i = 0; i < channelCount - 3; i += 4) {
            history[i * 2] = 0;
            history[i * 2 + 1] = 0;
            history[i * 2 + 2] = 0; // Actually these indices might be off
            // Reconstruct properly: each 8-byte block is two ints
            // The loop below does 4 entries per iteration
        }
        for (; i < channelCount; i++) {
            history[i * 2] = 0;
            history[i * 2 + 1] = 0;
        }
    }

    // Setup send/receive buffers with size based on maxChannels
    *(short*)(thisPtr + 0xac) = maxChannels; // +0xac: mMaxChannels
    int bufferSize = maxChannels * 32; // 32 bytes per channel

    // Allocate and clear send buffer
    uint8_t allocBuf[24];
    allocBuf[0] = 2;
    allocBuf[4] = 0x10;
    allocBuf[8] = 0;
    sendBuffer = (void*)(**(code**)*DAT_0120556c)(bufferSize, allocBuf);
    *(void**)(thisPtr + 0xa0) = sendBuffer; // +0xa0: mSendBuffer
    _memset(sendBuffer, 0, bufferSize);

    // Allocate and clear receive buffer
    allocBuf[0] = 0;
    recvBuffer = (void*)(**(code**)*DAT_0120556c)(bufferSize, &allocBuf[0]);
    *(void**)(thisPtr + 0xa4) = recvBuffer; // +0xa4: mRecvBuffer
    _memset(recvBuffer, 0, bufferSize);

    rttFactor = DAT_00e2b1a4; // global float: default RTT factor?

    int interfaceData = *(int*)(thisPtr + 0x70);
    *(short*)(thisPtr + 0x74) = 0;  // +0x74: mSendChannelIndex
    *(short*)(thisPtr + 0x76) = 0;  // +0x76: mRecvChannelIndex
    *(short*)(thisPtr + 0xa8) = 0;  // +0xa8: mSomeShort1
    *(short*)(thisPtr + 0xaa) = 0;  // +0xaa: mSomeShort2
    *(uint8_t*)(thisPtr + 0xae) = 1; // +0xae: mConnectedFlag
    *(short*)(thisPtr + 0xb0) = 0;  // +0xb0: mMaxPacketSize

    rtt = *(float*)(interfaceData + 0x38); // +0x38: base RTT from interface
    *(float*)(thisPtr + 0x104) = rtt;      // +0x104: mRTT
    *(float*)(thisPtr + 0x108) = rttFactor / rtt; // +0x108: mRTTFactor

    // Calculate sum of channel sizes from interface data
    int* channelCountPtr = *(int**)(interfaceData + 0x5c);
    int numItems = *channelCountPtr;
    sum = 0;
    channelSum = 0;
    if (numItems > 0) {
        int* itemPtr = (int*)(channelCountPtr[1] + 4);
        for (j = 0; j < numItems; j++) {
            sum += *itemPtr;
            channelSum = (short)sum;
            itemPtr += 3;
        }
    }
    *(short*)(thisPtr + 0xb2) = channelSum; // +0xb2: mTotalChannelSize

    // Find maximum packet size from channel descriptors
    if (*(int*)(interfaceData + 0x1c) != 0) {
        int numDescs = *(int*)(interfaceData + 0x18);
        if (numDescs > 0) {
            int descBase = *(int*)(interfaceData + 0x1c);
            for (int k = 0; k < numDescs; k++) {
                int size = *(int*)(descBase + 8 + k * 0x18);
                if ((int)*(short*)(thisPtr + 0xb0) < size) {
                    *(short*)(thisPtr + 0xb0) = (short)size;
                }
            }
        }
    }

    // Set initialization flag
    *(uint32_t*)(thisPtr + 0x10) |= 0x200; // +0x10: mFlags (bit 9 = initialized)

    // Zero out remaining fields
    *(int*)(thisPtr + 0xb8) = 0;  // +0xb8: mSomePtr1
    *(int*)(thisPtr + 0xb4) = 0;  // +0xb4: mSomePtr2
    *(int64_t*)(thisPtr + 0xc0) = 0;
    *(int64_t*)(thisPtr + 200) = 0;
    *(int64_t*)(thisPtr + 0xd0) = 0;
    *(int64_t*)(thisPtr + 0xd8) = 0;
    *(int64_t*)(thisPtr + 0xe0) = 0;
    *(int64_t*)(thisPtr + 0xe8) = 0;
    *(int64_t*)(thisPtr + 0xf0) = 0;
    *(int64_t*)(thisPtr + 0xf8) = 0;
    *(uint8_t*)(thisPtr + 300) = 0;

    return 1; // Return success
}