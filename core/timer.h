#pragma once
#include <chrono>

template <typename TPeriod = std::chrono::high_resolution_clock::period>
class timer {
public:
	using clock = std::chrono::high_resolution_clock;
	using clock_duration = std::chrono::duration<clock::rep, TPeriod>;

public:
	timer() : m_start_point(clock::now()) {}

	void reset() { m_start_point = clock::now(); }

	clock::rep elapsed_time() const {
		clock_duration duration = std::chrono::duration_cast<clock_duration>(clock::now() - m_start_point);
		return duration.count();
	}

	double seconds() {
		clock_duration duration = std::chrono::duration_cast<clock_duration>(clock::now() - m_start_point);
		return duration.count() / static_cast<double>(TPeriod::den);
	}

private:
	clock::time_point m_start_point;
};

using ns_timer = timer<std::nano>;
using mi_timer = timer<std::micro>;
using ms_timer = timer<std::milli>;
using s_timer = timer <std::ratio<1, 1>>;