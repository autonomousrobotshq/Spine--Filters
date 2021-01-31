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

#ifndef PEAKFILTER_HPP
#define PEAKFILTER_HPP

#include <stddef.h>
#include <stdlib.h>
#include "Filter.hpp"

template <typename T>
class PeakFilter : public Filter<T> {
	public:
	    PeakFilter(const size_t sample_count);
	    ~PeakFilter();
	    T GetFilteredSignal();
	private:
};

template <typename T>
PeakFilter<T>::PeakFilter(const size_t sample_count)
	: Filter<T>(sample_count)
{
}

template <typename T>
PeakFilter<T>::~PeakFilter()
{
}

template <typename T>
T PeakFilter<T>::GetFilteredSignal()
{
	if (this->_index == 0)
		return (0);
    T avg = 0;
    T dev[this->_index + 1];
    T dev_avg = 0;

    for (size_t i = 0; i + 1 < this->_index; i++) {
        dev[i] = abs(this->_readings[i] - this->_readings[i + 1]);
        dev_avg += dev[i];
    }
    dev_avg /= this->_index > 0 ? this->_index : 1;

    size_t number_of_qualified = 0;
    for (size_t i = 0; i + 1 < this->_index; i++) {
        if (dev[i] <= dev_avg) {
            avg += this->_readings[i];
            number_of_qualified++;
        }
    }
    return (number_of_qualified > 0 ? avg / number_of_qualified : this->_readings[0]);
}

#endif
