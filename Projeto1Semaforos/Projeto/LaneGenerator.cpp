/*
 * LaneGenerator.cpp
 *
 *  Created on: 28 de abr de 2017
 *      Author: vinicius
 */

#include "Lane.h"
namespace via {

enum LaneType {
	Creater = 0, Disposer = 1
};
enum LaneFromTo {
	North = 0, South = 1, East = 2, West = 3, Central = 4
};
enum speed {
	EastS = 8, RightSide = 11, LeftSide = 17, WestS = 22
};
Lane** LaneGenerator() {
	Lane* lanes_[14] { };
	int lanesize[160];
	int speeds[160];
	for (int from = North; from <= Central; from++)
		for (int type = Creater; type <= Disposer; type++)
			switch (from) {
			case North:
				for (auto side = 0; side <= 1; side++) {
					lanesize[type & from & side] = 500;
					if (side == 0)
						speeds[type & from & side] = RightSide;
					else
						speeds[type & from & side] = LeftSide;
				}
				break;
			case South:
				for (auto side = 0; side <= 1; side++) {
					lanesize[type & from & side] = 500;
					if (side == 0)
						speeds[type & from & side] = RightSide;
					else
						speeds[type & from & side] = LeftSide;
				}
				break;
			case East:
				lanesize[type & from & 0] = 400;
				speeds[type & from & 0] = EastS;
				break;
			case West:
				lanesize[type & from & 0] = 2000;
				speeds[type & from & 0] = WestS;
				break;
			case Central:
				lanesize[type & from & 0] = 300;
				speeds[type & from & 0] = LeftSide;
				break;
			}
	for (int from = North; from <= Central; from++)
		for (int type = Creater; type <= Disposer; type++) {
			int A = type * 100 + from * 10 + 0;
			auto temp = new Lane(speeds[A], 2 * from + type, lanesize[A]);
			lanes_[2 * from + type] = temp;
		}
	for (int from = North; from <= South; from++)
		for (int type = Creater; type <= Disposer; type++) {
			int A = type * 100 + from * 10 + 1;
			auto temp = new Lane(speeds[A], 2 * from + type, lanesize[A]);
			lanes_[2 * from + type + 10] = temp;
		}
	return lanes_;
}

} /* namespace via */
