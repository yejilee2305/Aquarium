/**
 * @file pch.h
 * @author Yeji Lee
 *
 * Precompiled header file for the application
 *
 * Includes necessary precompiled headers for the wxWidgets library,
 * which helps to speed up compilation time.
 *
 * Ensures that wxWidgets headers are only included once and optimizes
 * the compilation process by precompiling them.
 */
 
#ifndef PCH_H
#define PCH_H

// Include the precompiled headers for wxWidgets
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
// If WX_PRECOMP is not defined, include the full wxWidgets headers
#include <wx/wx.h>
#endif

#include <wx/xml/xml.h>
#endif //PCH_H
