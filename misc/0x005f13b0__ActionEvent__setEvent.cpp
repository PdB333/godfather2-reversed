// FUNC_NAME: ActionEvent::setEvent
void __fastcall ActionEvent::setEvent(int thisPtr, byte eventType, int eventValue, float time)
{
    // +0x1c: event type byte
    *(byte*)(thisPtr + 0x1c) = eventType;
    // +0x1d: sub-type or padding, cleared
    *(byte*)(thisPtr + 0x1d) = 0;
    // +0x10: flags (ushort), set bits 0x120 (bit5 and bit8) — indicates "active" or "triggered"?
    *(ushort*)(thisPtr + 0x10) |= 0x120;
    
    // Convert time from seconds to engine ticks using global time scale
    // DAT_00e445e0 is likely g_tickScale (ticks per second)
    float scaledTime = time * *(float*)0x00e445e0;
    // +0x14: duration or fire time in ticks (rounded to nearest integer)
    *(int*)(thisPtr + 0x14) = (int)(scaledTime + 0.5f);
    
    // +0x20: associated value (maybe ID or pointer)
    *(int*)(thisPtr + 0x20) = eventValue;
}