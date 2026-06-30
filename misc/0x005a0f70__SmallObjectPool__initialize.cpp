// FUNC_NAME: SmallObjectPool::initialize
void SmallObjectPool::initialize(void)
{
  // +0x00: m_usedCount (int)
  // +0x04: m_freeCount (int)
  // +0x08: m_freeList (pointer to first free node)
  // +0x0C: node array[2] (each 32 bytes)
  
  m_usedCount = 0;
  m_freeCount = 0;
  m_freeList = &m_nodes[0];              // head points to first node
  
  Node* node = &m_nodes[0];
  for (int i = 0; i < 2; i++, node++)
  {
    // Node layout:
    // +0x00: m_pad0 (int)
    // +0x04: m_pad4 (int)
    // +0x08: m_payloadPtr (void*) — points to own payload
    // +0x0C: m_payload[20] (char[20])
    
    node->m_pad0 = 0;
    node->m_pad4 = 0;
    node->m_payloadPtr = node->m_payload; // points to its own 20-byte payload
    memset(node->m_payload, 0, sizeof(node->m_payload));
  }
}