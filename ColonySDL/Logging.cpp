#include <SDL.h>
#include <iostream>
#include <windows.h>
#include <string>

const char* GetLogPriorityShortName(SDL_LogPriority priority) {
	switch (priority) {
	case SDL_LOG_PRIORITY_VERBOSE: return "VERB";
	case SDL_LOG_PRIORITY_DEBUG:   return "DEBUG";
	case SDL_LOG_PRIORITY_INFO:    return "INFO";
	case SDL_LOG_PRIORITY_WARN:    return "WARN";
	case SDL_LOG_PRIORITY_ERROR:   return "ERROR";
	case SDL_LOG_PRIORITY_CRITICAL:return "CRITICAL";
	default:                       return "UNKNOWN";
	}
}


void CustomLogOutput(void* userdata, int category, SDL_LogPriority priority, const char* message) {
	// Get the current time
	time_t current_time = time(nullptr);
	struct tm local_time;
	if (localtime_s(&local_time, &current_time) == 0) {
		// The conversion was successful, and you can use 'local_time' now
		// For example, you can format the time as desired using strftime
		char time_buffer[20];
		strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", &local_time);
		// Now 'time_buffer' contains the formatted time string based on 'local_time'
		// Print the log message with the timestamp

		printf("[%s] %s %s\n", time_buffer, GetLogPriorityShortName(priority), message);
	}
	else {
		// Handle the error if localtime_s fails
	}
}