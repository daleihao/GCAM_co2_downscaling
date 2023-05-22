#ifndef __EMISS_DOWNSCALE__
#define __EMISS_DOWNSCALE__

/*
 * LEGAL NOTICE
 * This computer software was prepared by Battelle Memorial Institute,
 * hereinafter the Contractor, under Contract No. DE-AC05-76RL0 1830
 * with the Department of Energy (DOE). NEITHER THE GOVERNMENT NOR THE
 * CONTRACTOR MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY
 * LIABILITY FOR THE USE OF THIS SOFTWARE. This notice including this
 * sentence must appear on any copies of this computer software.
 *
 * EXPORT CONTROL
 * User agrees that the Software will not be shipped, transferred or
 * exported into any country or used in any manner prohibited by the
 * United States Export Administration Act or any other applicable
 * export laws, restrictions or regulations (collectively the "Export Laws").
 * Export of the Software may require some form of license or other
 * authority from the U.S. Government, and failure to obtain such
 * export control license may result in criminal liability under
 * U.S. laws. In addition, if the Software is identified as export controlled
 * items under the Export Laws, User represents and warrants that User
 * is not a citizen, or otherwise located within, an embargoed nation
 * (including without limitation Iran, Syria, Sudan, Cuba, and North Korea)
 *     and that User is not otherwise prohibited
 * under the Export Laws from receiving the Software.
 *
 * Copyright 2011 Battelle Memorial Institute.  All Rights Reserved.
 * Distributed as open-source under the terms of the Educational Community
 * License version 2.0 (ECL 2.0). http://www.opensource.org/licenses/ecl2.php
 *
 * For further details, see: http://www.globalchange.umd.edu/models/gcam/
 *
 */

// include standard libraries
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <list>
#include <vector>

#include "../include/aspatial_data.h"

class EmissDownscale : public ASpatialData
{
public:
    EmissDownscale(int aNumLon, int aNumLat, int aNumMon, int aNumLev);
    ~EmissDownscale();
    // TODO: Eventually these will need to be vectors of regional emissions instead of global totals
    void downscaleSurfaceCO2Emissions(double *aCurrYearEmissions);
    void downscaleAircraftCO2Emissions(double *aCurrYearEmissions);
    void separateMonthlyEmissions(double *gcamoco2sfcjan, double *gcamoco2sfcfeb, double *gcamoco2sfcmar,
                                  double *gcamoco2sfcapr, double *gcamoco2sfcmay, double *gcamoco2sfcjun,
                                  double *gcamoco2sfcjul, double *gcamoco2sfcaug, double *gcamoco2sfcsep,
                                  double *gcamoco2sfcoct, double *gcamoco2sfcnov, double *gcamoco2sfcdec,
                                  int aNumLon, int aNumLat);
    void separateMonthlyEmissionsWithVertical(double *gcamoco2airlojan, double *gcamoco2airlofeb, double *gcamoco2airlomar,
                                              double *gcamoco2airloapr, double *gcamoco2airlomay, double *gcamoco2airlojun,
                                              double *gcamoco2airlojul, double *gcamoco2airloaug, double *gcamoco2airlosep,
                                              double *gcamoco2airlooct, double *gcamoco2airlonov, double *gcamoco2airlodec,
                                              double *gcamoco2airhijan, double *gcamoco2airhifeb, double *gcamoco2airhimar,
                                              double *gcamoco2airhiapr, double *gcamoco2airhimay, double *gcamoco2airhijun,
                                              double *gcamoco2airhijul, double *gcamoco2airhiaug, double *gcamoco2airhisep,
                                              double *gcamoco2airhioct, double *gcamoco2airhinov, double *gcamoco2airhidec,
                                              int aNumLon, int aNumLat);
    void readRegionalMappingData(std::string aFileName);
    void readRegionalBaseYearEmissionData(std::string aFileName);
    double aBaseYearEmissions_sfc[32];
    double aBaseYearEmissions_air[32];

private:
    std::vector<double> mBaseYearEmissVector;
    std::vector<double> mCurrYearEmissVector;

    // Number of latitude, longitude, and PFTs. Storing this so it doesn't have to be passed to every method
    int mNumLat;
    int mNumLon;
    int mNumMon;
    int mNumLev;


    
    //double aBaseYearEmissions_R[32] = {9663.0297,9663.0297,9663.0297,9663.0297,9663.0297,9663.0297,
    //                                   9663.0297,9663.0297,9663.0297,9663.0297,9663.0297,9663.0297,
    //                                   9663.0297,9663.0297,9663.0297,9663.0297,9663.0297,9663.0297,
    //                                   9663.0297,9663.0297,9663.0297,9663.0297,9663.0297,9663.0297,
    //                                   9663.0297,9663.0297,9663.0297,9663.0297,9663.0297,9663.0297,
    //                                   9663.0297,9663.0297};

    // Map grid cells to regions. Key is a string with longitude and latitude ("lon_lat").
    // Key maps to a vector of strings containing the region
    // Note that this map will be longer than lat * lon since some grid cells map to multiple regions
    std::map<std::string, std::vector<std::string>> mRegionMapping;

    // Map region weights (these indicate the fraction of a grid cell assigned to each region)
    // Key is a pair indicating the grid cell and the region/subregion
    // Key maps to a double representing the fraction of the grid cell in that region/subregion
    std::map<std::pair<std::string,std::string>, double> mRegionWeights;

    //! Map Region -> ID
     /*  {"Africa_Eastern", 1},
        {"Africa_Northern", 2},
        {"Africa_Southern", 3},
        {"Africa_Western", 4},
        {"Argentina", 5},
        {"Australia_NZ", 6},
        {"Brazil", 7},
        {"Canada", 8},
        {"CentralAmericaandCaribbean", 9},
        {"CentralAsia", 10},
        {"China", 11},
        {"Colombia", 12},
        {"EU-12", 13},
        {"EU-15", 14},
        {"Europe_Eastern", 15},
        {"Europe_Non_EU", 16},
        {"EuropeanFreeTradeAssociation", 17},
        {"India", 18},
        {"Indonesia", 19},
        {"Japan", 20},
        {"Mexico", 21},
        {"MiddleEast", 22},
        {"Pakistan", 23},
        {"Russia", 24},
        {"SouthAfrica", 25},
        {"SouthAmerica_Northern", 26},
        {"SouthAmerica_Southern", 27},
        {"SouthAsia", 28},
        {"SoutheastAsia", 29},
        {"SouthKorea", 30},
        {"Taiwan", 31},
        {"USA", 32}*/ 
    std::map<std::string, int> mRegionIDName{
        {"USA", 1},
        {"Africa_Eastern", 2},
        {"Africa_Northern", 3},
        {"Africa_Southern", 4},
        {"Africa_Western", 5},
        {"Australia_NZ", 6},
        {"Brazil", 7},
        {"Canada", 8},
        {"CentralAmericaandCaribbean", 9},
        {"CentralAsia", 10},
        {"China", 11},
        {"EU-12", 12},
        {"EU-15", 13},
        {"Europe_Eastern", 14},
        {"Europe_Non_EU", 15},
        {"EuropeanFreeTradeAssociation", 16},
        {"India", 17},
        {"Indonesia", 18},
        {"Japan", 19},
        {"Mexico", 20},
        {"MiddleEast", 21},
        {"Pakistan", 22},
        {"Russia", 23},
        {"SouthAfrica", 24},
        {"SouthAmerica_Northern", 25},
        {"SouthAmerica_Southern", 26},
        {"SouthAsia", 27},
        {"SouthKorea", 28},
        {"SoutheastAsia", 29}, 
        {"Taiwan", 30},
        {"Argentina", 31},
        {"Colombia", 32}
    };
};

#endif // __EMISS_DOWNSCALE__
