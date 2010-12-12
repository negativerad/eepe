/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MDICHILD_H
#define MDICHILD_H

#define FILE_TYPE_BIN 1
#define FILE_TYPE_HEX 2

#include <QtGui>
#include "pers.h"
#include "myeeprom.h"

class MdiChild : public QListWidget//QMdiSubWindow
{
    Q_OBJECT

private:
    EEPFILE eeFile;

public:
    MdiChild();

    void newFile();
    bool loadFile(const QString &fileName, bool resetCurrentFile=true);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName, bool setCurrent=true);
    bool hasSelection();
    QString userFriendlyCurrentFile();
    QString currentFile() { return curFile; }
    void keyPressEvent(QKeyEvent *event);
    bool hasPasteData();

signals:
    void copyAvailable(bool val);

protected:
    void closeEvent(QCloseEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);


private slots:
    void documentWasModified();
    void refreshList();


public slots:
    void OpenEditWindow();
    void ShowContextMenu(const QPoint& pos);
    void cut();
    void copy();
    void paste();
    void burnTo();
    void simulate();
    void print();
    void duplicate();
    void deleteSelected(bool ask);
    void setModified();
    void viableModelSelected(int idx);

private:
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    void doPaste(QByteArray *gmData, int index);
    void doCopy(QByteArray *gmData);
    QString strippedName(const QString &fullFileName);
    int getFileType(const QString &fullFileName);

    QPoint dragStartPosition;

    QString curFile;
    bool isUntitled;

//    ModelData g_model;
//    EEGeneral g_eeGeneral;

};

#endif
