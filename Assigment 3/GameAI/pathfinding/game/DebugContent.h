#ifndef DEBUG_CONTENT_H
#define DEBUG_CONTENT_H

#include <string>
#include <Trackable.h>

class DebugContent :public Trackable
{
public:
	DebugContent() {};
	virtual ~DebugContent() {};

	virtual std::string getDebugString() = 0;
};

#endif // !DEBUG_CONTENT_H