#include "main.h"
#include "AppClearBlocks.h"
#include "cocos2d.h"

USING_NS_CC;

//win32程序的入口,不需要进行修改//
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
