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

	void addCells(int amount);

	void vaporize(int index);

	std::vector<byte> getCells() { return cells; };
	byte getValueAtIndex(int index);

private:
	static const int initialCellCount = 64;
	std::vector<byte> cells;
	bool checkCellMatchesDescriptor(byte valueInCell, char oper, byte compareTo);
};

