#ifndef EMU_CORE_LOOPING_TEST_HARNESS_H_INC_
#define EMU_CORE_LOOPING_TEST_HARNESS_H_INC_ 1

#include "../Functors/Arithmetic.h"
#include <chrono>
#include <exception>
#include <filesystem>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace EmuCore::TestingHelpers
{
	/// <summary>
	/// <para> Type which may be used to easily perform basic timing tasks in bulk to calculate a semi-accurate average and collection of timings. </para>
	/// <para> Note that this is a basic loop test and, depending on the passed functor, may or may not attribute for cache misses. </para>
	/// </summary>
	/// <typeparam name="ToExecutePerLoop">Type which will be passed as a non-const reference to execute via the () operator for each iteration in timing.</typeparam>
	template<class ToExecutePerLoop>
	class LoopingTestHarness
	{
	public:
		using TimingType = double;

		template<bool PassLoopNumberOnExecution>
		inline std::string ExecuteAndOutputAsString(const std::size_t numLoops, ToExecutePerLoop& toExecutePerLoop, bool outputAllTimes = false)
		{
			std::ostringstream str;
			Execute<PassLoopNumberOnExecution>(numLoops, toExecutePerLoop, str, outputAllTimes);
			return str.str();
		}

		template<bool PassLoopNumberOnExecution>
		inline std::wstring ExecuteAndOutputAsWideString(const std::size_t numLoops, ToExecutePerLoop& toExecutePerLoop, bool outputAllTimes = false)
		{
			std::wostringstream str;
			Execute<PassLoopNumberOnExecution>(numLoops, toExecutePerLoop, str, outputAllTimes);
			return str.str();
		}

		template<bool PassLoopNumberOnExecution>
		inline void ExecuteAndOutputToFile(const std::size_t numLoops, ToExecutePerLoop& toExecutePerLoop, const std::filesystem::path& path, bool outputAllTimes = false)
		{
			std::ofstream outFile(path);
			if (outFile.is_open())
			{
				Execute<PassLoopNumberOnExecution>(numLoops, toExecutePerLoop, outFile, outputAllTimes);
			}
			else
			{
				throw std::exception("Failed to load a file to output the results of a LoopingTestHarness's execution.");
			}
		}

		template<bool PassLoopNumberOnExecution>
		inline void ExecuteAndOutputToWideFile(const std::size_t numLoops, ToExecutePerLoop& toExecutePerLoop, const std::filesystem::path& path, bool outputAllTimes = false)
		{
			std::wofstream outFile(path);
			if (outFile.is_open())
			{
				Execute<PassLoopNumberOnExecution>(numLoops, toExecutePerLoop, outFile, outputAllTimes);
			}
			else
			{
				throw std::exception("Failed to load a file to output the results of a LoopingTestHarness's execution.");
			}
		}

		template<bool PassLoopNumberOnExecution>
		inline void Execute(const std::size_t numLoops, ToExecutePerLoop& toExecutePerLoop, std::ostream& resultsStream, bool writeAllTimesToStream = false)
		{
			TimingType minTime = TimingType();
			TimingType maxTime = TimingType();
			TimingType totalTime = TimingType();
			TimingType meanTime = TimingType();
			std::vector<TimingType> times;
			PerformLoop<PassLoopNumberOnExecution>(numLoops, toExecutePerLoop, times, minTime, maxTime, totalTime, meanTime);

			resultsStream
				<< "Completed Looping Test Harness execution with " << numLoops << " iterations.\n"
				<< "Total Time: " << (totalTime * TimingType(0.001))
				<< "ms\nMin Time: " << minTime
				<< "us\nMax Time: " << maxTime
				<< "us\nMean Time: " << meanTime
				<< "us\nStandard Deviation: " << CalculateStandardDeviation(times, meanTime);
			if (writeAllTimesToStream)
			{
				resultsStream << "\nAll times:";
				for (std::size_t i = 0; i < numLoops; ++i)
				{
					resultsStream << "\n[" << i << "]: " << times[i] << "us";
				}
			}
		}

		template<bool PassLoopNumberOnExecution>
		inline void Execute(const std::size_t numLoops, ToExecutePerLoop& toExecutePerLoop, std::wostream& resultsStream, bool writeAllTimesToStream = false)
		{
			TimingType minTime = TimingType();
			TimingType maxTime = TimingType();
			TimingType totalTime = TimingType();
			TimingType meanTime = TimingType();
			std::vector<TimingType> times;
			PerformLoop<PassLoopNumberOnExecution>(numLoops, toExecutePerLoop, times, minTime, maxTime, totalTime, meanTime);

			resultsStream
				<< "Completed Looping Test Harness execution with " << numLoops << " iterations.\n"
				<< L"Total Time: " << (totalTime * TimingType(0.001))
				<< L"ms\nMin Time: " << minTime
				<< L"us\nMax Time: " << maxTime
				<< L"us\nMean Time: " << meanTime
				<< L"us\nStandard Deviation: " << CalculateStandardDeviation(times, meanTime);
			if (writeAllTimesToStream)
			{
				resultsStream << L"\nAll times:";
				for (std::size_t i = 0; i < numLoops; ++i)
				{
					resultsStream << L"\n[" << i << L"]: " << times[i] << L"us";
				}
			}
		}

	private:
		inline TimingType CalculateStandardDeviation(const std::vector<TimingType>& times, const TimingType meanTime) const
		{
			TimingType std_mean = TimingType(0);
			for (const TimingType& time_ : times)
			{
				TimingType subtracted = time_ - meanTime;
				std_mean += (subtracted * subtracted);
			}
			return EmuCore::do_sqrt<TimingType>()(std_mean / static_cast<TimingType>(times.size()));
		}

		template<bool PassLoopNumberOnExecution>
		inline void PerformLoop
		(
			const std::size_t numLoops,
			ToExecutePerLoop& toExecutePerLoop,
			std::vector<TimingType>& times,
			TimingType& minTime,
			TimingType& maxTime,
			TimingType& totalTime,
			TimingType& meanTime
		)
		{
			times.resize(numLoops, TimingType());
			totalTime = TimingType();
			minTime = std::numeric_limits<TimingType>::max();
			maxTime = std::numeric_limits<TimingType>::min();
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			std::chrono::steady_clock::time_point end;

			for (std::size_t i = 0; i < numLoops; ++i)
			{
				begin = std::chrono::steady_clock::now();
				if constexpr (PassLoopNumberOnExecution)
				{
					toExecutePerLoop(i);
				}
				else
				{
					toExecutePerLoop();
				}
				end = std::chrono::steady_clock::now();
				double thisTime = std::chrono::duration<TimingType, std::micro>(end - begin).count();
				totalTime += thisTime;
				times[i] = thisTime;

				if (thisTime < minTime)
				{
					minTime = thisTime;
				}
				if (thisTime > maxTime)
				{
					maxTime = thisTime;
				}
			}
			meanTime = totalTime / static_cast<TimingType>(numLoops);
		}
	};
}

#endif
