#include <iostream>
#include <vector>
#include "GameModel.h"
#include "Tool.h"

void StackTool::DrawPoints(Simulation *sim, std::vector<ui::Point> &points)
{
	for (int i=0; i<=sim->parts_lastActiveIndex; i++)
	{
		if (sim->parts[i].type)
		{
			int partx = (int)(sim->parts[i].x+0.5f);
			int party = (int)(sim->parts[i].y+0.5f);
		}
	}
}

void StackTool::Draw(Simulation *sim, Brush *cBrush, ui::Point position)
{
	if(cBrush)
	{
		std::vector<ui::Point> points;
		int radiusX = cBrush->GetRadius().X, radiusY = cBrush->GetRadius().Y, sizeX = cBrush->GetSize().X, sizeY = cBrush->GetSize().Y;
		unsigned char *bitmap = cBrush->GetBitmap();
		for(int y = 0; y < sizeY; y++)
			for(int x = 0; x < sizeX; x++)
				if(bitmap[(y*sizeX)+x] && (position.X+(x-radiusX) >= 0 && position.Y+(y-radiusY) >= 0 && position.X+(x-radiusX) < XRES && position.Y+(y-radiusY) < YRES))
					points.push_back(ui::Point(x, y));
		DrawPoints(sim, points);
	}
}

void StackTool::DrawLine(Simulation *sim, Brush *cBrush, ui::Point position, ui::Point position2, bool dragging)
{
	std::vector<ui::Point> points;
	int x1 = position.X, y1 = position.Y, x2 = position2.X, y2 = position2.Y;
	bool reverseXY = abs(y2-y1) > abs(x2-x1);
	int x, y, dx, dy, sy, rx = cBrush->GetRadius().X, ry = cBrush->GetRadius().Y;
	float e = 0.0f, de;
	if (reverseXY)
	{
		y = x1;
		x1 = y1;
		y1 = y;
		y = x2;
		x2 = y2;
		y2 = y;
	}
	if (x1 > x2)
	{
		y = x1;
		x1 = x2;
		x2 = y;
		y = y1;
		y1 = y2;
		y2 = y;
	}
	dx = x2 - x1;
	dy = abs(y2 - y1);
	if (dx)
		de = dy/(float)dx;
	else
		de = 0.0f;
	y = y1;
	sy = (y1<y2) ? 1 : -1;
	for (x=x1; x<=x2; x++)
	{
		if (reverseXY)
			points.push_back(ui::Point(y, x));
		else
			points.push_back(ui::Point(x, y));
		e += de;
		if (e >= 0.5f)
		{
			y += sy;
			if (!(rx+ry) && ((y1<y2) ? (y<=y2) : (y>=y2)))
			{
				if (reverseXY)
					points.push_back(ui::Point(y, x));
				else
					points.push_back(ui::Point(x, y));
			}
			e -= 1.0f;
		}
	}
	DrawPoints(sim, points);
}

void StackTool::DrawRect(Simulation *sim, Brush *cBrush, ui::Point position, ui::Point position2)
{
	std::vector<ui::Point> points;
	int x1 = position.X, y1 = position.Y, x2 = position2.X, y2 = position2.Y;
	int i, j;
	if (x1>x2)
	{
		i = x2;
		x2 = x1;
		x1 = i;
	}
	if (y1>y2)
	{
		j = y2;
		y2 = y1;
		y1 = j;
	}
	for (j=y1; j<=y2; j++)
		for (i=x1; i<=x2; i++)
			points.push_back(ui::Point(i, j));
	DrawPoints(sim, points);
}
