#pragma once
#include "Type_Definitions.h"
#include <vector>
#include <string>

class Tape
{
public:
	Tape();
	Tape(std::vector<byte> initialvalues);
	void add(byte num, char oper, byte compareTo);
	void add(byte num);

	void subtract(byte num, char oper, byte compareTo);
	void subtract(byte num);

	void multiply(byte num, char oper, byte compareTo);
	void multiply(byte num);

	void divide(byte num, char oper, byte compareTo);
	void divide(byte num);

	void band(byte num, char oper, byte compareTo);
	void band(byte num);

	void bor (byte num, char oper, byte compareTo);
	void bor(byte num);

	void addCell(byte num);
	void addCell();

	std::vector<byte> getCells() { return cells; };

private:
	std::vector<byte> cells;
	bool checkCellMatceshDescriptor(byte valueInCell, char oper, byte compareTo);
};

