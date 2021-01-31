//
// Spine - Spine - MCU code for robotics.
// Copyright (C) 2019-2021 Codam Robotics
//
// This file is part of Spine.
//
// Spine is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Spine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Spine.  If not, see <http://www.gnu.org/licenses/>.
//

#include <Arduino.h>
#include <ArduinoUnitTests.h>

#include "PeakFilter.hpp"

template <typename T>
bool	TestForArray(int nums[], int samplecount, int expected)
{
	PeakFilter<T> filter(samplecount);
	
	filter.Reset();
	
	for (int i = 0; i < samplecount; i++) {
	    filter.NewReading(nums[i]);
	}
	const int16_t f_avg = filter.GetFilteredSignal();

	return (f_avg == expected);
}

unittest(PeakFilter)
{
	// how to turn -std=c++0x on?
	int nums[] = {1, 1, 1, 5};
	assertTrue(TestForArray<int>(nums, sizeof(nums)/sizeof(int), 1));

	int nums0[] = {};
	assertTrue(TestForArray<int>(nums0, sizeof(nums0)/sizeof(int), 0));

	int nums1[] = {1};
	assertTrue(TestForArray<int>(nums1, sizeof(nums1)/sizeof(int), 1));

	int nums2[] = {-1, 0, 1, 5};
	assertTrue(TestForArray<int>(nums2, sizeof(nums2)/sizeof(int), 0));

	int nums3[] = {-500, 100, 500, 100, 100};
	assertTrue(TestForArray<int>(nums3, sizeof(nums3)/sizeof(int), 100));

	int nums4[] = {0, 500, 500};
	assertTrue(TestForArray<int>(nums4, sizeof(nums4)/sizeof(int), 500));

	int nums5[] = {100, 2, 2, 0, 0, 0};
	assertTrue(TestForArray<int>(nums5, sizeof(nums5)/sizeof(int), 1));

	int nums6[] = {500, 0};
	assertTrue(TestForArray<int>(nums6, sizeof(nums6)/sizeof(int), 250));
}

unittest_main()
