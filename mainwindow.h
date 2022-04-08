#pragma once

#include "pch.h"

class MainWindow : public QMainWindow
{
		Q_OBJECT
	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();

	protected:
		void paintEvent(QPaintEvent* event) override;

	private:
		QPointF startPoint;
		uint rowCount;
		uint colCount;
		uint radius;
};
