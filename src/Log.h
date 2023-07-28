#pragma once
#include "Error.h"

#include "spdlog/spdlog.h"
#include <spdlog\common.h>

#define VOID_CORE_TRACE(...) Log::GetLogger()->trace(__VA_ARGS__)
#define VOID_CORE_INFO(...) Log::GetLogger()->info(__VA_ARGS__)
#define VOID_CORE_WARN(...) Log::GetLogger()->warn(__VA_ARGS__)
#define VOID_CORE_ERROR(...) Log::GetLogger()->error(__VA_ARGS__)
//#define VOID_CORE_CRITICAL(...) Log::GetLogger()->critical(__VA_ARGS__)
#define VOID_CORE_CRITICAL(...) Log::Critical(__VA_ARGS__)
#define VOID_CORE_TERMINATE_APPLICATION(...) Error::TerminateApplication(__VA_ARGS__)

#define VOID_TRACE(...) Log::GetLogger()->trace(__VA_ARGS__)
#define VOID_INFO(...) Log::GetLogger()->info(__VA_ARGS__)
#define VOID_WARN(...) Log::GetLogger()->warn(__VA_ARGS__)
#define VOID_ERROR(...) Log::GetLogger()->error(__VA_ARGS__)
#define VOID_CRITICAL(...) Log::GetLogger()->critical(__VA_ARGS__)

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

	template<typename T>
	inline static void Critical(const T& Message)
	{
		s_Logger->critical(Message);

		VOID_CORE_TERMINATE_APPLICATION();
	}

	template<typename... Args>
	inline static void Critical(spdlog::string_view_t fmt, const Args&... args)
	{
		//log(level::critical, fmt, args...);
		s_Logger->critical(fmt, args...);

		VOID_CORE_TERMINATE_APPLICATION();
	}

private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};