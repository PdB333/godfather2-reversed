// FUNC_NAME: StreamEntry::StreamEntry
// Address: 0x0079a3d0
// Role: Constructor for a stream entry object, initializes fields and links into a global linked list.
// The object is part of a manager (likely StreamManager) that maintains a list of active streams.

StreamEntry * __thiscall StreamEntry::StreamEntry(StreamEntry *this, const char *name, uint id, uint flags1, uint flags2)
{
    // Call base class constructor (likely Object or some base)
    FUN_0064cc90();
    
    // Set vtable pointer
    this->vtable = &PTR_LAB_00d6a71c; // +0x00
    
    // Copy name (max 63 chars)
    _strncpy(this->name, name, 0x3f); // +0x08, 64 bytes including null
    
    // Set fields
    this->id = id;       // +0x04
    this->flags1 = flags1; // +0x0C (offset 3 words)
    this->flags2 = flags2; // +0x10 (offset 2 words)
    
    // Initialize next/prev pointers (likely for linked list)
    this->next = nullptr; // +0x14
    this->prev = nullptr; // +0x18
    this->unknown1 = 0;   // +0x1C
    this->unknown2 = 0;   // +0x20
    
    // Link into global list: set this->listPrev = g_streamEntryListHead
    this->listPrev = g_streamEntryListHead; // +0x70 (0x1c * 4)
    
    // Update global head to this
    g_streamEntryListHead = this;
    
    return this;
}