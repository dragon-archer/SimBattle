#include "pch.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), startPoint(Global::startPoint), drawShadow(false) {
	if(!loadResource()) {
		QMessageBox::critical(this, tr("Error"), tr("Failed to load resource file!"), QMessageBox::Ok, QMessageBox::Ok);
		exitProgram();
		return;
	}
	this->setFixedSize(Global::windowWidth, Global::windowHeight);
	grabMouse();
	grabKeyboard();
	setMouseTracking(true);
}

MainWindow::~MainWindow() {
}

void MainWindow::paintEvent(QPaintEvent* event) {
	QPainter painter;
	setupPainter(painter, this);
	drawGrid(painter);
	if(drawShadow) {
		drawHexagon(painter, startPoint + mousePos.toCorner());
	}
	painter.end();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
	static HexPosition lastPos;
	// Change the coordinate
	double x = event->position().x() - startPoint.x(),
		   y = this->height() - event->position().y() - startPoint.y();
	mousePos = posToHex(x, y);
	IF_LIKELY(mousePos == lastPos) return;
	lastPos = mousePos;
	if(mousePos.isValid()) {
		drawShadow = true;
		update();
	} else {
		drawShadow = false;
		update();
	}
}
