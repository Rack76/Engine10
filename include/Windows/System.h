#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
public:
    virtual void init() = 0;
	virtual void run() = 0;
	virtual void terminate() = 0;
};

#endif