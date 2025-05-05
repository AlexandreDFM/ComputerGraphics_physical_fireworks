/**
 * File Name: Fire.h
 * Author: Alexandre Kévin DE FREITAS MARTINS
 * Creation Date: 4/5/2025
 * Description: This is the Fire.h
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

#ifndef FIRE_H
#define FIRE_H

#include <deque>
#include "FireworksRule.h"
#include "Vec3f.h"
#include "particle.h"
#include "random.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class FireworksRule;

class Fire {
public:
    explicit Fire(int type);
    ~Fire();

    float m_size; // Fire size
    int m_type; // Fire type (0 = Init Fire, 1 = Child Fire)
    float m_age; // Fire's current age
    float m_initialAge; // Fire's initial age
    cyclone::Particle *m_particle;
    FireworksRule *m_rule; // Rule influencing this particle
    cyclone::Vector3 m_baseColor; // Fire Base color
    cyclone::Vector3 m_currentColor; // Fire Current color
    std::deque<cyclone::Vector3> m_history; // Position history

    bool update(float duration); // Update fire state
    void draw(int shadow); // Draw fire
    void drawHistory(); // Draw fire's history
    void setRule(FireworksRule *r); // Set rule
    void putHistory(); // Save current position in history
};

#endif // FIRE_H
