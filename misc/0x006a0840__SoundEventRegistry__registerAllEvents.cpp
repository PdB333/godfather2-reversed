// FUNC_NAME: SoundEventRegistry::registerAllEvents
// Address: 0x006a0840
// This function registers a large set of sound/audio events with the EARS audio system.
// It uses a pattern: get a context, create an event descriptor, register it with a hash ID.
// Hashes appear to be unique identifiers for each event type.

void registerAllEvents(void)
{
    uint context;
    uint eventDescriptor;
    int enable; // typically 0 or 1

    // --- Block 1: Many event registrations using getDefaultContext ---
    context = getDefaultAudioContext(); // 0x00496430
    enable = 1;
    eventDescriptor = createEventDescriptor(0x11, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x8c036aab, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x1f, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x46e7afe1, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x1e, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x1a271621, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x20, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xd7d6fc22, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x12, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xa08a43df, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x38, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x776def75, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x2a, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x78467823, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x1d, 0x9d, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x17a26743, eventDescriptor, context, enable);

    // --- Block 2: Using getContextByCategory ---
    context = getContextByCategory(0, 0xff); // 0x004965e0
    enable = 1;
    eventDescriptor = createEventDescriptor(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x2938c6cc, eventDescriptor, context, enable);

    context = getContextByCategory(1, 0xff);
    enable = 1;
    eventDescriptor = createEventDescriptor(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x3ddc7637, eventDescriptor, context, enable);

    // --- Back to default context ---
    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x10, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x6367ea84, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x39, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xed41087b, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x21, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xa7879506, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x21, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xf0c639eb, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x2e, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x657a83a5, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x2f, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x64ce24d7, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(0xf, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0xc1e9c75, eventDescriptor, context, enable);

    // --- More category-based ---
    context = getContextByCategory(0xff, 4);
    enable = 1;
    eventDescriptor = createEventDescriptor(0x2c, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x6ef11ea8, eventDescriptor, context, enable);

    context = getContextByCategory(0xff, 3);
    enable = 1;
    eventDescriptor = createEventDescriptor(0x2d, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xbe16155b, eventDescriptor, context, enable);

    // --- Default context, disabled events ---
    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(2, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0xc4aacd37, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(3, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0xc4aacd38, eventDescriptor, context, enable);

    // ... (similar pattern for IDs 4-11)
    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(4, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0xc4aacd39, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(5, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0xc4aacd3a, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(6, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0xc4aacd3b, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(7, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0xc4aacd3c, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(8, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0xc4aacd3d, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(9, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0xc4aacd3e, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(10, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0xc4aacd3f, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(0xb, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0xc4aacd36, eventDescriptor, context, enable);

    // --- More events ---
    context = getContextByCategory(0xff, 2);
    enable = 1;
    eventDescriptor = createEventDescriptor(0x39, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xebc77d43, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x13, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x62b07722, eventDescriptor, context, enable);

    context = getContextByCategory(0, 0xff);
    enable = 1;
    eventDescriptor = createEventDescriptor(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x54a314df, eventDescriptor, context, enable);

    context = getContextByCategory(1, 0xff);
    enable = 1;
    eventDescriptor = createEventDescriptor(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xd177df7c, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x11, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x3210a0c6, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x1f, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xec486385, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x1e, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x9f425b6d, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x20, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xded909d6, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x2a, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x66e0c2b3, eventDescriptor, context, enable);

    context = getContextByCategory(0, 0xff);
    enable = 1;
    eventDescriptor = createEventDescriptor(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x5dd81de3, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x1d, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xb4a5136c, eventDescriptor, context, enable);

    context = getContextByCategory(0xff, 2);
    enable = 1;
    eventDescriptor = createEventDescriptor(0x39, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x5855e99b, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x2c, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xf2448c6, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x10, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xc072d9d7, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x2e, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x6af3511e, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x21, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xc9694699, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x2f, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x5182bba0, eventDescriptor, context, enable);

    // --- Special events with custom ranges ---
    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(0xff, 0xff, 200, 0x48, 0xff, 0, 0, 3, context, 0);
    registerEvent(0xb0bda83a, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(0xff, 0xff, 0xd0, 0x50, 0xff, 0, 0, 3, context, 0);
    registerEvent(0xe1fe5cc1, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(0xff, 0xff, 0xcb, 0x4b, 0xff, 0, 0, 3, context, 0);
    registerEvent(0x51374386, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(0xff, 0xff, 0xcd, 0x4d, 0xff, 0, 0, 3, context, 0);
    registerEvent(0x923727fd, eventDescriptor, context, enable);

    // --- More disabled events ---
    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(1, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0x1d8e854d, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(0x1c, 0x9c, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0x318300a5, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(1, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0xd4c6db97, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(0x39, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0x5d4e479f, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 0;
    eventDescriptor = createEventDescriptor(199, 0, 0, 0, 0xff, 0, 0, 3, context, 0);
    registerEvent(0x388a33a7, eventDescriptor, context, enable);

    // --- More enabled events ---
    context = getContextByCategory(0xff, 2);
    enable = 1;
    eventDescriptor = createEventDescriptor(0x39, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xb14e178e, eventDescriptor, context, enable);

    context = getContextByCategory(0, 0xff);
    enable = 1;
    eventDescriptor = createEventDescriptor(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x4296e28d, eventDescriptor, context, enable);

    context = getContextByCategory(1, 0xff);
    enable = 1;
    eventDescriptor = createEventDescriptor(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x36d50d68, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(0x38, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x4238f65a, eventDescriptor, context, enable);

    // --- Enable vehicle-specific events? ---
    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(2, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x424a9b6b, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(3, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x424a9b6c, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(4, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x424a9b6d, eventDescriptor, context, enable);

    context = getDefaultAudioContext();
    enable = 1;
    eventDescriptor = createEventDescriptor(5, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0x424a9b6e, eventDescriptor, context, enable);

    // Final registration with category context
    context = getContextByCategory(1, 0xff);
    enable = 1;
    eventDescriptor = createEventDescriptor(0, 0, 0xff, 0xff, 0xff, 0, 0, 3, context, 1);
    registerEvent(0xc4417112, eventDescriptor, context, enable);

    return;
}