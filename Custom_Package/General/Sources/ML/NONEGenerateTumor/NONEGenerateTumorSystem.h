//----------------------------------------------------------------------------------
//! Project global and OS specific declarations.
/*!
// \file    
// \author  LL
*/
//----------------------------------------------------------------------------------


#pragma once


// DLL export macro definition.
#ifdef NONEGENERATETUMOR_EXPORTS
  // Use the NONEGENERATETUMOR_EXPORT macro to export classes and functions.
  #define NONEGENERATETUMOR_EXPORT ML_LIBRARY_EXPORT_ATTRIBUTE
#else
  // If included by external modules, exported symbols are declared as import symbols.
  #define NONEGENERATETUMOR_EXPORT ML_LIBRARY_IMPORT_ATTRIBUTE
#endif
