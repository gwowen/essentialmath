//===============================================================================
// @ Obstacle.cpp
// ------------------------------------------------------------------------------
// Obstacle
//
// Copyright (C) 2008 by Elsevier, Inc. All rights reserved.
//
// This is an obstacle for the player to hit.  It is derived from SimObject, 
// so all the integration and collision detection code can be found there.  
//
//===============================================================================

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include <IvEventHandler.h>

#include "Obstacle.h"
#include "Game.h"

//-------------------------------------------------------------------------------
//-- Static Members -------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ Obstacle::Obstacle()
//-------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------
Obstacle::Obstacle() : SimObject()
{
    mTranslate.Set( 0.0f, 3.0f, 0.0f );

    SetMass( 10.0f );
    mElasticity = 0.25f;
    
}   // End of Obstacle::Obstacle()


//-------------------------------------------------------------------------------
// @ Obstacle::~Obstacle()
//-------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------
Obstacle::~Obstacle()
{
}   // End of Obstacle::~Obstacle()


//-------------------------------------------------------------------------------
// @ Obstacle::Update()
//-------------------------------------------------------------------------------
// Main update loop
//-------------------------------------------------------------------------------
void
Obstacle::Update( float dt )
{   
    if (IvGame::mGame->mEventHandler->IsKeyDown(' '))
    {
        mTranslate.Set( 0.0f, 3.0f, 0.0f );
        mRotate.Identity();
        mVelocity.Zero();
        mAngularMomentum.Zero();
        mAngularVelocity.Zero();
    }

    SimObject::Update( dt );
}
