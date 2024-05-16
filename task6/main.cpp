#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

enum class PointsType { MANDATORY, OPTIONAL };

class ControlPoint {
public:
  ControlPoint(std::string name, float latitude, float longitude, float penalty,
               PointsType type)
      : _name{std::move(name)}, _latitude{latitude}, _longitude{longitude},
        _penalty{penalty}, _type{type} {}

  const std::string &GetName() const { return _name; }
  std::pair<float, float> GetCoords() const { return {_latitude, _longitude}; }
  float GetPenalty() const { return _penalty; }
  PointsType GetType() { return _type; }

private:
  std::string _name;
  float _latitude;
  float _longitude;
  float _penalty;
  PointsType _type;
};

class Builder {
public:
  Builder &AddPoint(std::string name, float latitude, float longitude,
                    float penalty, PointsType type) {
    _control_points.push_back(
        ControlPoint(std::move(name), latitude, longitude, penalty, type));
    return *this;
  }

protected:
  std::vector<ControlPoint> _control_points;
};

class InfoBuilder : public Builder {
public:
  void ShowControlPoins() {
    std::size_t i = 1;
    for (auto &cpoint : _control_points) {
      auto [latitude, longitude] = cpoint.GetCoords();
      std::cout << "pos:" << i++ << ", name:" << cpoint.GetName()
                << ", latitude:" << latitude << ", longitude:" << longitude
                << ", penalty:";
      switch (cpoint.GetType()) {
      case PointsType::OPTIONAL:
        std::cout << cpoint.GetPenalty() << '\n';
        break;
      case PointsType::MANDATORY:
        std::cout << "fail\n";
        break;
      }
    }
  }
};

class PenaltyBuilder : public Builder {
public:
  float GetSummaryPenalty() {
    float summary_penalty;
    for (auto &cpoint : _control_points) {
      if (cpoint.GetType() == PointsType::OPTIONAL) {
        summary_penalty += cpoint.GetPenalty();
      }
    }
    return summary_penalty;
  }
};

int main() {
  InfoBuilder info;
  info.AddPoint("Kaz", 100, 100, 100, PointsType::OPTIONAL);
  info.AddPoint("sdf", 100.1, 100, -1, PointsType::MANDATORY);
  info.AddPoint("Vladivostok", -90, 70, 2, PointsType::OPTIONAL);

  info.ShowControlPoins();

  PenaltyBuilder penalty;
  penalty.AddPoint("Kaz", 100, 100, 100, PointsType::OPTIONAL);
  penalty.AddPoint("sdf", 100.1, 100, -1, PointsType::MANDATORY);
  penalty.AddPoint("Vladivostok", -90, 70, 2, PointsType::OPTIONAL);

  std::cout << penalty.GetSummaryPenalty() << '\n';

  return 0;
}