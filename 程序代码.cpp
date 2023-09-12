#include <iostream>
using namespace std;
int main()
{
	cout<< "请输入10位密钥" << endl;
	//输入密钥
	int key[10];
	for(int i = 0; i < 10; i++)
	{
		cin >> key[i];
	}//得到密钥key[10]
	//p10置换
	int temp[10];
	temp[0] = key[2];
	temp[1] = key[4];
	temp[2] = key[1];
	temp[3] = key[6];
	temp[4] = key[3];
	temp[5] = key[9];
	temp[6] = key[0];
	temp[7] = key[8];
	temp[8] = key[7];
	temp[9] = key[5];//p10置换成功temp[10]
	//分两部分
	int L[5];
	int R[5];
	for (int i = 0; i < 5; i++)
	{
		L[i] = temp[i];
		R[i] = temp[i + 5];
	}
	//左移1位
	int temp_1_L = L[0], temp_1_R = R[0];
	for (int i = 0; i < 4; i++)
	{
		L[i] = L[i + 1];
		R[i] = R[i + 1];
	}
	L[4] = temp_1_L, R[4] = temp_1_R;//左移一位结束
	//p8置换
	int K1[8];
	K1[0] = R[0];
	K1[1] = L[2];
	K1[2] = R[1];
	K1[3] = L[3];
	K1[4] = R[2];
	K1[5] = L[4];
	K1[6] = R[4];
	K1[7] = R[3];
	//得到k1[8]
	//左移2位
	temp_1_L = L[0], temp_1_R = R[0];
	int temp_2_L = L[1], temp_2_R = R[1];
	for (int i = 0; i < 3; i++)
	{
		L[i] = L[i + 2];
		R[i] = R[i + 2];
	}
	L[3] = temp_1_L, R[3] = temp_1_R;
	L[4] = temp_2_L, R[4] = temp_2_R;//左移二位完成
	//p8置换
	int K2[8];
	K2[0] = R[0];
	K2[1] = L[2];
	K2[2] = R[1];
	K2[3] = L[3];
	K2[4] = R[2];
	K2[5] = L[4];
	K2[6] = R[4];
	K2[7] = R[3];
	//得到K2[8]
	cout << "请输入明文" << endl;
	int C[8];
	//输入明文
	for (int i = 0; i < 8; i++)
	{
		cin >> C[i];
	}
	//进行IP置换
	int IP[8];
	IP[0] = C[1];
	IP[1] = C[5];
	IP[2] = C[2];
	IP[3] = C[0];
	IP[4] = C[3];
	IP[5] = C[7];
	IP[6] = C[4];
	IP[7] = C[6];
	//分成两部分
	int L0[4];
	int R0[4];
	for (int i = 0; i < 4; i++)
	{
		L0[i] = IP[i];
		R0[i] = IP[i + 4];
	}
	//L1[4]就是R0[4]
	int L1[4];
	for (int i = 0; i < 4;i++)
	{
		L1[i] = R0[i];
	}//得到L1
	//R0[4]和K1[8]进行f运算
	//R0[4]进行ep运算
	int EP[8];
	EP[0] = R0[3];
	EP[1] = R0[0];
	EP[2] = R0[1];
	EP[3] = R0[2];
	EP[4] = R0[1];
	EP[5] = R0[2];
	EP[6] = R0[3];
	EP[7] = R0[0];
	//EP[8]和K1异或
	int EH[8];
	for (int i = 0; i < 8; i++)
	{
		if (EP[i] == K1[i])
		{
			EH[i] = 0;
		}
		else EH[i] = 1;
	}//异或结束
	//进入S盒
    //分两部分
	int S1[4];
	int S2[4];
	for (int i = 0; i < 4; i++)
	{
		S1[i] = EH[i];
		S2[i] = EH[i + 4];
	}
	//开始s盒置换
	int i_S1 = S1[0] * 2 + S1[3];//S1盒行数
	int j_S1 = S1[1] * 2 + S1[2];//S1盒列数
	int i_S2 = S2[0] * 2 + S2[3];//S2盒行数
	int j_S2 = S2[1] * 2 + S2[2];//S2盒列数
	int P4_1;
	int P4_2;//进入s盒之后的十进制数字
	int SH1[4][4] = { {1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2} };
	int SH2[4][4] = { {0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3} };
	P4_1 = SH1[i_S1][j_S1];
	P4_2 = SH2[i_S2][j_S2];
	//将得到的数字换成二进制
	int S_P4[4];
	if ( P4_1== 0)
	{
		S_P4[0] = 0;
		S_P4[1] = 0;
	}
	else if (P4_1 == 1)
	{
		S_P4[0] = 0;
		S_P4[1] = 1;
	}
	else if (P4_1 == 2)
	{
		S_P4[0] = 1;
		S_P4[1] = 0;
	}
	else if (P4_1 == 3)
	{
		S_P4[0] = 1;
		S_P4[1] = 1;
	}
	if (P4_2 == 0)
	{
		S_P4[2] = 0;
		S_P4[3] = 0;
	}
	else if (P4_2 == 1)
	{
		S_P4[2] = 0;
		S_P4[3] = 1;
	}
	else if (P4_2 == 2)
	{
		S_P4[2] = 1;
		S_P4[3] = 0;
	}
	else if (P4_2 == 3)
	{
		S_P4[2] = 1;
		S_P4[3] = 1;
	}
	int IP_4_1[4];
	IP_4_1[0] = S_P4[1];
	IP_4_1[1] = S_P4[3];
	IP_4_1[2] = S_P4[2];
	IP_4_1[3] = S_P4[0];
	//IP_4_1和L0异或
	for (int i = 0; i < 4; i++)
	{
		if (IP_4_1[i] == L0[i])
		{
			EH[i] = 0;
		}
		else EH[i] = 1;
	}
	//异或后是R1
	int R1[4];
	for (int i = 0; i < 4; i++)
	{
		R1[i] = EH[i];
	}
	//R1就是R2
	int R2[4];
	for (int i = 0; i < 4; i++)
	{
		R2[i] = R1[i];
	}
	//R1和K2进行f运算
	//R1进行EP运算
	EP[0] = R1[3];
	EP[1] = R1[0];
	EP[2] = R1[1];
	EP[3] = R1[2];
	EP[4] = R1[1];
	EP[5] = R1[2];
	EP[6] = R1[3];
	EP[7] = R1[0];
	//EP和K2异或
	for (int i = 0; i < 8; i++)
	{
		if (EP[i] == K2[i])
		{
			EH[i] = 0;
		}
		else EH[i] = 1;
	}
		//进行s盒运算
		for (int i = 0; i < 4; i++)
		{
			S1[i] = EH[i];
			S2[i] = EH[i + 4];
		}
		i_S1 = S1[0] * 2 + S1[3];//S1盒行数
		j_S1 = S1[1] * 2 + S1[2];//S1盒列数
		i_S2 = S2[0] * 2 + S2[3];//S2盒行数
		j_S2 = S2[1] * 2 + S2[2];//S2盒列数
		//进入s盒之后的十进制数字
		P4_1 = SH1[i_S1][j_S1];
		P4_2 = SH2[i_S2][j_S2];
		//将得到的数字换成二进制

		if (P4_1 == 0)
		{
			S_P4[0] = 0;
			S_P4[1] = 0;
		}
		else if (P4_1 == 1)
		{
			S_P4[0] = 0;
			S_P4[1] = 1;
		}
		else if (P4_1 == 2)
		{
			S_P4[0] = 1;
			S_P4[1] = 0;
		}
		else if (P4_1 == 3)
		{
			S_P4[0] = 1;
			S_P4[1] = 1;
		}
		if (P4_2 == 0)
		{
			S_P4[2] = 0;
			S_P4[3] = 0;
		}
		else if (P4_2 == 1)
		{
			S_P4[2] = 0;
			S_P4[3] = 1;
		}
		else if (P4_2 == 2)
		{
			S_P4[2] = 1;
			S_P4[3] = 0;
		}
		else if (P4_2 == 3)
		{
			S_P4[2] = 1;
			S_P4[3] = 1;
		}
		IP_4_1[0] = S_P4[1];
		IP_4_1[1] = S_P4[3];
		IP_4_1[2] = S_P4[2];
		IP_4_1[3] = S_P4[0];
		//IP_4_1和L1异或
		for (int i = 0; i < 4; i++)
		{
			if (IP_4_1[i] == L0[i])
			{
				EH[i] = 0;
			}
			else EH[i] = 1;
		}
		//异或之后是L2
		int L2[4];
		for (int i = 0; i < 4; i++)
		{
			L2[i] = EH[i];
		}
	//L2和R2进行IP逆置换
		int N_IP[8];
		N_IP[0] = L2[3];
		N_IP[1] = L2[0];
		N_IP[2] = L2[2];
		N_IP[3] = R2[0];
		N_IP[4] = R2[2];
		N_IP[5] = L2[1];
		N_IP[6] = R2[3];
		N_IP[7] = R2[1];
		cout << "密文是：" << endl;
		for (int i = 0; i < 8; i++)
		{
			cout << N_IP[i];
		}

		return 0;
}