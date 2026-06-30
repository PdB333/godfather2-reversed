// FUNC_NAME: ThreadHandle::close
class ThreadHandle {
public:
    // +0x18: HANDLE m_handle
    // Returns 8 on success, 2 on failure (CloseHandle failed)
    int __fastcall close() 
    {
        BOOL result = CloseHandle(*(HANDLE*)(this + 0x18));
        if (result == 0) {
            return 2;
        }
        *(HANDLE*)(this + 0x18) = INVALID_HANDLE_VALUE; // 0xffffffff
        return 8;
    }
};