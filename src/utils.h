/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2011 ~ 2017 Deepin, Inc.
 *               2011 ~ 2017 Wang Yong
 *
 * Author:     Wang Yong <wangyong@deepin.com>
 * Maintainer: Wang Yong <wangyong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */ 

#include "window_manager.h"
#include <QObject>
#include <QPainter>
#include <QString>

class Utils : public QObject
{
public:
    static QSize getRenderSize(int fontSize, QString string);
    static QString getQrcPath(QString imageName);
    static void blurRect(WindowManager *windowManager, int widgetId, QRectF rect);
    static void blurRects(WindowManager *windowManager, int widgetId, QList<QRectF> rects);
    static void clearBlur(WindowManager *windowManager, int widgetId);
    static void drawTooltipBackground(QPainter &painter, QRect rect, qreal opacity = 0.4);
    static void drawTooltipText(QPainter &painter, QString text, QString textColor, int textSize, QRectF rect);
    static void passInputEvent(int wid);
    static void setFontSize(QPainter &painter, int textSize);
};
