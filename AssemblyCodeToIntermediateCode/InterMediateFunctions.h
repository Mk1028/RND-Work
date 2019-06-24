#include "Header.h"
#include "Structures.h"

#ifndef _IntermediateMethiods_h
#define _IntermediateMethiods_h

void trim(char *input)
{
	int i = 0, len = strlen(input);
	if (input[len - 1] == '\n' || input[len - 1] ==':')
	{
		for (i = 0; i < len - 1; i++)
		{
			input[i] = input[i];
		}
		input[i] = '\0';
	}
}

int numberOfVariables(ST *SymbolTable)
{
	int i = 0;

	while (SymbolTable[i].Name[0] != '\0')
	{
		i++;
	}
	return i;
}

int compare(char command[20], char *str, int len)
{
	int i = 0;
	for (; str[i] != '\0' && command[i] != '\0'; i++)
	{
		if (command[i] != str[i])
			break;
	}
	if (command[i] == '\0' && i == len)
		return 1;
	return 0;
}

int getAddressOfVar(ST *SymbolTable, char * var)
{
	int NumberOfVariables = numberOfVariables(SymbolTable), ind = 0;

	for (ind = 0; ind < NumberOfVariables; ind++)
	{
		if (compare(SymbolTable[ind].Name,var,strlen(var)))
			return SymbolTable[ind].Address;
	}
}

int getOpCode(char *Inst)
{
	char Instruction[14][6] = { "MOV","MOV","ADD","SUB","MUL","JMP","IF","EQ","LT","GT","LTEQ","GTEQ","PRINT","READ" };
	int i;

	for (i = 0; i < 14; i++)
	{
		if (compare(Instruction[i], Inst, strlen(Inst)))
			return i + 1;
	}
}

int AddressOfRegister(char *Register)
{
	char Registers[8][3] = { "AX","BX","CX","DX","EX","FX","GX","HX" };
	int i;

	for (i = 0; i < 8; i++)
	{
		if (compare(Register, Registers[i], strlen(Registers[i])))
			return i;
	}
}

int addressOfBlock(char *Block,LT *LocalTable)
{
	int ind = 0;
	while (LocalTable[ind].BlockName[0]!='\0')
	{
		if (compare(LocalTable[ind].BlockName,Block,strlen(Block)))
			return LocalTable[ind].Address;
	}
	return 0;
}

void parseCommand(char *command, char **arg)
{
	int j, ind = 0, k = 0,i;

	for (i = 0; command[i] == ' '; i++);

	for (j = i; command[j] != ' '; j++)
	{
		arg[ind][k++] = command[j];
	}
	arg[ind][k] = '\0';

	ind++; k = 0;

	for (i = j+1; command[i] != '\0'; i++)
	{
		arg[ind][k++] = command[i];
	}
	arg[ind][k] = '\0';
}

void tokenizer(char *command, char **arg,char ch)
{
	int j, ind = 0, k = 0;
	for (j = 0; command[j] != '\0'; j++)
	{
		if (command[j] !=ch)
			arg[ind][k++] = command[j];
		else
		{
			arg[ind][k] = '\0';
			ind++; k = 0;
		}
	}
	arg[ind][k] = '\0';

}

int str_to_number(char *left)
{
	unsigned int number = 0; int i = 0,minus=1;
	if (left[i] == '-')
	{
		minus = -1;
		i++;
	}
	while (left[i] != '\0')
	{
		number = number * 10 + left[i] - '0';
		i++;
	}
	return minus*number;
}

void removeSpaces(char *str)
{
	int count = 0;
	for (int i = 0; str[i]; i++) {
		if (str[i] != ' ' && str[i] != 9)
			str[count++] = str[i];
	}
	str[count] = '\0';
}

ST * InitializeST()
{
	ST *SymbolTable = (ST *)malloc(sizeof(ST) * SizeOfST);

	for (int i = 0; i < SizeOfST; i++)
	{
		SymbolTable[i].Name[0] = '\0';
		SymbolTable[i].Size = 0;
		SymbolTable[i].Address = 0;
		SymbolTable[i].Type[0] = '\0';
	}
	return SymbolTable;
}

LT * InitializeLT()
{
	LT * LocalTable = (LT *)malloc(sizeof(LT) * localTableSize);

	for (int i = 0; i < localTableSize; i++)
	{
		LocalTable->BlockName[0] = '\0';
		LocalTable->Address = 0;
	}
	return LocalTable;
}

IL * InitializeIL()
{
	IL *IntermediateLang = (IL *)malloc(sizeof(IL) * SizeOfST);

	for (int i = 0; i < SizeOfST; i++)
	{
		IntermediateLang[i].Opcode = 0;
		IntermediateLang[i].par[0] = -1;
		IntermediateLang[i].par[1] = -1;
		IntermediateLang[i].par[2] = -1;
		IntermediateLang[i].par[3] = -1;
	}
	return IntermediateLang;
}

#endif
