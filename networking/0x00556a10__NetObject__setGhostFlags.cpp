// FUNC_NAME: NetObject::setGhostFlags
// Address: 0x00556a10
// Sets ghost priority flags on a network object. The flags field is at offset +0x2c.
// param_2: input value, shifted right by 2 and ORed with 0xC0000000 (bits 31 and 30 set)
// param_3: pointer to ghost object data (offset +0x2c is the flags uint32)
// param_4: identifier (used for debug/event)
void __thiscall NetObject::setGhostFlags(NetObject* this, uint value, void* ghostObject, uint identifier)
{
    // Initialization call (possibly sets up ghost reference)
    // FUN_00556ab0(this, 0, 0, identifier); // exact signature unknown
    initGhostObject(this, 0, 0, identifier); // hypothetical name

    // Write flags to ghostObject+0x2c
    // Flags: top 2 bits set to 11 (0xC0000000), lower 30 bits from value shifted right by 2
    *(uint*)((uintptr_t)ghostObject + 0x2c) = (value >> 2) | 0xC0000000;

    // Mark object as dirty for update
    markObjectDirty(); // 0x0043b490

    // Send debug/event message with identifier
    sendDebugEvent(0x2001, identifier, 0); // 0x009f01f0
}