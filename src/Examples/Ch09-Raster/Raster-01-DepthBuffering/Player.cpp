//===============================================================================
// @ Player.cpp
// ------------------------------------------------------------------------------
// Player
//
// Copyright (C) 2007 by Elsevier, Inc. All rights reserved.
//
//
//
//
//===============================================================================

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include <IvEventHandler.h>
#include <IvRenderer.h>
#include <IvRendererHelp.h>
#include <IvIndexBuffer.h>
#include <IvMath.h>
#include <IvMatrix44.h>
#include <IvResourceManager.h>
#include <IvShaderProgram.h>
#include <IvUniform.h>
#include <IvVertexBuffer.h>

#include "Player.h"
#include "Game.h"

//-------------------------------------------------------------------------------
//-- Static Members -------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ Player::Player()
//-------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------
Player::Player()
{
    mRotate.Identity();
    mTranslate.Set(0.0f, 0.0f, 0.0f);
    mScale = 3.0f;

    mShader = IvRenderer::mRenderer->GetResourceManager()->CreateShaderProgram(
        IvRenderer::mRenderer->GetResourceManager()->CreateVertexShaderFromFile(
        "uniformShader"),
        IvRenderer::mRenderer->GetResourceManager()->CreateFragmentShaderFromFile(
        "uniformShader"));

    mColor = mShader->GetUniform("constColor");

    mColor->SetValue(IvVector4(1.0f, 0.0f, 0.0f, 1.0f), 0);

    IvRenderer::mRenderer->SetShaderProgram(mShader);

    CreateQuad();
}   // End of Player::Player()


//-------------------------------------------------------------------------------
// @ Player::~Player()
//-------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------
Player::~Player()
{
}   // End of Player::~Player()


//-------------------------------------------------------------------------------
// @ Player::Update()
//-------------------------------------------------------------------------------
// Main update loop
//-------------------------------------------------------------------------------
void
Player::Update( float dt )
{
    // get scale, rotate, translate for this frame
    float s = 1.0f;
    float r = 0.0f;

    // set up scaling
    if (IvGame::mGame->mEventHandler->IsKeyDown(';'))
    {
        s -= 0.25f*dt;
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('p'))
    {
        s += 0.25f*dt;
    }
    mScale *= s;
    
    // set up rotate
    if (IvGame::mGame->mEventHandler->IsKeyDown('o'))
    {
        r -= kPI*0.25f*dt;
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('u'))
    {
        r += kPI*0.25f*dt;
    }
    IvMatrix33 rotate;
    rotate.RotationY(r);
    mRotate = rotate*mRotate;
    
    // set up translation
    IvVector3 xlate;
    xlate.Zero();
    if (IvGame::mGame->mEventHandler->IsKeyDown('k'))
    {
        xlate.SetX( xlate.GetX() - 3.0f*dt);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('i'))
    {
        xlate.SetX( xlate.GetX() + 3.0f*dt);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('l'))
    {
        xlate.SetY( xlate.GetY() - 3.0f*dt);
    }
    if (IvGame::mGame->mEventHandler->IsKeyDown('j'))
    {
        xlate.SetY( xlate.GetY() + 3.0f*dt);
    }
    mTranslate += xlate;
    
    // clear transform
    if (IvGame::mGame->mEventHandler->IsKeyDown(' '))
    {
        mRotate.Identity();
        mTranslate.Set(0.0f, 0.0f, 0.0f);
        mScale = 3.0f;
    }

}   // End of Player::Update()


//-------------------------------------------------------------------------------
// @ Player::Render()
//-------------------------------------------------------------------------------
// Render stuff
//-------------------------------------------------------------------------------
void 
Player::Render()                                    
{   
    // Draw backdrop quad, which must also write the depth buffer
    mColor->SetValue(IvVector4(0.5f, 0.5f, 0.5f, 1.0f), 0);
    IvRenderer::mRenderer->SetDepthWrite(true);
    IvRenderer::mRenderer->SetDepthTest(kLessEqualDepthTest);

    DrawQuad();

    // build 4x4 matrix for left (non-depth-buffered) teapot
    IvMatrix44 transform(mRotate);

    transform(0,0) *= mScale;
    transform(1,0) *= mScale;
    transform(2,0) *= mScale;
    transform(0,1) *= mScale;
    transform(1,1) *= mScale;
    transform(2,1) *= mScale;
    transform(0,2) *= mScale;
    transform(1,2) *= mScale;
    transform(2,2) *= mScale;
    transform(0,3) = mTranslate.GetX();
    transform(1,3) = mTranslate.GetY() + 4.0f;
    transform(2,3) = mTranslate.GetZ();
    
    ::IvSetWorldMatrix(transform);

    // draw non-depth-buffered teapot
    mColor->SetValue(IvVector4(1.0f, 0.0f, 0.0f, 1.0f), 0);
    IvRenderer::mRenderer->SetDepthWrite(false);
    IvRenderer::mRenderer->SetDepthTest(kDisableDepthTest);
    
    IvColor white = {255, 255, 255};
    IvDrawTeapot(white, false);
    
    // same as other teapot, but on the right side
    transform(1,3) = mTranslate.GetY() - 4.0f;

    ::IvSetWorldMatrix(transform);
    
    // draw depth-buffered teapot
    mColor->SetValue(IvVector4(0.0f, 0.0f, 1.0f, 1.0f), 0);
    IvRenderer::mRenderer->SetDepthWrite(true);
    IvRenderer::mRenderer->SetDepthTest(kLessEqualDepthTest);

    IvDrawTeapot(white, false);
    
}   // End of Player::Render()


//-------------------------------------------------------------------------------
// @ Player::DrawQuad()
//-------------------------------------------------------------------------------
// Draw a quad, centered around the origin
//-------------------------------------------------------------------------------
void 
Player::DrawQuad()                                  
{   
    IvRenderer::mRenderer->Draw(kTriangleStripPrim, mQuadVerts, mQuadIndices);

}   // End of Player::DrawQuad()

//-------------------------------------------------------------------------------
// @ Player::CreateQuad()
//-------------------------------------------------------------------------------
// Create a quad, centered around the origin
//-------------------------------------------------------------------------------
void 
Player::CreateQuad() 
{
    const float size = 7.0f;

    mQuadVerts = IvRenderer::mRenderer->GetResourceManager()->CreateVertexBuffer(
        kNPFormat, 4);

    // temporary pointers that can be stepped along the arrays
    IvNPVertex* tempVerts = (IvNPVertex*)(mQuadVerts->BeginLoadData());

    tempVerts->normal = IvVector3(-1.0f, 0.0f, 0.0f);
    tempVerts->position = IvVector3(0.0f, -size, size);
    tempVerts++;

    tempVerts->normal = IvVector3(-1.0f, 0.0f, 0.0f);
    tempVerts->position = IvVector3(0.0f, size, size);
    tempVerts++;

    tempVerts->normal = IvVector3(-1.0f, 0.0f, 0.0f);
    tempVerts->position = IvVector3(0.0f, -size, -size);
    tempVerts++;

    tempVerts->normal = IvVector3(-1.0f, 0.0f, 0.0f);
    tempVerts->position = IvVector3(0.0f, size, -size);
    tempVerts++;

    mQuadVerts->EndLoadData();

    mQuadIndices = IvRenderer::mRenderer->GetResourceManager()->
        CreateIndexBuffer(4);

    unsigned int* tempIndices = (unsigned int*)(mQuadIndices->BeginLoadData());

    int j;
    for (j = 0; j < 4; j++)
        *(tempIndices++) = j;

    mQuadIndices->EndLoadData();
}
