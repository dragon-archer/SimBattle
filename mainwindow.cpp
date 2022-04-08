#include "pch.h"
#include "mainwindow.h"
#include "utility.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent) {
	this->setFixedSize(Global::windowWidth, Global::windowHeight);
	rowCount = 30;
	colCount = 19;
	radius = 20;
	startPoint = {50, 50};
}

MainWindow::~MainWindow() {
}

void MainWindow::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setWindow(0, this->height(), this->width(), -1 * this->height());
	QPen pen;
	pen.setColor(Qt::red);
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(1);
	painter.setPen(pen);
	drawGrid(painter, startPoint, rowCount, colCount, radius);
	painter.end();
}
