#pragma once

#include <mutex>
#include <shared_mutex>

namespace demo
{
// Data structure to save sensors values and give thread safe access
class SlowProcessData
{
private:
	int m_Temperature_C{0};
	int m_Humidity_perc{0};

	mutable std::shared_mutex m_mutex;

public:
	auto Temperature() const -> int;
	auto Humidity() const -> int;
	auto SetTemperature(int aValue) -> void;
	auto SetHumidity(int aValue) -> void;
};

} // namespace demo