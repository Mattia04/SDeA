//
// Created by Mattia Ballico on 15/10/2026.
//
#pragma once

#include <chrono>

namespace common
{
	/**
	 * @brief Represents a simple stopwatch for measuring elapsed time.
	 *
	 * The StopWatch class provides utility methods for measuring time intervals in
	 * seconds or milliseconds. It supports multiple time intervals and provides
	 * functionalities to calculate elapsed time, reset the state, and retrieve statistical
	 * data such as the mean time per interval. The stopwatch is based on a steady clock
	 * for accuracy in time measurements.
	 */
	class StopWatch
	{
	public:
		/**
		 * @brief Starts the stopwatch to begin measuring elapsed time.
		 *
		 * This method sets the stopwatch to a running state and records the starting
		 * time as the current system time. If the stopwatch is already running,
		 * calling this method has no effect.
		 */
		void start() noexcept;
		/**
		 * @brief Stops the stopwatch and updates the total elapsed time.
		 *
		 * This method stops the stopwatch if it is currently running, calculates the duration
		 * of the current interval, and adds it to the total elapsed time. The count of intervals
		 * is incremented each time the stopwatch is successfully stopped.
		 *
		 * If the stopwatch is not running, the method exits without making any changes.
		 */
		void stop() noexcept;
		/**
		 * @brief Resets the stopwatch to its initial state.
		 *
		 * This method sets the total elapsed time to zero, clears the count of intervals,
		 * and marks the stopwatch as not running. After calling this method, all previously
		 * recorded intervals and running state will be cleared.
		 */
		void reset() noexcept;

		/**
		 * @brief Returns the elapsed time in seconds since the stopwatch was started.
		 *
		 * This method calculates the difference between the current time and the
		 * time when the stopwatch was last started. If the stopwatch is not running,
		 * the method returns 0.0.
		 *
		 * @return The elapsed time in seconds as a double precision value of the current interval.
		 */
		[[nodiscard]] double elapsed_now() const;
		/**
		 * @brief Returns the total elapsed time in seconds accumulated across all intervals.
		 *
		 * This method calculates the sum of all time intervals during which the stopwatch
		 * was running.
		 *
		 * @note It excludes any currently ongoing interval.
		 *
		 * @return The total elapsed time in seconds as a double precision value.
		 */
		[[nodiscard]] double elapsed() const;
		/**
		 * @brief Returns the elapsed time in milliseconds accumulated across all intervals.
		 *
		 * This method calculates the sum of all time intervals during which the stopwatch
		 * was running.
		 *
		 * @note It excludes any currently ongoing interval.
		 *
		 * @return The total elapsed time in milliseconds as a double precision value.
		 */
		[[nodiscard]] double elapsed_ms() const {return this->elapsed() * 1000;};
		/**
		 * @brief Checks if the stopwatch is currently running.
		 * @return True if the stopwatch is running, false otherwise.
		 */
		[[nodiscard]] bool is_running() const {return running_;};
		/**
		 * @brief Retrieves the mean elapsed time in seconds per interval.
		 *
		 * This method computes the average time in seconds across all intervals where
		 * the stopwatch was running. The mean is determined by dividing the total elapsed
		 * time by the number of intervals.
		 *
		 * @note if the stopwatch has not yet completed any interval, the result is zero.
		 *
		 * @return The mean elapsed time in seconds as a double precision value.
		 */
		[[nodiscard]] double elapsed_average() const {return mean_;};
		/**
		 * @brief Retrieves the standard deviation of the elapsed time intervals.
		 *
		 * This method calculates and returns the standard deviation of the recorded
		 * time intervals, reflecting the variability of the elapsed times.
		 *
		 * @note if the stopwatch has not yet completed two intervals, the result is zero.
		 *
		 * @return The standard deviation of the elapsed time intervals.
		 */
		[[nodiscard]] double elapsed_stddev() const;

	private:
		using clock = std::chrono::steady_clock;
		/**
		 * @brief Stores the total accumulated duration across all intervals measured by the stopwatch.
		 *
		 * This member variable represents the sum of all elapsed time intervals during which the stopwatch
		 * was running. It is updated whenever the stopwatch is stopped and reset to zero when the stopwatch
		 * is reset.
		 *
		 * @note The total duration does not include any currently ongoing interval.
		 */
		clock::duration total_ = clock::duration::zero();
		/**
		 * @brief Records the starting point of an elapsed time interval.
		 *
		 * This member variable stores the time at which the stopwatch starts measuring
		 * the duration of an interval. It is updated whenever the stopwatch transitions
		 * to a running state.
		 */
		clock::time_point start_{};
		/**
		 * @brief Tracks the number of intervals when the stopwatch is started and stopped.
		 *
		 * This member variable increments by 1 every time the stopwatch transitions from a running
		 * to a stopped state. It is used to calculate metrics such as the mean time elapsed
		 * per interval.
		 */
		std::size_t n_intervals_ = 0;
		/**
		 * @brief Indicates whether the stopwatch is currently running.
		 *
		 * This variable holds the running state of the stopwatch. It is set to `true`
		 * when the stopwatch is started and set to `false` when the stopwatch is stopped
		 * or reset. The state of this variable determines whether elapsed time is being
		 * actively measured.
		 */
		bool running_ = false;

		double mean_ = 0.0;
		double stddev_ = 0.0;
		/**
		 *
		 * @reference Welford's online algorithm: https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
		 * @param x
		 */
		void update_stats(const double &x) noexcept;
	};
}
