#pragma once

#include <common.h>
#include <interfaces.h>

#include "../data/maps/build_list.h"

#include "../data/maps/shahe_walking.h"
#include "../data/maps/shahe_bike.h"
#include "../data/maps/shahe_walking_busy.h"

#define MAX_HEIGHT 65
#define MAX_WIDTH  105
#define WALKABLE   0
#define INF 0xfffffff

static constexpr int dx[] = { 0, 0,-1, 1};
static constexpr int dy[] = {-1, 1, 0, 0};

constexpr size_t arrLen = (sizeof(dx) / sizeof(int));

struct Point2D {
	int x 	= 0; 
	int y 	= 0;
	int dis = INF;
	Point2D* parent = nullptr;
};

enum EvalueMode {
	SHORT_PATH ,
	SHORT_TIME ,
	SHORT_BIKE
};