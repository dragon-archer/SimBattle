#pragma once

#ifndef NDEBUG
	#include <QDebug>
#endif
#include <QApplication>
#include <QLocale>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QTranslator>

// Global variables
class Global
{
	private:
		Global() = delete;
		~Global() = delete;
	public:
		static uint windowHeight;
		static uint windowWidth;
};
