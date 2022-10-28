/****************************************************************************
** Author: J.-O. Lachaud, University Savoie Mont Blanc
** (vaguely adapted from Qt colliding mices example)
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
****************************************************************************/

#include <cmath>
#include <QtWidgets>
#include "objects.hpp"

static const int AsteroidCount = 5;

int main(int argc, char **argv)
{
  // Initializes Qt.
  QApplication app(argc, argv);
  // Initializes the random generator.
  qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

  // Creates a graphics scene where we will put graphical objects.
  QGraphicsScene graphical_scene;
  graphical_scene.setSceneRect(0, 0, IMAGE_SIZE, IMAGE_SIZE);
  graphical_scene.setItemIndexMethod(QGraphicsScene::NoIndex);

  // We choose to check intersection with 100 random points.
  logical_scene = new LogicalScene(100);

  // Creates a few asteroids...
  for (int i = 0; i < AsteroidCount; ++i)
  {
    QColor cok(150, 130, 110);
    QColor cko(255, 240, 0);

    // A master shape gathers all the elements of the shape.
    MasterShape *asteroid = new Asteroid(cok, cko,
                                         (qrand() % 20 + 20) / 10.0 /* speed */,
                                         (double)(10 + qrand() % 40) /* radius */);
    // Set direction and position
    asteroid->setRotation(qrand() % 360);
    asteroid->setPos(IMAGE_SIZE / 2 + ::sin((i * 6.28) / AsteroidCount) * 200,
                     IMAGE_SIZE / 2 + ::cos((i * 6.28) / AsteroidCount) * 200);
    // Add it to the graphical scene
    graphical_scene.addItem(asteroid);
    // and to the logical scene
    logical_scene->formes.push_back(asteroid);
  }

  // Creates a few Space Truck...
  for (int i = 0; i < AsteroidCount; ++i)
  {
    QColor cok(0, 255, 0);
    QColor cko(255, 240, 0);

    // A master shape gathers all the elements of the shape.
    MasterShape *st = new SpaceTruck(cok, cko, (qrand() % 20 + 20) / 10.0);
    // Set direction and position
    st->setRotation(qrand() % 360);
    st->setPos(IMAGE_SIZE / 2 + ::sin((i * 6.28) / AsteroidCount) * 200, IMAGE_SIZE / 2 + ::cos((i * 6.28) / AsteroidCount) * 200);
    // Add it to the graphical scene
    graphical_scene.addItem(st);
    // and to the logical scene
    logical_scene->formes.push_back(st);
  }

  // Creates a few Enterprise...
  for (int i = 0; i < AsteroidCount; ++i)
  {
    QColor cok(255, 0, 0);
    QColor cko(255, 240, 0);

    // A master shape gathers all the elements of the shape.
    MasterShape *st = new Enterprise(cok, cko, (qrand() % 20 + 20) / 10.0);
    // Set direction and position
    st->setRotation(qrand() % 360);
    st->setPos(IMAGE_SIZE / 2 + ::sin((i * 6.28) / AsteroidCount) * 200, IMAGE_SIZE / 2 + ::cos((i * 6.28) / AsteroidCount) * 200);
    // Add it to the graphical scene
    graphical_scene.addItem(st);
    // and to the logical scene
    logical_scene->formes.push_back(st);
  }

  // Standard stuff to initialize a graphics view with some background.
  QGraphicsView view(&graphical_scene);
  view.setRenderHint(QPainter::Antialiasing);
  view.setBackgroundBrush(QPixmap(":/images/stars.jpg"));
  view.setCacheMode(QGraphicsView::CacheBackground);
  view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  view.setDragMode(QGraphicsView::NoDrag); // QGraphicsView::ScrollHandDrag
  view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Space - the final frontier"));
  view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view.resize(IMAGE_SIZE, IMAGE_SIZE);
  view.show();

  // Creates a timer that will call `advance()` method regularly.
  QTimer timer;
  QObject::connect(&timer, SIGNAL(timeout()), &graphical_scene, SLOT(advance()));
  timer.start(30); // every 30ms

  return app.exec();
}
