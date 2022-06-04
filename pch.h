#pragma once

#ifndef _SIMBATTLE_PCH_H_
#define _SIMBATTLE_PCH_H_ 1

// STL Headers
#include <cmath>
#include <version>
#include <unordered_map>

// Qt Headers
#include <QApplication>
#include <QDate>
#include <QDebug>
#include <QFile>
#include <QLocale>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QTranslator>

// Thirdparty Headers
#include <thirdparty/json/json.hpp>
using namespace nlohmann;

// Global variables
class Global
{
	private:
		Global() = delete;
		~Global() = delete;
	public:
		enum {
			UNIT_FILE = 0,
			DATA_COUNT
		};
		static uint32_t windowHeight;
		static uint32_t windowWidth;
		static uint32_t rowCount;
		static uint32_t colCount;
		static uint32_t blockRadius;
		static QPointF  startPoint;
		static QString  dataFileNames[DATA_COUNT];
};

// Trait macros
#if __cplusplus < 201103L
	#error "C++ version should be at least C++11"
#elif __cplusplus < 201402L
	#define SIMBATTLE_CXX 11
	#define SIMBATTLE_CXX11
#elif __cplusplus < 201703L
	#define SIMBATTLE_CXX 14
	#define SIMBATTLE_CXX14
#elif __cplusplus < 202002L
	#define SIMBATTLE_CXX 17
	#define SIMBATTLE_CXX17
#else
	#define SIMBATTLE_CXX 20
	#define SIMBATTLE_CXX20
#endif

#if defined(__has_cpp_attribute) && __has_cpp_attribute(likely)
	#define IF_LIKELY(x)	if(x) [[likely]]
	#define IF_UNLIKELY(x)	if(x) [[unlikely]]
#elif SIMBATTLE_CXX >= 11 // Most compiler support likely & unlikely since C++11
	#define IF_LIKELY(x)	if(x) [[likely]]
	#define IF_UNLIKELY(X)	if(x) [[unlikely]]
#else
	#define IF_LIKELY(x)	if(x)
	#define IF_UNLIKELY(x)	if(x)
#endif

#endif // _SIMBATTLE_PCH_H_
