#pragma once
#include <chrono>

namespace alg_timer {
	class Timer {
	public:
		template<typename f>
		static auto code_timer(f alg) {
			auto start = std::chrono::steady_clock::now();
			alg();
			auto end = std::chrono::steady_clock::now();
			return end - start;
		}
	};
};