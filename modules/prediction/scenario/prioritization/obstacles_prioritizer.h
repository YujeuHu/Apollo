/******************************************************************************
 * Copyright 2019 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "cyber/common/macros.h"

#include "modules/prediction/container/obstacles/obstacles_container.h"
#include "modules/prediction/scenario/scenario_features/cruise_scenario_features.h"
#include "modules/prediction/scenario/scenario_features/scenario_features.h"

namespace apollo {
namespace prediction {

class ObstaclesPrioritizer {
 public:
  void PrioritizeObstacles();

  void AssignIgnoreLevel();

  void AssignCautionLevel();

 private:
  void AssignCautionLevelInJunction(const Obstacle& ego_vehicle,
                                    ObstaclesContainer* obstacles_container);

  void AssignCautionLevelCruiseKeepLane(
      const Obstacle& ego_vehicle, ObstaclesContainer* obstacles_container);

  void AssignCautionLevelCruiseChangeLane(
      const Obstacle& ego_vehicle, ObstaclesContainer* obstacles_container);

  void AssignCautionLevelByEgoReferenceLine(
      const Obstacle& ego_vehicle, ObstaclesContainer* obstacles_container);

  void AssignCautionByMerge(
      const Obstacle& ego_vehicle,
      std::shared_ptr<const hdmap::LaneInfo> lane_info_ptr,
      std::unordered_set<std::string>* const visited_lanes,
      ObstaclesContainer* obstacles_container);

  void AssignCautionByOverlap(
      const Obstacle& ego_vehicle,
      std::shared_ptr<const hdmap::LaneInfo> lane_info_ptr,
      std::unordered_set<std::string>* const visited_lanes,
      ObstaclesContainer* obstacles_container);

  void SetCautionBackward(
      const double distance, const Obstacle& ego_vehicle,
      std::shared_ptr<const hdmap::LaneInfo> start_lane_info_ptr,
      std::unordered_set<std::string>* const visited_lanes,
      ObstaclesContainer* obstacles_container);

  void SetCautionIfCloseToEgo(const Obstacle& ego_vehicle,
                              const double distance_threshold,
                              Obstacle* obstacle_ptr);

 private:
  std::unordered_set<std::string> ego_back_lane_id_set_;

  std::string ego_lane_id_ = "";

  double ego_lane_s_ = 0.0;

  DECLARE_SINGLETON(ObstaclesPrioritizer)
};

}  // namespace prediction
}  // namespace apollo
