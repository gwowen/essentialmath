//===============================================================================
// @ IvIndexedGeometry.h
// 
// Concrete class that implements rendering of an indexed triangle set as a set
// of vertex arrays
// ------------------------------------------------------------------------------
// Copyright (C) 2008 by Elsevier, Inc. All rights reserved.
//
//===============================================================================

#ifndef __IvIndexedGeometry__h__
#define __IvIndexedGeometry__h__

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "IvGeometry.h"
#include <IvReader.h>
#include <IvWriter.h>

class IvVector3;
class IvVertexBuffer;
class IvIndexBuffer;

//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class IvIndexedGeometry : public IvGeometry
{
public:
    // constructor/destructor
    IvIndexedGeometry();
    virtual ~IvIndexedGeometry();

    static IvIndexedGeometry* CreateFromStream(IvReader& in);

    virtual void Render();
    
protected:
    // geometry
    IvVertexBuffer* mVertices;
	IvIndexBuffer*  mIndices;

};

//-------------------------------------------------------------------------------
//-- Inlines --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Externs --------------------------------------------------------------------
//-------------------------------------------------------------------------------

#endif
