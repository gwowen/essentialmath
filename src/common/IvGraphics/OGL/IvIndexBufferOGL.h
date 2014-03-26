//===============================================================================
// @ IvIndexBufferOGL.h
// 
// Description
// ------------------------------------------------------------------------------
// Copyright (C) 2008   Elsevier, Inc.
//
// Change history:
//
// Usage notes
//===============================================================================

#ifndef __IvIndexBufferOGL__h__
#define __IvIndexBufferOGL__h__

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include "../IvIndexBuffer.h"
#ifdef PLATFORM_OSX
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class IvIndexBufferOGL : private IvIndexBuffer
{
public:
    // interface routines
    void* BeginLoadData();
    bool  EndLoadData();

    friend class IvResourceManagerOGL;
    friend class IvRendererOGL;
    
private:
    // constructor/destructor
    IvIndexBufferOGL(); 
	~IvIndexBufferOGL();

    // creation 
    bool Create( unsigned int numVertices );
    
    // destruction
    void Destroy();
    
    // activate
    bool MakeActive();
    
private:
    // copy operations
    IvIndexBufferOGL(const IvIndexBufferOGL& other);
	IvIndexBufferOGL& operator=(const IvIndexBufferOGL& other);

	GLuint mBufferID;
};


//-------------------------------------------------------------------------------
//-- Inlines --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Externs --------------------------------------------------------------------
//-------------------------------------------------------------------------------

#endif
