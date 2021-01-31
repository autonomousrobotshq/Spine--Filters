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

#ifndef MEDIANFILTER_HPP
#define MEDIANFILTER_HPP

#include <stddef.h>
#include <stdlib.h>
#include "Filter.hpp"

template <typename T>
class MedianFilter : public Filter<T> {
	public:
	    MedianFilter(const size_t sample_count);
	    ~MedianFilter();
	    T GetFilteredSignal();
	private:
};

template <typename T>
MedianFilter<T>::MedianFilter(const size_t sample_count)
	: Filter<T>(sample_count)
{
}

template <typename T>
MedianFilter<T>::~MedianFilter()
{
}

template <typename T>
T MedianFilter<T>::GetFilteredSignal()
{
	if (this->_index == 0)
		return (0);
    for (size_t j = 0; j < this->_index; j++) {
        for (size_t i = 0; i < this->_index - 1 - j; i++) {
            if (this->_readings[i] > this->_readings[i + 1]) {
                T temp_value = this->_readings[i];
                this->_readings[i] = this->_readings[i + 1];
                this->_readings[i + 1] = temp_value;
            }
        }
    }
    return (this->_readings[this->_index / 2]);
}

#endif
