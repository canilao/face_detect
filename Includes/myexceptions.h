/******************************************************************************/
//
/*! \file

    \brief

    \note

*******************************************************************************/

#ifndef MYEXCEPTIONS_H
#define MYEXCEPTIONS_H

// Standard dependencies.
#include <exception>

// General dependencies.

/******************************************************************************/
//
/*! \namespace

    \brief

*******************************************************************************/
namespace FaceDetect
{
/******************************************************************************/
//
/*! \class

    \brief

*******************************************************************************/
class PthreadCreateFailed : public std::exception
{
    virtual const char * what() const throw()
    {
        return "pthread_create failed";
    }
};

/******************************************************************************/
//
/*! \class

    \brief

*******************************************************************************/
class LoadFaceDetectorFailed : public std::exception
{
    virtual const char * what() const throw()
    {
        return "face detector failed to load";
    }
};

/******************************************************************************/
//
/*! \class

    \brief

*******************************************************************************/
class FutureRequestedTooSoon : public std::exception
{
    virtual const char * what() const throw()
    {
        return "client requested future object too soon";
    }
};

/******************************************************************************/
//
/*! \class

    \brief

*******************************************************************************/
class InvalidFutureValue : public std::exception
{
    virtual const char * what() const throw()
    {
        return "future value is being set incorrectly";
    }
};

}

#endif
