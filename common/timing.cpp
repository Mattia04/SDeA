//
// Created by Mattia Ballico on 16/10/2026.
//
#include <common/timing.hpp>

namespace common
{
	void StopWatch::start() noexcept
	{
		if (running_) return;
		running_ = true;
		start_ = clock::now();
	}

	void StopWatch::stop() noexcept
	{
		if (not running_) return;

		running_ = false;

		const auto end = clock::now();
		total_ += end - start_;
		++n_intervals_;

		update_stats(std::chrono::duration<double>(total_).count());
	}

	void StopWatch::reset() noexcept
	{
		total_ = clock::duration::zero();
		n_intervals_ = 0;
		running_ = false;
	}

	double StopWatch::elapsed_now() const
	{
		if (not running_) return 0.;

		const auto now = clock::now();
		const auto elapsed = now - start_;
		return std::chrono::duration<double>(elapsed).count();
	}

	double StopWatch::elapsed() const
	{
		return std::chrono::duration<double>(total_).count();
	}

	double StopWatch::elapsed_stddev() const
	{
		if (n_intervals_ < 2) return 0.;

		return stddev_ / static_cast<double>(n_intervals_ - 1);
	}

	void StopWatch::update_stats(const double &x) noexcept
	{
		if (n_intervals_ == 1)
		{
			mean_ = x;
			stddev_ = 0.;
			return;
		}

		const auto prev_mean = mean_;
		mean_ = mean_ + (x - mean_) / static_cast<double>(n_intervals_);
		stddev_ = stddev_ + (x - prev_mean) * (x - mean_);
	}
}
