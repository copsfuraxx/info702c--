/****************************************************************************
** Author: J.-O. Lachaud, University Savoie Mont Blanc
** (adapted from Qt colliding mices example)
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
****************************************************************************/

#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <vector>
#include <QGraphicsItem>

static const int IMAGE_SIZE = 600;
static const int SZ_BD = 100;

/// @brief Abstract class that describes a graphical object with additional
/// methods for testing collisions.
struct GraphicalShape : public QGraphicsItem
{
  virtual QPointF randomPoint() const = 0;
  virtual bool isInside(const QPointF &p) const = 0;
  // virtual QRectF  boundingRect() const override;
};

/// @brief Polymorphic class that represents the top class of any complex
/// shape.
///
/// It takes care of memorizing collisions and storing the
/// current main coordinates of a shape.
struct MasterShape : public GraphicalShape
{
  enum State
  {
    Ok,
    Collision
  };
  MasterShape(QColor cok, QColor cko);
  void setGraphicalShape(GraphicalShape *f);
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;
  virtual QPointF randomPoint() const override;
  virtual bool isInside(const QPointF &p) const override;
  virtual QRectF boundingRect() const override;

  // Checks if this shape collides with another shape and forces also
  // the shapes to stay in the graphical view.
  virtual void advance(int step) override;
  State currentState() const;
  QColor currentColor() const;

protected:
  GraphicalShape *_f;
  State _state;
  QColor _cok, _cko;
};

/// @brief An asteroid is a simple shape that moves linearly in some direction.
struct Asteroid : public MasterShape
{
  Asteroid(QColor cok, QColor cko, double speed, double r);
  // moves the asteroid forward according to its speed.
  virtual void advance(int step) override;

protected:
  double _speed;
};

/// @brief An Space truck is a simple shape that moves linearly in some direction.
struct SpaceTruck : public MasterShape
{
  SpaceTruck(QColor cok, QColor cko, double speed);
  // moves the asteroid forward according to its speed.
  virtual void advance(int step) override;

protected:
  double _speed;
};

/// @brief An Enterprise is a simple shape that moves linearly in some direction.
struct Enterprise : public MasterShape
{
  Enterprise(QColor cok, QColor cko, double speed);
  // moves the asteroid forward according to its speed.
  virtual void advance(int step) override;

protected:
  double _speed;
};

/// @brief A disk is a simple graphical shape.
///
/// It points to its master shape
/// in order to know in which color it must be painted.
struct Disk : public GraphicalShape
{
  Disk(qreal r, const MasterShape *master_shape);
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;
  virtual QPointF randomPoint() const override;
  virtual bool isInside(const QPointF &p) const override;
  virtual QRectF boundingRect() const override;
  const qreal _r;
  const MasterShape *_master_shape;
};

/// @brief A Tect is a simple graphical shape.
///
/// It points to its master shape
/// in order to know in which color it must be painted.
struct Rectangle : public GraphicalShape
{
  Rectangle(QPointF p, QPointF q, const MasterShape *master_shape);
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;
  virtual QPointF randomPoint() const override;
  virtual bool isInside(const QPointF &p) const override;
  virtual QRectF boundingRect() const override;
  const QPointF _p;
  const QPointF _q;
  const MasterShape *_master_shape;
};

struct Union : public GraphicalShape
{
  Union(GraphicalShape *shape1, GraphicalShape *shape2);
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  virtual QPointF randomPoint() const override;
  virtual bool isInside(const QPointF &p) const override;
  virtual QRectF boundingRect() const override;
  GraphicalShape *_shape1;
  GraphicalShape *_shape2;
  mutable bool isShape1;
};

struct Transformation: public GraphicalShape {
  Transformation( GraphicalShape* f, const QPointF dx, const qreal angle );
  Transformation( GraphicalShape* f, const QPointF dx);
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  virtual QPointF randomPoint() const override;
  virtual bool isInside(const QPointF &p) const override;
  virtual QRectF boundingRect() const override;
  GraphicalShape * _f;
  const QPointF _dx;
  const qreal _angle;
};

/// @brief A class to store master shapes and to test their possible
/// collisions with a randomized algorithm.
struct LogicalScene
{
  std::vector<MasterShape *> formes;
  int nb_tested;

  /// Builds a logical scene where collisions are detected by checking
  /// \a n random points within shapes.
  ///
  /// @param n any positive integer.
  LogicalScene(int n);
  /// Given two shapes \a f1 and \a f2, returns if they collide.
  /// @param f1 any master shape.
  /// @param f2 any different master shape.
  /// @return 'true' iff they collide, i.e. have a common intersection.
  bool intersect(MasterShape *f1, MasterShape *f2);
  /// @param f1 any master shape.
  /// @return 'true' iff it collides with a different master shape stored in this logical scene.
  bool intersect(MasterShape *f1);
};

extern LogicalScene *logical_scene;

#endif
