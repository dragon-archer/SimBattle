#pragma once

#ifndef _SIMBATTLE_MAINWINDOW_H_
#define _SIMBATTLE_MAINWINDOW_H_ 1

#include "pch.h"

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
		bool validId(uint32_t id) const;

	private:
		QPointF startPoint;
		double radius;
		uint32_t id;
		int rowCount;
		int colCount;
		bool drawShadow;
};

#endif // _SIMBATTLE_MAINWINDOW_H_
