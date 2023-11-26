#include<iostream>
#include<algorithm>
using namespace std;

int n;
int c;
double cw = 0, cv = 0;//ʣ�����������м�ֵ
int bestv = 0;//���ż�ֵ

struct subject
{
    double w;//����
    double v;//��ֵ
    double p;//ƽ����ֵ
}s[1008];

bool cmp(subject a, subject b)
{
    return a.p > b.p;
}

double bound(int t)//�ӵ�t����Ʒ��ʼ����
{
    //̰���㷨
    double leftw = cw;//���õ�����
    double b = cv;//���еļ�ֵ
    for (int i = t; i <= n; i++)
    {
        //cout << "t=" << t << "b=" << b << endl;
        if (leftw >= s[i].w)
        {
            b += s[i].v;
            leftw -= s[i].w;
        }
        else
        {
            b += leftw * s[i].v / (double)s[i].w;
            break;
        }
    }
    //cout << "t" << t << "b" << b << endl;
    return b;
}

void backtrack(int t)//��t��
{
    //cout << "bound" << bound(t) << endl;
    if (t > n)//����Ҷ�ӽڵ�
    {
        if (bestv < cv)
            bestv = cv;
        return;
    }
    else
    {
        //cout << t << " " << bound[t] << endl;
        if (cw >= s[t].w && bestv < bound(t))//�Ž�ȥ
        {//���
            cw -= s[t].w;
            cv += s[t].v;
            //cout << " t = " << t << " cw = " << cw << " cv = "<< cv << endl;
            backtrack(t + 1);
            cw += s[t].w;
            cv -= s[t].v;
        }
        if (bestv < bound(t + 1))
        {
            backtrack(t + 1);
        }

    }
}

int main()
{
    cin >> n >> c;
    cw = c;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i].w >> s[i].v;
        s[i].p = (double)s[i].v / (double)s[i].w;
    }
    sort(s + 1, s + 1 + n, cmp);
    backtrack(1);
    cout << bestv;
}