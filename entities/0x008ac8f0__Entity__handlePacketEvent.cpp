// FUNC_NAME: Entity::handlePacketEvent
void __thiscall Entity::handlePacketEvent(int *this, int *packetData)
{
    char isDebug;
    short someValue;

    // Check global debug/cheat flag
    isDebug = isDebugMode();
    if (isDebug != '\0') {
        // Override packet field at +0x18 with global value
        packetData[0x18 / 4] = g_someGlobalValue; // DAT_01205210
    }

    // Check if state at this[0x36] (offset 0xD8) is 2, or if packet's ID (offset 0x8) doesn't match expected ID at this[0x42] (offset 0x108)
    if ((this[0x36] == 2) || (packetData[0x8 / 4] != this[0x42])) {
        // Release or cleanup the packet
        releasePacket(packetData);

        // If state is less than 4, dispatch the packet data to a global handler
        if (this[0x36] < 4) {
            dispatchPacketEvent(
                &g_packetHandler,          // PTR_LAB_00e35c24
                packetData[0x4 / 4],       // field +0x04
                packetData[0x8 / 4],       // field +0x08
                packetData[0xC / 4],       // field +0x0C
                packetData[0x10 / 4],      // field +0x10
                packetData[0x14 / 4],      // field +0x14
                packetData[0x18 / 4],      // field +0x18
                packetData[0x1C / 4]       // field +0x1C
            );
        }

        // Decrement reference count or release object at packet+0x10
        releaseObject(packetData[0x10 / 4]);

        // Re-check debug flag
        isDebug = isDebugMode();
        if ((isDebug != '\0') && (packetData[0x8 / 4] == this[0x42])) {
            // Call virtual function at vtable+0xE4 (likely getInt) on the object at packet+0x10
            someValue = (*(short (__thiscall **)(int))(*(int *)this + 0xE4))(packetData[0x10 / 4]);

            // Check if this[0x25] (offset 0x94) is zero, or if someValue is less than that threshold
            if ((this[0x25] == 0) || ((int)someValue < this[0x25])) {
                // Check bit 5 of this[0x1F] (offset 0x7C)
                if (((uint)this[0x1F] >> 5 & 1) == 0) {
                    return;
                }
                // Call virtual function at vtable+0xD4 (likely isReady)
                isDebug = (*(char (__thiscall **)(void))(*(int *)this + 0xD4))();
                if (isDebug != '\0') {
                    return;
                }
            }
            // Call virtual function at vtable+0xB4 (likely execute)
            (*(void (__thiscall **)(void))(*(int *)this + 0xB4))();
        }
    }
    return;
}