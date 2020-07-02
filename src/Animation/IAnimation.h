#ifndef SNOWING_IANIMATION_H
#define SNOWING_IANIMATION_H

class IAnimation {
public:
    virtual ~IAnimation() = default;

    virtual void Init() = 0;
    virtual void Computing() = 0;
    virtual void Render(float GlobalFading) const = 0;
};

#endif
