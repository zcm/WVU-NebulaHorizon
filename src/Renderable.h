/*
 *  Sprite.h
 *  Nebula Horizon
 *
 *  Created by Zachary Murray on 11/15/09.
 *  Copyright 2009 West Virginia University. All rights reserved.
 *
 */

#ifndef NHZ_RENDERABLE_H
#define NHZ_RENDERABLE_H

class Renderable {
	public:
        virtual void render() = 0;
        virtual void idle(int elapsed);
        virtual void handleKeyboard(unsigned char key, int x, int y);
        virtual void handleSpecialKey(int key, int x, int y);
        virtual void handleMouseEvent(int button, int state, int x, int y);
        virtual void handleMouseDrag(int x, int y);
        virtual void handleMouseMotion(int x, int y);
};

#endif
