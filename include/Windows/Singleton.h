#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
public:
	static T* getInstance() {
		if (!instance)
			instance = new T;

		return instance;
	}

private:
	static T* instance;
};

template <typename T>
T* Singleton<T>::instance = nullptr;

#endif