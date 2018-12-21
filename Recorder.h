#pragma once
#include "smart_ptr.h"
#include "Vector.h"
#include <list>

PTR( Recorder );

/*

マウスの軌跡を保存して起き先頭ノードの座標を常に計算するクラス

*/

class Recorder {
public:
	Recorder( );
	virtual ~Recorder( );

public:
	bool record( );
	const std::list< Vector >& getNewNodes( ) const;

private:
	void fall( );
	void recordNewMousePos( );
	void convertNodePos( );

private:
	std::list< Vector > _create_nodes;
	std::list< Vector > _mouse_points;
};

