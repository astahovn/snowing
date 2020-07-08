#ifndef SNOWING_IWMHANDLER_H
#define SNOWING_IWMHANDLER_H


class IWMHandler {
public:
    virtual ~IWMHandler() = default;

    virtual void onWinCreate() = 0;
    virtual void onWinDestroy() = 0;
    virtual void onKeyDown(int key) = 0;
    virtual void onKeyUp(int key) = 0;
};


#endif
