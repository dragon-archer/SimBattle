#include "pch.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, startPoint(Global::startPoint)
	, drawShadow(false) {
	IF_UNLIKELY(!initComponents()) {
		qCritical("Failed to init components");
		QMessageBox::critical(this, tr("Error"), tr("Failed to init components"), QMessageBox::Ok, QMessageBox::Ok);
		exitProgram(1);
		return;
	}
	this->setFixedSize(Global::windowWidth, Global::windowHeight);
	grabMouse();
	grabKeyboard();
	setMouseTracking(true);
}

MainWindow::~MainWindow() {
}

bool MainWindow::initComponents() {
	IF_UNLIKELY(!Unit::initDataMap()) {
		qCritical("Unit::initDataMap() failed");
		return false;
	} else {
		qDebug("Unit::initDataMap() success");
	}
	return true;
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
	IF_LIKELY(mousePos == lastPos)
		return;
	lastPos = mousePos;
	if(mousePos.isValid()) {
		drawShadow = true;
		update();
	} else {
		drawShadow = false;
		update();
	}
}
