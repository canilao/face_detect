/******************************************************************************/
//
/*! \file   

    \brief  

    \note   

*******************************************************************************/

#ifndef PROXY_OBJECT_H
#define PROXY_OBJECT_H

// Standard dependencies.
#include <memory>

// General dependencies.
#include "ftor.h"
#include "ifuture.h"
#include "icommand.h"
#include "idispatcher.h"

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
template<class RETURN_TYPE>
class IProxy 
{
private:

   // Future object.
   IFuture<RETURN_TYPE> future;

public:

   // Constructor.
   IProxy()
   {
   }

   // Destructor.
   virtual ~IProxy()
   {
   }

   // Executes an operation.
   virtual void Execute(std::auto_ptr<ICommand> cmd, IDispatcher & dispatcher) = 0; 

   // Cancels the job.
   virtual void Cancel() = 0;

   // Gets a reference to the future object.
   const IFuture<RETURN_TYPE> & GetFuture() const
   {
      return future;
   }

};

}

#endif
