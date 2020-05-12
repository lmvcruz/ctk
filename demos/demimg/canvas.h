#ifndef CANVAS_H
#define CANVAS_H

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QRect>

#include "ctkimage.h"

class Canvas : public QOpenGLWidget
{
public:
    Canvas(QWidget* par=nullptr);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void paintGL() override;

private:
    QImage m_img;
    QImage m_imgcache;

    QRect m_rect;
    bool m_croppingMode;

    bool m_paintingMode;

    void RestoreCache();
    QImage CtkImage2QImage(ctk::RgbImage &rgb);
    ctk::RgbImage QImage2CtkImage();
};

#endif // CANVAS_H
