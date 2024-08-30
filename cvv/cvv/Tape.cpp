#include "Tape.h"

Tape::Tape()
{
}

Tape::Tape(std::vector<byte> initialvalues)
{
	this->cells = initialvalues;
}

void Tape::add(byte num, char oper, byte compareTo)
{
	for (auto& cell : this->cells) {
		if (checkCellMatceshDescriptor(cell, oper, compareTo)) {
			cell += num;
		}
	}
}

void Tape::add(byte num)
{
	for (auto &cell : this->cells) {
		cell += num;
	}
}

void Tape::subtract(byte num, char oper, byte compareTo)
{
	for (auto& cell : this->cells) {
		if (checkCellMatceshDescriptor(cell, oper, compareTo)) {
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
		if (checkCellMatceshDescriptor(cell, oper, compareTo)) {
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
		if (checkCellMatceshDescriptor(cell, oper, compareTo)) {
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
		if (checkCellMatceshDescriptor(cell, oper, compareTo)) {
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
		if (checkCellMatceshDescriptor(cell, oper, compareTo)) {
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

void Tape::addCell(byte num)
{
	this->cells.push_back(num);
}

void Tape::addCell()
{
	this->cells.push_back(0b00000000);
}

bool Tape::checkCellMatceshDescriptor(byte valueInCell, char oper, byte compareTo)
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