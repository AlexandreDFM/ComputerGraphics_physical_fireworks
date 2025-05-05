/**
 * File Name: Fire.cpp
 * Author: Alexandre Kévin DE FREITAS MARTINS
 * Creation Date: 4/5/2025
 * Description: This is the Fire.cpp
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

#include "Fire.h"

Fire::Fire(int type) :
    m_type(type), m_size(0.35f), m_age(5.0f), m_initialAge(5.0f), m_particle(nullptr), m_rule(nullptr) {
    m_particle = new cyclone::Particle();
    m_particle->setPosition(cyclone::Vector3(0.0f, 0.0f, 0.0f));
    m_particle->setVelocity(cyclone::Vector3(5.0f, 15.0f, 0.0f));
    m_particle->setMass(1.0f);
    m_particle->setDamping(0.99f);
    m_particle->setAcceleration(cyclone::Vector3(0.0f, -9.8f, 0.0f));

    static cyclone::Random randomGenerator;

    m_baseColor = randomGenerator.randomVector(cyclone::Vector3(0.0f, 0.0f, 0.0f), cyclone::Vector3(1.0f, 1.0f, 1.0f));
    m_currentColor = m_baseColor;
}

Fire::~Fire() { delete m_particle; }

bool Fire::update(float duration) {
    if (m_particle) {
        m_particle->integrate(duration);
        putHistory();
        if (m_type == 0 && m_particle->getVelocity().y <= 0) {
            return true;
        }
    }
    m_age -= duration;
    float t = 1.0f - (m_age / m_initialAge);

    m_currentColor.x = m_baseColor.x + t * (1.0f - m_baseColor.x);
    m_currentColor.y = m_baseColor.y + t * (1.0f - m_baseColor.y);
    m_currentColor.z = m_baseColor.z + t * (1.0f - m_baseColor.z);

    return (m_age < 0 || m_particle->getPosition().y < 0);
}

void Fire::draw(int shadow) {
    if (m_particle) {
        cyclone::Vector3 pos = m_particle->getPosition();
        glPushMatrix();
        glTranslatef(static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z));
        if (shadow) {
            glColor4f(0.1f, 0.1f, 0.1f, 0.5f);
        } else {
            float alpha = max(0.0f, m_age / 5.0f);
            glColor4f(static_cast<float>(m_currentColor.x), static_cast<float>(m_currentColor.y), static_cast<float>(m_currentColor.z), alpha);

            if (rand() % 2 == 0) {
                glColor4f(static_cast<float>(m_currentColor.x) * 0.8f, static_cast<float>(m_currentColor.y) * 0.8f, static_cast<float>(m_currentColor.z) * 0.8f, alpha);
            }
        }
        glutSolidSphere(m_size, 20, 20);
        glPopMatrix();
    }
    drawHistory();
}

void Fire::putHistory() {
    if (m_history.size() >= 30) {
        m_history.pop_front();
    }
    m_history.push_back(m_particle->getPosition());
}

void Fire::drawHistory() {
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    for (const auto &pos: m_history) {
        glVertex3f(static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z));
    }
    glEnd();
    glLineWidth(1.0f);
}

void Fire::setRule(FireworksRule *r) { m_rule = r; }