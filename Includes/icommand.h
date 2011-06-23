/******************************************************************************/
//
/*! \file   

    \brief  

    \note   

*******************************************************************************/

#ifndef COMMAND_OBJECT_H
#define COMMAND_OBJECT_H

// Standard dependencies.
#include <exception>

// General dependencies.

/******************************************************************************/
//
/*! \namespace 

    \brief      

*******************************************************************************/
namespace ActiveObject
{
/******************************************************************************/
//
/*! \class  

    \brief  

*******************************************************************************/
class ICommand
{
public:

   // Constructor.
   ICommand()
   {
   }

   // Destructor.
   virtual ~ICommand()
   {
   }

   // Execute command.
   virtual void Execute() = 0;
   
};

}

#endif
