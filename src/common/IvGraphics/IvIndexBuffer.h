//===============================================================================
// @ IvIndexBuffer.h
// 
// Description
// ------------------------------------------------------------------------------
// Copyright (C) 2008  Elsevier, Inc.
//
// Usage notes
//===============================================================================

#ifndef __IvIndexBuffer__h__
#define __IvIndexBuffer__h__

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class IvIndexBuffer
{
public:
    // interface routines
    // For now, all index buffers are unsigned int (32 bit)
    virtual void* BeginLoadData() = 0;
    virtual bool  EndLoadData() = 0;

    inline unsigned int GetNumIndices() { return mNumIndices; }

protected:
    // constructor/destructor
    IvIndexBuffer() : mNumIndices(0) {}
	virtual ~IvIndexBuffer() {}

    unsigned int        mNumIndices;

private:
    // copy operations (unimplemented so we can't copy)
    IvIndexBuffer(const IvIndexBuffer& other);
	IvIndexBuffer& operator=(const IvIndexBuffer& other);
}; 

//-------------------------------------------------------------------------------
//-- Inlines --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Externs --------------------------------------------------------------------
//-------------------------------------------------------------------------------

#endif
