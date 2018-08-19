//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2015-2018, Lawrence Livermore National Security, LLC.
// 
// Produced at the Lawrence Livermore National Laboratory
// 
// LLNL-CODE-716457
// 
// All rights reserved.
// 
// This file is part of Ascent. 
// 
// For details, see: http://ascent.readthedocs.io/.
// 
// Please also read ascent/LICENSE
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice, 
//   this list of conditions and the disclaimer below.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the disclaimer (as noted below) in the
//   documentation and/or other materials provided with the distribution.
// 
// * Neither the name of the LLNS/LLNL nor the names of its contributors may
//   be used to endorse or promote products derived from this software without
//   specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY,
// LLC, THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
// DAMAGES  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------------------------------------
///
/// file: ascent_runtime_entropy_trigger.cpp
///
//-----------------------------------------------------------------------------

#include "ascent_runtime_triggers.hpp"

//-----------------------------------------------------------------------------
// thirdparty includes
//-----------------------------------------------------------------------------

#ifdef ASCENT_MPI_ENABLED
#include <mpi.h>
#endif

using namespace conduit;
using namespace std;

using namespace flow;

//-----------------------------------------------------------------------------
// -- begin ascent:: --
//-----------------------------------------------------------------------------
namespace ascent
{

//-----------------------------------------------------------------------------
// -- begin ascent::runtime --
//-----------------------------------------------------------------------------
namespace runtime
{

//-----------------------------------------------------------------------------
// -- begin ascent::runtime::filters --
//-----------------------------------------------------------------------------
namespace filters
{

;
//-----------------------------------------------------------------------------
EntropyTrigger::EntropyTrigger()
: TriggerFilter(true, false, false)
{
// empty
}

//-----------------------------------------------------------------------------
EntropyTrigger::~EntropyTrigger()
{
// empty
}

//-----------------------------------------------------------------------------
bool   
EntropyTrigger::verify_params(const conduit::Node &params,
                              conduit::Node &info)
{
    bool res = TriggerFilter::verify_params(params, info);
    if(! params.has_child("threshold") || 
       ! params["threshold"].dtype().is_number() )
    {
        info["errors"].append() = "Missing required string parameter 'threshold'";
        res = false;
    }
    std::cout<<"Verified entropy "<<res<<"\n";
    return res;
}

//-----------------------------------------------------------------------------

std::string  
EntropyTrigger::get_type_name()
{
  return "entropy_trigger";
}

//-----------------------------------------------------------------------------
bool
EntropyTrigger::trigger()
{
  //field.print();
  // TODO generalize to any data type
  // this is not always a double
  const conduit::Node &field = this->get_field();
  const float64 *vals = field["values"].as_float64_ptr();

  const int32 field_size = field["values"].dtype().number_of_elements();
  std::cout<<"number of elements "<<field_size<<"\n";
  
  return true;
}

//-----------------------------------------------------------------------------
StateThresholdTrigger::StateThresholdTrigger()
: TriggerFilter(false, true, false)
{
// empty
}

//-----------------------------------------------------------------------------
StateThresholdTrigger::~StateThresholdTrigger()
{
// empty
}

std::string  
StateThresholdTrigger::get_type_name()
{
  return "state_threshold_trigger";
}

//-----------------------------------------------------------------------------
bool
StateThresholdTrigger::trigger()
{
  //field.print();
  // TODO generalize to any data type
  // this is not always a double
  const conduit::Node &state = this->get_state();
  float64 threshold = params()["threshold"].to_float64();
  const float64 val = state.to_float64();
  
  //const int32 field_size = field["values"].dtype().number_of_elements();
  //std::cout<<"number of elements "<<field_size<<"\n";
  
  return true;
}

bool   
StateThresholdTrigger::verify_params(const conduit::Node &params,
                              conduit::Node &info)
{
    bool res = TriggerFilter::verify_params(params, info);
    if(! params.has_child("threshold") || 
       ! params["threshold"].dtype().is_number() )
    {
        info["errors"].append() = "Missing required string parameter 'threshold'";
        res = false;
    }
    std::cout<<"Verified state threshold "<<res<<"\n";
    return res;
}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
// -- end ascent::runtime::filters --
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
// -- end ascent::runtime --
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
// -- end ascent:: --
//-----------------------------------------------------------------------------




