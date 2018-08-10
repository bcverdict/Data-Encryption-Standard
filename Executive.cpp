#include "Executive.h"
#include <iostream>
#include <bitset>
#include <cmath>
#include <sstream>
using namespace std;
Executive::Executive()
{
	M={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF};
	K={0x1,0x3,0x3,0x4,0x5,0x7,0x7,0x9,0x9,0xB,0xB,0xC,0xD,0xF,0xF,0x1};
	Final = new bool[64];
}
Executive::~Executive()
{
	delete [] Final;
}
void Executive::run()
{
	//assigns proper binary for K
	for(unsigned int i = 0; i<K.size(); i++)
	{
		for(int j = 3; j>=0; j--)
		{
			Kbit[4*i+abs(j-3)]=(bitset<4>(K.c_str()[i]))[j];
		}
	}
	//assigns proper 56-bit permutation
	for(int i = 0; i<8; i++)
	{
		for(int j = 0; j<7; j++)
		{
			Kplus[7*i+j]=Kbit[PC1[i][j]-1];
		}
	}
	Shift();
	Keys();
	IPpermutation();
	f(R0, R1, L0, L2, K1);
	f(R1, R2, L1, L3, K2);
	f(R2, R3, L2, L4, K3);
	f(R3, R4, L3, L5, K4);
	f(R4, R5, L4, L6, K5);
	f(R5, R6, L5, L7, K6);
	f(R6, R7, L6, L8, K7);
	f(R7, R8, L7, L9, K8);
	f(R8, R9, L8, L10, K9);
	f(R9, R10, L9, L11, K10);
	f(R10, R11, L10, L12, K11);
	f(R11, R12, L11, L13, K12);
	f(R12, R13, L12, L14, K13);
	f(R13, R14, L13, L15, K14);
	f(R14, R15, L14, L16, K15);
	f(R15, R16, L15, L17, K16);
	FinalPerm();
}
void Executive::Shift()
{
	for(int i = 0; i<28; i++)
	{
		C0[i]=Kplus[i];
		D0[i]=Kplus[i+28];
	}
	C1[27]=C0[0];
	D1[27]=D0[0];
	for(int i = 0; i<27; i++)
	{
		C1[i]=C0[i+1];
		D1[i]=D0[i+1];
	}
	C2[27]=C1[0];
	D2[27]=D1[0];
	for(int i = 0; i<27; i++)
	{
		C2[i]=C1[i+1];
		D2[i]=D1[i+1];
	}
	C3[26]=C2[0];
	C3[27]=C2[1];
	D3[26]=D2[0];
	D3[27]=D2[1];
	for(int i = 0; i<26; i++)
	{
		C3[i]=C2[i+2];
		D3[i]=D2[i+2];
	}
	C4[26]=C3[0];
	C4[27]=C3[1];
	D4[26]=D3[0];
	D4[27]=D3[1];
	for(int i = 0; i<26; i++)
	{
		C4[i]=C3[i+2];
		D4[i]=D3[i+2];
	}
	C5[26]=C4[0];
	C5[27]=C4[1];
	D5[26]=D4[0];
	D5[27]=D4[1];
	for(int i = 0; i<26; i++)
	{
		C5[i]=C4[i+2];
		D5[i]=D4[i+2];
	}
	C6[26]=C5[0];
	C6[27]=C5[1];
	D6[26]=D5[0];
	D6[27]=D5[1];
	for(int i = 0; i<26; i++)
	{
		C6[i]=C5[i+2];
		D6[i]=D5[i+2];
	}
	C7[26]=C6[0];
	C7[27]=C6[1];
	D7[26]=D6[0];
	D7[27]=D6[1];
	for(int i = 0; i<26; i++)
	{
		C7[i]=C6[i+2];
		D7[i]=D6[i+2];
	}
	C8[26]=C7[0];
	C8[27]=C7[1];
	D8[26]=D7[0];
	D8[27]=D7[1];
	for(int i = 0; i<26; i++)
	{
		C8[i]=C7[i+2];
		D8[i]=D7[i+2];
	}
	C9[27]=C8[0];
	D9[27]=D8[0];
	for(int i = 0; i<27; i++)
	{
		C9[i]=C8[i+1];
		D9[i]=D8[i+1];
	}
	C10[26]=C9[0];
	C10[27]=C9[1];
	D10[26]=D9[0];
	D10[27]=D9[1];
	for(int i = 0; i<26; i++)
	{
		C10[i]=C9[i+2];
		D10[i]=D9[i+2];
	}
	C11[26]=C10[0];
	C11[27]=C10[1];
	D11[26]=D10[0];
	D11[27]=D10[1];
	for(int i = 0; i<26; i++)
	{
		C11[i]=C10[i+2];
		D11[i]=D10[i+2];
	}
	C12[26]=C11[0];
	C12[27]=C11[1];
	D12[26]=D11[0];
	D12[27]=D11[1];
	for(int i = 0; i<26; i++)
	{
		C12[i]=C11[i+2];
		D12[i]=D11[i+2];
	}
	C13[26]=C12[0];
	C13[27]=C12[1];
	D13[26]=D12[0];
	D13[27]=D12[1];
	for(int i = 0; i<26; i++)
	{
		C13[i]=C12[i+2];
		D13[i]=D12[i+2];
	}
	C14[26]=C13[0];
	C14[27]=C13[1];
	D14[26]=D13[0];
	D14[27]=D13[1];
	for(int i = 0; i<26; i++)
	{
		C14[i]=C13[i+2];
		D14[i]=D13[i+2];
	}
	C15[26]=C14[0];
	C15[27]=C14[1];
	D15[26]=D14[0];
	D15[27]=D14[1];
	for(int i = 0; i<26; i++)
	{
		C15[i]=C14[i+2];
		D15[i]=D14[i+2];
	}
	C16[27]=C15[0];
	D16[27]=D15[0];
	for(int i = 0; i<27; i++)
	{
		C16[i]=C15[i+1];
		D16[i]=D15[i+1];
	}
}
void Executive::Keys()
{
	for(int i = 0; i<8; i++)
	{
		for(int j = 0; j<6; j++)
		{
			if((PC2[i][j]-1)<28)
			{
				K1[6*i+j]=C1[PC2[i][j]-1];
				K2[6*i+j]=C2[PC2[i][j]-1];
				K3[6*i+j]=C3[PC2[i][j]-1];
				K4[6*i+j]=C4[PC2[i][j]-1];
				K5[6*i+j]=C5[PC2[i][j]-1];
				K6[6*i+j]=C6[PC2[i][j]-1];
				K7[6*i+j]=C7[PC2[i][j]-1];
				K8[6*i+j]=C8[PC2[i][j]-1];
				K9[6*i+j]=C9[PC2[i][j]-1];
				K10[6*i+j]=C10[PC2[i][j]-1];
				K11[6*i+j]=C11[PC2[i][j]-1];
				K12[6*i+j]=C12[PC2[i][j]-1];
				K13[6*i+j]=C13[PC2[i][j]-1];
				K14[6*i+j]=C14[PC2[i][j]-1];
				K15[6*i+j]=C15[PC2[i][j]-1];
				K16[6*i+j]=C16[PC2[i][j]-1];
			}
			else
			{
				K1[6*i+j]=D1[PC2[i][j]-29];
				K2[6*i+j]=D2[PC2[i][j]-29];
				K3[6*i+j]=D3[PC2[i][j]-29];
				K4[6*i+j]=D4[PC2[i][j]-29];
				K5[6*i+j]=D5[PC2[i][j]-29];
				K6[6*i+j]=D6[PC2[i][j]-29];
				K7[6*i+j]=D7[PC2[i][j]-29];
				K8[6*i+j]=D8[PC2[i][j]-29];
				K9[6*i+j]=D9[PC2[i][j]-29];
				K10[6*i+j]=D10[PC2[i][j]-29];
				K11[6*i+j]=D11[PC2[i][j]-29];
				K12[6*i+j]=D12[PC2[i][j]-29];
				K13[6*i+j]=D13[PC2[i][j]-29];
				K14[6*i+j]=D14[PC2[i][j]-29];
				K15[6*i+j]=D15[PC2[i][j]-29];
				K16[6*i+j]=D16[PC2[i][j]-29];
			}
		}
	}
}
void Executive::IPpermutation()
{
	//assigns proper binary for M
	for(unsigned int i = 0; i<M.size(); i++)
	{
		for(int j = 3; j>=0; j--)
		{
			Mbit[4*i+abs(j-3)]=(bitset<4>(M.c_str()[i]))[j];
		}
	}
	//assigns proper 64-bit permutation
	for(int i = 0; i<8; i++)
	{
		for(int j = 0; j<8; j++)
		{
			IPbit[8*i+j]=Mbit[IP[i][j]-1];
		}
	}
	for(int i = 0; i<32; i++)
	{
		L0[i]=IPbit[i];
		L1[i]=R0[i]=IPbit[i+32];
	}
}
bool * Executive::XOR(bitset<48> Rn, bitset<48> Kn)
{
	for(int i = 0; i<48; i++)
	{
		Final[i]=(Rn[i]!=Kn[i]);
	}
	return(Final);
}
void Executive::f(bitset<32> Rn, bitset<32>& Rn1, bitset<32>& Ln0, bitset<32>& Ln, bitset<48> Kn)
{
	bitset<48> tempRn;
	bool * XORFin;
	for(int i = 0; i<48; i++)
	{
		tempRn[i]=Rn[ETable[i/6][i%6]-1];
	}
	XORFin = XOR(tempRn,Kn);
	bitset<2> Row;
	bitset<4> Col;
	bitset<4> Sol;
	bitset<32> PSol;
	for(int k = 0; k<8;k++)
	{
		for(int i = 0; i<2; i++)
		{
			//Row must begin at five thus 'i+5'
			//Row must then decrement by 6 thus '-i*6'
			//Row must increment every 6 bits thus '+k*6'
			Row[i]=XORFin[i+5-i*6+k*6];
		}
		for(int j = 0; j<4; j++)
		{
			//Columns must begin at 4 and decrement by 1 thus '4-j'
			//Columns must increment every 6 bits thus '+k*6'
			Col[j]=XORFin[4-j+6*k];
		}
		//cout<<endl<<"["<<Row.to_ulong()<<"]["<<Col.to_ulong()<<"]";
		switch(k)
		{
			case 0:
				Sol=S1[Row.to_ulong()][Col.to_ulong()];
			break;
			case 1:
				Sol=S2[Row.to_ulong()][Col.to_ulong()];
			break;
			case 2:
				Sol=S3[Row.to_ulong()][Col.to_ulong()];
			break;
			case 3:
				Sol=S4[Row.to_ulong()][Col.to_ulong()];
			break;
			case 4:
				Sol=S5[Row.to_ulong()][Col.to_ulong()];
			break;
			case 5:
				Sol=S6[Row.to_ulong()][Col.to_ulong()];
			break;
			case 6:
				Sol=S7[Row.to_ulong()][Col.to_ulong()];
			break;
			case 7:
				Sol=S8[Row.to_ulong()][Col.to_ulong()];
			break;
			default:
			break;
		}
		for(int i = 0; i<4;i++)
		{
			PSol[i+4*k]=Sol[3-i];
		}
	}
	for(int i = 0; i<32; i++)
	{
		Rn1[i]=PSol[P[i/4][i%4]-1];
	}
	for(int i = 0; i<32; i++)
	{
		bitset<1> x(Rn1[i]);
		bitset<1> y(Ln0[i]);
		x^=y;
		Rn1[i]=x[0];
		Ln[i] = x[0];
	}
}
void Executive::FinalPerm()
{
	for(int i = 0; i<64; i++)
	{
		if((IPFin[i/8][i%8]-1)<32)
		{
			//index '63-i' is used to reverse the order of the bits since accessing the bits like an array will reverse the order 
			Finalbit[63-i]=R16[IPFin[i/8][i%8]-1];
		}
		else
		{
			Finalbit[63-i]=L16[IPFin[i/8][i%8]-33];
		}
	}
	cout<<endl<<"Final result:"<<endl<<hex<<uppercase<<Finalbit.to_ulong();
}

