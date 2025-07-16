#include "SlowProcessData.h"

namespace demo
{

auto SlowProcessData::Temperature() const -> int
{
	std::shared_lock lock(m_mutex);

	return m_Temperature_C;
}

auto SlowProcessData::Humidity() const -> int
{
	std::shared_lock lock(m_mutex);

	return m_Humidity_perc;
}

auto SlowProcessData::SetTemperature(int aValue) -> void
{
	std::unique_lock lock(m_mutex);

	m_Temperature_C = aValue;
}

auto SlowProcessData::SetHumidity(int aValue) -> void
{
	std::unique_lock lock(m_mutex);

	m_Humidity_perc = aValue;
}

} // namespace demo