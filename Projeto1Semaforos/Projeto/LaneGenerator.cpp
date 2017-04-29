/*
 * LaneGenerator.cpp
 *
 *  Created on: 28 de abr de 2017
 *      Author: vinicius
 */

namespace via {


enum LaneType {Creater = 0, Disposer = 1};
enum LaneFromTo {North = 0, South = 1, East = 2, West = 3, Central = 4};
enum speed {EastS = 8, RightSide = 11, LeftSide = 17, WestS = 22};
Lane& LaneGenerator() {
	Lane lanes_[14]{};
	int lanesize[160];
	int speeds[160];
	for (auto from = North; from <= Central; from++)
		for (auto type = Creater; type <= Disposer; type++)
					switch (LaneFromTo){
					case North:
						for(auto side = 0; side <= 1 ; side++){
							lanesize[type&from&side] = 500;
							if(side == 0)
								speeds[type&from&side] = RightSide;
							else
								speeds[type&from&side] = LeftSide;
						}
					break;
					case South:
						for(auto side = 0; side <= 1 ; side++){
							lanesize[type&from&side] = 500;
							if(side == 0)
								speeds[type&from&side] = RightSide;
							else
								speeds[type&from&side] = LeftSide;
						}
					break;
					case East:
						lanesize[type&from&0] = 400;
						speeds[type&from&0] = EastS;
					break;
					case West:
						lanesize[type&from&0] = 2000;
						speeds[type&from&0] = WestS;
					break;
					case Central:
						lanesize[type&from&0] = 300;
						speeds[type&from&0] = LeftSide;
					break;
					}
	int i = 0;
	for (auto from = North; from <= Central; from++)
		for (auto type = Creater; type <= Disposer; type++)
			lanes_[2*from+type] = new Lane(speeds[type&from&0], 2*from+type, lanesize[type&from&0]);
	for(auto from = North; from <= South; from++)
		for(auto type = Creater; type <= Disposer; type++){
			lanes_[2*from+type+10] = new Lane(speeds[type&from&1], 2*from+type+10, lanesize[type&from&1]);
		}
	return lanes_;
}

} /* namespace via */
