#ifndef iSENSOR_H
#define ISENSOR_H

class iSensor
{
public:
	virtual ~iSensor();
	virtual int GetData() = 0;
};

#endif
