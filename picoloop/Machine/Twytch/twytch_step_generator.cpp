/* Copyright 2013-2016 Matt Tytel
 *
 * mopo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * mopo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with mopo.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "twytch_step_generator.h"
#include "twytch_utils.h"

#include <cmath>

namespace mopotwytchsynth {

  StepGenerator::StepGenerator(int max_steps) :
      Processor(kNumInputs + max_steps, kNumOutputs), max_steps_(max_steps),
      offset_(0.0), current_step_(0) { }

  void StepGenerator::process() {
    static mopo_float integral;
    unsigned int num_steps = static_cast<int>(input(kNumSteps)->at(0));
    num_steps = twytchutils::iclamp(num_steps, 1, max_steps_);

    int i = 0;
    if (input(kReset)->source->triggered) {
      offset_ = 0.0f;
      current_step_ = 0;
      i = input(kReset)->source->trigger_offset;
    }

    offset_ += buffer_size_ * input(kFrequency)->at(0) / sample_rate_;
    offset_ = twytchutils::mod(offset_, &integral);
    current_step_ += integral;
    current_step_ = (current_step_ + num_steps) % num_steps;

    int size = buffer_size_ * sizeof(mopo_float);
    memcpy(output(kValue)->buffer, input(kSteps + current_step_)->source->buffer, size);
    output(kStep)->buffer[0] = current_step_;
  }

  void StepGenerator::correctToTime(mopo_float samples) {
    static mopo_float integral;

    unsigned int num_steps = static_cast<int>(input(kNumSteps)->at(0));
    num_steps = twytchutils::iclamp(num_steps, 1, max_steps_);

    offset_ = samples * input(kFrequency)->at(0) / sample_rate_;
    offset_ = twytchutils::mod(offset_, &integral);
    current_step_ = integral;
    current_step_ = (current_step_ + num_steps) % num_steps;
  }
} // namespace mopo
