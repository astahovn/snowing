#ifndef SNOWING_IANIMATION_H
#define SNOWING_IANIMATION_H

class IAnimation {
public:
    virtual ~IAnimation() = default;

    virtual void init() = 0;
    virtual void computing() = 0;
    virtual void render(float globalFading) const = 0;
};

#endif
