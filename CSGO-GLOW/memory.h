#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>

#include <cstdint>
#include <string_view>

class Hafiza
{
private:
	std::uintptr_t islemnumarasi = 0;
	void* islemitamamla = nullptr;

public:
	// Constructor that finds the process id
	// and opens a handle
	Hafiza(const std::string_view processName) noexcept
	{
		::PROCESSENTRY32 entry = { };
		entry.dwSize = sizeof(::PROCESSENTRY32);

		const auto snapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		while (::Process32Next(snapShot, &entry))
		{
			if (!processName.compare(entry.szExeFile))
			{
				islemnumarasi = entry.th32ProcessID;
				islemitamamla = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, islemnumarasi);
				break;
			}
		}

		// Free handle
		if (snapShot)
			::CloseHandle(snapShot);
	}

	// Destructor that frees the opened handle
	~Hafiza()
	{
		if (islemitamamla)
			::CloseHandle(islemitamamla);
	}

	// Returns the base address of a module by name
	const std::uintptr_t ModulAdresiniCek(const std::string_view moduleName) const noexcept
	{
		::MODULEENTRY32 entry = { };
		entry.dwSize = sizeof(::MODULEENTRY32);

		const auto snapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, islemnumarasi);

		std::uintptr_t result = 0;

		while (::Module32Next(snapShot, &entry))
		{
			if (!moduleName.compare(entry.szModule))
			{
				result = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
				break;
			}
		}

		if (snapShot)
			::CloseHandle(snapShot);

		return result;
	}

	// Read process memory
	template <typename T>
	constexpr const T oku(const std::uintptr_t& address) const noexcept
	{
		T value = { };
		::ReadProcessMemory(islemitamamla, reinterpret_cast<const void*>(address), &value, sizeof(T), NULL);
		return value;
	}

	// Write process memory
	template <typename T>
	constexpr void yaz(const std::uintptr_t& address, const T& value) const noexcept
	{
		::WriteProcessMemory(islemitamamla, reinterpret_cast<void*>(address), &value, sizeof(T), NULL);
	}
};
