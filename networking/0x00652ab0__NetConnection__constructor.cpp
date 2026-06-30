// FUNC_NAME: NetConnection::constructor
void NetConnection::constructor(void)
{
  // Global allocation counter (likely in data section)
  s_allocCount++;

  // Set vtable pointer
  this->m_pVTable = &PTR_LAB_00e43088;               // +0x00

  // Initialize many fields to zero
  this->m_field1 = 0;                                 // +0x04
  this->m_field2 = 0;                                 // +0x08

  this->m_packetWindowFlags = 0;                      // +0xB8 (0x2e)
  *(short *)(&this->m_unk0x100) = 0;                  // +0x100
  *(short *)((byte*)this + 0x102) = 0;                // +0x102
  this->m_sequenceGap = 0;                            // +0x110 (0x44)
  this->m_lastAckedSeq = 0;                           // +0x10C (0x43)
  this->m_sendSeq = 0;                                // +0x108 (0x42)
  this->m_recvSeq = htonl(0);                         // +0x104 (0x41) - network order 0
  this->m_reliableSendQueue = 0;                      // +0x124 (0x49)
  this->m_gatherList = 0;                             // +0x150 (0x54)
  this->m_gatherList2 = 0;                            // +0x154 (0x55)
  this->m_flowControlState = 0;                       // +0x158 (0x56)
  this->m_flowControlTimer = 0;                       // +0x15C (0x57)
  this->m_retransmitQueue = 0;                        // +0x18C (99)
  this->m_roundTripTime = 0;                          // +0x184 (0x61)
  this->m_roundTripDeviation = 0;                     // +0x188 (0x62)
  this->m_lastSendTime = 0;                           // +0x194 (0x65)
  *(byte *)(&this->m_unk0x190) = 0;                   // +0x190 (byte)
  *(byte *)((byte*)this + 0x132) = 0;                 // +0x132
  *(byte *)((byte*)this + 0x131) = 0;                 // +0x131
  *(byte *)(&this->m_receivedACKs) = 0;               // +0x130 (0x4c)
  *(byte *)(&this->m_flowControlDecrease) = 0;        // +0x198 (0x66)
  *(byte *)((byte*)this + 0x191) = 0;                 // +0x191
  this->m_flowControlIncrease = 0;                    // +0x1A4 (0x69)
  this->m_estimatedBandwidth = 0;                     // +0x1B0 (0x6c)

  u_long currentTime = FUN_0065bf40();                 // Get current time
  this->m_currentTime = currentTime;                  // +0xA4 (0x29)

  // One-time initialization of global object
  if (s_globalInitFlag == '\0') {
    s_globalInitFlag = '\x01';
    FUN_00662100(&DAT_01203740);                       // Initialize global structure
    FUN_006622a0(&DAT_01203740);                       // Prepare global structure
  }

  // Initialize some substructure at offset 0x133 (size 8)
  FUN_00662350((int)this + 0x133, 8, &DAT_01203740);

  // Set packet size limits (2500 bytes)
  this->m_maxPacketSize = 0x9c4;                      // +0xE0 (0x38)
  this->m_maxPacketSizeAlt = 0x9c4;                   // +0xDC (0x37)

  // Clear additional fields
  this->m_retransmitTimer = 0;                        // +0xCC (0x33)
  this->m_sendWindowStart = 0;                        // +0xC0 (0x30)
  this->m_packetSendRate = 0x60;                      // +0xD8 (0x36) - 96ms
  this->m_packetSendRateAlt = 0x60;                   // +0xD4 (0x35)

  // Copy 8 bytes from m_packetSendRateAlt to m_currentSendRate? (likely two ints)
  *(uint64*)(&this->m_currentSendRate) = *(uint64*)(&this->m_packetSendRateAlt); // +0xE4 (0x39)

  this->m_ackTimer = 0;                               // +0xC8 (0x32)
  this->m_timeoutTimer = 0;                           // +0xD0 (0x34)

  this->m_lastSendTime2 = 0;                          // +0xBC (0x2f)
  this->m_timeSinceLastAck = 0;                       // +0xC4 (0x31)

  this->m_retransmitCount = 0;                        // +0x1B4 (0x6d)
  this->m_expectedAckSeq = 0;                         // +0x11C (0x47)
  this->m_recvWindowStart = 0;                        // +0x120 (0x48)

  // Copy 8 bytes from m_maxPacketSizeAlt to m_currentWindowSize?
  *(uint64*)(&this->m_currentWindowSize) = *(uint64*)(&this->m_maxPacketSizeAlt); // +0xEC (0x3b)

  *(byte *)(&this->m_flowControlActive) = 1;          // +0xF4 (0x3d) - enable flow control

  FUN_006538d0();                                      // Reset packet queue or similar

  // Store global pointers into instance
  this->m_globalConfig = DAT_00e2b04c;                 // +0x1B8 (0x6e)
  this->m_packetCountOOB = 0;                          // +0x114 (0x45)
  this->m_packetCountReliableOOB = 0;                  // +0x118 (0x46)

  this->m_notifyList = 0;                              // +0x90 (0x24)
  this->m_lastAckTime = this->m_currentTime;           // +0x94 (0x25)
  this->m_lastSendTimeReliable = this->m_currentTime;  // +0x98 (0x26)
  this->m_connectionState = 0;                         // +0x9C (0x27)
  this->m_connectionStateFlags = 0;                    // +0xA0 (0x28)

  this->m_bandwidthTimer = 0;                          // +0x1C0 (0x70)
  this->m_flowControlTimer2 = 0;                       // +0x1C8 (0x72)

  this->m_configPtr = DAT_00e2afb8;                    // +0x1BC (0x6f)

  this->m_initialTimeout = 5000;                       // +0xB0 (0x2c) - 5 seconds
  this->m_maxRetries = 10;                             // +0xB4 (0x2d) - 10 retries
  return;
}