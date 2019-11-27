/*
 * box2dworld.h
 * Copyright (c) 2010 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 * Copyright (c) 2011 Joonas Erkinheimo <joonas.erkinheimo@nokia.com>
 * Copyright (c) 2012 Adriano Rezende <atdrez@gmail.com>
 *
 * This file is part of the Box2D QML plugin.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef DUNGEON_H
#define DUNGEON_H

#include <QQuickItem>
#include <QApplication>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QDesktopWidget>
#include <QTime>
#include <utils.h>
#include <DungeonGenerator.h>

class Dungeon : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(int cellSize READ cellSize WRITE setCellSize NOTIFY cellSizeChanged) // cell size
    Q_PROPERTY(int levelWidth READ levelWidth WRITE setLevelWidth) // level size
    Q_PROPERTY(int levelHeight READ levelHeight WRITE setLevelHeight) // level size

public:
    explicit Dungeon(QQuickItem *parent = 0){

        //--------Create Debug Console
        QQmlComponent component(&engine);
        //QString s("import QtQuick 1.1; Flickable {x:0; y:0; width:"+QString::number(QApplication::focusWidget()->geometry().width(),10) + "; height: 300; Text{x:0; y:0; text: \"Hello world!\"} }");

        //-----------ADD GENERATION FUNCTION TO ADD CONTENT + HERO AND OTHER CPP PLUGINS AS ITEMS USE


    };
    ~Dungeon(){};

    // TODO: придумать либо генерацию имен с одинаковыми началами для objectName либо таки как свойство обектов для определения колизий но что бы обьекты можна было найти и по ojectname каждый

    Q_INVOKABLE void generateMapNew(int width, int height){
        // MAP GENERATION
        QList<QList<int> > t;

        DungeonGenerator mydungeon( QString::number(QTime::currentTime().msec()).toStdString(), 30, 30); // for repeat level set the same string name
        mydungeon.Generate();
        Grid griddata = mydungeon.GetGrid();
         m_MapNew = griddata;
    }

    //TODO: load from file, save to file, now it just fill level from generated map
    Q_INVOKABLE void loadMap(){


        QQmlEngine engine;
        QQmlComponent component(&engine);

        for (int i=0; i<mLevelWidth; i++){
            for (int k=0; k<mLevelHeight; k++){
                switch(m_MapNew[i][k]){
                // empty
                case Empty:{
                    component.loadUrl(QUrl("qrc:/qml/ANGSC1/tile-wall.qml"));
                    QQuickItem *item = qobject_cast<QQuickItem *>(component.create());
                    QObject *ground = this->findChild<QObject*>("ground");
                    item->setParentItem(qobject_cast<QQuickItem *>(ground));
                    item->setProperty("x", i*mCellSize);
                    item->setProperty("y", k*mCellSize);
                    mapItems.append(item);
                    break;
                }
                // floor
                case Floor:{
                    //IMPORTANT !!! here can load - file.qml too, not only from string
                    // !!! Приведения Обьекта к типу QML item из созданого компонента загруженог ос QML файла
                    component.loadUrl(QUrl("qrc:/qml/ANGSC1/tile-floor.qml"));
                    QQuickItem *item = qobject_cast<QQuickItem *>(component.create());
                    // !!! Ищем дочерний елемент с именем обьекта ground и делаем базовым для нашего созданого компонента
                    QObject *ground = this->findChild<QObject*>("ground");
                    item->setParentItem(qobject_cast<QQuickItem *>(ground));
                    // преобразовываем свойства загруженого QML компонента
                    item->setProperty("x", i*mCellSize);
                    item->setProperty("y", k*mCellSize);
                    // добавляем его в список наш на всякий случай для доступа
                    mapItems.append(item);
                    break;
                }
                // Corridor
                case Corridor:{
                    component.loadUrl(QUrl("qrc:/qml/ANGSC1/tile-corridor.qml"));
                    QQuickItem *item = qobject_cast<QQuickItem *>(component.create());
                    QObject *ground = this->findChild<QObject*>("ground");
                    item->setParentItem(qobject_cast<QQuickItem *>(ground));
                    item->setProperty("x", i*mCellSize);
                    item->setProperty("y", k*mCellSize);
                    mapItems.append(item);
                    break;
                }
                // Door
                case Door:{
                    component.loadUrl(QUrl("qrc:/qml/ANGSC1/tile-door.qml"));
                    QQuickItem *item = qobject_cast<QQuickItem *>(component.create());
                    QObject *ground = this->findChild<QObject*>("ground");
                    item->setParentItem(qobject_cast<QQuickItem *>(ground));
                    item->setProperty("x", i*mCellSize);
                    item->setProperty("y", k*mCellSize);
                    mapItems.append(item);
                    break;
                }
                // Trap
                case Trap:{
                    component.loadUrl(QUrl("qrc:/qml/ANGSC1/tile-trap.qml"));
                    QQuickItem *item = qobject_cast<QQuickItem *>(component.create());
                    QObject *ground = this->findChild<QObject*>("ground");
                    item->setParentItem(qobject_cast<QQuickItem *>(ground));
                    item->setProperty("x", i*mCellSize);
                    item->setProperty("y", k*mCellSize);
                    mapItems.append(item);
                    break;
                }
                // Treasure
                case Treasure:{
                    component.loadUrl(QUrl("qrc:/qml/ANGSC1/tile-treasure.qml"));
                    QQuickItem *item = qobject_cast<QQuickItem *>(component.create());
                    QObject *ground = this->findChild<QObject*>("ground");
                    item->setParentItem(qobject_cast<QQuickItem *>(ground));
                    item->setProperty("x", i*mCellSize);
                    item->setProperty("y", k*mCellSize);
                    mapItems.append(item);
                    break;
                }
                // Monster
                case Monster:{
                    component.loadUrl(QUrl("qrc:/qml/ANGSC1/tile-monster.qml"));
                    QQuickItem *item = qobject_cast<QQuickItem *>(component.create());
                    QObject *ground = this->findChild<QObject*>("ground");
                    item->setParentItem(qobject_cast<QQuickItem *>(ground));
                    item->setProperty("x", i*mCellSize);
                    item->setProperty("y", k*mCellSize);
                    mapItems.append(item);
                    break;
                }
                // Entrance
                case Entrance:{
                    component.loadUrl(QUrl("qrc:/qml/ANGSC1/tile-entrance.qml"));
                    QQuickItem *item = qobject_cast<QQuickItem *>(component.create());
                    QObject *ground = this->findChild<QObject*>("ground");
                    item->setParentItem(qobject_cast<QQuickItem *>(ground));
                    item->setProperty("x", i*mCellSize);
                    item->setProperty("y", k*mCellSize);
                    mapItems.append(item);
                    break;
                }
                // Exit
                case Exit:{
                    component.loadUrl(QUrl("qrc:/qml/ANGSC1/tile-exit.qml"));
                    QQuickItem *item = qobject_cast<QQuickItem *>(component.create());
                    QObject *ground = this->findChild<QObject*>("ground");
                    item->setParentItem(qobject_cast<QQuickItem *>(ground));
                    item->setProperty("x", i*mCellSize);
                    item->setProperty("y", k*mCellSize);
                    mapItems.append(item);
                    break;
                }
                }
            }
        }

    }


    // cell size
    int cellSize() const { return mCellSize; }
    void setCellSize(int cellSize){mCellSize = cellSize;}
    // level width
    int levelWidth() const { return mLevelWidth; }
    void setLevelWidth(int levelWidth){mLevelWidth = levelWidth;}
    // level height
    int levelHeight() const { return mLevelHeight; }
    void setLevelHeight(int levelHeight){mLevelHeight = levelHeight;}

signals:
    void cellSizeChanged();

private:
    //- access to context
    QQmlEngine engine;

    // List of loaded QML items may be usable
    QList<QQuickItem*> mapItems;

    int mCellSize; // cell size
    int mLevelWidth; // level width
    int mLevelHeight; // level height

    struct Map{
        QList<QList<int> > ground;
        QList<QList<int> > enivorment;
        QList<QList<int> > creatures;
    } map;

    //QList<QList<int> > m_MapNew;
    std::vector<std::vector<uint> > m_MapNew;
};

QML_DECLARE_TYPE(Dungeon)

#endif // DUNGEON_H
