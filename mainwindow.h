#pragma once

#ifndef _SIMBATTLE_MAINWINDOW_H_
#define _SIMBATTLE_MAINWINDOW_H_ 1

#include "pch.h"
#include "utility.h"

class MainWindow : public QMainWindow
{
		Q_OBJECT
	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();

	protected:
		void paintEvent(QPaintEvent* event) override;
		void mouseMoveEvent(QMouseEvent* event) override;

	private:
		QPointF startPoint;
		HexPosition mousePos;
		bool drawShadow;
};

#endif // _SIMBATTLE_MAINWINDOW_H_
