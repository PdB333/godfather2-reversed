// FUNC_NAME: ChangeTrackedObject::IsDirty
bool __thiscall ChangeTrackedObject::IsDirty()
{
    // Current revision stored at an offset of 0x30 from this
    int currentRevision = *(int*)((char*)this + 0x30);

    // Obtain the change tracker structure associated with this object.
    // The tracker structure is an array of two ints:
    //   [0] = pointer to the m_tracker field (should equal this+0x2c)
    //   [1] = cached revision number
    int* tracker = (int*)GetChangeTracker(this);

    // Debug assertion: verify that the tracker pointer is valid.
    // If it's non-null, it must point back to the object's m_tracker field.
    if ((*tracker == 0) || (*tracker != (int)((char*)this + 0x2c)))
    {
        DebugAssertionFailed();
    }

    // The object is considered changed if the cached revision does not match the current revision.
    return tracker[1] != currentRevision;
}