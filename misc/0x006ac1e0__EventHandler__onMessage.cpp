// FUNC_NAME: EventHandler::onMessage
void __thiscall EventHandler::onMessage(int innerThis, int* pPacket)
{
    int* arrayBase = *reinterpret_cast<int**>(0x0112a554); // DAT_0112a554
    int outerThis = innerThis - 0x1c; // Outer object is at offset 0x1c in this inner class

    // Compare first field of packet against a known event type stored at +0x14 of inner class
    if (*pPacket == *reinterpret_cast<int*>(innerThis + 0x14)) {
        // Match: handle direct event (e.g., processed locally)
        reinterpret_cast<SomeOuterClass*>(outerThis)->processDirectEvent(); // FUN_006accf0
        freePacket(pPacket); // FUN_0046c6a0
        return;
    }

    // Second check: packet type matches a global event type (DAT_0120e93c)
    if (*pPacket == *reinterpret_cast<int*>(0x0120e93c)) {
        int index = reinterpret_cast<SomeOuterClass*>(outerThis)->getArrayIndex(); // FUN_006ac320
        // arrayBase + index * 0x30 + 0x10 (0x10 seems to be header or base offset)
        int* slot = reinterpret_cast<int*>(reinterpret_cast<int>(arrayBase) + index * 0x30 + 0x10);
        if (slot != nullptr) {
            // Store value from +0x1c of inner class into slot at offset 0x20
            slot[0x20 / 4] = *reinterpret_cast<int*>(innerThis + 0x1c);
        }
        releaseGlobalEvent(&DAT_0120e93c); // FUN_004086d0 (decrement refcount or similar)
    }

    // Free the packet in all cases
    freePacket(pPacket);
}