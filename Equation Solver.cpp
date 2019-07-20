#include<iostream>
#include<string>
#include<cstdlib>
#include<sstream>
using namespace std;
// فنكشن ل gauss jordon elimination 
void Gauss(float coff[101][101], double sv[101][101], int n)
{
	for (int i = 0; i < n ; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			if (j != n)
			{
				sv[i][j] = coff[i][j];
			}
			if (j == n)
			{
				sv[i][j] = coff[i][100];
			}
			
		}
	}
	for (int i = 0; i<n; i++) 
	{
		// بحدد اكبر قيمه فى العمود علشان اخليها اول حاجه و اصفر تحتها
		double maxEl = abs(sv[i][i]);
		int maxR = i;
		for (int u = i + 1; u<n; u++) 
		{
			if (abs(sv[u][i]) > maxEl) 
			{
				maxEl = abs(sv[u][i]);
				maxR = u;
			}
		}
		// ببدل الاكبر بالاقل 
		for (int u = i; u<n + 1; u++) 
		{
			double temp = sv[maxR][u];
			sv[maxR][u] = sv[i][u];
			sv[i][u] = temp;
		}
		// بصفر تحت كل عنصر فى الصف طبع القطر الرئيسى
		for (int u = i + 1; u<n; u++) 
		{
			double c = -sv[u][i] / sv[i][i];
			for (int j = i; j<n + 1; j++) 
			{
				if (i == j) 
				{
					sv[u][j] = 0;
				}
				else 
				{
					sv[u][j] += c * sv[i][j];
				}
			}
		}
	}
}
// فنكشن علشان احل المحدد
float det(int m, float detn[101][101])
{
	int si;
	int sj;
	float sdet[101][101];
	float d = 0;
	if (m == 2)
	{
		return((detn[0][0] * detn[1][1]) - (detn[1][0] * detn[0][1]));
	}
	else
	{
		for (int h = 0; h < m; h++)
		{
			si = 0;
			for (int i = 1; i < m; i++)
			{
				sj = 0;
				for (int j = 0; j < m; j++)
				{


					if (j == h)
					{
						continue;
					}
					sdet[si][sj] = detn[i][j];
					sj++;
				}
				si++;
			}
			if (h % 2 != 0)
			{
				d -= detn[0][h] * det(m - 1, sdet);
			}
			if (h % 2 == 0)
			{
				d += detn[0][h] * det(m - 1, sdet);
			}
		}
	}
	return d;
}
int main()
{
	int x;// عدد المعادلات للى هاخده من اليوزر
	string eq[100];// المعادلات اللى هاخدها من اليوزر
	string Var_Name[100];// علشان اخزن اسم المتغيرات
	string eq_ed[100];// هسيف المعادلات بعد التعديل
	string va = "";// هخزن المتغير فيه قبل الاراى
	string coff_const = "";// هخزن الثوابت قبل الاراى
	string coff_final = "";// هجمع المعاملات
	string coff_count = "";// بجمع فيه رقم رقم 
	string cut_str[101][101];// هخزن فيها بعد التقطيع
	string coff_var;// معاملات المتغيرات
	string name;// هستخدمها علشان اقص معاملات المتغير الواحد
				// متغيرات هستخدمها و انا شغال و لازم اعرفها فى الاول
	int k = 0;// هينفعنى فى اللوب علشان اعرف الف لحد فين 
	int m = 0;// عدد المتغيرات
	float coff[101][101];// المعاملات النهائيه بعد تحوليها لارقام
	float coff_num = 0;// بخزن فيه المعامل قبل الاراى و بعد التحويل على طول
	cin >> x;
	for (int i = 0; i < x; i++)
	{
		cin >> eq[i];
	}
	for (int i = 0; i < 100; i++)
	{
		Var_Name[i] = " ";
	}
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			cut_str[i][j] = "";
			coff[i][j] = 0;
		}
	}
	for (int i = 0; i < x; i++)
	{
		eq_ed[i] = eq[i];
	}
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < eq[i].length(); j++)
		{
			if (eq[i][j] != '0' && eq[i][j] != '1' && eq[i][j] != '2' && eq[i][j] != '3' && eq[i][j] != '4' && eq[i][j] != '5' && eq[i][j] != '6' && eq[i][j] != '7' && eq[i][j] != '8' && eq[i][j] != '9' && eq[i][j] != '+' && eq[i][j] != '-' && eq[i][j] != '.' && eq[i][j] != '=')
			{
				// بسأل هو حرف ولا لا
				for (int n = 1; n < eq[i].length(); n++)
				{
					if (eq[i][j + n] == '+' || eq[i][j + n] == '-' || eq[i][j + n] == '=')
					{
						// علشان اعرف اخر المتغير فين
						va = eq[i].substr(j, n);// بقص من اول الحرف لحد ما يلاقى بلص او مينص او يساوى
						j += n;// علشان مخشش فى نفس المتغير تانى
						k++;// بحدد من خلاله انا هلف اد ايه علشان اتأكد هو اتكرر ولا لا
						for (int s = 0; s < k; s++)
						{
							if (Var_Name[s] == va)
							{
								break;
								// لو موجود اخلع
							}
							if (Var_Name[s] != va && Var_Name[s] == " ")
							{
								Var_Name[s] = va;
								m++;
								break;// مش موجود عد يا عداد
							}
						}
						break;// اخرج علشان انا حددت اخره
					}
					if (j + n == eq[i].length())
					{
						// لازم اعمل دى علشان لو كان اخر حاجه مش هيبقى فيه بعده بلص او مينص او يساوى
						va = eq[i].substr(j, n + 1);
						j += n;
						k++;
						for (int s = 0; s < k; s++)
						{
							if (Var_Name[s] == va)
							{
								break;
							}
							if (Var_Name[s] != va && Var_Name[s] == " ")
							{
								Var_Name[s] = va;
								m++;
								break;
							}
						}
						break;
					}
				}
			}
		}
	}
	// sorting ترتيب
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			if (Var_Name[j] < Var_Name[i])
			{
				Var_Name[j].swap(Var_Name[i]);
			}
		}
	}
	// بعدل المعادلات على شكل جنيرال استخدمه على كيفى
	for (int i = 0; i < x; i++)
	{
		int tsawi;
		if (eq_ed[i][0] != '0' && eq_ed[i][0] != '1' && eq_ed[i][0] != '2' && eq_ed[i][0] != '3' && eq_ed[i][0] != '4' && eq_ed[i][0] != '5' && eq_ed[i][0] != '6' && eq_ed[i][0] != '7' && eq_ed[i][0] != '8' && eq_ed[i][0] != '9' && eq_ed[i][0] != '+' && eq_ed[i][0] != '-' && eq_ed[i][0] != '.')
		{
			eq_ed[i].insert(0, "+1");// لو بادىء باسم المتغير زود +1
		}
		if (eq_ed[i][0] == '0' || eq_ed[i][0] == '1' || eq_ed[i][0] == '2' || eq_ed[i][0] == '3' || eq_ed[i][0] == '4' || eq_ed[i][0] == '5' || eq_ed[i][0] == '6' || eq_ed[i][0] == '7' || eq_ed[i][0] == '8' || eq_ed[i][0] == '9' || eq_ed[i][0] == '.')
		{
			eq_ed[i].insert(0, "+");//  لو بادىء بالمعامل زود اشاره
		}
		tsawi = eq_ed[i].find('=');
		// نفس الكلام على اللى بعد اليساوى
		if (eq_ed[i][tsawi + 1] != '0' && eq_ed[i][tsawi + 1] != '1' && eq_ed[i][tsawi + 1] != '2' && eq_ed[i][tsawi + 1] != '3' && eq_ed[i][tsawi + 1] != '4' && eq_ed[i][tsawi + 1] != '5' && eq_ed[i][tsawi + 1] != '6' && eq_ed[i][tsawi + 1] != '7' && eq_ed[i][tsawi + 1] != '8' && eq_ed[i][tsawi + 1] != '9' && eq_ed[i][tsawi + 1] != '+' && eq_ed[i][tsawi + 1] != '-' && eq_ed[i][tsawi + 1] != '.')
		{
			eq_ed[i].insert(tsawi + 1, "+1");
		}
		if (eq_ed[i][tsawi + 1] == '0' || eq_ed[i][tsawi + 1] == '1' || eq_ed[i][tsawi + 1] == '2' || eq_ed[i][tsawi + 1] == '3' || eq_ed[i][tsawi + 1] == '4' || eq_ed[i][tsawi + 1] == '5' || eq_ed[i][tsawi + 1] == '6' || eq_ed[i][tsawi + 1] == '7' || eq_ed[i][tsawi + 1] == '8' || eq_ed[i][tsawi + 1] == '9' || eq_ed[i][tsawi + 1] == '.')
		{
			eq_ed[i].insert(tsawi + 1, "+");
		}
		for (int j = 0; j < eq_ed[i].length(); j++)
		{
			if ((eq_ed[i][j] == '+' || eq_ed[i][j] == '-') && (eq_ed[i][j + 1] != '0' && eq_ed[i][j + 1] != '1' && eq_ed[i][j + 1] != '2' && eq_ed[i][j + 1] != '3' && eq_ed[i][j + 1] != '4' && eq_ed[i][j + 1] != '5' && eq_ed[i][j + 1] != '6' && eq_ed[i][j + 1] != '7' && eq_ed[i][j + 1] != '8' && eq_ed[i][j + 1] != '9' && eq_ed[i][j + 1] != '.'))
			{
				eq_ed[i].insert(j + 1, "1");
			}
		}
		tsawi = eq_ed[i].find('=');
		// بغير اشارت بعد اليساوى
		// ملحوظه انا هنا غيرت اشارت الثوابت برضه هعمل حسابها فى كود تانى ليها
		for (int j = tsawi + 1; j < eq_ed[i].length(); j++)
		{
			if (eq_ed[i][j] == '+')
			{
				eq_ed[i][j] = '-';
				j++;
			}
			else if (eq_ed[i][j] == '-')
			{
				eq_ed[i][j] = '+';
			}
		}
	}
	// هنا بقص المعاملات بنفس مبدأ قص المتغير
	for (int i = 0; i < x; i++)
	{
		for (int u = 0; u < m; u++)
		{
			for (int j = 0; j < eq_ed[i].length(); j++)
			{
				if (eq_ed[i][j] != '0' && eq_ed[i][j] != '1' && eq_ed[i][j] != '2' && eq_ed[i][j] != '3' && eq_ed[i][j] != '4' && eq_ed[i][j] != '5' && eq_ed[i][j] != '6' && eq_ed[i][j] != '7' && eq_ed[i][j] != '8' && eq_ed[i][j] != '9' && eq_ed[i][j] != '+' && eq_ed[i][j] != '-' && eq_ed[i][j] != '.' && eq_ed[i][j] != '=')
				{
					for (int n = 1; n < eq_ed[i].length(); n++)
					{
						if (eq_ed[i][j + n] == '+' || eq_ed[i][j + n] == '-' || eq_ed[i][j + n] == '=')
						{
							name = eq_ed[i].substr(j, n);
							if (name == Var_Name[u])
							{
								int k = 0;
								for (int q = j - 1; q < eq_ed[i].length(); q--)
								{
									k++;
									if (eq_ed[i][q] == '+' || eq_ed[i][q] == '-')
									{
										coff_var = coff_var + eq_ed[i].substr(q, k);
										break;
									}
								}
							}
							j += n;
							break;
						}
						if (j + n == eq_ed[i].length())
						{
							name = eq_ed[i].substr(j, n + 1);
							if (name == Var_Name[u])
							{
								int k = 0;
								for (int q = j - 1; q < eq_ed[i].length(); q--)
								{
									k++;
									if (eq_ed[i][q] == '+' || eq_ed[i][q] == '-')
									{
										coff_var = coff_var + eq_ed[i].substr(q, k);
										break;
									}
								}
							}
							j += n;
							break;
						}
					}
				}
			}
			cut_str[i][u] = coff_var;
			coff_var = "";
		}
	}
	// بقص الثوابت بنفس المبدأ برضه
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < eq_ed[i].length(); j++)
		{
			if (eq_ed[i][j] == '+' || eq_ed[i][j] == '-')
			{
				coff_const += eq_ed[i][j];
				for (int n = j + 1; n < eq_ed[i].length(); n++)
				{
					if (eq_ed[i][n] == '0' || eq_ed[i][n] == '1' || eq_ed[i][n] == '2' || eq_ed[i][n] == '3' || eq_ed[i][n] == '4' || eq_ed[i][n] == '5' || eq_ed[i][n] == '6' || eq_ed[i][n] == '7' || eq_ed[i][n] == '8' || eq_ed[i][n] == '9' || eq_ed[i][n] == '.')
					{
						coff_const += eq_ed[i][n];
						if (eq_ed[i][n + 1] == '+' || eq_ed[i][n + 1] == '-' || eq_ed[i][n + 1] == '=')
						{
							coff_final += coff_const;
							coff_const = "";
							j = n;
							break;
						}
						if (n == eq_ed[i].length() - 1)
						{
							coff_final += coff_const;
							coff_const = "";
							j = n;
							break;
						}
					}
					if (eq_ed[i][n + 1] != '0' && eq_ed[i][n + 1] != '1' && eq_ed[i][n + 1] != '2' && eq_ed[i][n + 1] != '3' && eq_ed[i][n + 1] != '4' && eq_ed[i][n + 1] != '5' && eq_ed[i][n + 1] != '6' && eq_ed[i][n + 1] != '7' && eq_ed[i][n + 1] != '8' && eq_ed[i][n + 1] != '9' && eq_ed[i][n + 1] != '.')
					{
						coff_const = "";
						j = n;
						break;
					}
				}
			}
		}
		// انا كنت فى الكود اللى فوق عكست اشاره الثوابت اللى بعد اليساوى هنا بقى انا بعد ما جمعتهم عكست كله لان كده كده بقى اللى قبل و بعد اليساوى عكس الاشاره
		for (int u = 0; u < coff_final.length(); u++)
		{
			if (coff_final[u] == '+')
			{
				coff_final[u] = '-';
				u++;
			}
			else if (coff_final[u] == '-')
			{
				coff_final[u] = '+';
			}
		}
		cut_str[i][100] = coff_final;
		coff_final = "";
	}
	// كود تحويل المعاملات من استرينجات لفلوت
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			for (int p = 0; p < cut_str[i][j].length(); p++)
			{
				if (cut_str[i][j][p] == '+' || cut_str[i][j][p] == '-')
				{
					for (int n = p + 1; n < cut_str[i][j].length(); n++)
					{
						if (cut_str[i][j][n] != '+' && cut_str[i][j][n] != '-')
						{
							coff_count += cut_str[i][j][n];
							if (cut_str[i][j][n + 1] == '+' || cut_str[i][j][n + 1] == '-')
							{
								if (cut_str[i][j][p] == '+')
								{
									coff_num += (atof(coff_count.c_str()));
									coff_count = "";
									p = n;
									break;
								}
								if (cut_str[i][j][p] == '-')
								{
									coff_num += (-1) * (atof(coff_count.c_str()));
									coff_count = "";
									p = n;
									break;
								}
							}
							if (n == cut_str[i][j].length() - 1)
							{
								if (cut_str[i][j][p] == '+')
								{
									coff_num += atof(coff_count.c_str());
									coff_count = "";
									p = n;
									break;
								}
								if (cut_str[i][j][p] == '-')
								{
									coff_num += (-1) * atof(coff_count.c_str());
									coff_count = "";
									p = n;
									break;
								}
							}
						}
					}
				}
			}
			coff[i][j] = coff_num;
			coff_num = 0;
		}
	}
	while (1)
	{
		string o;
		getline(cin, o);
		if (o == "num_vars")
		{
			cout << m << "\n";
		}
		if (o.substr(0, 8) == "equation")
		{
			int g = atof(o.substr(9).c_str());
			int b = g - 1;
			for (int i = 0; i < m; i++)
			{
				if (coff[b][i] > 0)
				{
					cout << coff[b][i] << Var_Name[i];
					for (int j = i + 1; j < 100 - i; j++)
					{
						if (coff[b][j] > 0)
						{
							cout << '+';
							break;
						}
						if (coff[b][j] < 0)
						{
							break;
						}
					}
				}
				if (coff[b][i] < 0)
				{
					cout << coff[b][i] << Var_Name[i];
					for (int j = i + 1; j < 100 - i; j++)
					{
						if (coff[b][j] > 0)
						{
							cout << '+';
							break;
						}
						if (coff[b][j] < 0)
						{
							break;
						}
					}
				}
			}
			cout << '=' << coff[b][100] << "\n";
		}
		if (o.substr(0, 6) == "column")
		{
			string col = o.substr(7);
			for (int i = 0; i < m; i++)
			{
				if (Var_Name[i] == col)
				{
					for (int j = 0; j < x; j++)
					{
						cout << coff[j][i] << "\n";
					}
					break;
				}
			}
		}
		if (o.substr(0, 3) == "add")
		{
			string num = o.substr(4);
			int t = num.find(" ");
			int a = atof(num.substr(0, t).c_str()) - 1;
			int b = atof(num.substr(t + 1).c_str()) - 1;
			float add[101];
			for (int i = 0; i < 101; i++)
			{
				add[i] = 0;
			}
			for (int i = 0; i < m; i++)
			{
				add[i] = coff[b][i] + coff[a][i];
			}
			add[100] = coff[a][100] + coff[b][100];
			for (int i = 0; i < m; i++)
			{
				if (add[i] > 0)
				{
					cout << add[i] << Var_Name[i];
					for (int j = i + 1; j < 100 - i; j++)
					{
						if (add[j] > 0)
						{
							cout << '+';
							break;
						}
						if (add[j] < 0)
						{
							break;
						}
					}
				}
				if (add[i] < 0)
				{
					cout << add[i] << Var_Name[i];
					for (int j = i + 1; j < 100 - i; j++)
					{
						if (add[j] > 0)
						{
							cout << '+';
							break;
						}
						if (add[j] < 0)
						{
							break;
						}
					}
				}
			}
			cout << '=' << add[100] << "\n";
		}
		if (o.substr(0, 8) == "subtract")
		{
			string num = o.substr(9);
			int t = num.find(" ");
			int a = atof(num.substr(0, t).c_str());
			int b = atof(num.substr(t + 1).c_str());
			float sub[101];
			for (int i = 0; i < 101; i++)
			{
				sub[i] = 0;
			}
			for (int i = 0; i < m; i++)
			{
				sub[i] = coff[a - 1][i] - coff[b - 1][i];
			}
			sub[100] = coff[a - 1][100] - coff[b - 1][100];
			for (int i = 0; i < m; i++)
			{
				if (sub[i] > 0)
				{
					cout << sub[i] << Var_Name[i];
					for (int j = i + 1; j < 100 - i; j++)
					{
						if (sub[j] > 0)
						{
							cout << '+';
							break;
						}
						if (sub[j] < 0)
						{
							break;
						}
					}
				}
				if (sub[i] < 0)
				{
					cout << sub[i] << Var_Name[i];
					for (int j = i + 1; j < 100 - i; j++)
					{
						if (sub[j] > 0)
						{
							cout << '+';
							break;
						}
						if (sub[j] < 0)
						{
							break;
						}
					}
				}
			}
			cout << '=' << sub[100] << "\n";
		}
		if (o.substr(0, 10) == "substitute")
		{
			string cut = o.substr(11);
			string var = cut.substr(0, cut.find(" "));
			string eq_num = cut.substr(cut.find(" ") + 1);
			int a = atof(eq_num.substr(0, eq_num.find(" ")).c_str()) - 1;
			int b = atof(eq_num.substr(eq_num.find(" ") + 1).c_str()) - 1;
			int n;
			float sut[2][101];
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 101; j++)
				{
					sut[i][j] = 0;
				}
			}
			for (int i = 0; i < m; i++)
			{
				if (Var_Name[i] == var)
				{
					n = i;
					break;
				}
			}
			sut[0][100] = coff[a][100];
			sut[1][100] = coff[b][100];
			for (int j = 0; j < m; j++)
			{
				sut[0][j] = coff[a][j];
				sut[1][j] = coff[b][j];
			}
			if (coff[b][n] == 0 || coff[a][n] == 0)
			{
				for (int i = 0; i < m; i++)
				{
					if (coff[a][i] > 0)
					{
						cout << coff[a][i] << Var_Name[i];
						for (int j = i + 1; j < 100 - i; j++)
						{
							if (coff[a][j] > 0)
							{
								cout << '+';
								break;
							}
							if (coff[a][j] < 0)
							{
								break;
							}
						}
					}
					if (coff[a][i] < 0)
					{
						cout << coff[a][i] << Var_Name[i];
						for (int j = i + 1; j < 100 - i; j++)
						{
							if (coff[a][j] > 0)
							{
								cout << '+';
								break;
							}
							if (coff[a][j] < 0)
							{
								break;
							}
						}
					}
				}
				cout << '=' << coff[a][100] << "\n";
			}
			else
			{
				float temp = (sut[1][n] / sut[0][n]);
				sut[0][100] *= temp;
				for (int i = 0; i < m; i++)
				{
					sut[0][i] *= temp;
				}
				float s[101];
				for (int i = 0; i < 101; i++)
				{
					s[i] = 0;
				}
				s[100] = sut[0][100] - sut[1][100];
				for (int i = 0; i < m; i++)
				{
					if (i != n)
					{
						s[i] = sut[0][i] - sut[1][i];
					}
				}
				for (int i = 0; i < m; i++)
				{
					if (i != n)
					{
						if (s[i] > 0)
						{
							cout << s[i] << Var_Name[i];
							for (int j = i + 1; j < 100 - i; j++)
							{
								if (s[j] > 0)
								{
									cout << '+';
									break;
								}
								if (s[j] < 0)
								{
									break;
								}
							}
						}
						if (s[i] < 0)
						{
							cout << s[i] << Var_Name[i];
							for (int j = i + 1; j < 100 - i; j++)
							{
								if (s[j] > 0)
								{
									cout << '+';
									break;
								}
								if (s[j] < 0)
								{
									break;
								}
							}
						}
					}
				}
				cout << '=' << s[100] << "\n";
			}
		}
		if (o == "D")
		{
			for (int i = 0; i < x; i++)
			{
				for (int j = 0; j < m; j++)
				{
					cout << coff[i][j] << "\t";
				}
				cout << "\n";
			}
		}
		if (o.substr(0, 2) == "D ")
		{
			string var = o.substr(2);
			int n;
			for (int i = 0; i < m; i++)
			{
				if (Var_Name[i] == var)
				{
					n = i;
				}
			}
			for (int i = 0; i < x; i++)
			{
				for (int j = 0; j < m; j++)
				{
					if (j != n)
					{
						cout << coff[i][j] << "\t";
					}
					if (j == n)
					{
						cout << coff[i][100] << "\t";
					}
				}
				cout << "\n";
			}
		}
		if (o == "D_value")
		{
			if (x > m || m > x)
			{
				cout << "Not Valid" << "\n";
			}
			if (x == m)
			{
				if (m == 1)
				{
					cout << coff[0][0] << "\n";
				}
				if (m == 2)
				{
					cout << (coff[0][0] * coff[1][1]) - (coff[1][0] * coff[0][1]) << "\n";
				}
				else
				{
					cout << det(m, coff) << "\n";
				}
			}
		}
		if (o == "solve")
		{
			if (x > m || x < m)
			{
				cout << "No Solution" << "\n";
			}
			if (x == m)
			{
				if (m == 1)
				{
					cout << Var_Name[0] << "=" << coff[0][100] / coff[0][0] << "\n";
				}
				else
				{
					double sv[101][101];
					Gauss(coff, sv, m);
					double values[100];
					for (int i = m - 1; i >= 0; i--)
					{
						values[i] = sv[i][m] / sv[i][i];
						for (int k = i - 1; k >= 0; k--)
						{
							sv[k][m] -= sv[k][i] * values[i];
						}
					}
					for (int i = 0; i < m; i++)
					{
						cout << Var_Name[i] << "=" << values[i] << "\n";
					}
				}
			}
		}
		if (o == "quit")
		{
			break;
		}
	}
	system("Pause");
	return 0;
}