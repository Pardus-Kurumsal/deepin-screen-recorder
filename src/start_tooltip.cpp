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

#include <QWidget>
#include <QPainter>
#include <QDesktopWidget>
#include <QApplication>
#include <QStyle>
#include <QEvent>
#include "start_tooltip.h"
#include "utils.h"
#include "constant.h"

#include <QDebug>

StartTooltip::StartTooltip(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::WindowDoesNotAcceptFocus | Qt::BypassWindowManagerHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    iconImg = QImage(Utils::getQrcPath("deepin-screen-recorder.png"));

    installEventFilter(this);

    text = tr("Click or drag to\nselect the area to record");
    QSize size = Utils::getRenderSize(Constant::RECTANGLE_FONT_SIZE, text);

    setFixedSize(size.width() + Constant::RECTANGLE_PADDING * 2,
                 size.height() + iconImg.height() + Constant::RECTANGLE_PADDING * 3);
    
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
            )
        );
    
    Utils::passInputEvent(this->winId());
}

void StartTooltip::setWindowManager(WindowManager *wm)
{
    windowManager = wm;
}

void StartTooltip::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    Utils::drawTooltipBackground(painter, rect());

    painter.setOpacity(1);
    painter.drawImage(QPoint((rect().width() - iconImg.width()) / 2, Constant::RECTANGLE_PADDING), iconImg);

    Utils::drawTooltipText(painter, text, "#000000", Constant::RECTANGLE_FONT_SIZE,
                           QRectF(rect().x(),
                                  rect().y() + Constant::RECTANGLE_PADDING + iconImg.height(),
                                  rect().width(),
                                  rect().height() - Constant::RECTANGLE_PADDING - iconImg.height()
                               ));
}

bool StartTooltip::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::ShowToParent) {
        Utils::blurRect(windowManager, this->winId(), rect());
    } else if (event->type() == QEvent::HideToParent) {
        Utils::clearBlur(windowManager, this->winId());
    }
    
    return false;
}
