#pragma once

#include <chrono>

namespace demo
{
class SlowProcessData;

using Callable = std::function<void(int)>;

auto WriteSensorsData(std::stop_token aSToken
						, const Callable& aFunc
						, int aAmp
						, int aPhaseShift
						, const std::chrono::milliseconds& aSleepingTime) -> void;

auto ReadSensorsData(std::stop_token aSToken
						, const SlowProcessData& aData
						, const std::chrono::milliseconds& aSleepingTime) -> void;

} // namespace demo