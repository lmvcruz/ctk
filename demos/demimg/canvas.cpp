#include "canvas.h"

#include <QPainter>
#include <QDebug>
#include <QDir>

#include "opencv2/imgproc.hpp"

Canvas::Canvas(QWidget* par)
    : QOpenGLWidget(par)
{
    setFocusPolicy(Qt::WheelFocus);
    m_croppingMode = false;
    m_paintingMode = false;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (m_croppingMode) {
        m_rect.setX(event->pos().x());
        m_rect.setY(event->pos().y());
        m_rect.setWidth(0);
        m_rect.setHeight(0);
    }
    else if (m_paintingMode) {
        float wf = static_cast<float>(width());
        float iwf = static_cast<float>(m_img.width());
        float hf = static_cast<float>(height());
        float ihf = static_cast<float>(m_img.height());
        int rx = static_cast<int>(static_cast<float>(event->x()) * iwf / wf);
        int ry = static_cast<int>(static_cast<float>(event->y()) * ihf / hf);
        m_img.setPixel(rx, ry, qRgb(255, 0, 0));
    }
    update();
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (m_croppingMode) {
        m_rect.setWidth(event->x()-m_rect.x());
        m_rect.setHeight(event->y()-m_rect.y());
    }
    else if (m_paintingMode) {
        float wf = static_cast<float>(width());
        float iwf = static_cast<float>(m_img.width());
        float hf = static_cast<float>(height());
        float ihf = static_cast<float>(m_img.height());
        int rx = static_cast<int>(static_cast<float>(event->x()) * iwf / wf);
        int ry = static_cast<int>(static_cast<float>(event->y()) * ihf / hf);
        m_img.setPixel(rx, ry, qRgb(255, 0, 0));
    }
    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_croppingMode) {
        m_rect.setWidth(event->x()-m_rect.x());
        m_rect.setHeight(event->y()-m_rect.y());
        if (m_rect.width()*m_rect.height()>1) {
            float wf = static_cast<float>(width());
            float iwf = static_cast<float>(m_img.width());
            float hf = static_cast<float>(height());
            float ihf = static_cast<float>(m_img.height());
            int rx = static_cast<int>(static_cast<float>(m_rect.x()) * iwf / wf);
            int ry = static_cast<int>(static_cast<float>(m_rect.y()) * ihf / hf);
            int rw = static_cast<int>(static_cast<float>(m_rect.width()) * iwf / wf);
            int rh = static_cast<int>(static_cast<float>(m_rect.height()) * ihf / hf);
            ctk::RgbImage rgb = QImage2CtkImage();
            rgb.SelfCrop(rx, ry, rw, rh);
            m_img = CtkImage2QImage(rgb);
            qDebug() << "Cropping: " << m_img.width() << m_img.height();
        }
        else {
            qDebug() << "Invalid Crop";
        }
    }
    else if (m_paintingMode) {
        float wf = static_cast<float>(width());
        float iwf = static_cast<float>(m_img.width());
        float hf = static_cast<float>(height());
        float ihf = static_cast<float>(m_img.height());
        int rx = static_cast<int>(static_cast<float>(event->x()) * iwf / wf);
        int ry = static_cast<int>(static_cast<float>(event->y()) * ihf / hf);
        m_img.setPixel(rx, ry, qRgb(255, 0, 0));
    }
    update();
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    m_croppingMode = false;
    m_paintingMode = false;
    //
    switch (event->key()) {
    case 'O': {
        ctk::RgbImage rgb;
        rgb.Open("rgb_img.jpg");
        m_img = CtkImage2QImage(rgb);
        m_imgcache = m_img;
        qDebug() << "Opening" << m_img.width() << m_img.height();
        break;
    }
    case 'L': {
        RestoreCache();
        ctk::RgbImage rgb = QImage2CtkImage();
        ctk::RgbImage gray = rgb.toGrayImage().toRgbImage();
        m_img = CtkImage2QImage(gray);
        qDebug() << "Luminosity: " << m_img.width() << m_img.height();
        break;
    }
    case 'R': {
        RestoreCache();
        ctk::RgbImage rgb = QImage2CtkImage();
        for (int x=0; x<rgb.width(); x++) {
            for (int y=0; y<rgb.height(); y++) {
                m_img.setPixel(x, y, qRgb(rgb.red(x,y), 0, 0));
            }
        }
        qDebug() << "Red: " << m_img.width() << m_img.height();
        break;
    }
    case 'G': {
        RestoreCache();
        ctk::RgbImage rgb = QImage2CtkImage();
        for (int x=0; x<rgb.width(); x++) {
            for (int y=0; y<rgb.height(); y++) {
                m_img.setPixel(x, y, qRgb(0, rgb.green(x,y), 0));
            }
        }
        qDebug() << "Green: " << m_img.width() << m_img.height();
        break;
    }
    case 'B': {
        RestoreCache();
        ctk::RgbImage rgb = QImage2CtkImage();
        for (int x=0; x<rgb.width(); x++) {
            for (int y=0; y<rgb.height(); y++) {
                m_img.setPixel(x, y, qRgb(0, 0, rgb.blue(x,y)));
            }
        }
        qDebug() << "Green: " << m_img.width() << m_img.height();
        break;
    }
    case 'F': {
        ctk::RgbImage rgb = QImage2CtkImage();
        rgb.SelfFlipHorizontally();
        m_img = CtkImage2QImage(rgb);
        qDebug() << "Flip Hor: " << m_img.width() << m_img.height();
        break;
    }
    case 'V': {
        ctk::RgbImage rgb = QImage2CtkImage();
        rgb.SelfFlipVertically();
        m_img = CtkImage2QImage(rgb);
        qDebug() << "Flip Ver: " << m_img.width() << m_img.height();
        break;
    }
    case 'A': {
        ctk::RgbImage rgb = QImage2CtkImage();
        rgb.SelfRotate90();
        m_img = CtkImage2QImage(rgb);
        qDebug() << "Flip Ver: " << m_img.width() << m_img.height();
        break;
    }
    case 'C': {
        m_croppingMode = true;
        break;
    }
    case 'P': {
        m_paintingMode = true;
        break;
    }
    case 'S': {
        ctk::RgbImage rgb = QImage2CtkImage();
        rgb.Save("out.png");
        qDebug() << "Saving: " << rgb.width() << rgb.height();
        break;
    }
    default: qDebug() << "Unknown key";
    }
    update();
}

void Canvas::paintGL()
{
    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0,0,width(), height());
    //
    if (m_img.width()>0) {
        painter.drawImage(QRect(0,0,width(), height()),m_img);
    }
    if (m_croppingMode) {
        painter.setPen(Qt::black);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(m_rect);
    }
    painter.end();
}

void Canvas::RestoreCache()
{
    m_img = m_imgcache;
}

QImage Canvas::CtkImage2QImage(ctk::RgbImage &rgb)
{
    cv::Mat &data = rgb.get_data();
    cv::cvtColor(data, data, cv::COLOR_BGR2RGB);
    QImage dest((const uchar *) data.data, data.cols, data.rows, data.step, QImage::Format_RGB888);
    dest.bits();
    return dest;
}

ctk::RgbImage Canvas::QImage2CtkImage()
{
    cv::Mat tmp(m_img.height(),m_img.width(),CV_8UC3,
                (uchar*)m_img.bits(),m_img.bytesPerLine());
    cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
    cv::cvtColor(tmp, result,cv::COLOR_BGR2RGB);
    return result;
}
