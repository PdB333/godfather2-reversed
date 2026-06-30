// FUNC_NAME: PathFollower::setWaypoint
void __thiscall PathFollower::setWaypoint(PathFollower* this, uint32_t param2, uint32_t param3, uint32_t param4) {
    // Store waypoint coordinates (apparently non‐contiguous – offsets 0x50, 0x60, 0x70)
    this->m_waypointX = param2;         // +0x50
    this->m_waypointZ = param4;         // +0x70
    this->m_waypointY = param3;         // +0x60

    // Clear per‑axis presence flags (bytes after each coordinate)
    this->m_hasWaypointX = 0;           // +0x54
    this->m_hasWaypointY = 0;           // +0x64 (decimal 100)
    this->m_hasWaypointZ = 0;           // +0x74

    // Clear bit 1 (0b10) of the flags word – possibly “active” or “valid”
    this->m_flags &= ~0x2;              // +0x4c
}