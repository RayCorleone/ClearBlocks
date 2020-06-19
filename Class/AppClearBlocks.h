#ifndef  _APP_CLEARBLOCKS_H_
#define  _APP_CLEARBLOCKS_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class  AppClearBlocks : private cocos2d::Application
{
public:
    AppClearBlocks();
    virtual ~AppClearBlocks();

    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  Called when the application moves to the background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  Called when the application reenters the foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_CLEARBLOCKS_H_