#include "main.h"
#include "Classes/AppClearBlocks.h"
#include "cocos2d.h"

USING_NS_CC;

//win32��������,����Ҫ�����޸�//
int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppClearBlocks app;
    return Application::getInstance()->run();
}
