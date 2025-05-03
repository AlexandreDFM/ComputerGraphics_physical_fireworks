/**
 * File Name: FireworksRule.h
 * Author: Alexandre Kévin DE FREITAS MARTINS
 * Creation Date: 4/5/2025
 * Description: This is the FireworksRule.h
 * Copyright (c) 2025 Alexandre Kévin DE FREITAS MARTINS
 * Version: 1.0.0
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the 'Software'), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef FIREWORKSRULE_H
#define FIREWORKSRULE_H

#include "particle.h"

class FireworksRule {
public:
    FireworksRule() = default;
    ~FireworksRule() = default;

    unsigned type; // Fire type
    cyclone::real minAge; // Minimum age of fire
    cyclone::real maxAge; // Maximum age of fire
    cyclone::Vector3 minVelocity; // Minimum velocity
    cyclone::Vector3 maxVelocity; // Maximum velocity
    cyclone::real damping; // Damping factor
    unsigned payloadCount; // Number of child fires spawned

    void setParameters(unsigned type, cyclone::real minAge, cyclone::real maxAge, const cyclone::Vector3 &minVelocity,
                       const cyclone::Vector3 &maxVelocity, cyclone::real damping, int count);
};

#endif // FIREWORKSRULE_H
