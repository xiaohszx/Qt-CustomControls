#include "StripSliderStyleTwo.h"
#include "ui_StripSliderStyleTwo.h"
#include<QPainter>
#include <QDebug>
#include <QPalette>
#include<QMouseEvent>
#include<math.h>
StripSliderStyleTwo::StripSliderStyleTwo(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::StripSliderStyleTwo;
	ui->setupUi(this);

	this->hander_lab = ui->hander_lab;
	this->hander_lab->installEventFilter(this);

	//初始化
	slive_width = 0;
	top_value = 0;
	bottom_value = 0;
	round_value_x = 0;
	round_value_y = 0;
	wid_width = 0;
	wid_height = 0;
	min_value = 0;
	max_value = 0;
	cur_value = 0;
	hander_x_axis = 0;
	hander_y_dis = 0;
	haner_y_step = 0;

	triangle_width = 0;
}

StripSliderStyleTwo::~StripSliderStyleTwo()
{
	delete ui;
}

void StripSliderStyleTwo::SetSliveWidth(int value)
{
	this->slive_width = value;
}

void StripSliderStyleTwo::SetBackgrondColor(QColor slive_color, QColor slider_color)
{
	this->slive_color = slive_color;
	this->slider_color = slider_color;
}

void StripSliderStyleTwo::SetTopAndBottomBlank(int top_value, int bottom_value)
{
	this->top_value = top_value;
	this->bottom_value = bottom_value;
}

void StripSliderStyleTwo::SetTriangleWidth(int triangle_width)
{
	this->triangle_width = triangle_width;
}

void StripSliderStyleTwo::SetSliderWidgetWidthAndHeight(int width, int height)
{
	this->wid_width = width;
	this->wid_height = height;
}

void StripSliderStyleTwo::SetSliderRange(int min_value, int max_value)
{
	if (min_value >= max_value)
	{
		this->min_value = 0;
		this->max_value = 100;
	}

	this->min_value = min_value;
	this->max_value = max_value;
}

void StripSliderStyleTwo::SetSliveRoundValue(int x_value, int y_value)
{
	this->round_value_x = x_value;
	this->round_value_y = y_value;
}


void StripSliderStyleTwo::SetHanderLabelProperty(QFont font, QColor font_color, QColor back_color)
{
	hander_lab->SetBackgroundColor(back_color);
	hander_lab->SetLabelFontAndColor(font, font_color);
}


void StripSliderStyleTwo::SetHanderLabelRoundValue(int border_x_value, int border_y_value)
{
	hander_lab->SetRoundValue(border_x_value, border_y_value);
}



void StripSliderStyleTwo::Update()
{
	//固定下来的x轴
	hander_x_axis = (m_width - wid_width) / 2;
	//y轴移动的总距离(多减去一个滑块高度加2个宽度)
	hander_y_dis = m_height - top_value - bottom_value - wid_height - 2 * triangle_width;
	//y轴的步长
	haner_y_step = (double)hander_y_dis / (max_value - min_value);

	hander_lab->show();
	SetSliderValue(min_value);
}

void StripSliderStyleTwo::SetSliderValue(int value)
{
	if (value<min_value&&value >max_value)
	{
		cur_value = 0;
		MoveSlider(cur_value);
		emit ValueChange(cur_value);
	}

	cur_value = value;
	MoveSlider(cur_value);
	emit ValueChange(cur_value);
}

void StripSliderStyleTwo::resizeEvent(QResizeEvent* size)
{
	this->m_width = this->width();
	this->m_height = this->height();

	hander_lab->resize(wid_width, wid_height);
	hander_lab->show();


	this->Update();
}
void StripSliderStyleTwo::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
	//设置透明笔
	painter.setPen(QColor(1, 1, 1, 0));

	//画背景
	painter.setBrush(slider_color);
	painter.drawRoundedRect(0, 0, m_width, m_height, 8, 8);

	//画杆子
	painter.setBrush(slive_color);
	//计算下杆子的坐标以及长宽
	int slive_x = (m_width - slive_width) / 2;
	int slive_y = top_value + triangle_width;
	int slive_width_new = this->slive_width;
	int slive_height = this->height() - top_value - bottom_value - 2 * triangle_width;
	painter.drawRoundedRect(slive_x, slive_y, slive_width_new, slive_height, round_value_x, round_value_y);

	/*****类特殊点,画两端的方块以及方块上的三角********/
	int top_x_axis = (m_width - triangle_width) / 2;//x轴
	int top_y_axis = top_value;
	//上方块三角形
	painter.setBrush(QColor(157, 173, 220));
	//取点
	QPoint top_points[3] = { QPoint(top_x_axis,top_y_axis+ triangle_width),QPoint(top_x_axis + triangle_width/2,top_y_axis),QPoint(top_x_axis+ triangle_width,top_y_axis + triangle_width) };//左 上 右顺序
	painter.drawPolygon(top_points, 3);

	int bottom_x_axis = (m_width - triangle_width) / 2;//x轴
	int bottom_y_axis = m_height - bottom_value - triangle_width;
	//下方三角形
	painter.setBrush(QColor(157, 173, 220));
	//取点
	QPoint bottom_points[3] = {QPoint(bottom_x_axis,bottom_y_axis),QPoint(bottom_x_axis + triangle_width / 2,bottom_y_axis + triangle_width),QPoint(bottom_x_axis + triangle_width,bottom_y_axis) };//左 上 右顺序
	painter.drawPolygon(bottom_points, 3);

	this->update();
}
void StripSliderStyleTwo::MoveSlider(int value)
{
	//当前value值对应的y值
	int cur_y = top_value + triangle_width + (value - min_value)*haner_y_step;
	hander_lab->move(hander_x_axis, cur_y);
	hander_lab->SetText(QString::number(value));
}

bool StripSliderStyleTwo::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == hander_lab&&event->type() == QEvent::MouseButtonPress)
	{
		cur_state = Checked_State;
	}
	else if (obj == NULL&&event->type() == QEvent::MouseButtonPress)
	{
		cur_state = UnCheck_State;
	}
	if (obj == hander_lab&&event->type() == QEvent::MouseButtonRelease)
	{
		cur_state = UnCheck_State;
	}
	else if (obj == NULL&&event->type() == QEvent::MouseButtonRelease)
	{
		cur_state = UnCheck_State;
	}
	return QWidget::eventFilter(obj, event);
}

void StripSliderStyleTwo::leaveEvent(QEvent* event)
{
	QWidget::leaveEvent(event);
	cur_state = UnCheck_State;
	update();
}

void StripSliderStyleTwo::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons()&Qt::LeftButton)
	{
		switch (cur_state)
		{
		case Checked_State:
		{
			if (event->y() <= top_value + wid_height / 2 + triangle_width)
			{
				cur_value = min_value;
				hander_lab->move(hander_x_axis, top_value + triangle_width);
				hander_lab->SetText(QString::number(cur_value));

				emit ValueChange(cur_value);
				this->update();
				return;
			}
			else if (event->y() >= m_height - bottom_value - triangle_width - wid_height / 2)
			{
				cur_value = max_value;
				hander_lab->move(hander_x_axis, m_height - bottom_value - triangle_width - wid_height);
				hander_lab->SetText(QString::number(cur_value));

				emit ValueChange(cur_value);
				this->update();
				return;
			}

			float move = (event->y() - top_value - triangle_width - wid_height / 2) / haner_y_step;

			cur_value = round(move);
			hander_lab->move(hander_x_axis, event->y() - wid_height / 2);
			hander_lab->SetText(QString::number(cur_value));

			emit ValueChange(cur_value);
			break;
		}
		}
	}
	update();
}

