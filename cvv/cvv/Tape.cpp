#include "Tape.h"

Tape::Tape()
{
	for (int j = 0; j < this->initialCellCount; j++) {
		cells.push_back(0b00000000);
	}
}

Tape::Tape(std::vector<byte> initialvalues)
{
	this->cells = initialvalues;
}

void Tape::add(byte num, char oper, byte compareTo)
{
	for (auto& cell : this->cells) {
		if (checkCellMatchesDescriptor(cell, oper, compareTo)) {
			cell += num;
		}
	}
}

void Tape::add(byte num)
{
	for (auto& cell : this->cells) {
		cell += num;
	}
}

void Tape::subtract(byte num, char oper, byte compareTo)
{
	for (auto& cell : this->cells) {
		if (checkCellMatchesDescriptor(cell, oper, compareTo)) {
			cell -= num;
		}
	}
}

void Tape::subtract(byte num)
{
	for (auto& cell : this->cells) {
		cell -= num;
	}
}

void Tape::multiply(byte num, char oper, byte compareTo)
{
	for (auto& cell : this->cells) {
		if (checkCellMatchesDescriptor(cell, oper, compareTo)) {
			cell *= num;
		}
	}
}

void Tape::multiply(byte num)
{
	for (auto& cell : this->cells) {
		cell *= num;
	}
}

void Tape::divide(byte num, char oper, byte compareTo)
{
	for (auto& cell : this->cells) {
		if (checkCellMatchesDescriptor(cell, oper, compareTo)) {
			cell /= num;
		}
	}
}

void Tape::divide(byte num)
{
	for (auto& cell : this->cells) {
		cell /= num;
	}
}

void Tape::band(byte num, char oper, byte compareTo)
{
	for (auto& cell : this->cells) {
		if (checkCellMatchesDescriptor(cell, oper, compareTo)) {
			cell = cell & num;
		}
	}
}

void Tape::band(byte num)
{
	for (auto& cell : this->cells) {
		cell = cell & num;
	}
}

void Tape::bor(byte num, char oper, byte compareTo)
{
	for (auto& cell : this->cells) {
		if (checkCellMatchesDescriptor(cell, oper, compareTo)) {
			cell = cell | num;
		}
	}
}

void Tape::bor(byte num)
{
	for (auto& cell : this->cells) {
		cell = cell | num;
	}
}

void Tape::addCells(int amount)
{
	for(int j = 0; j < amount; j++)
		this->cells.push_back(0b00000000);
}

void Tape::vaporize(int index)
{
	this->cells.erase(this->cells.begin() + index);
}

byte Tape::getValueAtIndex(int index)
{
	if (index >= 0 && index < cells.size()) {
		return cells[index];
	}
	return -999;
}

bool Tape::checkCellMatchesDescriptor(byte valueInCell, char oper, byte compareTo)
{
	switch (oper) {
		case '>':
			return valueInCell > compareTo;
			break;
		case '<':
			return valueInCell < compareTo;
			break;
		case '=':
			return valueInCell == compareTo;
			break;
	}
}