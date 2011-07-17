#include <QtGui>
#include "mainwindow.h"

/*Copyright (C) 2011  Rafat Hussain

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  See COPYING.LESSER and COPYING files that come
 * with the software.
*/


using namespace std;
extern "C" int _get_output_format( void ){ return 0; }


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
;
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);

    w.show();

    return a.exec();
}

