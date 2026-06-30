// FUNC_NAME: NetConnection::establishConnection
int __fastcall NetConnection::establishConnection(void *this)
{
    bool bVar1;
    int iVar2;
    wchar_t ipString[22]; // 44 bytes, wide char
    short connectResult[10];
    char buffer[2040]; // actually undefined2, but used as char buffer
    int dummy0;
    int dummy1;

    dummy1 = 0x6a2d7a;

    bVar1 = FUN_006a2950(); // platform initialization check
    if (bVar1 == false) {
        return 1;
    }

    // check if already connected (vtable method at +0x9c)
    bVar1 = ((bool (__thiscall *)(void *))(*(int **)this)[0x27])(); // 0x9c/4 = 0x27
    if ((bVar1 == false) && (iVar2 = FUN_006a2b50(), iVar2 != 0)) { // try next address
        return iVar2;
    }

    buffer[0] = 0;
    // format IP address from stored bytes at +0x80..+0x8c
    FUN_006a2080(ipString, L"%d.%d.%d.%d",
                 *(uint *)((char *)this + 0x80),
                 *(uint *)((char *)this + 0x84),
                 *(uint *)((char *)this + 0x88),
                 *(uint *)((char *)this + 0x8c));

    // send HTTP/payload request (vtable method at +0xa0)
    bVar1 = ((bool (__thiscall *)(void *, const char *, const wchar_t *, char *, int))(*(int **)this)[0x28])(
        &DAT_00d5d584,          // format string or resource path
        this,
        ipString,               // IP string
        buffer,                 // response buffer
        0x800);                 // buffer size
    if (bVar1 == false) {
        return 3;
    }

    if (connectResult[0] != 0) {
        FUN_006a2830();         // start socket connection
        iVar2 = FUN_006a21b0(connectResult, dummy0); // socket connect with timeout
        if (iVar2 < 0) {
            FUN_006a2540();     // cleanup socket
            return 4;
        }
        FUN_006a2540();         // cleanup socket
    }
    return 0;
}