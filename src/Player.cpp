/*
 *  Player.cpp
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/24/09.
 *
 */

#include <iostream>
#include <fstream>
#include "WavefrontGLMeshLoader.h"
#include "KeyboardManager.h"
#include "Player.h"

Renderable* Player::_mesh = 0;

Player::Player() {
    initialize();
}

Player::Player(float xVelocity, float yVelocity) {
    initialize(xVelocity, yVelocity);
}

void Player::render() {
    glTranslatef(_x, _y, -10.0f);
    glRotatef(_xAngle, 1.0, 0.0, 0.0);
    glRotatef(_zAngle, 0.0, 0.0, 1.0);
    glScaled(0.35, 0.35, 0.35);
    getMesh().render();
}

void Player::idle(int elapsed) {
    float time = (float)elapsed;
    if(elapsed != 0) {
        _lastX = _x;
        _lastY = _y;
        _lastXAngle = _xAngle;
        _lastZAngle = _zAngle;
        KeyboardManager& keyboard = KeyboardManager::getInstance();
        if(keyboard.isKeyDown('w')) {
            _y += _yVelocity*time/1000;
            _xAngle += _xAngle < 30.0 ? 0.35*time: 0.0;
            if(_xAngle > 30.0) {
                _xAngle = 30.0;
            }
        }
        if(keyboard.isKeyDown('a')) {
            _x -= _xVelocity*time/1000;
            _zAngle += _zAngle < 45.0 ? 1.0*time: 0.0;
            if(_zAngle > 45.0) {
                _zAngle = 45.0;
            }
        }
        if(keyboard.isKeyDown('s')) {
            _y -= _yVelocity*time/1000;
            _xAngle -= _xAngle > -30.0 ? 0.35*time: 0.0;
            if(_xAngle < -30.0) {
                _xAngle = -30.0;
            }
        }
        if(keyboard.isKeyDown('d')) {
            _x += _xVelocity*time/1000;
            _zAngle -= _zAngle > -45.0 ? 1.0*time: 0.0;
            if(_zAngle < -45.0) {
                _zAngle = -45.0;
            }
        }
        if(!keyboard.isKeyDown('a') && !keyboard.isKeyDown('d')) {
            if(_zAngle != 0.0) {
                std::cerr << "_zAngle: " << _zAngle << " ";
                _zAngle += (_zAngle > 0 ? -0.9 : 0.9)*time;
            }
            if((_lastZAngle < 0.0 && _zAngle > 0.0) ||
               (_lastZAngle > 0.0 && _zAngle < 0.0)) {
                _zAngle = 0.0;
            }
        }
        if(!keyboard.isKeyDown('w') && !keyboard.isKeyDown('s')) {
            if(_xAngle != 0.0) {
                std::cerr << "_xAngle: " << _xAngle << std::endl << std::endl;
                _xAngle += (_xAngle > 0 ? -0.4 : 0.4)*time;
            }
            if((_lastXAngle < 0.0 && _xAngle > 0.0) ||
               (_lastXAngle > 0.0 && _xAngle < 0.0)) {
                _xAngle = 0.0;
            }
        }
    }
}

Renderable& Player::getMesh() {
    if(_mesh == 0) {
        std::ifstream viper_file("viper.obj");
        MeshLoader* loader = new WavefrontGLMeshLoader;
        _mesh = loader->loadMesh(viper_file);
        delete loader;
    }
    return *_mesh;
}

void Player::initialize() {
    initialize(1.0f, 1.0f);
}

void Player::initialize(float xVelocity, float yVelocity) {
    _x = 0.0f;
    _y = 0.0f;
    _lastX = 0.0f;
    _lastY = 0.0f;
    _xVelocity = xVelocity;
    _yVelocity = yVelocity;
    _xAngle = 0.0;
    _zAngle = 0.0;
    _lastXAngle = 0.0;
    _lastZAngle = 0.0;
}
