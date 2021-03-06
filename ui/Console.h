#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <vector>
#include <list>
#include "../CommonTypes.h"
#include "../math/Vector4.h"

class XLFont;
class IDriver3D;
class XL_Console;

class Console
{
public:
    enum ConsoleItemType
    {
        CTYPE_UCHAR=0,
        CTYPE_CHAR,
        CTYPE_UINT,
        CTYPE_INT,
        CTYPE_FLOAT,
        CTYPE_BOOL,
        CTYPE_STRING,
        CTYPE_CSTRING,
        CTYPE_VEC3,
        CTYPE_VEC4,
        CTYPE_FUNCTION,
        CTYPE_COUNT
    };

    typedef void (*ConsoleFunction)(const std::vector<std::string>&, void *);

public:
    Console(IDriver3D *pDriver3D);
    ~Console();

    void SetGameInfo(const std::string& gameName, int32_t versionMinor, int32_t versionMajor);

    void AddItem(const std::string& itemName, void *ptr, ConsoleItemType type, const std::string& itemHelp, void *pUserData=nullptr);
    void RemoveItem(const std::string& itemName);

    void SetDefaultCommand(ConsoleFunction func);
    void SetMaxCommands(int maxCmd) { m_MaxCommands = maxCmd; }
    void SetFont(XLFont *pFont) { m_pFont = pFont; }

    void Print(const std::string& text);
    void PrintCommandHelp(const std::string& cmd);

    void PassKey(char key);
    void PassEnter();
    void PassBackspace();
    void PassVirtualKey(int32_t key);

    void Render();

    bool IsActive() { return m_bActive; }
    bool IsPaused() { return m_bPaused; }
    bool IsChatActive() { return m_bChatMode; }
    void EnableCommandEcho(bool bEnable) { m_bEchoCommands = bEnable; }

    void PrintCommands(const char *pszText=nullptr);
    void LoadNewBackground(const char *pszBackground);

private:
    bool ParseCommandLine();

public:
    struct ConsoleItem
    {
        std::string name;
        std::string help;
        ConsoleItemType type;

        union
        {
            void *varPtr;
            ConsoleFunction func;
        };
        void *userData;
    };

    std::vector<std::string> m_CommandBuffer;
    std::list<ConsoleItem> m_ItemList;
    std::vector<std::string> m_TextBuffer;

    ConsoleFunction m_DefaultCommand;
    std::string m_CommandLine;
    char m_szGameInfo[128];

    IDriver3D *m_pDriver;

    uint32_t m_MaxCommands;
    uint32_t m_MaxTextLines;
    bool m_bEchoCommands;
    bool m_bPaused;
    int32_t m_nCommandHistory;
    int32_t m_nScrollOffs;
    int32_t m_nBlinkFrame;
    uint32_t m_CaretPos;
    bool m_bActive;
    bool m_bChatMode;

    float m_fAnimDropDown;
    float m_fAnimDelta;

    TextureHandle m_hBackground;

    XLFont *m_pFont;
    Vector4 m_Color;

private:
    static bool _Compare_nocase(ConsoleItem first, ConsoleItem second);
};

#endif //CONSOLE_H
