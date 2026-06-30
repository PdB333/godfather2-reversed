// FUNC_NAME: AnimationBlender::stopOutgoingTrack
// Address: 0x0054e390
// Role: Stops the outgoing animation track during a transition. The method is called when switching between two tracks (A and B). It checks if the currently playing track (m_activeTrack) is either trackA or trackB, and then calls stopTrack on the specified outgoing track (parameter: 0 for trackA, 1 for trackB).

void __thiscall AnimationBlender::stopOutgoingTrack(int param_2)
{
    // +0x18: m_activeTrack (pointer to current playing track)
    // +0x1c: m_trackA (pointer to track A)
    // +0x20: m_trackB (pointer to track B)
    if ((*(int *)(this + 0x18) == *(int *)(this + 0x1c)) ||
        (*(int *)(this + 0x18) == *(int *)(this + 0x20)))
    {
        if (param_2 == 0)
        {
            // Stop track A
            stopTrack(*(int *)(this + 0x1c));
        }
        else
        {
            // Stop track B
            stopTrack(*(int *)(this + 0x20));
        }
    }
}