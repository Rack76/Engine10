#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
public:
    virtual void init() = 0;
	virtual void run(float dt) = 0;
	virtual void terminate() = 0;
};

#endif