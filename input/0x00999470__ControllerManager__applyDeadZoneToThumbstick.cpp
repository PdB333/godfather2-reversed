// FUNC_NAME: ControllerManager::applyDeadZoneToThumbstick
// Address: 0x00999470
// Applies a dead zone filter to the left thumbstick input for a controller slot.
// Resets stick to center if within dead zone, and updates network state.

void ControllerManager::applyDeadZoneToThumbstick()
{
    // Check if this slot's thumbstick processing is enabled (bit 4) and if the
    // global dead zone factor is below a limit (likely a developer toggle).
    if ( ((m_flags & 0x10) != 0) && (g_deadZoneEnabled < 10) )
    {
        // Refresh/converge dead zone parameters from globals.
        updateDeadZoneConfig();

        float deadZone = g_deadZoneThreshold; // DAT_00e44598
        bool isInDeadZone;

        // Process X axis
        if (m_stickX >= 0.0f)
        {
            isInDeadZone = false;
            // If within [0, max+deadZone], consider it potentially dead.
            if (m_stickX <= g_stickMax + deadZone)
            {
                // If the stick was previously not in dead zone, call specific handler.
                if ( !(m_flags & 0x2) )
                {
                    onStickWithinBoundsX();
                }
                deadZone = g_deadZoneThreshold;
                isInDeadZone = (m_stickY <= m_stickX + g_deadZoneThreshold);
                m_stickX = g_stickCenter; // Reset X to center.
            }
        }
        else
        {
            isInDeadZone = true;
        }

        // Process Y axis
        if ( (m_stickY >= g_minStickY) &&
             (m_stickY <= g_stickMax + deadZone) &&
             isInDeadZone )
        {
            if ( !(m_flags & 0x2) )
            {
                onStickWithinBoundsY();
                onStickDeadZoneEntered();
            }

            // If the previous value differs from the stored "last" value,
            // handle any transition (e.g., network update).
            if ( m_lastRawStickX != m_stickCenterStorage )
            {
                handleStickTransition(m_lastRawStickX);
            }

            if ( m_flags & 0x2 )
            {
                // Check if the associated network controller is not already flagged.
                auto* netCtl = reinterpret_cast<NetController*>(m_networkSlotPtr);
                if ( !(netCtl->flags_0x184 & 0x2) )
                {
                    notifyNetworkStick();
                    m_flags |= 0x80;
                }
                sendNetworkMessage(4, m_networkSlotPtr);
            }

            m_stickY = g_stickCenter; // Reset Y to center.
        }
    }
}