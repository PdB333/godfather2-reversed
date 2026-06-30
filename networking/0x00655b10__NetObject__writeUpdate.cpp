// FUNC_NAME: NetObject::writeUpdate
void __thiscall NetObject::writeUpdate(int this, BitStream* stream, char forceUpdate, char includeOwner) {
    int* refCountPtr;
    int* someObject;
    char headerByte;
    uint flags;
    uint someValue; // actually uVar5 (used as bool later)
    undefined4 packResult;
    char localBuf[1024]; // 0x400 bytes
    undefined4 local_50c; // unused? Actually initialized but not used
    undefined4 local_508; // unused
    // ... other local variables

    // Initialize local bitstream buffer? Or just local variables
    localBuf[0] = 1; // Write a header byte indicating something
    // Write 8 bits (value 1) into the stream? But stream is a parameter, not localBuf.
    // Actually FUN_0064b810 might write into a global bitstream context, not the local buffer.
    // The code writes to the stream (second parameter) using FUN_0064b810.
    // The localBuf is later used as a temporary buffer for copying to mWriteBuffer.
    // Reinterpret:

    // Write a header byte indicating update type
    headerByte = 1;
    BitStream::writeBits(stream, 8, &headerByte); // FUN_0064b810(8, &local_541)

    // Write some data from the object (maybe a mask)
    // in_EAX is the value returned by the previous call? Or the value of EAX before? Unknown.
    // Probably the previous writeBits returns a value that is used as an argument to serialize.
    // We'll assume that the previous call returns a boolean or size.
    uint serializedSize = BitStream::writeBits(stream, 0x40, &someValue); // in_EAX is likely the return of the previous call but not correct
    // Actually the code: FUN_0064b810(0x40, in_EAX); where in_EAX is not defined. We'll assume it's a pointer.
    // More likely, these calls are part of a state serialization routine.

    // Serialize object state
    uint stateResult = FUN_00655000(this, stream, someValue); // returns something
    BitStream::writeBits(stream, 0x20, &stateResult);

    // Write net ID (64-bit) from offsets +0x44 and +0x48
    uint netIdLow = *(uint*)(this + 0x44);
    uint netIdHigh = *(uint*)(this + 0x48);
    BitStream::writeBits(stream, 0x40, &netIdLow); // writes 64 bits? Actually writes two 32-bit values? But passing &netIdLow writes only 32? Probably the function writes from the pointer given a size in bits, so 0x40 bits = 8 bytes, so it reads 8 bytes from &netIdLow which would include netIdHigh as well if netIdLow is at lower address. The order matches: local_540 = low, local_53c = high, then call with &local_540. So it writes 64 bits (low then high).
    // Write object type ID
    uint objectTypeId = *(uint*)(this + 0x38);
    flags = BitStream::writeBits(stream, 0x20, &objectTypeId); // returns something (maybe bit count or status)

    // Determine update flags
    if ((*(char*)(this + 0x68) == '\0') && ((forceUpdate == '\0') || (*(int*)(this + 0x30) == 0))) {
        flags = flags & 0xffffff00; // clear lower byte
    } else {
        flags = 1;
    }
    char hasOwner = FUN_0064bb50(flags); // Probably checks if flags indicate owner presence
    if (hasOwner != '\0') {
        // Determine if we need to include owner reference
        if ((includeOwner == '\0') || (*(int*)(this + 0x34) == 0)) {
            someValue = 0; // no owner
        } else {
            someValue = 1; // owner present
        }
        char ownerCheck = FUN_0064bb50(someValue);
        if (ownerCheck == '\0') {
            // Owner not present in this context? Actually the condition: if ownerCheck false, we do the refcount dance.
            // Get pointer to owner object's data
            int* ownerData = *(int**)(*(int*)(this + 0x30) + 0x18);
            if (ownerData != (int*)0x0) {
                ownerData[2] = ownerData[2] + 1; // increment refcount at offset +8
            }
            // Call some function on the owner (maybe to add reference)
            FUN_0064bbb0(ownerData);
            if (ownerData != (int*)0x0) {
                int* refCountField = ownerData + 2;
                *refCountField = *refCountField - 1;
                if (*refCountField == 0) {
                    (**(code**)(*ownerData + 8))(); // call destructor via vtable
                }
            }
        } else {
            // Owner present, just call function on the object at +0x34
            FUN_0064bbb0(*(undefined4*)(this + 0x34));
        }
    }

    // Copy the packed data to the object's send buffer (offset +0x5c)
    uint dataSize = (someLocalVar + 7) >> 3; // someLocalVar is from local_520 which was 20? Actually local_520 was set to 0, but then used in size calculation. Likely it's the number of bits written? We'll assume it's the total bit count from the serialization.
    // Actually local_520 is set to 0 earlier, and then used: local_520 + 7U >> 3. So local_520 is 0, so size = 0? That doesn't make sense. Probably the decompiler missed an assignment. We'll ignore and use a placeholder.
    FUN_00658230(this + 0x5c, localBuf, dataSize, 0); // Copies localBuf to mWriteBuffer

    // Finalize the stream (flush)
    FUN_0064b440(); // Possibly stream->flush()
}