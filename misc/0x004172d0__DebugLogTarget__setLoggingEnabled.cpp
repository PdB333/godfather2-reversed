// FUNC_NAME: DebugLogTarget::setLoggingEnabled
void __thiscall DebugLogTarget::setLoggingEnabled(byte enable) {
    // +0x62: flag byte, bit 0 = logging enabled
    byte& flag = *(byte*)((int)this + 0x62);
    byte oldFlag = flag;

    if ((oldFlag & 1) != (enable & 1)) {
        // Toggle the flag bit
        flag = (oldFlag ^ (enable & 1)) & 1 ^ oldFlag;

        // Query current time / state via virtual calls:
        // param_1[2] (offset +8) -> object with vtable at +0x20 (getTime?)
        uint time = (**(uint (__thiscall **)(void*))((*(int*)((int)this + 8) + 8) + 0x20))();
        // param_1->vtable+0x70: returns char (bool) – e.g. isLoggingEnabled?
        bool loggingActive = (**(char (__thiscall **)(void*))(*(int*)this + 0x70))(this) != 0;

        // Global logging buffer at DAT_01206880+0x14 points to next write slot
        int* logBuf = *(int**)(DAT_01206880 + 0x14);

        // Write a log entry: format/packet type, this, time, bool
        *logBuf++ = (int)&PTR_LAB_01124690;  // "STATE_CHANGE" format string
        *logBuf++ = (int)this;
        *logBuf++ = time;
        *(bool*)logBuf = loggingActive;
        logBuf = (int*)(((int)logBuf + 4) & ~3); // align to 4

        *(int*)(DAT_01206880 + 0x14) = (int)logBuf;

        // If the flag is now set (enabled), also log a 0x40-byte snapshot
        if ((flag & 1) != 0) {
            // param_1[3] (offset +12) -> object with vtable at +0x60 (getSnapshot)
            void* src = (*(void* (__thiscall **)(void*))(*(int*)((int)this + 12) + 0x60))();
            int* wptr = *(int**)(DAT_01206880 + 0x14);
            *wptr++ = (int)&PTR_LAB_0112467c; // "SNAPSHOT" format
            *wptr++ = (int)this;
            // Align dst to 16-byte boundary for memcpy (size 0x40)
            void* dst = (void*)(((int)wptr + 13) & ~0xF);
            memcpy(dst, src, 0x40);
            wptr = (int*)((char*)dst + 0x40);
            *(int*)(DAT_01206880 + 0x14) = (int)wptr;
        }
    }
}