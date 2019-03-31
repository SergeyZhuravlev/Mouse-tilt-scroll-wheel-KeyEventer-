#include "stdafx.h"
#include <boost\property_tree\ptree.hpp>
#include "Settings.h"
#include "Windows.h"
#include <algorithm>
#include <filesystem>
#include <fstream>

Settings::Settings(HINSTANCE hInstance)
	: _hInstance(hInstance)
{
	Load();
}

void Settings::Load() 
{
	auto path = SettingsPath();
	if (!std::filesystem::exists(path))
		return;
	auto jsonData = LoadFile(path);
	boost::property_tree::ptree pt(jsonData);
	KeyRepeatPeriodInMilliseconds = pt.get_optional<UINT>("KeyRepeatPeriodInMilliseconds").get_value_or(KeyRepeatPeriodInMilliseconds);
	KeySpanInMilliseconds = pt.get_optional<UINT>("KeySpanInMilliseconds").get_value_or(KeySpanInMilliseconds);
	TiltModeEnabled = pt.get_optional<bool>("TiltModeEnabled").get_value_or(TiltModeEnabled);
	LegacyModeEnabled = pt.get_optional<bool>("LegacyModeEnabled").get_value_or(LegacyModeEnabled);
}

Settings::~Settings()
{
}

std::string Settings::LoadFile(const std::string& path)
{
	std::stringstream result;
	std::ifstream file;
	file.open(path, std::ios::in);
	result << file.rdbuf();
	return result.str();
}

std::string Settings::ExeDirectory()
{
	std::string result("");
	auto bufferSize = GetModuleFileNameA(nullptr, result.data(), 0);
	if(bufferSize <= 0)
		throw std::runtime_error("Can't get length info about current module");
	result.resize(bufferSize + 1);
	if (GetModuleFileNameA(nullptr, result.data(), result.size()) <= 0)
		throw std::runtime_error("Can't get info about current module");
	auto pos = result.find_last_of("\\");
	if (pos == std::string::npos)
		throw std::runtime_error("Can't get info about current module. Wrong path");
	auto it = result.cbegin() + pos;
	result.erase(it, result.cend());
	return result;
}

std::string Settings::SettingsPath()
{
	return ExeDirectory()+"\\KeyEventerSettings.json";
}

UINT Settings::GetKeyRepeatPeriodInMilliseconds() const
{
	return KeyRepeatPeriodInMilliseconds;
}

UINT Settings::GetKeySpanInMilliseconds() const
{
	return KeySpanInMilliseconds;
}

bool Settings::GetTiltModeEnabled() const 
{
	return TiltModeEnabled;
}

bool Settings::GetLegacyModeEnabled() const
{
	return LegacyModeEnabled;
}
