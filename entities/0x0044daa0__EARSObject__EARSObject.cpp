// FUNC_NAME: EARSObject::EARSObject

// Global callback for post-initialization (if set)
extern void (*g_initCallback)(EARSObject*);

class EARSObject
{
public:
    int m_field10; // +0x10
    int m_field14; // +0x14
    int m_field30; // +0x30
    int m_field34; // +0x34
    int m_field50; // +0x50
    int m_field54; // +0x54
    int m_field70; // +0x70
    int m_field74; // +0x74
    int m_field90; // +0x90
    int m_ownerId; // +0x94 (parameter)
    int m_field98; // +0x98
    int m_field9C; // +0x9C
    int m_fieldA0; // +0xA0
    int m_fieldA4; // +0xA4
    int m_field8C; // +0x8C
    int m_field88; // +0x88
    int m_field84; // +0x84
    int m_field80; // +0x80

    EARSObject(int ownerId)
    {
        // Zero-initialize most members
        m_field10 = 0;
        m_field14 = 0;
        m_field30 = 0;
        m_field34 = 0;
        m_field50 = 0;
        m_field54 = 0;
        m_field70 = 0;
        m_field74 = 0;
        m_field90 = 0;

        // Set the owner ID from parameter
        m_ownerId = ownerId;

        // Clear remaining fields
        m_field98 = 0;
        m_field9C = 0;
        m_fieldA0 = 0;
        m_fieldA4 = 0;
        m_field8C = 0;
        m_field88 = 0;
        m_field84 = 0;
        m_field80 = 0;

        // Call global initialization hook if present
        if (g_initCallback != nullptr)
        {
            g_initCallback(this);
        }
    }
};