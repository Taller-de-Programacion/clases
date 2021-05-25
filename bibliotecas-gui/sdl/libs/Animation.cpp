/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "Area.h"
#include "Animation.h"
#include "SdlTexture.h"

Animation::Animation(const SdlTexture *texture) : texture(texture) {
    /* assumes the frames are squares */
    this->numFrames = this->texture->getHeight() / this->texture->getWidth();
    this->size = this->texture->getWidth();

    assert(this->numFrames > 0);
    assert(this->size > 0);
}

Animation::~Animation() {}

void Animation::update(float dt) {
    this->elapsed += dt;
    /* checks if the frame should be updated based on the time elapsed since the last update */
    while (this->elapsed > this->frameRate) {
        this->advanceFrame();
        this->elapsed -= this->frameRate;
    }
}

/**
 * @brief Renders the animation in the given coordinates.
 *
 * @param renderer Renderer.
 * @param x X coordinate.
 * @param y Y corrdinate.
 */
void Animation::render(const Area &dst, const SDL_RendererFlip &flipType) {
    Area src(0, this->size * this->currentFrame, this->size, this->size);
    this->texture->render(src, dst, flipType);
}

void Animation::advanceFrame() {
    this->currentFrame += 1;
    this->currentFrame = this->currentFrame % this->numFrames; 
}
