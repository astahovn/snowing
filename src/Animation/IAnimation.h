#ifndef SNOWING_IANIMATION_H
#define SNOWING_IANIMATION_H

class IAnimation {
public:
    static const int COMPUTING_OK = 1;
    static const int COMPUTING_END = 2;

    virtual ~IAnimation() = default;

    virtual void init() = 0;
    virtual int computing() = 0;
    virtual void render(float globalFading) const = 0;
    virtual void processKeys(const bool keys[]) = 0;
};

#endif
