// FUNC_NAME: StreamObject::shutdown
void __thiscall StreamObject::shutdown() {
  int index; // index into global table

  // Only proceed if both stream handle and channel state are valid
  if (m_pStreamBuffer != nullptr && m_channelState != 0 && m_channelState != 0x48) {
    // Compute index: if channel state is 0, index = 0; else subtract 0x48 (72)
    index = (m_channelState == 0) ? 0 : m_channelState - 0x48; // +0x54

    // Stop audio playback for this channel via global event table
    stopAudioChannel(g_soundEventTable[index], m_pStreamBuffer, 0, 1, 0, 0); // 0x00424df0
  }

  // Release the stream buffer object (call its destructor via vtable)
  if (m_pStreamBuffer != nullptr) {
    m_pStreamBuffer->release(); // vtable[0] with param 1
  }

  m_pStreamBuffer = nullptr; // +0x5c
}