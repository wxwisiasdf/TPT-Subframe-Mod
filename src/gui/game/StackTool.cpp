#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "GameModel.h"
#include "Tool.h"

void StackTool::ProcessParts(Simulation *sim, std::vector<int> &parts, ui::Point stackPos)
{
	if (parts.empty()) return;
	bool samePos = true;
	int partx = sim->parts[parts[0]].x;
	int party = sim->parts[parts[0]].y;
	for (size_t i = 1; i < parts.size(); i++)
	{
		Particle part = sim->parts[parts[i]];
		if (part.x != partx || part.y != party)
		{
			samePos = false;
			break;
		}
	}
	if (samePos)
	{
		if (party + parts.size() - 1 >= YRES)
		{
			gameModel->Log(std::string("Not enough space to unstack."), false);
			return;
		}
		for (size_t i = 1; i < parts.size(); i++){
			if (sim->pmap[party + i][partx])
			{
				gameModel->Log(std::string("Not enough space to unstack."), false);
				return;
			}
		}
		for (size_t i = 1; i < parts.size(); i++){
			sim->parts[parts[i]].y += i;
		}
	}
	else
	{
		if (parts.size() > 5)
		{
			gameModel->Log(std::string("Too many particles to stack."), false);
			return;
		}
		for (size_t i = 0; i < parts.size(); i++){
			sim->parts[parts[i]].x = stackPos.X;
			sim->parts[parts[i]].y = stackPos.Y;
		}
	}
}

void StackTool::Draw(Simulation *sim, Brush *cBrush, ui::Point position)
{
	if (cBrush)
	{
		std::vector<int> parts;
		int radiusX = cBrush->GetRadius().X, radiusY = cBrush->GetRadius().Y, sizeX = cBrush->GetSize().X, sizeY = cBrush->GetSize().Y;
		unsigned char *bitmap = cBrush->GetBitmap();
		for (int i=0; i<=sim->parts_lastActiveIndex; i++)
		{
			if (sim->parts[i].type)
			{
				int partx = (int)(sim->parts[i].x+0.5f);
				int party = (int)(sim->parts[i].y+0.5f);
				int partbmpx = partx - position.X + radiusX;
				int partbmpy = party - position.Y + radiusY;
				if (partbmpx >= 0 && partbmpx < sizeX && partbmpy >= 0 && partbmpy < sizeY && bitmap[partbmpy * sizeX + partbmpx])
					parts.push_back(i);
			}
		}
		ProcessParts(sim, parts, position);
	}
}

bool comparePoints(ui::Point a, ui::Point b)
{
	if (a.Y == b.Y) return a.X < b.X;
	else return a.Y < b.Y;
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
	std::sort(points.begin(), points.end(), comparePoints);
	std::vector<int> parts;
	for (int i=0; i<=sim->parts_lastActiveIndex; i++)
	{
		if (sim->parts[i].type)
		{
			int partx = (int)(sim->parts[i].x+0.5f);
			int party = (int)(sim->parts[i].y+0.5f);
			ui::Point partpos(partx, party);
			std::vector<ui::Point>::iterator it = std::lower_bound(points.begin(), points.end(), partpos, comparePoints);
			if (it != points.end() && *it == partpos)
				parts.push_back(i);
		}
	}
	ProcessParts(sim, parts, ui::Point(x1, y1));
}

void StackTool::DrawRect(Simulation *sim, Brush *cBrush, ui::Point position, ui::Point position2)
{
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
	std::vector<int> parts;
	for (int i=0; i<=sim->parts_lastActiveIndex; i++)
	{
		if (sim->parts[i].type)
		{
			int partx = (int)(sim->parts[i].x+0.5f);
			int party = (int)(sim->parts[i].y+0.5f);
			if (partx >= x1 && partx <= x2 && party >= y1 && party <= y2)
				parts.push_back(i);
		}
	}
	ProcessParts(sim, parts, ui::Point(x1, y1));
}
