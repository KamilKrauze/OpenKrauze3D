#ifndef ARG_PARSE_H
#define ARG_PARSE_H

#include <iostream>
#include <string>
#include <thread>

#include <omp.h>

static void set_omp_threads(int argc, char** argv) {
	const unsigned int max_threads = std::thread::hardware_concurrency();
	unsigned int thread_override = max_threads;
	unsigned int thread_ratio = 1;

	// Default
	if (argc == 1) {
	default_settings:
		thread_override = static_cast<unsigned int>(static_cast<float>(max_threads) * 0.75f);
		std::cout << "Using " << thread_override << " threads" << "\n";
		omp_set_num_threads(thread_override);
		return;
	}

	// If invalid arguments theb use default settings
	if (!(argc % 2) && (argc < 3 || argc < 5)) goto default_settings;

	// Process arguments
	for (size_t i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == std::string("-t").c_str()) {
			char*& arg = argv[i + 1];
			thread_override = static_cast<int>(*arg) - 0x30;
		}

		if (std::string(argv[i]) == std::string("-tR").c_str()) {
			char*& arg = argv[i + 1];
			thread_ratio = static_cast<int>(*arg) - 0x30;
		}
	}

	thread_override = std::max(std::min(thread_override, max_threads), static_cast<unsigned int>(2));
	if (thread_ratio < 0) thread_ratio = 1;

	thread_override = thread_override / thread_ratio;
	thread_override = std::max(thread_override, static_cast<unsigned int>(2));
	
	std::cout << "Using " << thread_override << " threads" << std::endl;
	omp_set_num_threads(thread_override);
	return;

}

#endif // !ARG_PARSE_H
