#pragma once
#include <expected>
#include <unordered_set>
#include <type_traits>

#include "FireMode.h"

template<typename T>
concept ProperlyDerived = std::derived_from<T, FireMode>;

class FireModeFactory
{
public:
	FireModeFactory() = default;
	~FireModeFactory() = default;

	auto appendMode(std::string_view pName, std::unique_ptr<FireMode> pMode)  -> void;
	auto replaceMode(std::string_view pName, std::unique_ptr<FireMode> pMode) -> void;
	auto setMode(std::string_view pName) -> void;

	auto isExist(std::string_view pName) -> bool;
	
	auto getReadMode()	 					 -> std::expected<std::reference_wrapper<const FireMode>, std::string_view>;
	auto getReadMode(std::string_view pName) -> std::expected<std::reference_wrapper<const FireMode>, std::string_view>;
	auto getMode()							 -> std::expected<std::reference_wrapper<FireMode>, std::string_view>;
	auto getMode(std::string_view pName)     -> std::expected<std::reference_wrapper<FireMode>, std::string_view>;

	template<typename T>
	requires ProperlyDerived<T>
	auto getExactMode(std::string_view pName) -> std::expected<std::reference_wrapper<FireMode>, std::string_view>;
	template<typename T>
	requires ProperlyDerived<T>
	auto getExactMode() -> std::expected<std::reference_wrapper<FireMode>, std::string_view>;

	auto getStorageLabels() -> std::unordered_set<std::string>;

private:
	std::string mCurrentFireMode;
	std::unordered_set<std::string> mStorageLabels;
	std::unordered_map<std::string, std::unique_ptr<FireMode>> mStorageFireModes;
};

