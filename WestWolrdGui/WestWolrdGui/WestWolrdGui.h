#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_WestWolrdGui.h"

class WestWolrdGui : public QMainWindow
{
	Q_OBJECT

public:
	WestWolrdGui(QWidget *parent = Q_NULLPTR);

private:
	Ui::WestWolrdGuiClass ui;
};
