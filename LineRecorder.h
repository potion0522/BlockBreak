#pragma once
#include "smart_ptr.h"
#include "Vector.h"
#include <list>

PTR( LineRecorder );

class LineRecorder {
public:
	LineRecorder( );
	virtual ~LineRecorder( );

public:
	void record( );
	const std::list< Vector >& getRecordingData( ) const;

private:
	void recordNewPos( );
	void adjust( );
	void deleteOnBecameInvisible( );

private:
	const double CREATE_POS_Y;

private:
	std::list< Vector > _recorder;
};

