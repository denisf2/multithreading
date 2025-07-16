#include <cmath>
#include <functional>
#include <iostream>
#include <syncstream>

#include "AuxFunctions.h"
#include "SlowProcessData.h"

namespace demo
{

// auxiliary code to simulate sensors reading functionali
auto WriteSensorsData(std::stop_token aSToken
                        , const Callable& aFunc
                        , int aAmp
                        , int aPhaseShift
                        , const std::chrono::milliseconds& aSleepingTime) -> void
{
    constexpr int period{128};
    for(auto i{0}; !aSToken.stop_requested(); i = (i + 1) % period)
    {
        const auto sensorValue = aAmp * static_cast<int>(std::nearbyint(std::sin(i + aPhaseShift)));
        aFunc(sensorValue);

        std::this_thread::sleep_for(aSleepingTime);
    }
}

// auxiliary code to simulate stored data reading
auto ReadSensorsData(std::stop_token aSToken
                        , const SlowProcessData& aData
                        , const std::chrono::milliseconds& aSleepingTime) -> void
{
    while(!aSToken.stop_requested())
    {
        std::osyncstream(std::cout)
            << "Thread ID:"
            << std::this_thread::get_id()
            << " Temperature:"
            << aData.Temperature()
            << " Humidity:"
            << aData.Humidity()
            << '\n';

        std::this_thread::sleep_for(aSleepingTime);
    }
}

} // namespace demo