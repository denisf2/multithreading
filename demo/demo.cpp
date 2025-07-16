#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

#include "AuxFunctions.h"
#include "SlowProcessData.h"

using namespace std::chrono_literals;

int main()
{
    demo::SlowProcessData sensors;

    // make wrapper objects to bind class member method and main object
    auto setTemp = std::bind(std::mem_fn(&demo::SlowProcessData::SetTemperature)
                            , std::ref(sensors)
                            , std::placeholders::_1);

    auto setHumid = std::bind(std::mem_fn(&demo::SlowProcessData::SetHumidity)
                            , std::ref(sensors)
                            , std::placeholders::_1);

    std::vector<std::jthread> threads;
    
    // starting acquisition processes
    threads.emplace_back(demo::WriteSensorsData, setTemp, 10, 0, 50ms); // Temperature writer
    threads.emplace_back(demo::WriteSensorsData, setHumid, 30, 10, 70ms); // Humidity writer

    // starting reading processes
    threads.emplace_back(demo::ReadSensorsData, std::ref(sensors), 100ms); // Display graph builder
    threads.emplace_back(demo::ReadSensorsData, std::ref(sensors), 50ms); // Console / file logger

    // time to work for demo
    std::this_thread::sleep_for(3s);

    // request to stop all threads
    std::for_each(threads.begin(), threads.end()
                    , [](auto& aTread) {
                            aTread.request_stop();
                      });

    std::cout << "The end.\n";
}