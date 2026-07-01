// FUNC_NAME: debugLogTlsEntry
void __fastcall debugLogTlsEntry(undefined4 *entry)
{
  int logIndex;

  logIndex = entry[2]; // +0x08: log index
  if (-1 < logIndex) {
    TlsGetValue(DAT_01139810); // TLS value (unused here)
    FUN_00aa26e0(*entry, logIndex << 4, 0x17); // call with handle, size=logIndex*16, type=0x17
  }
}