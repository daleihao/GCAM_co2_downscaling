#ifndef _MAGICC_MODEL_H_
#define _MAGICC_MODEL_H_
#if defined(_MSC_VER)
#pragma once
#endif

/*! 
* \file magicc.h
* \ingroup Objects
* \brief The MagiccModel header file.
* \author Josh Lurz
* \date $Date$
* \version $Revision$
*/

#include <string>
#include <vector>
#include "climate/include/iclimate_model.h"

class Modeltime;
/*! 
* \ingroup Objects
* \brief An implementation of the IClimateModel interface using the MAGICC
*        climate module.
* \details The MagiccModel performs climate calculations by passing data to and
*          from the MAGICC fortran module. No climate calculating code is
*          contained in the C++ MagiccModel code. This wrapper is responsible
*          for reading in a set of default gas emissions for each gas by period,
*          overriding those with values from the model where calculated, and
*          interpolating them into a set of inputs for MAGICC. It then writes
*          those values to a file and calls MAGICC to calculate climate
*          parameters. A subset of those output can then be written by this
*          wrapper to the database and a CSV file.
* \author Josh Lurz
* \date $Date$
* \version $Revision$
*/

class MagiccModel: public IClimateModel {
public:
    MagiccModel( const Modeltime* aModeltime );
    void completeInit( const std::string& aScenarioName );
    bool setEmissions( const std::string& aGasName, const int aPeriod, const double aEmission );
    bool runModel();
    void printFileOutput() const;
    void printDBOutput() const;
private:
    int getGasIndex( const std::string& aGasName ) const;
	static unsigned int getNumGases();
    void readFile();
    
	//! A fixed list of the gases Magicc reads in.
	static const std::string sGasNames[];
	
	//! Return value of getGasIndex if it cannot find the gas.
    static const int INVALID_GAS_NAME = -1;
	
	//! Emissions levels by gas and period.
    std::vector<std::vector<double> > mEmissionsByGas;

	//! Name of the scenario.
    std::string mScenarioName;

	//! A reference to the scenario's modeltime object.
    const Modeltime* mModeltime;
};

#endif // _MAGICC_MODEL_H_