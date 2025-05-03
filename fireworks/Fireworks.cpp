/**
 * File Name: Fireworks.cpp
 * Author: Alexandre Kévin DE FREITAS MARTINS
 * Creation Date: 4/5/2025
 * Description: This is the Fireworks.cpp
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

#include "Fireworks.h"

Fireworks::Fireworks() {
    m_rule[0].setParameters(1, 2.0f, 5.0f, cyclone::Vector3(-5, 10, -5), cyclone::Vector3(5, 15, 5), 0.9f, 20);
    m_rule[1].setParameters(1, 3.0f, 8.0f, cyclone::Vector3(-15, 5, -5), cyclone::Vector3(15, 6, 15), 0.2f, 40);
    m_rule[2].setParameters(1, 4.0f, 10.0f, cyclone::Vector3(-5, 0, -5), cyclone::Vector3(5, 5, 5), 0.7f, 25);
}

Fireworks::~Fireworks() {
    for (Fire *fire : fireworks) {
        delete fire;
    }
    fireworks.clear();
}

void Fireworks::update(float duration) {
    std::vector<Fire *> toRemove;

    for (auto iter = fireworks.begin(); iter != fireworks.end();) {
        Fire *fire = *iter;
        if (fire->update(duration)) {
            if (fire->m_type == 0) {
                toRemove.push_back(fire);
            }
            iter = fireworks.erase(iter);
        } else {
            ++iter;
        }
    }

    for (Fire *fire : toRemove) {
        create(fire);
        delete fire;
    }
}

void Fireworks::create() {
    cyclone::Random randomGenerator;

    for (int i = 0; i < 5; ++i) {
        Fire *fire = new Fire(0);
        fire->setRule(&m_rule[rand() % 3]);

        fire->m_particle->setPosition(cyclone::Vector3(
            randomGenerator.randomReal(-5.0f, 5.0f),
            0.0f,
            randomGenerator.randomReal(-5.0f, 5.0f)
        ));

        fire->m_particle->setVelocity(randomGenerator.randomVector(
            cyclone::Vector3(0.0f, 30.0f, 0.0f),
            randomGenerator.randomVector(
                cyclone::Vector3(-10.0f, 60.0f, -10.0f),
                cyclone::Vector3(10.0f, 60.0f, 10.0f)
            )
        ));

        fire->m_particle->setAcceleration(cyclone::Vector3(0.0f, -9.8f, 0.0f));

        fire->m_particle->setDamping(0.99f);

        fireworks.push_back(fire);
    }
}

void Fireworks::create(Fire *parent) {
    FireworksRule *rule = parent->m_rule;
    cyclone::Random randomGenerator;

    for (unsigned i = 0; i < rule->payloadCount; ++i) {
        Fire *child = new Fire(1);

        child->m_particle->setPosition(parent->m_particle->getPosition());

        cyclone::Vector3 velocity = parent->m_particle->getVelocity();
        velocity += randomGenerator.randomVector(rule->minVelocity, rule->maxVelocity);
        child->m_particle->setVelocity(velocity);

        child->m_particle->setAcceleration(cyclone::Vector3(0.0f, -9.8f, 0.0f));

        child->m_particle->setDamping(rule->damping);

        child->m_age = randomGenerator.randomReal(rule->minAge, rule->maxAge);

        child->setRule(rule);
        fireworks.push_back(child);
    }
}

void Fireworks::draw(int shadow) {
    for (Fire *fire : fireworks) {
        fire->draw(shadow);
    }
}

void Fireworks::drawHistory() {
    for (Fire *fire : fireworks) {
        fire->drawHistory();
    }
}
