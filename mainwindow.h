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
		void mouseMoveEvent(QMouseEvent* event) override;

	private:
		bool validId(uint32_t id) const;

	private:
		QPointF startPoint;
		int rowCount;
		int colCount;
		double radius;
		// bool noUpdateGrid;
		uint32_t id, lastid;
};
